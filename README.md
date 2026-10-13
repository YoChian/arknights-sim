# 明日方舟本地数据与环境原型

> 当前 GitHub 暂存版本：v9。代码与研究证据已归档；恢复方法和本地依赖见 [快照说明](docs/GITHUB_SNAPSHOT.md)。完整关卡及训练接口仍未就绪。

这是重构训练环境的可运行起点，当前提供 **敌人数据合并、出场延迟、原生移动和格子缓存组件、出生/漏怪/回收生命周期、祭坛来源化技能准备与逻辑筛选、纯伤害死亡链、FP运算及出怪调度内核**。完整场景与训练接口仍待接入和对局核验。

输入来自本机 PC 客户端提取的 `level_rogue6_1-1` 以及敌人、干员、技能、肉鸽主题和常量表。无需启动游戏，无需连接游戏服务器，Python 3.11 标准库即可运行。

## 运行

在 PowerShell 中：

```powershell
Set-Location 'D:\Repo\arknights-sim'
python -X utf8 -m arknights_probe prepare
python -X utf8 -m arknights_probe inspect
python -X utf8 -m arknights_probe trace --seed 42 --limit 5
python -X utf8 -m arknights_probe topology --route 10
python -X utf8 -m arknights_probe topology --route 16 --row-mapping bottom_origin
python -X utf8 -m arknights_probe render --route 10 --output artifacts/map.svg
python -X utf8 -m arknights_probe render --route 16 --row-mapping matrix --output artifacts/map_raw_matrix.svg
python -X utf8 -m arknights_probe rng --seed 42 --count 8 --max 100
python -X utf8 -m arknights_probe rng-reference
python -X utf8 -m arknights_probe enemies
python -X utf8 -m arknights_probe enemies --selected-multipliers examples/enemy_attribute_mul_selected.json
python -X utf8 -m arknights_probe timeline --config examples/timeline_normal_resolved.json --frames 1200
python -X utf8 -m arknights_probe timeline --config examples/timeline_four_star_resolved.json --frames 1200
python -X utf8 -m arknights_probe timeline --config examples/timeline_normal_external.json --frames 1200
python -X utf8 -m arknights_probe timeline --config examples/timeline_four_star_external.json --frames 1200
python -X utf8 -m arknights_probe scene-audit --config examples/timeline_normal_resolved.json
python -X utf8 scripts/probe_route_lifecycle.py --frames 300
python -X utf8 -m arknights_probe altar-component --frames 5000 --output artifacts/altar_component_external.json
python -X utf8 scripts/probe_altar_prepared.py --frames 10000
python -X utf8 -m arknights_probe preprocess --seed 42 --topic rogue_6 --mimic-count 0 --gold-count 0 --group-order t1,t2,c1
python -X utf8 -m unittest discover -s tests -v
```

`prepare` 默认读取 `D:\Repo\.rea-tools\arknights-pc\resources_v2\normalized`，生成 `data/manifest.json`。清单记录每个 JSON 的 SHA-256 和提取证据路径，**不会复制或改写游戏文件**。输入变化时加载会停止，需要重新准备快照。

可换数据目录：

```powershell
python -X utf8 -m arknights_probe --manifest data/other.json prepare --source-dir 'D:\path\resources_v2'
```

该目录需含同样格式的 `normalized/`；没有 `verification.json` 的快照会明确标记为等待结构验证。

## 当前能确认和推进的部分

最新v9把选定NPC工厂、真实Buff会员/共享snapshot/Start与Finish、Entity/Unit受击反应、Finish7/death2与Scheduler清理接入同一对象。受控upeopl从第1帧BORN6到第2帧MOVE1；第10帧decoded modifier触发恢复/Finish7，同步UID0/event8使final归零且life3；独立death2使life2，声明的Single0.6延迟在第28帧回收。OwnerBorn12、Start0、PostBorn35严格分开，Entity Tick先FSM后Buff。原件49入口/109精确范围匹配，旧v8及更早pins不重写。完整ApplyModifier/HP、Unity物理/初始化副作用/override/audio/Tween/mode/global/非空路线和箱子仍有外部或拒绝项，完整图与训练仍未就绪。详见[v9报告](research/arknights-pc/native_v9/REPORT.md)。

~~~powershell
python -X utf8 scripts/probe_npc_pipeline.py
python -X utf8 scripts/verify_v9_snapshot.py
~~~

v9最终全量验证468项测试全部通过，0失败/错误/跳过；346文件pin、49新增原生入口/109原件范围一致；旧v8 290pins/136ranges、v7 310pins/190ranges、v6 323pins/358ranges保持不变。

