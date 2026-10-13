# 当前研究状态与继续入口

2026-10-13。本项目是明日方舟集成战略离线训练环境的早期数据/规则恢复原型。用户已授权从本地 PC 客户端继续实际分析与实现。

- 客户端：`D:\Hypergryph Launcher\games\Arknights`；本地资源版本 `26-09-13-15-28-10-30688348`。
- 最新原生调查报告：`D:\Repo\.rea-tools\arknights-pc\native_v9\REPORT.md`；历史v8报告保持固定；祭坛旧条件组件为`native_v6`，移动/生命周期为`native_v5`，敌人/初步寻路为`native_v4`，FP/调度为`native_v3`。analysis root的`REPORT.md`是首轮历史记录，资源未解码/Ghidra未安装的说法已过时。
- 全量规则表及提取验证：`D:\Repo\.rea-tools\arknights-pc\resources_v2`；当前小图 `level_rogue6_1-1` = “猎犬病原”。
- 上一阶段原生输出：`native_v2/focused_results*.json`，共43个选定候选入口；本阶段新增恢复见native_v3报告。元数据关联是候选符号，PE unwind入口佐证，不是运行时身份证明。
- 坐标已从静态原生访问恢复为 `matrix[height-row-1,col] -> tiles`。源码 `coordinates.py` 保存证据地址/散列，默认 bottom_origin；raw matrix 只用于存储诊断。
- 独立 LegacyRandom 已恢复编译默认分支并与 C# 转写参考比较；inextp=31，不能替换成 Python random/System.Random。未验证热修补实际生效路径或真实对局的种子/消费序列，不自动绑定到 `DeclarationProbeEnv`。
- 复查：`python -X utf8 scripts/verify_snapshot.py`。产物在 `artifacts/verification.json`、`tests.txt`、拓扑和SVG地图。

必须保留 `battle_ready=false`，直到有真实战斗行为和轨迹核验。`DeclarationProbeEnv.step`仍只前进原始声明数组；另有独立`TimelineEnv`推进条件调度内核，两者reward=None。四邻接BFS不是游戏寻路。禁止简单累加SPAWN count或delay冒充游戏时间轴；属性m_defined=false不等于有效0。

用户已接受顺序：敌人属性/创建→无人操作自动出怪、移动、漏怪与结束→少量基础干员战斗→轨迹核验/训练接口→技能与肉鸽战略层。继续实际实现，不要重新问同样的授权。当前敌人数据与原生移动组件已实现，但第一个端到端自动关卡里程碑尚未完成；不得把component测试通过当成自动战斗完成。

## 最新v9继续入口

v9最终全量验证468项测试全部通过，0失败/错误/跳过；346文件pin、49新增原生入口/109原件范围一致；旧v8 290pins/136ranges、v7 310pins/190ranges、v6 323pins/358ranges保持不变。

新增 `scripts/probe_npc_pipeline.py`，总核验 `scripts/verify_v9_snapshot.py`；统计 `artifacts/verification_v9.json`、组合 `artifacts/npc_pipeline.json`、固定证据 `evidence/v9`。旧v8及之前pins不repin。

新 `enemy_factory.py` / `buff_container.py` / `npc_damage.py` / `npc_lifecycle.py`，组合 `npc_pipeline.py`：FactoryEnemy与NpcEntity/Buff/Lifecycle共享同一引用；来源化upeoplHP3500、frame1Born6/frame2Move1（同帧不Move）。common在Unit.OnBorn Attach立即Start，talent在Init注册但首次Tick才Start。OwnerBorn12、Start0、PostBorn35不同；先FSM后BuffTick。共享snapshot nested遍历、真实priority/member/finish/clear重入已接，Reset/override/attributes仍receipt。

