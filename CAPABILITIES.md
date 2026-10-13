# 能力与证据边界

当前输入快照：本地 PC 客户端提取的 `level_rogue6_1-1`，主题“沉沦者的黑流树海”，阶段“猎犬病原”。哈希与源文件路径见 `data/manifest.json`。

| 组件 | 当前能力 | 证据与限制 |
| --- | --- | --- |
| 资源读取 | 已实现 | 社区 schema 可达字段边界验证通过；运行语义还需原生代码/对局验证 |
| 数据校验 | 已实现 | 7×11 地图、38条主声明、2分支、38+2路线、10敌人引用；缺失引用和源文件变化会停止 |
| reset/step | 声明探针已实现 | 保持数组顺序，无时间推断；seed只记录状态；reward=None；终止仅表示列表读完 |
| 坐标访问 | 已根据静态原生代码恢复 | `matrix[height-row-1,col]`→`tiles`，默认bottom_origin；两个get_Item入口和维度getter提供依据 |
| 导航 | 诊断探针已实现 | 四邻接 BFS，正确逻辑坐标下28/28 WALK路线可达；与已恢复的原生路径/移动组件分别使用，完整阻挡战斗仍未接入 |
| 原生路径/局部几何 | 独立组件已实现 | 完整显式缓存格子快照下的 weighted FIFO/SPFA、方向 mask、corner/Bresenham 平滑；局部坐标 Single、nearest 归格 |
| 移动控制与格子缓存 | 条件组件已实现 | Cursor MOVE/WAIT、加速度/避障、deterministic四位取整、Tile/Hole缓存及改格；实际运行flag、foot offset、全路线可达闸门必须明确 |
| 敌人生命周期 | 默认模式逻辑组件已实现 | Born→Move、到出口、临时生命先吸收、波次/最终集合、延迟回收；另有普通敌人纯伤害死亡条件链；动态天赋、热修补和Unity退场未闭合 |
| 自动路线生命周期 | 单敌人组件已接通 | RouteLifecycleProbe可自动移动至漏怪/回收/逻辑结束；使用受控fixture，没有完整场景scheduler/攻击链，reward=None |
| 祭坛组件 | 来源化准备及受控施放→伤害→死亡→回收已接通 | 准备后前摇.6/持续1/冷却1、自然SP/AUTO/FP等待/瞬时buff；Unity初始化/场景上下文及碰撞仍有显式输入，尚非完整关卡 |
| 目标筛选与范围 | 普通逻辑组件已实现 | x-1范围3个重叠盒；实际side/layer/purpose、状态计数/HitRange聚合、128上限/去重/UInt32及普通ALL weighted queue；Physics2D、动态provider与sandbox扩展未闭合 |
| 纯伤害/HP | 普通目标条件组件已实现 | PURE/NONE的FP伤害、HP clamp及严格EN5归零、取消优先级、死亡/回收；护盾/天赋/模式监听/一般buff挂载等未覆盖形状明确拒绝 |
| 共享帧循环与协程 | 选定静态组件已实现 | UInt32对象注册顺序、阶段快照、即时prime/嵌套/停止/共享tick及Unity宿主有效性；完整BattleController模块初始化未实现 |
| NPC动作/召唤 | 受限组件与fixture组合已实现 | UID/context/黑板/条件/finish事件/共享wait/counter/深复制/final-only；完整Buff会员、factory/birth/模式回收未闭合 |
| NPC消失/恢复 | 受限组件已实现 | float0.3隐藏/0.15Append颜色/停协程/DEFAULT→Move/当前格与空CP route恢复；Tween/FSM/事件modifier/非空CP/blocker等explicit providers |
| Unity物理查询接口 | 参数/阶段/版本化receipt已实现 | serialized声明与实际world pose分开；真实bounds/TransformVector/filter一致性/命中/同步/Simulate仍external |
| 场景规则预检 | 已实现 | 完整Transform子树、动态天赋/技能、隐藏箱子与召唤依赖；未知有效规则明确阻止完整图执行 |
| 路线等待 | 独立及cursor组件已实现 | FP max(0,remaining-dt)倒计时；99秒在资产dt下2971独立tick；cursor顺序由明确FSM和运行上下文驱动 |
| LegacyRandom | 独立组件已实现，跨语言参考对照通过 | 静态原生算法译写；inextp=31、unchecked int32；不等同System.Random；未接入battle RNG或声明探针 |
| FP运算 | 独立组件已恢复并有跨语言参考 | 有符号Q32.32，运算/转换遵循恢复的原生指令；不是运行中客户端oracle |
| 组预处理 | 独立Rogue默认分支已实现 | binary32权重、Range和LE epsilon；显式seed/order/retain计数，未证明真实run消费；通用pack组不支持 |
| 出怪时间 | 条件调度内核已实现 | RuntimeHandler嵌套first flag、serial queue、ties-even等待、自动预览、同键不稳定排序；mode hook排除，敌人属性/创建及门控依赖有来源的外部输入 |
| 按帧reset/step | TimelineEnv独立接口已实现 | current_frame/time_raw/pending/alive/gate；默认dt来自资产初值，runtime未验证；reward=None、battle_ready=false |
| 预定义装置 | 读取/引用校验及激活请求事件 | 祭坛已有普通目标受控伤害链；箱子反伤/触发、敌人模式联动和自动分支未恢复；两个分支仍仅支持显式external触发的受限形状 |
| 敌人属性 | 原生默认合并组件已实现 | 十个引用的精确等级、继承、默认、覆写、blackboard/skill/sp合并；45 primitive/34 Reset FP；动态entity效果、global Rogue/hotfix排除 |
| 选定属性乘数 | 独立运算已实现 | Single→FP multiply/clamp→Single与ties-even整数写回；显式选择字段，不推断Rune.Verify或完整实际run属性 |
| 敌人出场延迟 | 从实际预制体恢复 | 两种1秒/八种0秒、全部onlyDelayOnStartTile=false；notCount源于DB；post-Init存活计数条件仍external fixture |
| 完整战斗胜负/奖励 | 未实现 | deploy、skill及完整场景执行仍拒绝；单敌人默认模式有逻辑结束请求，未核验真实对局、未定义训练奖励 |
| 肉鸽战略流程 | 未实现 | 已读取主题和阶段表；节点、事件、商店、奖励概率和服务器依赖需另行确认 |