最终全量统计见 artifacts/verification_v9.json；battle_ready/autonomous_route_ready/runtime_battle_validated仍false，reward=None。

历史v8接通了受限NPC动作/召唤/消失恢复组件，并为物理查询增加帧、阶段、状态版本和参数fingerprint核对。受控NPC样例第1帧召唤、第9帧隐藏；第10帧提供明确ON_TAKE_DAMAGE信号后恢复当前NPC格子/route/progress，reason7不扣生命；独立reason2经Dead/dead黑板绑定使life3→2。实际Tween/FSM hooks、初始化会员、NPC pose/伤害事件、factory/模式回收仍明确外部，final成员待真实回收。祭坛样例第一query为210帧objects_fixed，首次伤害227，18×500后4343帧回收；Unity bounds/filter/hits均显式receipt，未生成真实碰撞。详见[v8报告](research/arknights-pc/native_v8/REPORT.md)。

~~~powershell
python -X utf8 scripts/probe_npc_component.py
python -X utf8 scripts/probe_physics_altar.py
python -X utf8 scripts/verify_v8_snapshot.py
~~~

v8最终全量验证383tests全部通过，0失败/错误/跳过；290固定filepins、72新原生入口/136原件ranges全部一致，旧v7 310pins/190ranges和v6 323pins/358ranges保持不变。

完整地图仍未ready，reward=None；旧v5/v6/v7来源清单保持不变，v8验证不自动repin。

历史v7样例使用真实技能/角色/预制体准备参数：前摇约.6秒、持续/冷却各1秒；实际祭坛side2、目标mask7、层掩码268436992、默认筛选用途0，普通ALL顺序由恢复的优先队列生成。第二次伤害为469帧，18次各500伤害后4325帧死亡、4343帧回收。289项测试全部通过，310项v7文件散列与190段原件检查一致。Physics2D碰撞、原生字段/异常状态/空provider、模式与全局上下文仍需明确输入；未接通完整NPC/箱子/原图scheduler。新入口是probe_altar_prepared.py，旧altar-component保留历史fixture。[v7报告](research/arknights-pc/native_v7/REPORT.md)。

历史v6受控样例接通共享帧循环与协程、祭坛自然SP/AUTO施放、目标去重、HP扣减、死亡和延迟回收。一个静止的敌人从资源基础HP 9000开始，18次各500伤害后归零，第4139帧完成回收和样例逻辑结束；初始生命3保持不变。该版本的目标碰撞、ALL输出顺序和.6/0/0准备后时间为明确外部输入。v7改用来源化准备与普通ALL，两个版本均reward=None、三个ready/validated标记为false。

v6历史全量验证248项测试通过，323项v6文件散列和358段原件范围检查一致；其固定文件不改写。最新全量结果见artifacts/verification_v9.json；独立C#转写对照与真实客户端轨迹分别记录，后者尚未进行。[能力边界](CAPABILITIES.md)。

- 严格检查地图维度、格子索引、路线坐标、敌人数据库等级、预定义单位别名、主波次与分支路线引用；拒绝重复 JSON 键、非法数值和缺失引用。
- 查看一张真实 7 × 11 地图及源数据中的等待点，保留 38 条主波次声明、两个独立分支和 10 个敌人数据库引用。
- 关联主题“沉沦者的黑流树海”、阶段“猎犬病原”的普通/紧急记录；检查载入的 1,382 个角色记录、1,820 个技能和 2,181 个敌人 ID。全表中另有 3 条非空技能引用缺失，摘要会逐条列出；本图预定义单位的角色引用均通过校验。
- `reset(seed=42)` 固定探针的初始状态，`step({"type": "next"})` 按 JSON 数组顺序前进到下一条声明。输入相同，检查序列相同。
- 指定 `options={"branch": "shsbox1"}` 可检查该分支的数据。此选择是人工审阅，不代表分支已被游戏触发。
- 已根据原生 `MapData.get_Item` 恢复逻辑坐标到矩阵的访问：`matrix_row = height - logical_row - 1`，列保持不变，再用矩阵里的值索引 `tiles`。默认采用该方向；本图 28/28 条 WALK 路线的全部 MOVE 检查点段均可做四邻接连通诊断。
- SVG 默认显示逻辑行列（row 0 在底部）。`--row-mapping matrix` 保留原始矩阵存储视图，仅用于检查序列；它不适合作为路线坐标访问。