frame10 decoded modifier受击反应→恢复当前NPCgrid(3,5)/route/progress4→Finish7；owner event4重入第二次恢复，lock0/Clear0/life3；event6→UID0→event8→pool final0。取消damage仍进Buff；无取消时Unit动画在UID0后继续。完整ApplyModifier前后hooks与HP写仍未实现，不扣NPC HP。death2为显式finish输入：Dead(-1)life2/恢复1，frame10final1，声明Single0.6共享延迟frame28UID0/final0；音频CreateBuff/pool/animation外部。fresh first OnGameReset已证实际BattleEvent6/conditional8委托绑定，整个EventPool/全bootstrap未重构。

本轮49新入口/109精确ranges全部匹配，模块独立C#转写不是client oracle；最终test/pin数以verification_v9为准。static/自有程序，未运行/注入/改写客户端或联网。仍三个ready/validated=false、reward=None。完整图还需Unity query/sync/pose、NPC初始化/完整HP/非空route、箱子ore_listener/branch/格子改写与run/RNG/global，再基础干员/训练接口。别把final0当全图win。

早期OwnerBorn=Start0的推测已更正（实际OwnerBorn12）；旧v8报告fixture保持不变，不把旧provider模型当出生事件证明。

## 历史v8继续入口

v8最终全量验证383tests全部通过，0失败/错误/跳过；290固定filepins、72新原生入口/136原件ranges全部一致，旧v7 310pins/190ranges和v6 323pins/358ranges保持不变。

新增 `scripts/probe_npc_component.py`、`scripts/probe_physics_altar.py`；总核验 `scripts/verify_v8_snapshot.py`。产物 `artifacts/npc_component.json`、`altar_physics_contract.json`、`verification_v8.json`。固定新证据在 `evidence/v8`；旧v5/v6/v7不repin，验证不会自动生成新pins。源码与报告的绝对路径均在清单中。

- `npc_actions.py` 有界指定Buff事件执行：ObjectPtr当前UID等值/Unity存在（alive独立且相等zero UID可过）、Context先解析再复制栈/Dispose、previousResult条件、List<DataPair>黑板/prefix OrdinalIgnoreCase、GetInt的floor(Single)、Finish7/death/exit事件。默认invariant ASCII是fixture，真实culture未观察；完整double-buffered会员遍历与一般节点不支持，upeople_t_1音频CreateBuff拒绝。28 tests、187自有C# vectors通过；25新函数/51ranges和22 raw records/31ranges原件匹配；75pins。
- `npc_restore.py` float版.3等待与两个顺序Append .15颜色段、当前格恢复/StillPull/空CProute Reset+progress、停协程/appearance/DEFAULT0→Move1。State-transition、Move hooks、事件30/23、modifier效果、Tween、父链active和非空CP/阻挡backend明确；必须active_hierarchy_matches_self=true。21tests、48自有C#向量；16函数/36导入ranges、19raw/39原件ranges、90pins。GameObject.activeSelf与activeInHierarchy不可任意合并。
- `npc_summon.py` d__129捕获origin route/progress/UID再FPwait，零delay至少1帧；allow gate/actual stop=false没有额外alive gate；counter/Options、RouteData/checkpoints深复制、explicit生成路线/初始化factory、progress/hostUid→列表→position/face/buff→mode。dontBlockWave只入final；null factory早退无mode_after。11tests，6函数/24ranges。两个raw mode jump-table thunk不满足严格leaf边界而被拒绝，不扩大猜测跨度。
- `physics_context.py` 5prefab完整声明、128 buffer、两次bounds→Area/Box参数、Circle外部TransformVector→Single magnitude、初始28bytefilter、epoch/fingerprint→external receipt→旧targeting接口。Circle分支由真实CircleColliderOverlapFixed marker而非Rigidbody2D判定（精确MethodSpec已更正早期误名）。25tests（21行为+4自有C#对照）；5prefab均无serialized CircleColliderOverlapFixed marker，runtime仍需独立输入，不能由Rigidbody或prefab absence默认。Collider.bounds/TransformVector/CheckConsistency后filter/命中/同步均外部；UnityPlayer507名称/地址候选配对未证明，不是engine oracle。
- `npc_component.py` 6组合检查：frame0passive→共享召唤与隐藏；frame1NPC创建；frame9host不active；frame10明示ON_TAKE_DAMAGE10后恢复NPC当前grid(3,5)/route/progress4，显式finish7→event4同步重入导致这个fixture两次restore，lock0/Clear0/life3。frame11appearance与state1，frame12才Move provider。另reason2信号dead.value=-1使life2/restore1。信号/姿态/初始化会员/factory/Move/FSM/Tween/native mode&pool仍external，NPC HP未算，final保留1待真实回收，没有制造win。
- `physics_altar.py` 3组合检查：仪表化firstquery210 objects_fixed，不是假定coroutines/Simulate后；3查询receipt经真实接口去重，damage227/469/.../4325，回收4343。Bounds getter pairs/filter/hits/live settings都fixture；没有计算engine碰撞。

