# v6：祭坛条件施放、目标筛选与伤害死亡链

> 后续v7已恢复来源化准备与普通ALL。旧provisional SortedSet实际为PriorityQueue；damage的旧unharmful标签对应BObject.isDisappeared+0x26。v6的side4/purpose1/mask123及.6/0/0是明确fixture，新来源化样例使用side2/purpose0/268436992及.6/1/1。以下保留v6当时的结果与限制，详情和更正见[v7报告](../native_v7/REPORT.md)。固定v6组件证据不改写。

2026-10-13。继续从本地PC客户端静态原件恢复“猎犬病原”所需组件。本轮接通了受控祭坛的自动施放→目标过滤/去重→纯伤害HP结算→死亡→延迟回收；全量248项测试通过。完整关卡尚未运行，训练接口尚未就绪。

## 可重复运行的结果

在 D:\Repo\arknights-sim 中执行：

~~~powershell
python -X utf8 -m arknights_probe altar-component --frames 5000 --output artifacts/altar_component_external.json
python -X utf8 scripts/probe_altar_component.py --frames 5000
python -X utf8 scripts/verify_snapshot.py
~~~

主产物：[受控样例轨迹](../../../arknights-sim/artifacts/altar_component_external.json)、[全量验证](../../../arknights-sim/artifacts/verification.json)、[v6证据检查](../../../arknights-sim/artifacts/v6_component_evidence_verification.json)。

| 样例记录 | 结果 |
| --- | --- |
| 目标 | 一个静止enemy_1034_laxe，EnemyDB与关卡引用合并后的基础HP9000 |
| 祭坛 | sktok_ore第1等级，AUTO、time SP、cost7/init0/increment1、blackboard伤害500 |
| 首次伤害 | 第227帧，HP9000→8500 |
| 总伤害 | 18次，各500；同一目标在3个重叠盒中只结算一次 |
| 死亡 | 第4121帧，HP0，finish_reason=2 |
| 延迟回收 | 第4139帧完成，样例逻辑请求win；初始生命3不变 |
| 奖励/可训练标记 | reward=null；battle_ready/autonomous_route_ready/runtime_battle_validated均false |

伤害帧为227、457、686、915、1144、1373、1602、1831、2060、2289、2518、2747、2976、3205、3434、3663、3892、4121。样例不使用external_resolve/recycle直接终结目标，18次HP变化来自伤害组件。回收触发时清除注册对象instanceUid，late阶段不再包含目标。

CLI另经230帧冒烟检查：1次施放、HP8500、尚未死亡/回收，输出altar_component_cli_smoke.json。reset及分段step与一次性step的组件结果一致。

## 样例所依赖的外部输入

这是一个初始化后的祭坛和一个固定目标的组件实验，没有运行完整“猎犬病原”：

- 技能准备后preDelay=.6、duration=0、cooldown=0显式提供。完整Init/AssignData/LoadBlackboard与准备时间修饰尚未执行。
- 时钟dt_raw=143165440及half_default_frame_raw=71582720来自资产初值；未验证运行时setter或热修补。
- deterministic=true；Unity协程宿主存在且active_in_hierarchy=true，与敌人alive状态分别记录。
- 三个Physics2D重叠结果均显式包含同一uid2。LayerMask123为样例输入，不是已恢复的真实层掩码；side、mapLayer、purpose、HitRange和camouflage也保留输入来源。
- ALL后处理使用单uid的外部输出快照。adapter要求完整permutation；这项约束不证明原生ALL始终保留membership，也没有恢复其SortedSet/gap/extraMode。
- 目标初始生命/临时生命3/0、birthDelay0/recycleDelay.6、无AI移动/攻击、无其它BattleController模块、单actor出怪已结束均是明确fixture。
- HP9000是应用肉鸽全局增益之前的基础属性。无实际run RNG、动态runes、热修补、模式事件或真实客户端轨迹输入。
- 目标无天赋/其它buff/护盾等；完成的ore_s瞬时模板在结束回调时执行伤害。一般buff挂载、未完成ore_buff、laxe以外的模式监听尚未接入。

逻辑win来自这一个actor的默认结束条件，不代表游戏胜利或完整关卡等价性。

## 新组件与关键恢复点

### 帧循环与共享协程

[frame报告](frame/REPORT.md)与frame_runtime.py恢复选定的对象注册顺序、阶段快照与CoroutineSimulator。BObject.instanceUid是UInt32；CoroutineSimulator计数器和handler id是UInt64。不能以有符号排序替代UID顺序，也不能把Unity宿主有效性等同于Entity.alive。

Start立即prime；嵌套启动返回本次分配的handle，不返回随后变化的计数器。stop清除栈/id，不伪造Dispose。每轮协程使用开始时的快照：fixed阶段启动的协程可在本帧进入simulator；在simulator内部新启动的协程只立即prime，下一快照再推进。选定主循环为fixed→显式before模块→协程→显式after模块→late；完整BattleController模块初始化未实现。

### 技能状态与FP等待

[skill报告](skill/REPORT.md)与skill_runtime.py恢复选定AUTO/timeSP路径的BORN、Idle、Skill及重入状态队列；自然SP、可用性与AT_BEGINNING浅目标快照、立即prime的施放协程、减SP及SP_STOP注册顺序均保留。

