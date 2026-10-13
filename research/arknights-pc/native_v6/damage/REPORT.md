# 普通 PURE 伤害、死亡与共享回收组件

`arknights_probe/damage.py` 已实现可执行的普通敌人伤害组件。它消费已恢复的 `FixedDamageAction`，与 `LifecycleRuntime` 共用敌人 HP、状态和 Scheduler 成员；延迟回收注入 `SharedCoroutineSimulator` 和明确的 Unity owner，不另建私有 runner。本轮没有运行客户端，也没有启动 Java/Ghidra；复用父级静态反编译，并直接从原件 PE 做 Capstone 验证。

GameAssembly SHA-256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。metadata SHA-256：`d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`。73 个相关反编译条目的 171 个 imported range 校验全部通过；93 个静态反汇编入口的 200 段唯一原件范围重新核对成功，共 65,628 字节。范围来自递归 PE UNW_FLAG_CHAININFO 或已注明的短直线 leaf；没有把相邻 padding 当函数体。metadata 名称是候选关联，shared body 的别名与伪代码缺失返回值不作为原始源码声明。

## 算术及门控

| 行为 | 原件证据 | 实现 |
| --- | --- | --- |
| PURE 数值 | BattleFormula.CalculateDamageInternal `0x180656ba0`，GetFinalAtk `0x180648250`，AttackInfo ctor `0x180648380` | 在已明确 additive attack=Zero 的分支，FP 原生乘法后取 signed max(0, product)；PURE3 不走防御/MR公式。没有把普通伤害写成未经证明的 hp-=500。 |
| Modifier 资格 | FixedValueDamage.Execute `0x181057850`、BattleFormula.CalculateDamage `0x1806573c0`、Entity.ApplyModifier `0x1806efd80`、OnTakeDamage `0x1806fa4c0`、_VerifyAbilityDamageMiss `0x180700d10` | BattleFormula.OnBeingCalculateDamage 在 ApplyModifier 的 get_alive 入口门之前。SourceAttackType.NONE0 仍可能检查 source 的 projectile/ability hitFailed；调用方提供明确快照，projectile 存在时优先。 |
| 取消 | Modifier.Cancel `0x1808b0a70` | 先取消的 reason 保留；INVINCIBLE1 后的 HIT_FAILED6 不覆盖它。OnTakeDamage/event12 在这两种取消中仍执行，HP 写入和 OnAppliedModifier 不执行。 |
| HP写入 | Entity.DoApplyModifier `0x1806f1c00`、set_hp `0x180709750`、SetHpInternal `0x1806fd230` | 无 shield/minusHP/undead/修改回调的明确分支：signed Clamp(requested,0,maxHP)，再按 MathUtil.LE(hp,Zero) 决定归零。applied delta 用写入后的 HP 差值。 |
| HP epsilon | SetHpInternal 对 LE 的 CALL `0x1806fd3c7`、`0x1806fda9c`；LE `0x1866e5700`；共享比较 leaf `0x185ed91f0` | LE 在 rhs 加 FP_LARGE_EPS 后调用 `cmp rcx,rdx; setl al; ret`，因此严格 `hp.raw < 42950`。MathUtil.cctor `0x1866e6e50` 从 FP.EN5 静态字段+0x78取值；FP.cctor `0x1866fd010` 的 One/100000 给 raw42950。它不是 Single(1e-5) 转 FP。 |

**边界修正**：早期 Python 和 C#参考都用了 `<=42950`，最终已改为原件严格 `<42950`。HP=42949 会归零并死亡；HP=42950 保持该值，get_alive 的 GT 测试又为 false，因此不触发 OnHpZero、不 Finish、wave/final 成员保留，后续普通 ApplyModifier 也不再进入。实现和测试保留这个原件边界，没有修补成更直观的行为。

对于仍存在的逻辑目标对象，重复伤害请求先经过无动作的 OnBeingCalculateDamage，再因 get_alive=false 拒绝 Modifier；HP/finish/recycle 不变。Unity目标对象销毁/对象池复用身份由上层隔离，本组件不复刻 GetActionTarget/Unity fake-null。

## 同步死亡与回收顺序

普通 Move1/Born6 目标、空 talents 的 CheckReborn `0x180ac68b0` 返回 false。HP归零进入 Enemy.OnHpZero `0x180a70e80`→Entity.OnHpZero `0x1806f9170`，先 OnOwnerBeforeDead，再 FinishMe reason2。NONE0/PURE3 的实际 hp setter 参数 noSource=false，因此使用 HP_ZERO2；无来源 reason8 与复活/特殊状态没有混入支持范围。