两轮core串行新72入口/136范围全部导入匹配；root20组合/召唤检查及旧12lifecycle检查的独立只读复查32tests通过。最新全量tests/pins和子参考统计见verification_v8，root报告native_v8/REPORT.md。旧v7 310pins/190原件ranges、v6 323pins/358ranges已重新验不变。独立Python/C#不是client oracle；仍battle_ready/autonomous_route_ready/runtime_battle_validated=false，reward=None。

下一步需关闭真实Unity query/sync/pose/filter结果及NPC factory/birth、完整Buff membership/mode/pool/非空route；接箱子/ore_listener/自动branch/格子改写与scheduler/run/RNG/global上下文。完整无人操作图+可信轨迹后，才基础干员与训练接口。所有本轮操作保持静态/自有程序，不启动游戏、注入、修改客户端或游戏服务联网。

## 最新v7继续入口

运行`python -X utf8 scripts/probe_altar_prepared.py --frames 10000`；全量核验用`scripts/verify_v7_snapshot.py`。产物`artifacts/altar_component_prepared.json`、`verification_v7.json`。v5/v6代码/清单不改写，新总pin在`evidence/v7`；代码不自动repin。

新样例实际结果：预定义祭坛PHASE_0/level1/skill1，前摇raw2576980480/持续4294967296/冷却4294967296；基础HP9000的静止laxe受18×500伤害，帧227/469/710/.../4325，第4343帧回收/逻辑win，life3不变。最终289tests全部通过、0失败/错误/跳过，310项v7文件pin/190段原件字节核验通过，旧v6 323pins/358ranges不变。4个新增集成检查覆盖第一伤、v6/v7第二伤457→469、死亡/延迟回收、reset/分段一致；新参考数字以verification_v7为准，三个ready/validated仍false。

- `skill_preparation.py`：prepare_altar_skill(dataset,native_default_no_hotfix=True,no_external_skill_modifier=True)返回FP时间、SP、黑板与provenance/remaining_context。SkillData.duration0写BB，但SPECIFIED2用serialized cooldown1，GetDuration读m_attackTime，所以实际持续1。空animKey查不到默认MeshAnimator的Idle/Born/Die，跳过缩放。只准备数据，Unity Init/owner/override等仍explicit。BasicSkill.Behaviour0与AbilityStandard.Behaviour实际UberEffectEmitter须区分。
- `targeting_runtime.py`：实际Trap._sideType2；Side same[1,2,4]/opposite[2,5,2]；BOTH→mask7，TagManager层10/9/28→268436992，TargetSelector purpose getter默认0。属性Int16 counts/UInt64 basebits和HitRange聚合有界恢复；普通ALL使用PriorityQueue<WeightedTarget<Entity>>，FP.EN3raw4294967/大阈值1000000/FP分箱/UInt32比较。可用postfilter_alive显式二阶段变化，sandbox/hotfix未知拒绝。Physics2D仍external。
- `altar_prepared.py`复用不可变v6基础组件，第0帧安装新context/registry。source/target mapLayer、目标其它原生字段、createdTime0、零异常count、空provider、非sandbox、无其它模块、initiallife/temp3/0和无全局修饰均明确fixture；没有original map scheduler/敌人移动攻击/NPC/箱子。
- 新核心4轮85入口/190精确范围（21/38/21/5；58/71/48/13），源导入一致；全部Java结束。child证据分别skill_preparation、targeting_runtime、npc；root新pin脚本只供显式复审，旧v6 323pins/358ranges继续检查。
- `native_v7/npc`：31入口/69导入ranges+raw，先静态接口调查。零delay也wait至少1帧，managed/dontBlockWave只入final；origin优先cache，否则cursor；恢复到NPC当前grid/route/cursor；noReason Finish7非death-event3；ActionRunner按previousResult条件控制后置lock/Clear，不能仅据资源数组顺序执行。NPC完整ObjectPtr/Disappear/事件/修饰写回仍有拒绝项，不是自动NPC战斗。