```python
from arknights_probe import Dataset, DeclarationProbeEnv

dataset = Dataset.from_manifest("data/manifest.json")
env = DeclarationProbeEnv(dataset)
observation, info = env.reset(seed=42)
observation, reward, terminated, truncated, info = env.step({"type": "next"})
assert reward is None
assert info["battle_ready"] is False
```

## 按帧推进调度内核

`TimelineEnv` 与原声明探针独立。它恢复选定原生默认分支的嵌套协程栈、主wave/fragment顺序、串行队列等待、SPAWN/ACTIVATE一帧执行，以及自动生成的两个PREVIEW_CURSOR事件。同一计划时间的多个出怪请求仍逐帧串行执行；排序使用原生中点快速排序，同时间项会交换，不能用Python稳定排序替代。它记录请求及外部门控，不计算移动、伤害或装置触发。

两个示例配置明确给出 `t1/t2/c1` 的**原actionIndex**，选择空候选；NORMAL按数据rune启用normal组，FOUR_STAR启用raid组。它们还明确提供零extraSpawnDelay、计入总数和成功创建的**审阅fixture**，这些值不是已恢复的敌人属性合并结果。缺组选择、无来源输入、未恢复动作和非ALWAYS变体会停止。需要另一套假设时修改配置并保留准确的`input_source`。

新的 `timeline_*_resolved.json` 示例从 `EnemyDB.TryGet` 与实际敌人预制体导出 `notCountInTotal` 和 `extraSpawnDelay`：`enemy_2133_shdopl`、`enemy_2152_shezlc` 为 1 秒，其余八种为 0。它们仍显式假设创建后满足存活/计数条件，并排除原生热修补；不会把预制体存在当作实际 `Init` 成功。这两个字段的新来源不会自动改变所有事件时间：负的调整后延时会被原生 Clamp 到 0，当前空随机组示例的首波记录仍相同。原来的 `*_external.json` 保留为独立调度参考 fixture。

NORMAL示例推进1200帧后有15个出怪请求和2个预览请求，停在wave1的存活敌人闸门；FOUR_STAR有14个出怪请求，不自动推进下一波。这里的帧0从调度内核启动计算，排除了game mode开场/结束hook。默认时钟来自序列化TimeManager的初值：`dt_raw=143165440`，float32约0.03333330154；`info.clock_origin`明确标记资产来源，`live_fixed_delta_validated=false`。可用`--dt-raw`指定外部时钟。原生等待实际是`max(1,round_ties_even(float32(delay/dt)))`，不是向上取整；零延时也等待一帧。

```python
from pathlib import Path
from arknights_probe import Dataset, TimelineEnv, compile_timeline
from arknights_probe.data import read_json

dataset = Dataset.from_manifest("data/manifest.json")
config = read_json(Path("examples/timeline_normal_external.json"))
env = TimelineEnv(dataset, compile_timeline(dataset, **config))
obs, info = env.reset(seed=42)     # 此seed只记录；选择已在config明确给出
obs, reward, done, truncated, info = env.step({"type": "tick", "frames": 1200})
assert obs["phase"] == "wave_gate" and reward is None
```

`external_release_wave`只解除当前波成员关系，`external_recycle`只解除最终成员关系并移出alive列表。它们分别对应静态原生的ReleaseEnemyFromCurrentWave和OnEnemyRecycled，不能把释放当前波当作完整终结。`external_resolve`的killed/missed是**已包含回收完成的外部终结fixture**，会记录来源；它不是伤害模型或原生MarkEnemyKilled的替代实现。最终内核结束还需明确`external_final_complete`输入；`terminated`表示内核及外部闸门处理完毕，不表示胜利。`external_wave_gate`可提供有来源的game mode门控结果。

`external_trigger_branch`仅支持本图两个单phase、单action、零延时分支，使用extraRoutes；它不会推断箱子触发，也没有恢复完整分支回调等待流程。源石祭坛、箱子行为、实际敌人创建状态、动态配置与热修补尚未接入该时间内核。

## 敌人属性与移动组件

`enemy_data.resolve_enemy(database, reference)` 恢复本图全部十个 `useDb=true` 引用：精确等级命中、按数据库原序继承、构造函数默认值、关卡覆写、blackboard/技能合并和数值字段转换。它提供 45 个解码原始值及 34 个 `Battle.Attributes.Reset` 后的 FP 值；后者还未应用动态 entity effects。`enemy_3001_upeopl` 未定义的法抗与基础间隔分别取默认 0 和 1；`enemy_2133_shdopl` 的 `summon.enemy_key=enemy_3001_upeopl` 覆写保留。

