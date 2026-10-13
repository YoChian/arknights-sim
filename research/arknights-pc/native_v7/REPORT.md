# v7：祭坛准备、ALL目标顺序与NPC召唤接口

2026-10-13。已把祭坛技能准备、所属方/层掩码、默认筛选用途与普通ALL顺序接入新的受控样例。物理碰撞仍由外部快照提供，完整“猎犬病原”尚未接通，三个ready/validated标记均为false。

## 本轮可运行结果

在 D:\Repo\arknights-sim 执行：

~~~powershell
python -X utf8 scripts/probe_altar_prepared.py --frames 10000
python -X utf8 scripts/verify_v7_snapshot.py
~~~

[新样例轨迹](../../../arknights-sim/artifacts/altar_component_prepared.json)、[v7全量核验](../../../arknights-sim/artifacts/verification_v7.json)、[源码与后续入口](../../../arknights-sim/docs/HANDOFF.md)。旧altar-component命令与v6样例保留，供重现当时的显式输入实验。

| 参数/记录 | v6显式样例 | v7来源化样例 |
| --- | --- | --- |
| 前摇/施放持续/冷却 | .6 /0 /0，外部输入 | FP raw2576980480 /4294967296 /4294967296，约.60000002384 /1 /1 |
| 所属方 | 外部side4 | 实际Trap._sideType=2（ENEMY） |
| 目标方/层掩码/用途 | 外部7 /123 /1 | 原生推导7 /268436992 /0 |
| ALL输出 | 外部单UID permutation | 普通WeightedTarget优先队列生成 |
| HitRange | 外部true | 原生manager对明确空provider字典返回true |
| 第二次伤害 | 第457帧 | 第469帧 |
| 最后伤害/回收 | 第4121/4139帧 | 第4325/4343帧 |
| 伤害总量 | 18×500，基础HP9000→0 | 18×500，基础HP9000→0 |

新伤害帧为227、469、710、951、1192、1433、1674、1915、2156、2397、2638、2879、3120、3361、3602、3843、4084、4325。生命3不变；回收后请求单actor样例逻辑win。没有external_resolve/recycle直接终结目标，没有训练奖励。

最终全量289项测试通过，0失败/错误/跳过；310项v7文件固定散列与190段原件字节检查一致，旧v6的323文件/358范围仍一致。4个新集成检查覆盖准备参数与真实掩码到首次伤害、第二次施放节奏差异、18次伤害后的延迟回收、reset/分段tick一致。详细结果以verification_v7.json为准。

技能准备子清单118文件，12测试及18个独立C#算术向量一致；其30个新入口/87范围加raw helpers共135个原件范围核对通过。目标子清单93文件（含原样保留的旧targeting pins），25测试；C#参考为1500 comparator pairs、120 queue/3786 UID、400 status case、64 side mask。NPC子清单99文件，31反编译入口/69范围与47 raw记录/93范围均核对通过。根清单按路径去重，三个子清单数字不能简单相加当作新文件数量。上述参考都是自建静态转写，不是运行游戏取得的金标准。

## 技能准备的恢复范围

skill_preparation.py以实际预定义PHASE_0/level1/mainSkillLvl1、sktok_ore与trap_011_ore完整规则组件为输入，恢复选定GetSkillData/SkillData.InitIfNot、BasicSkill.AssignData、Ability.SetData/UpdateBlackboard/Attach与动画时间准备路径。它准备数据，不创建Unity对象或执行完整Character.Init。

SkillData.InitIfNot把技能表duration=0写入blackboard；SP与value=500同时保留。实际Ability时间模式是SPECIFIED=2，该分支使用序列化_cooldown=1，而不从_cooldownKey=duration读黑板。AbstractAnimatedAbility.UpdatePlaybackSpeed把get_cooldown写入m_attackTime；GetDuration读取该运行字段，所以施放持续为1秒。

默认TrapMode无animatorHooker；MeshAnimator由实际Idle/Born/Die条目构造动画字典，能力_animKey为空，查找失败，跳过动画缩放。preDelay=min(attackTime,FP(float32(serializedPreDelay*1)))。有动画命中、其它time mode、热修补或外部准备修饰的输入须另行恢复。

BasicSkill.Behaviour与AbilityStandard.Behaviour分别核对，不能把前者的空列表推广成后者为空。UberEffectEmitter属于能力Behaviour；新准备证据记录该视觉组件及其选定时间回调，受控战斗样例不执行Unity视觉效果。

## 目标初始化与普通ALL

targeting_runtime.py使用原件SideTypes/Layers初始化和TagManager资源层表。same=[1,2,4]、opposite=[2,5,2]；实际源方ENEMY2与BOTH3转换为目标mask7。ALLY、ENEMY、NEUTRAL实际层索引10、9、28，全OR为268436992。TargetSelector.sourcePurposeMask原生默认返回0，独立于AbilityStandard自身purposeMask=1。