必须沿用v7更正：旧provisional SortedSet实际PriorityQueue；旧v6 owner4/purpose1/mask123为fixture；damage +0x26实际BObject.isDisappeared，不是Enemy.Options.unharmful，不能推断NPC免伤；SkillData.duration0不能替代Ability.GetDuration1。普通laxe旧模型门控false，历史fixture继续可重现。

下一步：UBody/Collider/Transform/真实Physics2D与同步→NPC source有效性/ActionRunner回调重入/消失/出生与生命事件→箱子/自动branch/ore_listener与格子改写→完整scheduler/mode/RNG/global/life上下文与轨迹。之后基础干员和训练接口。具体NPC已证入口/next helpers在其报告；先复用已恢复85入口及raw，不重复全图Ghidra。

## 历史v6继续入口

本轮最终验证248项测试全部通过；323项v6文件pin、358段原件字节范围检查一致，旧v5 pins未变。入口`python -X utf8 -m arknights_probe altar-component --frames 5000`和`scripts/probe_altar_component.py`输出`artifacts/altar_component_external.json`；全量报告`artifacts/verification.json`。CLI的230帧冒烟检查也通过，1次扣血后HP8500。

受控样例：一个基础HP9000的静止enemy_1034_laxe与初始化后祭坛，18次各500纯伤害，首次第227帧，死亡第4121帧，回收/逻辑win第4139帧，life3不变。没有external_resolve/recycle直接结束目标。准备后时间preDelay=.6/duration=0/cooldown=0、Unity宿主存在且激活、三个碰撞盒的Overlap结果、LayerMask123、HitRange与ALL输出顺序、单actor调度已结束、无其他控制模块均是显式外部fixture。不是原图对局，也没有攻击/移动；reward=None，battle_ready/autonomous_route_ready/runtime_battle_validated均false。

- `frame_runtime.py`：UInt32对象注册顺序及阶段快照、共享CoroutineSimulator的UInt64 handle、立即prime/嵌套/stop、当轮协程快照。Unity coroutine owner存在/active是输入，不能由Entity.alive代替。死亡不立即移出有效对象；回收时令instanceUid=0再进入late阶段。
- `skill_runtime.py`：选定AUTO/timeSP的BORN→Idle→Skill、重入FSM队列、SP恢复、AT_BEGINNING目标快照、FP等待、释放SP_STOP的下一fixed tick。完整AssignData/LoadBlackboard/准备时间、其它行为与热修补未执行。152子manifest pins、119入口/303字节范围；21测试；独立C#6case/5550frame/263event，不是客户端oracle。
- `targeting.py`：资源range x-1生成3重叠盒，显式碰撞/谓词输入的过滤→去重→128上限→UInt32排序。ALL输入/输出完整permutation是adapter约束，原生ALL membership/SortedSet/gap/extraMode尚未闭合；不得用同uid输出例子证明ALL。53子pins；25测试；独立C#148几何case/4562盒与112collector case/10722决策/1660uid。
- `damage.py`：普通无天赋目标的PURE/NONE、空初始化动作slots、未完成ore_buff明确拒绝；FP乘法/HP clamp、hp<EN5归零（相等不归零且alive=false）、首个取消理由、死亡→波释放→共享协程回收。OnBeingCalculateDamage在alive门控之前；Unit+270是整个talents列表。101子pins；15测试/255独立C#向量。
- `altar_component.py`把上述组件与生命周期连接；4个集成测试覆盖首伤/去重、18次伤害与延迟回收、目标快照后死亡、reset/分段tick一致。`tests/test_frame_runtime.py`10测试。`v6_validation.py`固定源散列与原件，不自动repin。`scripts/pin_v6_evidence.py`只在显式复审后运行。
- 新v6 Ghidra三轮串行119/34/14候选、271/67/20范围，共167/358；`0x182648530`在已有PE unwind body内部，被明确拒绝，166接受入口不是全部行为已恢复。UInt32.CompareTo临时Int32误名更正在`native_v6/frame/identity_corrections.json`。详细报告各在frame/skill/targeting/damage；native_v6/summary.json聚合当前验证。

