# 可执行 NPC 动作与事件组件

新模块 `D:\Repo\arknights-sim\arknights_probe\npc_actions.py` 已实现有界动作链、ObjectPtr UID 校验、黑板绑定、同步事件重入和上下文恢复。它处理**指定已初始化 Buff 的显式事件**，并通过提供者调用生命周期、出生、恢复、模式和生命处理；不是完整 NPC、场景事件注册表或客户端运行时对照。没有执行、加载或注入游戏，没有联网；旧 v5/v6/v7 固定文件未修改。

## 支持接口

`NpcEntity` 明确输入 UInt32 UID、Unity 存在性和 alive；`EntityPtr.capture` 保存 UID，`resolve` 复现原件 IsDestroyedOrNull → 当前 UID 等值校验。alive 不属于此校验，原件也没有额外拒绝相等零 UID。当前 UID/Unity 存在性来自外部 BObject 快照，组件不读原生 heap 或初始化 IL2CPP class fast tags。

`NpcBuff` 输入 owner、带 UID 的 source、黑板、实际 onEventPriority 和 initialized/membership 上下文。BUFF_SOURCE 每次解析时校验 source ObjectPtr；BUFF_OWNER 取 container.owner；Snapshot SOURCE/TARGET 为已取得的直接对象引用。管理类 Buff 不当作 Unity 对象：未知 removal/registry 状态严格拒绝，失效 Buf UID 可以在优先级插入中跳过。

`NpcActionRuntime(NpcContext(), NpcCallbacks(...), no_hotfix=True, mode="default_noncoop", dispatch_source="explicit fixture")`：

- `run_buff_event(buff, 10)` 执行显式 ON_TAKE_DAMAGE 信号，不制造自然伤害或 Physics 命中。
- `owner_finish(buff, 7/2, finish_source=...)` 执行原生 reason 对应事件。death 集合 `{2,3,5,8}` 执行 event3；非8且 source存在可选择29；reach-exit1选择34；最后选择4。只执行模板中有动作的事件。
- callbacks 提供 `restore_to(RestoreRequest)->bool`，以及 void `set_disappeared`、`finish_buffs`、`finish_no_reason`、`clear_buffs`、`schedule_summon`；`modify_life(LifeRequest)->bool` 传回模式实际结果。void 回调的返回值不会改变原件固定成功节点结果。
- `SummonRequest` 传入 host、Buff source、bound enemy_key、显式 host-root grid、黑板副本与 Snapshot。支持本图原件的 count1/delay0/只有 enemy_key 黑板输入；计数、随机和延迟黑板覆盖必须另行恢复。调度后节点返回 true，子实体创建交给共享 summon provider。

独立 `run_action_list` 复现 allowedSource 与 previousResult：初值 true，condition0=always、1=previous、2=!previous，其他 false；CheckExecute=false 退出整个列表，Execute 返回值成为下一步 previousResult。九个受支持节点的原件 allowedSource getter 均返回 `0x3f`；默认 condition1 与 IfNot2 延用 v7 逐范围原件证据。

## 原件补齐与易错边界

Blackboard 是**有序 List<DataPair>**，不是 Dictionary。构造副本保留顺序、重复键和值位。数值 Assign 先 `ToLower()` 当前 culture，替换首个 `String.Compare(old,key,true)==0` 行，并清空 valueStr；字符串 Assign 同样替换首行，将数值设0。数字读取扫描至首个匹配且 valueStr 为空的行；非数字匹配行不会阻止后续重复数字行。

Enemy._AssignTalent 的前缀 literal 已从原件 usage slot `0x1887fb958` 解出 `'{0}.'`。两种 AssignByPrefix 用 `StartsWith(...,5)`；真实 metadata enum 证实 **OrdinalIgnoreCase=5**，再 Substring(prefix.Length)。先数字 pass，再字符串 pass（只对非空 valueStr），所以 `Dead` 能匹配 `dead.value`，`summon.enemy_key` 最后为字符串并清零数值。`bind_talent_blackboard` 支持非 Character Enemy 的 unscaled path，不宣称恢复 Talent Ability 激活、delta 合并或 character skill scale。

通用 Assign/lookup 的 current-culture 行为有显式范围：组件只接受 **ASCII + invariant-culture fixture**。没有声称已观察真实游戏线程 culture；Unicode 和未知 culture 拒绝。真实目标 `Dead/dead.value` 绑定已由 prefix 与 source 字面量证明，不能把这个证明扩成任意 Unicode 键的等价实现。