异常状态采用显式Attributes计数与基础位掩码；未知所需计数停止，不能把缺失当0。HitRangeManager重现provider聚合及选定注册语义；空provider字典可接纳，但真实provider注册与几何算法仍需来源。主样例的零异常状态、空provider与原生createdTime字段raw0是明确小场景输入，不是已证明的真实run状态。

ALL真实类型为PriorityQueue<WeightedTarget<Entity>>。通过generic method/type/RGCTX身份和原件比较器恢复普通createdTime权重、FP.EN3分箱、大值分支及UInt32 UID比较；队列线性插入保持原生比较语义。第二阶段alive变化可显式提供并影响membership。Sandbox额外权重路径拒绝，未用普通路径代替。

Physics2D overlap的Collider/Transform/接触容差、查询顺序与同步相位尚未实现。范围盒声明与逻辑过滤不能证明某个敌人实际命中。主样例仍提供3个命中同一uid的外部碰撞快照。

## NPC调查得到的执行接口

native_v7/npc记录了31个新增精确入口及69个导入范围，另有源绑定raw helpers与资源动作树。这里只恢复执行关系，没有将NPC接入自动战斗。

- SummonEnemiesFollowMyRouteWithBuff采集宿主originRoute、originCursorIndex与UID，构造带buff的召唤配置。origin优先缓存字段，没有缓存才读当前cursor，并非总是关卡出生起点。
- d__129即使delay=0也经过FP WaitForFixedSeconds，至少等待1帧。选定managed=true/dontBlockWave=true配置进入最终集合，不进入当前wave阻塞集合。
- 恢复节点把非giant-boss宿主搬到NPC当前GridPosition，再ReassignRoute接入NPC当前route/cursorIndex；不能直接重置出生坐标。
- InstantKill的noReason分支调用FinishWithNoReason，reason7=OTHER。IfReasonIsDeath集合为2、3、5、8，排除7；upeopl的扣生命动作属于event3，不能绑定到任意InstantKill。
- event10资源顺序是恢复/清宿主passive→InstantKill→lock=1→ClearAllBuffs。ActionRunner先消费Execute返回值；lock与Clear节点继承要求previousResult=true的条件。正常InstantKill返回alive=false后，后续lock/Clear不会执行。Finish7的同步event4在该返回之前发生，不能预设后置lock已经防止重入或宣称只恢复一次。
- BUFF_SOURCE是通过ObjectPtr<Entity>解析的来源，不是可直接保留的裸host指针。DisappearState、buff清除/修改器写回、scheduler与真正出生/管理回调仍有精确缺口。

## 对上一轮名称与假设的更正

以下更正保留在v7，v5/v6固定文件不重写：

1. 旧targeting记录中provisional SortedSet名实际是PriorityQueue<WeightedTarget<Entity>>。v6只接收外部ALL输出，没有执行错误名称对应的排序算法。
2. v6受控owner side4/purpose1/mask123是样例输入；当前实际资源/默认原生路径为side2/purpose0及派生mask268436992。
3. Entity.OnTakeDamage与IsUnhurtableWithModifier读取的继承字段+0x26属于BObject.isDisappeared，不是Enemy.Options.unharmful。旧damage shape/report沿用unharmful标签；普通laxe样例对应门控为false，行为数据不变。召唤Options.unharmful必须单独追踪，不能据名字解释为受伤链免疫。
4. SkillData.duration=0不等于Ability.GetDuration=0。v6的.6/0/0是明确外部输入；新样例按准备链得到.6/1/1，因此施放节奏变化。

## 证据与保留的外部上下文

新增核心Ghidra4轮21/38/21/5入口、58/71/48/13范围，共85个候选/190个精确范围，导入与原件字节相同。旧v6的323项固定文件/358原件范围继续单独核验；验证不自动repin。自建CLI/Ghidra与独立C#转写属于静态恢复证据，不是REA MCP游戏Evidence或实际客户端轨迹。

固定GameAssembly.dll SHA-256：
583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5

主样例仍显式给出：初始life/temp3/0、静止目标、出生/回收delay、Unity宿主存在且激活、默认mode及无动画override、无外部准备/全局修饰、source/target mapLayer等原生字段、零异常计数/基础mask、空HitRange providers、createdTime0、非Sandbox、无其它控制模块、单actor调度完成、默认无天赋纯伤害路径。不把这些输入视作已恢复完整场景。

本轮未运行/注入/修改游戏，未连接游戏服务；只执行自建静态分析工具、组件和参考程序，4轮Ghidra均已结束。

## 继续顺序

1. 在原件和资源约束下恢复UBody/Collider/Transform、真实物理查询与帧同步，继续封闭目标/全局状态来源。
2. 实现NPC ActionRunner/重入/来源有效性、消失与召唤出生闭包，再接宿主恢复与准确的生命事件。
3. 恢复箱子反伤/激活/自动branch、ore_listener模式及格子改写。
4. 补scheduler事件绑定、模式/全局增益/RNG/初始生命，组合完整无人操作关卡并核验轨迹。
5. 之后实现基础干员与观察/动作mask/奖励/批量训练接口。

当前battle_ready=false、autonomous_route_ready=false、runtime_battle_validated=false。