下一步先补祭坛完整技能准备、真实LayerMask/HitRange/UBody/Transform/Physics2D与ALL后处理，再恢复shdopl→upeopl召唤/隐藏宿主/路线与死亡扣生命，接着箱子反伤/激活/branch/mode/格子改写。补Scheduler反射event绑定与运行上下文后，才组合完整无人操作图并核验轨迹，之后基础干员与训练接口。旧v5设备模型与新v6技能施放模型须区分，不能重复推进SP或私有回收runner。

## 历史v5继续入口

最终全量验证173项测试通过、0失败/错误/跳过；94个固定组件文件和9个frame源pin通过。7个主要客户端文件散列复核不变。单敌人fixture自动在120帧完成回收/逻辑win、life3→2；完整“猎犬病原”未ready。结果路径：`artifacts/verification.json`、`route_lifecycle_component.json`、`scene_normal_audit.json`、`scene_four_star_audit.json`；总快照为`.rea-tools/arknights-pc/native_v5/summary.json`。

- `runtime_movement.py`：Tile/HoleTile cache/init/rewrite、NativeDirectionCursor、NativeMoveController、NativeRouteMover.tick；MovementContext 9字段全部必填。位置是Single localPosition、WAIT是FP、deterministic在FSM后/cursor前round4。零CP路线ctor启用stable逐节点访问；actual alwaysCheckCurrentPoint只有shsdgo为true，其他9为false（资源pin在v5）。
- 10prefab steering8/maxForce10/halfBodyWidth≈.2；BattleOptions.STEERING_ENABLED cctor=false，但实际开场setter没证。不能由level.steeringEnabled=true直接推断全局分支。
- `lifecycle.py`：生命周期初始life/temp和useRecycleToFinishScheduler必须显式；Born6→Move1本tick不重入Move；hp.raw>42950才alive。ReachExit-only；NPC模板、死亡状态及global modifiers严格拒绝。FinishMe virtualOnFinish含Unit event6/Enemy life/event7完成后，DefaultGameMode.DestroyEntity才延迟回收。此前误把slot118当Recycle，它实际是ClearAbilities；已据vtable和raw更正。
- 真实正延迟用MonoBehaviour `_RecycleAsync>d__3`=180661ec0，而不是GameObject d__2。IReusable.OnRecycle dispatch185c27ff0→Enemy.OnRecycle；zero delay也同步该回调。Scheduler event6/8反射监听注册链未证，逻辑后端只作明确绑定。
- `route_runtime.py` 自动连接单敌人FSM→移动/cursor→漏怪/生命→回收→逻辑final，无external lifecycle事件。`python -X utf8 scripts/probe_route_lifecycle.py`输出controlled fixture；这是组件实验，不是“猎犬病原”真实胜负。完整场景scheduler尚未接入。
- `devices.py` 提供自然SP PrecisePeriodicTimer（remaining<FP.EN5=42950）、preDelay、IMMEDIATE buff、ore damage/mode请求。deterministic simulator branch明确要求true且StartBattleCoroutine立即prime；Unity coroutine分支不支持。首点SP当前资产dt是30帧，7点潜在210帧；AUTO技能FSM整体施放时钟没证。
- `scene-audit --config examples/timeline_normal_resolved.json`读取v5完整16 prefab Transform子树和22 buff literal闭包，保留9预定义（8隐藏）、条件branch与shdopl→upeopl dependency。Full-map明确拒绝未实现能力，不因无干员而忽略祭坛或NPC。
- v5 core三次Ghidra共200 unique entries/494 ranges，全decompile和source比较通过；没有并发Java。raw_round4是pool3、raw_round5是StartBattleCoroutine1，不计入Ghidra200。
- 独立C#移动320rounding/80avoidance/2400controller-frame与生命周期322向量；均不是client oracle。完整测试数以artifacts/verification.json为准。新证据固定pins在evidence/scene与各组件evidence；verify不得自动repin。

