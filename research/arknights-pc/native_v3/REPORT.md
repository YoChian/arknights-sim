# 猎犬病原：定点数与出怪时间轴恢复

2026-10-13。本阶段把 `D:\Repo\arknights-sim` 从声明审阅推进到按帧执行的调度内核，并恢复原生 Q32.32 运算。**目前能复现已确认的静态调度规则，仍没有移动、阻挡、伤害、技能和胜负；不能把当前内核当作完整训练战斗环境。**

输入固定为本机 PC 客户端 `26-09-13-15-28-10-30688348` / Unity 2021.3.39f1 / x64 IL2CPP。GameAssembly SHA-256 为 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。本阶段只读分析游戏文件，未启动游戏或连接其服务器。

## 可运行入口

```powershell
Set-Location 'D:\Repo\arknights-sim'
python -X utf8 -m arknights_probe timeline --config examples/timeline_normal_external.json --frames 1200
python -X utf8 scripts/verify_snapshot.py
```

`timeline` 要求显式输入难度、随机组选项、敌人创建/统计条件和输入来源。示例选择 t1/t2/c1 的空候选，假设敌人额外预出场延迟为零并成功创建；这是供检查的外部条件，未宣称来自真实对局。时间原点设在被排除的模式开场 hook 之后的 scheduler 启动时刻。普通和紧急示例、事件导出、测试结果见原型的 [README](../../../arknights-sim/README.md)、[能力记录](../../../arknights-sim/CAPABILITIES.md) 和 [verification.json](../../../arknights-sim/artifacts/verification.json)。

在这组明确条件下，NORMAL 的前 14 个出怪请求发生在第 **5–18 帧**，后续路线预览在 **740、750 帧**，正常候选的第 15 个出怪请求在 **832 帧**。这是排除了模式 hook、使用指定空候选和额外延迟零的条件时间轴，不是实机开局时间。推进到 1200 帧仍会停在 wave gate，15 个被跟踪的请求不会自行死亡。独立 C# 协程转写得到同样的执行帧；两份转写都来自静态证据。

旧 `DeclarationProbeEnv` 保留为声明审阅。新 `TimelineEnv` 执行帧和调度事件，`reward=None`、`battle_ready=false`。外部击杀/漏怪、波次释放、回收、模式 gate 和箱子分支触发都需要带来源的明确输入；内核不会自动编造这些事件。

## 定点数与两类时间

`Torappu.FP` 使用 signed int64，低 32 位是小数：`value = raw / 2^32`。恢复的独立组件包含整数/float32/double 转换、比较、普通加减乘除余数，以及 floor/ceiling/round。普通运算保持原生 unchecked int64 边界；除法保留恢复出的饱和、回绕和除零特殊结果，不能直接套 Python 的 `/`。当前除零 raw 是 `-4294967296`（-1.0），不是异常。

Python 与依据静态指令另行转写的 C# 参考程序对照，覆盖 7,073 组 raw 二元输入、81 个一元输入、93 个 float32 位模式和 92 个 double 位模式。对照结果见 [FP 恢复说明](fixedpoint/REPORT.md) 与原型 [FP 校验](../../../arknights-sim/evidence/fp/verification_report.json)。**这是跨语言移植验证，两份程序都来自静态证据；没有运行游戏取得金标准。**

调度声明中的 `preDelay`、`interval` 和队列 planned time 使用 **binary32**；游戏累计时钟使用 **FP**。需要分别保留这两种表示，不能把全部时间都用 Python double 累加。

已确认默认时钟的静态来源链：

1. `GlobalConsts..cctor 0x1866e20d0` 读取 `UnityEngine.Time.fixedDeltaTime`，通过 FP(float32) 写入 `GlobalConsts.FIXED_DELTA_TIME_FP`（static +0x40）。
2. `BattleController.RestoreDeltaTimeScale 0x180630c30` 把这个值复制到 `s_deltaPlayTimeFP`（static +0x48）。BattleController 的构造器自身先设 raw=0。
3. 安装目录 `globalgamemanagers` 的 TimeManager 初值是 binary32 bits **0x3d088880**，即 **0.03333330154418945**；对应 FP raw **143165440**。