**GetInt 是 floor，不是 round。** TryGetInt `0x182320170` 将 Single 提升 Double，调用 CRT `0x1804d3200`；SSE4 分支 `0x1804eefb0` 是 `ROUNDSD ... ,9`（向负无穷取整），scalar fallback `0x1804d3220` 对负非整数减1。之后 CVTTSD2SI。本组件接受有限 Single 且 floor 在 Int32 内；非有限/越界拒绝。例如 1.9→1、-1.1→-2；资源 death=-1 保持 -1。

Filter GE 使用 MathUtil.GE(FP,FP) `0x1866e4ba0`：`left.raw >= unchecked(right.raw - EN5)`，**包含相等边界**。MathUtil.cctor 将 FP static+0x78(EN5，raw42950) 复制至 epsilon 字段；其 GE delegate usage word 指向 metadata method220331，写入 static+0x28，GetCompareFuncFP(3) 读取该槽。证明和 bytes 位于 `native_proofs.json`/`raw_helpers.json`。

Context Guard 的 ctor 调用 `_DuplicateAll`：先 TakeSnapshot 解析当前 ObjectPtrs，再由解析后的对象创建新 ObjectPtrs 并 push。setter pop/push 替换复制后的顶项；Dispose 对各 stack pop。因此 stale pointer 被复制为 null，即使回调期间 UID 又变回旧值，复制顶项也不会自动复活。Dispose 后原始底层 pointer 才重新按当前 UID 解析。支持 source/target/buff/mainTarget；owner_finish 将 finish_source 放进 **m_mainTarget(+0x50)**，不是 source。已测试嵌套返回与 Python provider 异常后的恢复；不宣称完整 CLR 异常系统恢复。黑板与生命周期变化不随 Guard 回滚。

SortedDoubleBufferedBuffList.Add `0x180692370` 已恢复**立即列表插入**：高 priority 在前，相同有效 priority 新项排在既有项之后；无效 incoming append，逆向寻找时跳过无效 existing。完整遍历 snapshot、pending additions/removals 和 callback membership 尚未实现。组件不自行广播所有 Buff，而由显式已初始化 membership provider 指定要 dispatch 的 Buff，因此不会用 Python 列表排序冒充全 BuffContainer。

## 已执行的关键事件路径

受控 event10 依次请求恢复宿主、显示宿主、结束宿主 passive、InstantKill(noReason)。finish_no_reason provider 在返回前设置 alive=false 并同步 dispatch owner_finish7；此时 event4 的 lock 默认为0，经 Filter(false)→IfNot(true) 再次请求恢复。随后 InstantKill 返回 alive=false，下一 condition1 的 AssignValueToBB 被拒绝，**lock 和 Clear 不执行**。测试的“两次恢复”要求明确的有效 source 与 finishBuff membership fixture；不是任意真实对局的无条件次数。

独立 death2 分支中，已绑定的 upeople_t event3 请求 `ModifyLifePoint(-1, owner, branch0, isReachExit=false)`；actual life/tempLife/global-modifier/mode consumption 交给外部提供者。Finish7 不执行这个死亡扣血事件。音频 `upeople_t_1` 的 CreateBuff 节点未恢复，调用时拒绝，不把它静默视作 no-op。

位置、阻挡、still-pull、state11/tween/appearance 和 route-progression 由新恢复组件提供。shared coroutine / spawn factory / final membership / mode callbacks 由新的 tracked summon 组件提供；本动作模块不复用旧 lifecycle 的 NPC 拒绝后端，也不把这些显式外部结果称为全 NPC 原件闭包。

## 校验与固定输入

- **28 tests 全部通过**，覆盖 UID 复用/零值/死亡仍有效、Guard stale-null 复制和重入恢复、重复 DataPair、floor 边界、condition 短路、priority/失效项、event10/Finish7/death2 与未闭合路径拒绝。
- **187 独立 C# 对照向量全部通过**：CLR Math.Floor/Single、OrdinalIgnoreCase prefix、current-culture invariant List assignment、UInt32 equality、unchecked signed GE 和 condition truth table。Single 按 bits 比较，避免 JSON 显示精度掩盖差异。对照程序没有加载游戏或提取后的 native 可执行代码。
- 新 Ghidra **25 入口 / 51 imported ranges / 11,518 bytes**，全部 decompile 完成、SHA 与原件一致。
- 新 raw **22 函数记录 / 31 ranges / 3,206 bytes**，每个范围 hash 和指令 bytes 与原件一致；少数 CRT leaf/trampoline 标明独立边界规则，无 PE 范围猜测填充。
- v7 NPC manifest 的 **99 files 全部重新验 hash 一致**；没有改旧 source、模块或 pins。

`manifest.json` 和 `D:\Repo\arknights-sim\evidence\npc_actions\manifest.json` 固定新模块、测试、参考源/向量、原件结果、资源/metadata 输入与本报告。source/metadata SHA 沿用本地已核实版本。完整 NPC/场景 ready 仍是 false。