当时下一步为祭坛TargetOptions/range/admission→Character AUTO技能状态→伤害HP/死亡/ore_listener模式。本轮已接通限定形状的前半条链；仍需按最新v6入口补准备/物理/ALL、模式监听、NPC和箱子。完整无操作图和真实轨迹确认后才加基本干员与训练接口。不要把单敌人fixture的逻辑win、源表覆盖、独立参考一致误报为完整图ready。

目前均为离线静态分析；未启动游戏、注入、修改客户端或连接游戏服务。脚本分析原件只读，测试仅执行我们自己的程序。Codex REA 已登记Ghidra12.1.4/Android Studio JDK21；实际bridge工具就绪已用小型自建PE验证。配置更新读取需使用新MCP进程；不要因旧连接环境不变而重装。Ghidra project目录不能含点开头组件，临时project使用 `D:\Repo\arknights-ghidra-work\project`；安装/脚本/输出可以在`.rea-tools`下。

## 历史v4敌人/移动阶段

- `enemy_data.py`：真实EnemyDB.TryGet顺序→GetComputedEnemyData→非null overwrite ApplyDefinedData。十个refs/20 DB rows；34numeric/11Boolean；默认与defined零/false保留，BB/skills/sp合并。runtime key通过真实AssignName metadata从prefabKey映射。`attributes`仅是Reset cached FP，动态Entity效果不包括。629独立C#数值对照在`evidence/enemy_data`，manifest固定文件、module/test哈希。
- `enemy_rules.py`：明确选定runtime字段的FP乘数/clamp/write运算。整数先Single再double ties-even再CVTT int32；整体修饰后refresh。`examples/enemy_attribute_mul_selected.json`来自本图FOUR_STAR BB，但Rune.Verify及实际Rogue全局增益未恢复，不能称实际完整紧急属性。
- `enemy_creation_inputs.py`：从shipped prefab读extraSpawnDelay、DB读notCountInTotal；shdopl/shezlc=1秒，其他8种=0；所有onlyDelayOnStartTile=false；getter原件`0x180a7c370`在flagfalse且hotfixnull时读取+310。post-Init get_alive仍external fixture：stateMachine.isRunning要求id>0且已注册，HP.raw>42950，不能只检查HP>0。新`timeline_*_resolved.json`使用这些来源，原`*_external.json`保留参考fixture。
- `movement.py`：FP WAIT + Single Vector2几何/归格、显式cached tile snapshot的weighted FIFO/SPFA + Bresenham/corner/mask。需要继续恢复Tile.Init/cache来源、设备重写、controller实时force/tick、真实AssignLocalPosInternal/deterministic mode、cursor与exit/recycle顺序。严禁静默回退BFS或匀速直线。
- 本图源石祭坛可见，sktok_ore AUTO/time SP7、value500，Ability preDelay0.6；ore_s buff声明纯伤害并排除ore_immune，ore_buff声明特殊mode切换；祭坛TrapMode还rewriteTileOptions/passableMask2。执行时机/范围/Modifier结算尚未恢复，必须纳入真正的无人操作轨迹。配置在`native_v4/resources/prefab_inputs.json`、`ore_buff_templates.json`。
- 关卡maxLifePoint99是静态level输入，不是实际肉鸽run剩余生命。ModifyLifePoint有global Modifier/event消费路径；Enemy.FinishMe/Entity.FinishMe和延迟回收不同，不能漏怪时立即假定final成员清除。
- 原件补查：creation/results_round1(16)和round2(50)均完整，所有imported-range source比较true；creation/raw_round3(4)有getter、Entity.FinishMe、Default OnModifyLifePoint、Modifier.finalDelta。它们是CLI/raw静态证据，不是REA MCP Evidence，也不是完整规则证明。
- 本阶段Ghidra采用串行独占，1536M/maxcpu1；曾三个Java同时导入导致内存压力，movement失败round1保留作诊断而排除统计。各launch保存process_TAG.json，先核实owned PID再处理，别按java进程名整体终止。完成运行均关闭，无客户端运行会话。