这个资产值与 `float32(1/30)` 的 raw 143165584 不同。FP 累计到第 600 tick 时仍略小于 20 秒，第一次达到 20 秒是第 601 tick；但 float 等待 20 秒经 binary32 除法和取整后仍是 600 帧，两种时间判断不能混用。原型可显式覆盖 `dt_raw`，默认标为 `serialized_TimeManager_initial_value`，并保留 `live_fixed_delta_validated=false`。静态 setter 扫描只确认一个直接调用来自 XLua 的 Unity Time 包装器，仍不能排除 Lua、间接调用或热修补修改运行时值。[时钟来源与字段证据](fixedpoint/CLOCK_REPORT.md)。

## 调度的实际规则

| 行为 | 已恢复的规则 | 主要原生入口 |
| --- | --- | --- |
| 声明编译 | binary32(fragment.preDelay + action.preDelay)，SPAWN 减去敌人额外预出场延迟后下限为零；第 i 次事件时间再加 binary32(i*interval) | `_DealAction 0x180919fb0` |
| 路线预览 | SPAWN 的 autoPreviewRoute 生成两个同队列 PREVIEW_CURSOR，planned time 为出怪基础时间 -3 秒及再加 0.3 秒 | `_DealAction` / Preview MoveNext `0x180953330` |
| 时间排序 | 按 tuple 中 float time 比较，进入恢复出的 midpoint Quicksort；相同时间会交换，不能使用 Python 稳定排序 | comparator `0x180950a00` / wrappers `0x184543930`→`0x184544810` / sorter `0x184547860` |
| 队列执行 | 串行执行；相邻事件 planned time 增大时等待它们的差值。实际执行时间还包含每个 executor 的帧边界 | ExecuteActionQueue MoveNext `0x18094e650` |
| Float 等待 | binary32(delay / deltaPlayTimeFloat)，取最近整数，正好一半时取偶数，至少等待一帧 | WaitForFixedSeconds / raw helper `0x18059e290` |
| 嵌套协程 | 新进入的空 IEnumerator 本身产生帧边界；已运行子协程结束可在同帧继续父协程。StartCoroutine 会立即推进一次 | RuntimeHandler `0x18065ff70` / StartCoroutine `0x18065d200` |
| 执行器 | 本图 SPAWN、ACTIVATE_PREDEFINED 和生成的 PREVIEW_CURSOR 均有 NEXTFRAME；count/interval 已在队列展开 | Spawn `0x1809547a0` / Activate `0x180952770` / Preview `0x180953330` |
| 片段门控 | 队列完成后 WaitWhileFixed(blockCounter>0)，即使初始条件为 false 也先占一帧 | DealFragment `0x180951a70` / WaitWhileFixed |
| 波次门控 | 片段按顺序执行，再等待 managed wave enemies / 显式模式条件。此图三个 wave 均 maxTimeWaitingForNextWave=-1 | DealWave `0x180951ed0` |

`0x18059e290` 在早期输出中曾临时命名为 `UnresolvedCall.CeilToInt`。这是分析标签错误，原始文件保留用于追溯；其实际指令是 nearest ties-even，**不是 ceil**。以本阶段说明和新实现为准。排序同样不能根据 .NET 常见实现猜测 insertion/introsort：此客户端的恢复入口直接使用 Quicksort。

不要把计划时间排序后直接当作绝对秒数。例如数个 preDelay=0 的敌人仍会串行跨帧出现；预览也不能丢弃。NORMAL 的第二片段自带 preDelay=7、正常候选 action.preDelay=20，实际等待基准是本片段串行队列开始；它并不是固定“开局第 27 秒”。全局波次位置还取决于敌人终结和模式 hook。

## 猎犬病原上下文与随机

主声明仍是 38 条、两个分支各一条；地图 7×11。NORMAL rune 启用 `normal`，FOUR_STAR 启用 `raid`。shsdgo/shsdgo4/shsdgo3/shsdgo2 在本图 rune 中没有启用，不能默认放行全部五条相关动作。普通与紧急都使用同一张地图，紧急属性倍率是另外的规则，当前调度实现不计算攻击或血量。