最新v9把选定NPC工厂、真实Buff会员/共享snapshot/Start与Finish、Entity/Unit受击反应、Finish7/death2与Scheduler清理接入同一对象。受控upeopl从第1帧BORN6到第2帧MOVE1；第10帧decoded modifier触发恢复/Finish7，同步UID0/event8使final归零且life3；独立death2使life2，声明的Single0.6延迟在第28帧回收。OwnerBorn12、Start0、PostBorn35严格分开，Entity Tick先FSM后Buff。原件49入口/109精确范围匹配，旧v8及更早pins不重写。完整ApplyModifier/HP、Unity物理/初始化副作用/override/audio/Tween/mode/global/非空路线和箱子仍有外部或拒绝项，完整图与训练仍未就绪。详见[v9报告](research/arknights-pc/native_v9/REPORT.md)。

~~~powershell
python -X utf8 scripts/probe_npc_pipeline.py
python -X utf8 scripts/verify_v9_snapshot.py
~~~

v9最终全量验证468项测试全部通过，0失败/错误/跳过；346文件pin、49新增原生入口/109原件范围一致；旧v8 290pins/136ranges、v7 310pins/190ranges、v6 323pins/358ranges保持不变。

最终全量统计见 artifacts/verification_v9.json；battle_ready/autonomous_route_ready/runtime_battle_validated仍false，reward=None。

历史v8最终全量验证383tests全部通过，0失败/错误/跳过；290固定filepins、72新原生入口/136原件ranges全部一致，旧v7 310pins/190ranges和v6 323pins/358ranges保持不变。

v8新增受限npc_actions/npc_restore/npc_summon及physics_context。动作Context/UID/条件/黑板prefix与floor整数、Finish事件，隐藏float等待/停止/DEFAULT→Move、空CP路线恢复、共享召唤与RouteData深复制现可执行；Unity、Tween、FSM/Move hooks、完整BuffContainer、factory/birth、mode/pool仍显式提供。受控ON_TAKE_DAMAGE10导致reason7与同步event4重入，当前fixture恢复两次但不构成通用会员遍历证明；lock0/Clear0/life3，另reason2的Dead.value=-1使life2。NPC HP/physics未计算，final成员保留1等待模式回收，完整图继续拒绝。