## 按帧内核与独立参考

- FP/调度阶段原生总报告：`D:\Repo\.rea-tools\arknights-pc\native_v3\REPORT.md`。选定函数体在timeline/results_round2..6，字段偏移与时钟在fixedpoint；queue sort在sorting。
- `fp.py`为恢复的有符号Q32.32组件，独立C#运算向量覆盖边界/转换。不要用普通float或未经核验的通用定点库替换。
- `coroutines.py`实现RuntimeHandler的`(first, IEnumerator)`栈，首次空child会耗一帧；WaitWhile先yield再判；零delay至少一帧。等待helper`0x18059e290`实际nearest ties-even，尽管早期临时label误称CeilToInt。
- `queue_sort.py`是原生中点Quicksort，equal也交换，没有16阈值。独立C#参考涵盖152队列/5616身份顺序/81比较；宿主.NET List.Sort有56case不同，不可直接作为oracle。
- `timeline.py`可按真实wave/fragment生成并串行执行SPAWN、ACTIVATE与自动PREVIEW请求。`reset`frame0立即prime一次，`step({type:tick,frames:N})`每tick加FP时钟。默认143165440来自TimeManager资产初值，未验证live setter/hotfix，clock_anchor为排除mode hooks后的scheduler start。
- `examples/timeline_normal_external.json`及`timeline_four_star_external.json`明确给出original actionIndex选择(t1=0,t2=5,c1=4)，以及zero extraSpawnDelay/计数/成功创建的外部fixture。CLI `timeline --config ... --frames 1200`不会杜撰击杀：NORMAL15出怪+2预览；FOUR_STAR14出怪；都停wave1 gate。
- `preprocess.py`是独立Rogue预处理，可显式提供rng、group_order、topic和retain counters；根据gameConst分类，binary32 Range/epsilon weighted选择；EMPTY仍参与。它不推断客户端运行seed/Dictionary枚举或全局RNG消费，结果通过外部choices传入timeline。
- 外部生命周期：`external_release_wave`仅删wave；`external_recycle`仅删final/alive；`external_resolve killed/missed`是已包含回收的完整外部terminal fixture。`external_final_complete`代表外部门控处理完毕，不表示游戏胜利。箱子自动触发未恢复；两个branch仅支持单phase单action零delay external trigger，terminated后拒绝触发。
- `evidence/timeline/provenance.json`固定11个静态报告来源散列；验证不自动更新pins。`scripts/pin_timeline_evidence.py`仅用于复审之后有意更新来源。C#参考是我们独立转写并执行的程序，不是运行游戏的金标准。
- 全量验证与完整数字以`artifacts/verification.json`和tests.txt为准。源码、配置、诊断报告和能力界限已分开，不需Gymnasium或其他依赖。