`enemy_rules.apply_selected_attribute_mul` 对明确选择的 runtime 字段执行 Single→FP→乘法→范围限制→Single/整数写回→Reset。整数写回采用 ties-to-even；例如 3×0.5 写成 2，5×0.5 也写成 2。示例乘数来自本图紧急 rune 的 atk=1.2/max_hp=1.4，但本接口不推断 Rune.Verify、实际肉鸽增益或修饰顺序，不能称为完整紧急对局属性。

`movement.py` 提供 Single 的局部地图几何、ties-to-even 归格、FP WAIT 倒计时，以及输入完整缓存格子状态的加权 FIFO/SPFA 与 Bresenham 平滑。它与旧 BFS 拓扑诊断并列；不从 tileKey 猜缓存状态。99 秒 WAIT 在当前资产默认 dt 下独立倒计时需要 2971 tick，调度等待的 nearest 舍入规则不能用于它。

`runtime_movement.py` 新增 cursor、控制器加速度/避障、四位坐标取整、Tile/HoleTile 缓存初始化和显式设备重写。`MovementContext` 要求明确 deterministic、steering、脚底偏移及实际 prefab 参数；不能用构造默认值覆盖资源中的值。`lifecycle.py` 提供 Born→Move、出口生命扣减、波次释放与回收后的最终门控；初始生命与临时生命必须来自场景输入，不取关卡99作为实际肉鸽生命。

`RouteLifecycleProbe` 将这些组件自动接成单敌人路线实验，无需 external_resolve/release/recycle。`scripts/probe_route_lifecycle.py` 输出每帧坐标、状态和事件至 `artifacts/route_lifecycle_component.json`。该演示使用明确的开放格子与无天赋场景 fixture，`finish_request` 是逻辑默认模式结果，不能当作“猎犬病原”的实际胜负。完整图的执行仍受 `scene-audit` 预检限制。

场景预检纳入选定出怪、隐藏箱子、独立技能预制体、NPC召唤依赖和递归 buff 模板。新增完整 Transform 子树提取避免遗漏动态扫描的 Talents/Skills。声明、已恢复组件、完整场景执行和真实客户端轨迹核验是不同层次；未知有效规则不会静默跳过。

本图源石祭坛在初始数据中已可见，技能与 buff 模板表明会造成真实伤害，并可重写格子通行设置。因此“没有干员”仍有战斗与地图变化；不能把只沿静态路线移动的结果当作真实无人操作对局。配置证据保存在 `native_v4/resources/prefab_inputs.json` 与 `ore_buff_templates.json`。

独立`preprocess`命令可按显式LegacyRandom种子、组枚举顺序和两个retain计数恢复Rogue带权选择。任一计数为负时走普通选择；非负时先选择mimic/gold组再过滤候选，EMPTY继续参与选择。因此“保留mimic组”不能保证实际出场mimic。`group_order`必须明确给出，不能由Python字典顺序推断客户端RNG消费；结果可作为有来源的外部选择交给调度内核，尚未证明真实对局种子及全局消费顺序。

## 必须保留的边界

`DeclarationProbeEnv.step` 的单位仍是**声明条数**，`terminated`仅表示声明审阅完毕。`TimelineEnv.step`可推进上述调度内核时间，两者均没有敌人移动、扣血或胜负，`reward=None`。接口形状参考常见环境，未声称满足Gymnasium契约，因此没有引入Gymnasium。

两个环境的`seed`只记录状态。独立LegacyRandom与preprocess可显式采样，但没有自动绑定游戏randomSeed或宣称与真实对局消费一致；客户端中的`randomSeed`在检查摘要中单独展示。

另外提供独立的 `LegacyRandom` 算法组件。它根据本次 PC 快照的静态原生反编译实现有种子构造、`sample()`/`next_double()`、`next()`、`next(max)` 和不发生 int32 范围溢出的 `next_range(min,max)`，支持 JSON 可序列化的 `snapshot()`/`restore()`。它尚未接入声明探针或完整战斗。

```python
from arknights_probe import LegacyRandom

rng = LegacyRandom(42)             # seed 为有符号 int32
checkpoint = rng.snapshot()
values = [rng.next(100) for _ in range(5)]
rng.restore(checkpoint)
assert values == [rng.next(100) for _ in range(5)]
```

该算法**不等同于 System.Random**：环偏移 `inextp=31`，没有 `ret==MBIG` 的修正；构造遵循 unchecked int32 算术，`INT_MIN` 的绝对值仍为 `INT_MIN`。`next(0)` 会消耗一次采样，而 `next_range(min,max)` 的宽度 0/1 分支直接返回 min，不消耗采样。宽度超过 `INT_MAX` 的区间主动拒绝。检查点是本组件自己的格式，不能当作客户端存档，也不验证手工改写状态是否可由某个种子到达。