physics_context固定5prefab声明并只生成query参数/绑定external receipts：两次Unity bounds、CircleColliderOverlapFixed marker和外部TransformVector、28-byte CheckConsistency后filter、128buffer、epoch/fingerprint。Prefab不能自行建立runtime world pose、Rigidbody不能代替marker，UnityPlayer候选名称/函数数组未证明注册配对。新祭坛组合query210帧objects_fixed（可以Simulate前查询）、damage227、4325死亡/4343回收，物理命中仍fixture。新验证入口scripts/verify_v8_snapshot.py，数字见artifacts/verification_v8.json；三个ready/validated仍false、reward=None。

v7受控样例使用来源化准备和普通ALL，无外部ALL输出；18×500伤害令基础HP9000归零，第4325帧死亡、第4343帧回收。289项测试全部通过，310项v7文件pin/190段原件检查一致，旧v6 pins保持一致。物理碰撞、原生字段快照/零异常状态/空provider、mode/global/初始life仍显式给出。详细统计见artifacts/verification_v7.json。85个新增候选/190个原件范围属于静态选定覆盖，不等于85个行为完整实现。

历史v7 NPC执行接口调查：零延迟召唤也至少等1帧、选定dontBlockWave配置只入final、宿主恢复至NPC当前路线/位置、Finish7不触发death event3；正常InstantKill返回false后，要求previousResult的后置lock/Clear不执行，其同步回调不能靠后置lock保护。没有把这些节点拼成自动NPC战斗；完整图继续拒绝。

旧记录的名称须按v7更正：ALL的SortedSet实际为PriorityQueue；damage形状中旧unharmful标签对应BObject.isDisappeared+0x26，与Enemy.Options.unharmful不同。固定v6代码/报告保留原样，普通laxe fixture该门控false；新研究不能复用错误字段名推断NPC免伤。

全表中3条技能引用缺失（本图预定义单位未受影响）：`trap_755_cdsoul`→`sktok_cdsoul`、`trap_332_blkcan`→`sktok_blkcan`、`trap_338_almytw`→`sktok_almytw`。不声称当前快照覆盖全部游戏技能。

坐标证据文件：`D:\Repo\.rea-tools\arknights-pc\native_v2\focused_results_round2.json`。`MapData.get_Item`：`0x18241d270`、`0x18241d1e0`；`get_height`：`0x18241d300`；`get_width`：`0x18241d330`。目标 `GameAssembly.dll` SHA-256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。这确认该快照的坐标索引计算；函数名称由元数据/指针表推定并与PE unwind入口相互支持。

核验产物：`artifacts/verification.json`、`artifacts/tests.txt`、结构/声明/拓扑/SVG、RNG参考与两模式条件时间轴。以verification内的tests_run/failed/skipped为准；包含非对称坐标回归、原生同键排序、首次空子协程、先yield的WaitWhile、实际地图串行出怪/预览及不会自行解除的闸门。原始矩阵视图仅用于存储诊断。

v6最终全量验证248项测试通过，0失败/错误/跳过；323项v6文件pin和358段原件字节检查一致，既有v5的94个组件文件及9个帧源pin保持一致。167个选定候选入口中1个因处于既有PE函数体内部而被排除，166个接受入口不等于166个行为完整实现。全部独立C#对照、静态源字节检查与真实客户端轨迹核验分别记录。

受控`altar_component_external.json`：一个静止普通敌人，资源基础HP 9000，祭坛18次各500伤害，第227帧首次扣血、第4121帧死亡、第4139帧回收并请求样例逻辑win，生命3不变。碰撞结果、ALL顺序、初始化后准备参数、运行宿主与无其他控制模块均为显式fixture；未使用外部resolve/recycle直接终结敌人，也未连接原图scheduler。该结果不是完整“猎犬病原”对局。`route_lifecycle_component.json`仍是独立的单敌人路线fixture，`scene_*_audit.json`保留两模式完整场景缺口。

