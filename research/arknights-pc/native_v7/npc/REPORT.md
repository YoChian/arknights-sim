# NPC 召唤、隐藏、恢复与 Finish 的静态恢复

本轮恢复了 `enemy_2133_shdopl → enemy_3001_upeopl` 的关键普通分支和动作执行门控，可用于设计下一步组件接口。**尚未实现或宣称 NPC 战斗闭包**：出生工厂、Disappear 状态机、路由重指派、Buff 容器重入/排序与天赋黑板绑定仍需要恢复。没有启动、加载或注入游戏，也没有取得客户端运行时 oracle。

原件 `GameAssembly.dll` SHA-256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`；metadata SHA-256：`d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`。Ghidra 由父任务统一运行；本目录保留 NPC 对应结果和逐范围原件校验。可执行普通分支的讨论均以**明确无 hotfix、指定支持模式、明确全局修饰上下文**为前提；不能据此认定真实 Rogue 对局不存在动态修饰。

## 资源声明与输入

`resource_inputs.json` 保留两个完整规则 Transform 子树、五个模板、数据库记录、本关卡引用和 overwrite 的原始结构。采用 v5 完整子树而非 v4 仅直接 GO/PPtr 图：shdopl 的 `Talents/summon` 含 Talent（pathID `-8304574259895132655`）和 PassiveBuffAbility（`3677509209081716241`）。其 `enemy_shdopl_passive` 是无限 Buff，带 INVINCIBLE/BLOCK_FREE/ALLY_TARGET_FREE，动作模板有 ON_BUFF_START。

shdopl 的数据库默认 `summon.enemy_key=enemy_1000_gopro_3`；本图 overwrite 的 wrapper 全部未定义，**非 wrapper talentBlackboard 仍将召唤键改为 `enemy_3001_upeopl`**。不能因为 wrapper 全 false 就丢弃整个 overwrite。

upeopl 的 NeutralTag 有 BLOCK_FREE 与空动作模板；`Talent/Dead` 声明 `upeople_t` 和 `upeople_t_1`。数据库有 `dead.value=-1`。资源 GO 名是 `Dead`，数据库前缀是小写 `dead`；`BasicTalent.get_talentKey` 普通分支取非空 overwrite，否则取 Unity 对象名。Enemy._AssignTalent 的 prefix 格式和 Blackboard 大小写/前缀算法还没完全封闭，因此这里的 `-1` 是**资源声明**，不是已证明的实际 callback 黑板绑定结果。

## 召唤的真实边界

`SummonEnemiesFollowMyRouteWithBuff.Execute` (`0x1810dcf50`) 创建捕获黑板与 Buff source 的 callback，并启动 Scheduler coroutine。厂函数 `0x1809163b0` 使用 TypeInfo usage `0x188899458`；原件 word `0x200342f1`、native type index `106872` 和类型记录准确指向 definition `10870`，即 **Scheduler.d__129**，MoveNext `0x18094fb90`，而非同名 d__127/d__128。记录详见 `identity_proofs.json`。

首次 prime 会检查 `m_allowSummonSpawnEnemy`、捕获 host UID、originRoute 和 originCursorIndex，再 yield **FP 版 WaitForFixedSeconds**。即使资源 delay=0，等待帧数也有最小值 1；不是 Execute 内同步创建 NPC。该 coroutine 属于 BattleController 的共享模拟器，不应私自以宿主 alive 当 coroutine owner。一般非零延迟使用 FP 除法及 RoundToInt；不能拿 float 版等待计算替换。每帧 phase/snapshot 顺序沿用已恢复的共享 coroutine 证据。

`get_originRoute` 首选缓存 route，否则取当前 cursor.route；`get_originCursorIndex` 首选非负缓存 index，否则取当前 index，无 cursor 返回 -1。**origin 不必等于关卡最初出生点**。资源 `_stopSummonIfHostDead=false`，所以 resumed 分支没有启用捕获 UID 与 alive 的这组停止检查；不能自行添加它作为“合理”规则。

resumed 分支复制 route.data、生成 runtime route，再调用 `_DoSpawnEnemyInternal` (`0x18091b310`)。原件 Options 写入：unharmful 来自参数、alwaysCountAsKilled=false、dontCountAsFinished=true、isSummon=true、spawnedCnt 为 Scheduler 计数。`managedByScheduler=true`、`dontBlockWave=true` 导致加入 **m_managedFinalEnemies(+0xc8)**，跳过 **m_managedWaveEnemies(+0xc0)**。不能把不阻波次误解为不阻最终完成。

资源 ignoreOffset=true / skipCheckpoint=false / checkMotionMode=ALL；成功创建后设置 hostUid、NPC 位置和朝向，调用 route-progress helper，随后 callback 将 `enemy_shdopl_finish` 加给 NPC，source 为宿主。创建工厂、三处 gameMode helper 与 route-progress helper尚未封闭，故这里是调用顺序证明，不是完整出生成功模拟。

## 隐藏与恢复

`SetDisappear.Execute` (`0x181172300`) 调用 `BObject.SetDisappeared` (`0x180662be0`)。UID 非零且值发生变化时，先 before-change hook，再写 inherited **BObject.isDisappeared(+0x26)**，再执行 changed hook。Enemy hidden=true 分支切换到 **DISAPPEAR 状态 11**。false 分支可调整朝向，但本体没有直接切换 Move；DisappearState 的 OnTick/DoAppear/tween 等还未恢复，不能把显示 flag=false 自动等同于当帧恢复移动。

**v6 标签更正：Entity+0x26 是 isDisappeared，不是 Enemy.Options.unharmful。** v6 的普通 laxe 形状两者都是 false，数值分支仍适用，但此前对此字段的文字标签不能扩展到 NPC。NPC 的 unharmful 是另一个 Options 字段，不能用它推断 damage hook 被跳过。Entity.OnTakeDamage 的 disappeared 分支会 Cancel(0) 并绕过 Buff.OnTakeDamage；INVINCIBLE 是其他条件。旧 v5/v6 固定文件未修改；此处保存更正。

`ForceSetToSourcePosition.Execute` (`0x18107c4b0`) 在此资源中把 BUFF_SOURCE（宿主）放到 BUFF_OWNER（NPC）的**当前 GridPosition**。它检查目标存在且非 giant boss，按声明 ReleaseFromBlocker、DisableCurrentStillPull，并以 NPC 当前 cursor.route/current index 调用 Enemy.ReassignRoute (`0x180a738a0`)。重指派调用 BasicCursor.OnRouteChanged 与 DirectionCursor.AssignHostRouteProgress。

这不是重置宿主到最初出生点，也不是直接复制 NPC 任意连续坐标。随后 SetDisappear(false)、FinishBuffsById(host, enemy_shdopl_passive) 的先后来自资源和已恢复 Execute。Buff source 通过 **ObjectPtr** 解析，不是永久裸指针；已恢复 generic wrapper `0x185159d80`，内部有效性 helper `0x1800c9210` 未完全恢复，因此接口仍要求 source UID/引用有效性证明。

## Finish、life 与动作短路

`enemy_shdopl_finish` 的 ON_TAKE_DAMAGE(10) 声明依次恢复位置、显示宿主、结束宿主 passive、InstantKill(NPC)、lock=1、ClearAllBuffs。**资源数组不保证全部节点执行。**

该 InstantKill `_noReason=true` 调用 `Entity.FinishWithNoReason` (`0x1806f3610`)，virtual FinishMe reason **7 OTHER**；并非 Suicide 或 HP_ZERO，也不直接写 HP。`IfReasonIsDeath` 的 death 集合是 `{2,3,5,8}`，不含 7。`Buff.OnOwnerFinish` 对 death 执行 ON_OWNER_KILLED(3)，对 reach exit 执行 34，最后对所有 finish 执行 ON_OWNER_FINISH(4)。所以 **这条 Finish7 路径不会因为名字 InstantKill 而自动触发 upeople_t 的 event3 扣血**。

已恢复 ActionUtil.RunActions (`0x181190690`)、CheckExecute (`0x18118fb90`) 和 base ActionNode.get_executeCondition (`0x180fcc600`) 的原件 raw：previousResult 初始 true；每个节点先检查 allowedSource 和 executeCondition，再 Execute，将返回值赋回 previousResult。condition 0=true、1=previousResult、2=!previousResult；CheckExecute=false **退出整个列表**。AssignValueToBB / ClearAllBuffs 没有 slot 5 override，继承 condition **1**。它们 allowedSource=0x3f，包含 Buff 调用的 source type 1。

InstantKill 正常 Finish 后返回 target.get_alive=false。因此后续 AssignValueToBB 被 CheckExecute 拒绝，**这条普通成功 finish 路径不会写 lock=1，也不会执行后续 ClearAllBuffs**。不能为了简化模拟提前写 lock。Finish 的 owner callback 在 InstantKill 返回前同步发生，event4 中 Filter(lock>=1)+IfNot 路径因此可能在旧 lock 值上再次执行恢复。IfNot condition=2，执行成功返回 true；具体再次恢复的合法性仍受 source、容器 mutation、callback 排序及黑板取值约束，不能无条件宣称双恢复或一次恢复。原件 flow 与 slot 证据见 `raw_dispatch.json`、`identity_proofs.json`。

upeople_t 的 event3 是 **ON_OWNER_KILLED**，不是 ReachExit。实际 HP 死亡、Buff 有效且 blackboard 绑定成功时，ModifyLifePoint (`0x181040fe0`) 取 value 的整数值；资源 isSub=false，所以普通非 coop 分支不取反，isReachExit=false。若 value 实际绑定为 -1，则请求 BattleController.ModifyLifePoint(-1, owner, branch0, false)。coop 的额外分支、global modifiers/tempLife/模式消费者仍须按支持上下文处理，不能把资源 `-1` 写成无条件全局 `life -= 1`。

复用既有 finish 顺序：Entity virtualOnFinish / Buff callbacks → gameMode DestroyEntity → recycle。Default mode reason7 属非 death、非 reach-exit，即 immediate recycle 分支；这是 **指定模式下** 的规则，不是所有模式的通用结论。Scheduler 的真实订阅/全场景注册仍未封闭；不把回收 callback、final release 和 HP death 动画等待混为一件事。

## 可实施接口与严格门

`interfaces.json` 给出建议的四层接口：有 UID 的 source/owner 解析、共享 coroutine 的 summon plan、grid/route/state 恢复、带 previousResult 与重入的 Buff dispatch。这些是下一阶段接口设计，未并入 simulator。组件必须显式接收 supported mode/hotfix/global modifiers/initialLife，父对象/源对象身份、已初始化才有效的 Buff 列表、原生排序与 deferred mutation、factory/route/state 回调。上述任一未封闭就拒绝宣称完整 NPC ready。

精确下一步地址和普通小闭包见 `selection_next.json`。本轮不再请求大规模 Java 扩展；ActionRunner 的已闭合部分应保留，余下门集中在 `_DoSpawnEnemyInternal`、DisappearState、路由重指派、ObjectPtr validation、BB prefix/case 和 Buff priority/mutation。

## 校验

- 本轮 NPC Ghidra **31 入口、69 imported ranges、16,150 bytes**，decompile 完成、导入 bytes SHA 与原件一致。
- 原件 raw **47 函数记录、93 ranges、19,434 bytes**（包含上述 31 入口）；每个范围 hash 和输出指令 bytes 重新核对一致。GetActionTarget 的 44-byte jump table 单独标为数据，没有当作指令执行语义。
- native_fields 含 **42 types / 2,013 fields**；native type/field offsets 不依同名 metadata 简称猜测。Options value-type offsets 包含 boxed header，使用时减 0x10。
- 原有 v5 lifecycle manifest 的 **12 files** 和 v6 damage manifest 的 **101 files** 全部重新验 hash，一致且未 repin。
- 这些是原件/元数据/静态边界校验，不是客户端运行时对照，不包含本轮 NPC 实现测试。

`manifest.json` 固定本轮证据、所复用的旧输入和报告；所有路径为绝对路径。新报告和接口不改变任何已冻结 v5/v6 模块。