t1/t2 各有五个原始候选，声明权重合计 1040；c1 合计 105。空候选参与随机选择，选中后才被删除。分组身份由 wave/fragment/group key 共同决定；原型当前针对本图唯一键，重复跨片段键主动拒绝。箱子技能 blackboard 的 branch_id 与 shsbox1/shsbox2 引用已确认，但自动触发条件仍未恢复。

新增独立 Rogue 预处理组件，包含保留的 mimic/gold 数量对候选组的筛选、binary32 权重累加、float Range 与 `draw <= binary32(weight + binary32(1e-5))` 的选择边界。调用需要显式 rng、topic、retain count 和 group_order，不能用 Python 随机库或权重百分比替代。Rogue 的 `randomRogueScheduler` 是独立来源；客户端实际 seed 派生、Dictionary 遍历/全局随机数消费、事件上下文对权重的修改没有核验，故不自动把 Timeline 的 seed 当作其输入。

## 敌人生命周期边界

SPAWN 在成功创建、managedByScheduler、计数资格等条件满足时加入 final 集合；只有未 dontBlockWave，且主路线或 forceBlockWaveInBranch 时加入 wave 集合。原型要求显式创建/计数条件，尚未重建 Enemy 的完整初始化。

- `ReleaseEnemyFromCurrentWave 0x1809149f0` 只释放当前 wave，不代表敌人死亡或 final 完成。
- `MarkEnemyKilled 0x1809141e0` 释放 wave；final 是否立即释放还受 `useRecycleToFinishScheduler` 等参数控制。
- `_OnEnemyRecycled 0x18091bb70` 处理 final 回收。

因此原型分开支持外部 wave release 和 recycle。`external_resolve` 是声明“完整终结已完成”的测试/观测输入，不能当作原生 MarkEnemyKilled 的单次等价调用。最终结束的模式逻辑、分支阻塞键和胜负也没有恢复成自动行为；完成内核需显式外部 gate。

## 分析质量与继续位置

本阶段使用已安装的官方 Ghidra 12.1.4 headless CLI，导入只读，关闭默认全图分析。各入口按 PE unwind 的全部递归 CHAININFO 片段建立非连续函数体；无 unwind 的短叶函数另有 RET/INT3 与候选入口边界证明。符号仍是元数据/指针表支持的候选关联，输出不是原始 C# 源码，也不是 REA MCP Evidence。

timeline round1 的不完整范围已被 round2 替代。round5/round6 以及排序阶段把选定范围从导入后的 Ghidra 内存读回，对照源文件 SHA-256；这些检查支持载入字节一致，不证明反编译器对每条指令的语义建模都正确。原生 cctor 的 PIC 跳转误建模有独立 raw disassembly 佐证。

上一阶段 native_v2 的 43 个入口经独立审计有 8 个漏了 chained 片段；本阶段重新恢复两个 ResetSeed 完整组，其余费用/伤害/Update 等仍属后续工作。旧伪代码“生成成功”不代表这些规则已可靠恢复。[覆盖审计](coverage_audit/REPORT.md)。

源文件完整性、每轮输入/输出 hash 与入口清单在 [summary.json](summary.json)，可运行 `python D:\Repo\.rea-tools\arknights-pc\native_v3\summarize.py` 重核。7 个源文件与本阶段固定基线一致。当前所选完整分析记录覆盖 121 个唯一入口地址，这个数量不是“恢复了 121 个游戏机制”。

原型统一检查当前为 **71 项测试通过，0 失败、0 错误、0 跳过**，结果由 `verify_snapshot.py` 生成。排序对照覆盖 152 个队列、5,616 个元素身份顺序和 81 个浮点比较，见 [排序报告](sorting/REPORT.md)；独立协程对照另覆盖 106 个场景、155 组等待输入和 6 个调度流程，见 [协程参考报告](../../../arknights-sim/evidence/timeline_reference/REPORT.md)。FP、随机数、排序和协程各自的跨语言对照都保留参考程序和来源，均未声称经过真实客户端轨迹验证。

下一步优先恢复 Enemy 属性继承与等级/难度/rune 覆盖，取代外部 extraSpawnDelay 和计数条件；随后恢复路线 checkpoint 的移动/等待、到达和阻挡，再接费用、部署、攻击与技能。待一张小型确定性战斗能与真实轨迹对照后，再开放训练动作、奖励和完整训练 API。