晋级为训练组件前，应有：固定客户端版本及算法地址、输入输出定义、代码/指令证据、边界测试、和实际对局或可信参考轨迹核验。现有探针测试通过不能代替战斗等价性验证。

LegacyRandom证据：`native_v2/focused_results_round3.json`；有种子构造`0x186505240`，Sample`0x1860e0e90`，Next`0x1860e0e40`，Next(max)`0x186505190`，Next(min,max)`0x186505090`，有种子RandomFactory`0x1867323a0`。组件覆盖int32 seed、基本采样、非负max和不溢出的窄范围；宽范围主动拒绝。独立C#参考向量及后续客户端/热修补运行时对照属于不同验证层次，不能相互替代。

独立C#跨语言实现对照已通过，报告为 `artifacts/rng_reference_comparison.json`。8种子：1,024个Next整数、Sample/NextDouble各128次binary64位比较、64个Next(max)、56个Next(min,max)、8次后续采样顺序检查，共1,408项输出精确比较；8组参考中的System.Random序列均与LegacyRandom不同。源码SHA-256=`3f3daa216291e2b54466094f95706ac7cfa857db53950af7334edc04a2f13627`，向量SHA-256=`642f90baf3ed87c29c340eda5c71e9906449fc7a09e14cc61865d61de538bf02`，原生报告SHA-256=`f48a1ac56f11064265e0ebb7dbc12f7815f180e36a00e9d64a53a4febb568a72`。这不能称为真实客户端金标准：没有运行游戏或验证热修补分派，`battle_ready=false`，声明探针仍不消耗LegacyRandom。

本轮整体进展见 [PROGRESS-2026-10-13.md](research/arknights-pc/PROGRESS-2026-10-13.md)；历史第一轮检查见 [REPORT.md](research/arknights-pc/REPORT.md)。

最新原生总报告：[native_v9/REPORT.md](research/arknights-pc/native_v9/REPORT.md)。历史v8：[native_v8/REPORT.md](research/arknights-pc/native_v8/REPORT.md)。历史v7：[native_v7/REPORT.md](research/arknights-pc/native_v7/REPORT.md)。祭坛旧条件组件见[native_v6/REPORT.md](research/arknights-pc/native_v6/REPORT.md)，移动/生命周期与资源闭包见[native_v5/REPORT.md](research/arknights-pc/native_v5/REPORT.md)，敌人合并与初步寻路见[native_v4/REPORT.md](research/arknights-pc/native_v4/REPORT.md)，FP/调度见[native_v3/REPORT.md](research/arknights-pc/native_v3/REPORT.md)。独立数值参考与原件范围校验分别记录，未运行游戏。

调度依据在`native_v3/timeline/results_round2..6.json`，字段偏移/类型与时钟在`native_v3/fixedpoint`；选定来源散列保存在`evidence/timeline/provenance.json`。关键地址：RuntimeHandler.MoveNext `0x18065ff70`、StartCoroutine `0x18065d200`、serial队列 `0x18094e650`、等待舍入helper `0x18059e290`、排序 `0x184547860`。该等待helper曾被临时标签称作CeilToInt，实际反编译/指令显示nearest ties-even，命名不能替代行为证据。队列比较器只比较float time，同键会交换，即使仅2项也不稳定。

条件示例清楚区分三种输入：NORMAL/FOUR_STAR的hidden组来自本图runes；random组来自显式原actionIndex选择；extraSpawnDelay/notCountInTotal/创建成功来自带来源的fixture。示例没有模拟击杀。`external_release_wave`不清除final；`external_recycle`不清除wave；killed/missed输入仅为已经完成两者的外部终结fixture。最终external完成闸门不等于游戏胜利。

新增 `timeline_*_resolved.json` 将前两个runtime字段换成已恢复的DB/预制体值，保留明确的post-Init eligibility fixture。旧zero fixture保留作独立调度参考。祭坛选定准备路径、普通ALL与普通目标伤害已接入受控组件；完整Unity初始化/真实物理/动态provider与状态、sandbox扩展、NPC召唤与箱子联动仍未闭合，因此`autonomous_route_ready=false`、`battle_ready=false`、`runtime_battle_validated=false`。