Enemy.FinishMe `0x180a6d0d0` 先进入 DEAD5；DeadState.OnEnter `0x180a8b390` 只有 `_useSpecificDeadAnim`=true 时才在 `0x180a8b56f` 写 `m_delayToRecycle`。真实 laxe 的该字段为 false，本组件保留已由创建链供给的 delay；动画、Tween、视觉色彩和音效后端明确排除。没有猜 Die clip duration，也没有等动画结束才释放波次。

Entity.FinishMe `0x1806f3360` 停 FSM，`0x1806f3433` 调 virtual OnFinish，**之后** `0x1806f3512` 尾调 DefaultGameMode.DestroyEntity `0x180c18e70`。OnFinish 中 source OnTargetKilled/buff event9、Killed/entity event1、Unit finished event6 和 wave/final 释放在模式回收调度之前发生；Enemy.OnFinish 的 level event3 在声明无动作的上下文保留选定 trace，reason2 不扣 reach-exit life。模式 death 分支选择 RecycleSelfWithDelay。

正 delay 的共享 coroutine 立即 prime WaitForFixedSeconds，再按共享 simulator snapshot 时序推进；owner.exists/activeInHierarchy 与敌人 alive 是不同输入。在已开始的 coroutine phase 中新建的回收 runner 不会进入当前旧 snapshot。zero/effectively-zero Single delay 同步 OnRecycle，甚至先于返回后的 OnAppliedModifier。回收移除 final membership；最终 finish 由上层 Scheduler/check_final 判定，`DamageRuntime.apply` 不主动推进时钟或强制结束战斗。

## 已审查的资源形状与范围

真实目标仅 `enemy_1034_laxe`，完整规则 Transform 子树没有非空 buff 声明。它仍有 MeleeAttack；本模块不会声称攻击/选择器/FSM 的整场景已经封闭。目标模板、talents、active skills、level-event actions、shield、minusHP、undead、damaged-SP、blocker 或 specific-dead-animation 分支会拒绝。

真实祭坛 source 是 `trap_011_ore`。它的 **frosts_effect 不是空 buff 列表**：保留 flags5 INVINCIBLE、7 HEAL_FREE，templateKey=`empty`，原件模板的 eventToActions._items 确为空、attributeModifiers 为空。damage kernel 要求调用方明确提供已初始化的空 action slots；声明本身不能证明实际 Unity 场景初始化流程。

`finished_transient_templates` 只接受明确已 finished 的 ore_s/ore_buff。原件 `_FinishBuff` 在同步 ON_BUFF_FINISH 回调之前标记 finished，damage hooks 遇 isFinishedOrDisabled=true 跳过它；因此当前 ore_s 回调可明确供给该快照。**未 finished 的 ore_buff 不能隐式白名单**：死亡清理可能使其 ON_BUFF_FINISH 的 SwitchMode 执行。本模块不模拟这条未完成路径。源 OnTargetKilled 的完整 raw body已核对：Buff._IsActionValid event9 空 slot 时直接返回，无 RunActions。

默认模式、无 hotfix dispatch、空 global modifiers、无未审查场景监听器均为显式 offline scenario 范围，不是对实际 Rogue run 的观察。NPC宿主召唤/隐藏/恢复、upeopl death扣life、箱子/模式切换、任意动态能力、真实 Unity 对象工厂/物理/视觉与全图战斗仍未闭合。v5 Scheduler finished/recycled 处理函数和逻辑回调连接已复用，但真实反射注册链未证，不能从本组件的显式连接倒推出注册完成。

## 使用与验证

稳定入口：`ordinary_altar_shape(...)`；`DamageRuntime(lifecycle, simulator, context_source=...)`；`attach(identifier, shape, recycle_owner=...)`；`apply(identifier, action, atk_scale=..., finished_transient_templates=...)`。独立数值入口为 `pure_damage_value`、`ordinary_hp_write`。DamageResult 包含 calculated（取消前公式值）、applied_delta、hp_before/hp_after、killed 与 finish_reason；取消后的 native modifier delta 为零。

`python -m unittest tests.test_damage -v`：15 项通过，覆盖取消顺序、HP epsilon 两侧/相等、非致死/死亡、同步/延迟回收、owner禁用、新 runner snapshot 和明确拒绝条件。自有 `NativeDamageReference.cs` 用 BigInteger 全宽乘积/低64位有符号解释，独立编译并运行，255个数值/边界向量与Python一致。参考程序没有载入游戏程序集，也不是运行时 oracle。

`native_report.json`保留原反编译及 import hash；`native_disassembly.json`保留每段原件指令/哈希/别名；`resource_inputs.json`、`enum_constants.json`、`fields.json`固定声明证据；`reference_comparison.json`记录参考校验；`audit_summary.json`含全部冻结 v5 lifecycle 校验均通过的结果。v5 lifecycle.py、其tests和manifest未修改。模块依赖的共享 frame runtime 由父级集成和最终统一固定。