技能使用FP等待重载：FP除法后经FP.Round/AsInt，ties-to-even且至少1帧。它不同于旧调度的float32等待重载，不能共用浮点商。casting清除在SkillEnd/AfterSkill/Idle回调之前；SP_STOP在完成后的下一object fixed更新释放，恢复在随后一帧生效。

准备后.6/1/1的独立参考例与主样例的.6/0/0属于不同fixture，不混用时钟。完整准备、chant、异常状态、其它能力和真实初始化仍未闭合。

### 范围与目标过滤

[targeting记录](targeting/NOTES.md)、arknights-sim/evidence/targeting/REPORT.md和targeting.py保存x-1范围构造：3个中心均为(0,0)的重叠盒，size分别为(1,5)、(3,3)、(5,1)。生成多个盒时重复使用全体格子集合，不能消耗格子后构造下一盒。

显式碰撞快照经过null/destroyed/uid0/alive及各谓词过滤，再去重、128个接纳上限和UInt32排序。真实Physics2D overlap、layer来源、HitRange provider和ALL后处理尚未实现；这些输入缺失即停止。SafeBounds相关getter是Behaviour.isActiveAndEnabled，不能误写为GameObject.activeInHierarchy。泛型List<Entity>.Sort/Filter身份通过metadata genericInst确认，未凭共享VA猜测。

### 纯伤害、HP与死亡回收

arknights-sim/evidence/damage/REPORT.md和damage.py实现普通目标限定形状的PURE/NONE路径：显式atkScale的FP乘法与非负伤害、HP范围限制、严格hp.raw<42950时归零。hp.raw恰等于42950时不归零，但alive=false，也不触发本次死亡；保留集合与后续门控差异。

OnBeingCalculateDamage在alive门控之前。取消理由保留第一个结果，后来的Miss不覆盖Invincible；相关OnTakeDamage钩子顺序分别记录。普通死亡路径经Enemy/Unit/Entity的HP归零、Dead状态/FSM停止、killed/波释放、DefaultDestroy与共享回收协程，随后保留OnAppliedModifier/sourceAfterDamage顺序。特定死亡动画分支未纳入当前shape。

Unit+270是完整talents列表，不仅是reborn来源；空才允许当前普通路径。source buff容器存在但声明actions/attributeModifiers及初始化action slots为空是明确上下文。完成的ore_s/ore_buff瞬时模板与未完成ore_buff区别处理，后者可能触发onClear，不能忽略。

## 验证与证据身份

| 检查 | 本轮结果与边界 |
| --- | --- |
| Python全量测试 | 248，0失败/错误/跳过 |
| v6文件固定散列 | 323项全部一致，包含子manifest、代码、测试和静态来源 |
| v6核心原件 | 3轮选定167个候选，358个导入范围与原件相同 |
| 入口筛查 | 拒绝1个位于既有PE函数体内部的候选，接受166个；不等于所有入口行为均已实现 |
| frame新增测试 | 10项，含高UInt32 UID、嵌套启动handle、阶段快照与stop |
| 组件集成测试 | 4项，含首次伤害/去重、18次伤害/回收、目标快照后死亡、reset/分段一致 |
| skill独立C# | 6 case /5550 frame /263 event；21测试 |
| targeting独立C# | 148几何case/4562盒；112 collector case/10722决策/1660 UID；25测试 |
| damage独立C# | 255向量；15测试 |
| 既有v5来源 | 94个组件文件pin与9个frame pin继续一致，未自动重写 |

子manifest分别为evidence/skill_runtime/native_manifest.json（152 pins）、evidence/targeting/native_evidence.json（53）、evidence/damage/manifest.json（101）；323总数经过路径去重和根文件加入，不是三个数字简单相加。verify只比较，不自动repin；pin_v6_evidence.py用于有意复审后的更新。

核心Ghidra按119/34/14候选及271/67/20范围分三轮串行执行。0x182648530的字节位于0x1826484b0函数体内，被入口guard拒绝，保留在core/rejected_entries.json作为负证据。不能遇到其后RET就提升为新函数入口。UInt32.CompareTo的临时Int32误名通过metadata/raw更正，记录于frame/identity_corrections.json，原始批次文件不改写。

目标GameAssembly.dll SHA-256：
583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5

metadata SHA-256：
d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f

自建Ghidra/字节导出与独立C#转写提供静态重构证据，不是REA MCP Evidence或运行中的客户端oracle。本轮未启动/注入/修改客户端，未连接游戏服务；所有Ghidra会话已完成。

## 后续仍按无人操作关卡优先

1. 闭合祭坛技能Init/AssignData/LoadBlackboard/准备参数，以及LayerMask/HitRange/UBody/Transform/Physics2D、ALL排序/间隔/extraMode。用真实来源替换当前显式输入。
2. 恢复shdopl→upeopl召唤、隐藏宿主、宿主路线/位置恢复及upeopl死亡扣生命。
3. 接箱子inverse_damage/激活/自动branch、敌人ore_listener模式、装置格子改写。
4. 补完整scheduler反射事件绑定、模式/全局增益/RNG/初始生命上下文，再组合全图自动时间轴、移动、伤害、生命周期并核验轨迹。
5. 完成上述里程碑后再加基础干员阻挡/攻击，随后观察、动作mask、奖励与批量训练接口。

目前保持battle_ready=false、autonomous_route_ready=false、runtime_battle_validated=false。不能用BFS/匀速、直接外部终结、忽略NPC/箱子或静态表覆盖代替完整战斗。