原生证据见 `native_v2/focused_results_round3.json`：有种子构造 `0x186505240`、`Sample` `0x1860e0e90`、`Next` `0x1860e0e40`、`Next(max)` `0x186505190`、`Next(min,max)` `0x186505090`。工厂静态默认 `type=0` 选择该类，但真实客户端热修补、虚函数分派与战斗随机数消耗顺序尚未核验，不能据此声明完整战斗确定性。

Python 已与独立编译运行的 C# 转写参考对照：8 个种子（含负数、地图种子及 int32 两端）、1,024 个 `Next()` 整数、256 次 Sample/NextDouble 的 binary64 位比较、64 个混合 max、56 个窄范围结果与8个后续采样顺序检查全部一致。示例 seed=42 首值为 `1436392141`，参考运行中的 `System.Random` 为 `1434747710`。这属于**跨语言实现对照**：两份代码都依据同一份原生静态证据，不能代替实际客户端轨迹验证。C#源码、向量与原生报告的小型副本保存在 `evidence/rng/`，其 SHA-256 固定并纳入测试。

地图含预定义箱子/装置、隐藏组、带权重的候选组，以及需要触发的分支。不能把所有 SPAWN 的 `count` 相加当作实际敌人总数，也不能简单累加 `preDelay`/`interval` 推导绝对出怪时间。`compile_battle_schedule()` 会主动拒绝；部署、使用技能、战斗推进动作也会主动拒绝，避免让模型从编造机制学习。

`topology` 命令仍只是四邻格子连通诊断。新的原生路径组件需要显式缓存格子状态；完整逐帧移动、碰撞/阻挡、动态障碍和设备行为尚未接入环境。前 10 条 `E_NUM` 是数据中的合法占位声明，保留它们但不当作敌人路径。

具体证据：`D:\Repo\.rea-tools\arknights-pc\native_v2\focused_results_round2.json` 中 `Torappu.MapData.get_Item` 的两个候选入口 `0x18241d270`、`0x18241d1e0` 均执行 `GetLength(0) - row - 1` 后读取 `matrix[matrix_row,col]` 并索引 `tiles`；`get_height` `0x18241d300` 和 `get_width` `0x18241d330` 对应维度 0/1。函数身份由本地元数据/指针表与 PE unwind 入口关联，静态证据没有运行游戏。目标二进制 SHA-256、证据文件 SHA-256 与地址也存于清单及 `arknights_probe/coordinates.py`。

FlatBuffer 的可达字段边界验证已经通过，字段名称来自固定版本的社区 schema。`m_defined=false` 的占位值不参与覆盖；敌人合并组件另根据原生代码恢复默认与继承。资源结构检查和独立 C# 参考都不等于实际对局验证。

## 后续接入位置

先把原生算法证据和作用范围写入能力记录，再为相应组件加入单元测试和真实轨迹核验。可逐项增加随机数、调度器、路径搜索、属性覆盖、战斗与技能；只有达到核验门槛的组件才开放到训练 `step`。完整肉鸽节点生成、事件和奖励概率需要单独证据。

资源提取验证见 `D:\Repo\.rea-tools\arknights-pc\resources_v2\verification.json`；最新原生恢复见 [native_v9/REPORT.md](research/arknights-pc/native_v9/REPORT.md)，历史v8见 [native_v8/REPORT.md](research/arknights-pc/native_v8/REPORT.md)，历史v7见 [native_v7/REPORT.md](research/arknights-pc/native_v7/REPORT.md)，祭坛原始条件组件见[native_v6/REPORT.md](research/arknights-pc/native_v6/REPORT.md)，移动/生命周期见[native_v5/REPORT.md](research/arknights-pc/native_v5/REPORT.md)，敌人/路径见[native_v4/REPORT.md](research/arknights-pc/native_v4/REPORT.md)，FP/协程见[native_v3/REPORT.md](research/arknights-pc/native_v3/REPORT.md)。当前原型源码不包含游戏美术或整包资源。

具体组件状态见 [CAPABILITIES.md](CAPABILITIES.md)。`python -X utf8 scripts/verify_snapshot.py`重新生成结构/拓扑、敌人属性、两套来源的时间轴、WAIT摘要和证据核验，并运行全量测试。timeline、enemy_data、enemy_rules和movement各有固定散列；源报告变化会拒绝核验，复审后才有意更新pins。各C#参考均为独立原生转写对照，没有运行游戏。
