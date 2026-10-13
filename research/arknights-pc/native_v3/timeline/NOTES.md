# 猎犬病原：出怪时间轴的语义待证清单

> 这是恢复前的调查清单，保留用于追溯。后续已恢复的定点数、队列、等待和门控见 [最新报告](../REPORT.md)；剩余限制以该报告与原型能力记录为准。

本文件对应 `map_inventory.json` 与 `metadata_declarations.json`，所有内容来自本机静态资源/元数据；没有启动游戏。这里尚未编译绝对时间轴，所有 `absolute_time` 明确保留为 null。

## 地图声明与引用

输入 `resources_v2/normalized/level_rogue6_1-1.json`。7×11 地图，随机种子字段 `1808733512`，38 个主 action、两个各含一个 action 的分支，38 个主 route、两个 extra route，10 个 EnemyDB 引用。全部 action 均 `count=1`、`interval=1`、`managedByScheduler=true`；`blockFragment`、`dontBlockWave`、`forceBlockWaveInBranch` 均 false。

| wave | fragment | fragment.preDelay | 声明 |
| --- | --- | --- | --- |
| 0 | 0 | 0 | 10个ACTIVATE_PREDEFINED，分为t1/t2两个候选组 |
| 1 | 0 | 0 | 17个SPAWN：12个空值体、2个屠夫、3个雇佣军萨卡兹术师候选；其中6个有normal/raid隐藏组 |
| 1 | 1 | 7 | 1个normal动作preDelay=20；5个shsdgo*隐藏组动作preDelay=80 |
| 2 | 0 | 0 | c1的4个SPAWN候选及1个EMPTY候选 |

三个 wave 的 `preDelay=0`、`postDelay=0`、`maxTimeWaitingForNextWave=-1`。这些字段尚不能直接相加成绝对秒数。尤其要检查：fragment延时参考哪个时钟；action执行队列是否并发；最后一个count=1的SPAWN是否仍等待interval；wave结束是否依赖managed敌人外部死亡/漏怪。

## 隐藏组与难度

地图 rune 数据声明：NORMAL 的 `level_hidden_group_enable` 指向 `normal`；FOUR_STAR 指向 `raid`；FOUR_STAR 的 `enemy_attribute_mul` 有 `atk=1.2`、`max_hp=1.4`。这些是规则数据字段，rune执行器与调用顺序仍需代码证明。

| hiddenGroup | 主action数量 | 声明时序字段 |
| --- | --- | --- |
| normal | 4 | 3个preDelay=0；1个preDelay=20在fragment1 |
| raid | 3 | preDelay=0 |
| shsdgo | 1 | preDelay=80 |
| shsdgo4 | 2 | preDelay=80 |
| shsdgo3 | 1 | preDelay=80 |
| shsdgo2 | 1 | preDelay=80 |

shsdgo*未出现在本图三个rune的启用值中，不能默认放行。需检查run retain data、肉鸽保密等级、藏品或模式预处理是否传入额外组。主题表的 `modeDifficulty`/`grade` 与关卡记录的 `difficulty=NORMAL/FOUR_STAR` 是两个独立字段，不能混成同一个枚举。

主题的两个stage记录：`ro6_n_1_1`（NORMAL）与`ro6_e_1_1`（FOUR_STAR，linkedStageId指向普通版本）；二者均指向同一个level，`boxProb=[0.2,0.2]`、`capsuleProb=0`、`redCapsuleProb=0`。如何覆盖预处理权重仍待证。

## 带权随机候选与预定义装置

t1/t2各有5个声明：空key权重850，普通箱105，其他箱35/35/15，总权重 **1040**。c1四个SPAWN各权重5、EMPTY权重85，总权重 **105**。不能按百分数理解，也不能直接用这些权重和Python随机库推导真实选中结果。必须恢复具体preprocessor、retain数据、候选遍历顺序、过滤、draw区间与随机数消耗。

predefines中有9个token实例。`trap_011_ore#1` 源石祭坛；其余8项为箱子候选，其中部分别名跨两个点成组。两个 `trap_323_shsbox#1/#2` 的技能覆盖blackboard含 `branch_id=shsbox1/shsbox2`，两条引用均存在于branches。branches每条有一个SPAWN `enemy_2152_shezlc`，routeIndex对应extraRoutes。**只有引用关联已经确认；箱子被激活、击破或其他事件触发分支的时间与条件尚未恢复。**

## 元数据关系与原生定位

直接读取原件 `global-metadata.dat` 的92字节定制type记录、nested_types表、fields表和parameters表。完整输出37个相关类型的字段顺序、TypeIndex、token、方法metadata index、参数名与候选地址；未猜native field offset。

raw nested_types确认：`Torappu.Battle.Scheduler` 的typeDefinition index为10886，其子类/协程包含DefaultWaveHandler（10858）、DoSchedule（10859）、DealWave（10862）、DealFragment（10864）、DealBranchPhase（10865）、DoSpawn（10867）。DefaultWaveHandler又拥有WaitForPredelay（10855）、WaitForPostDelay（10856）、ExecuteActionQueue（10857）。声明关系以nested表为准，避免namespace为空或同名类混淆。raw declaring_type值是父类的native TypeIndex（如73794），不是metadata index10886。

LevelData index4680→WaveData4666→FragmentData4664→ActionData4662关系同样由原件nested表确认。ActionData的24字段包括JSON里缺省的runtime字段：`useExtraRoute`、`randomSpawnGroupPackKey`、`isValid`、`notCountInTotal`、`extraMeta`、`actionId`。其默认值与预处理写入语义需单独恢复；缺省JSON字段不能擅自当作显式false。

Scheduler.Init（`0x1809135c0`）参数名：`driver, subIndex, levelData, waveHandler, enabledHiddenGroups, disabledHiddenGroups`。静态默认分支清空/加入/移除隐藏组，构造enemyMap、统计通过CheckActionEnabled的SPAWN数并配置分支/执行器；入口有XLua替代路径。Scheduler.Reset（`0x180914d40`）也有XLua替代入口，并重置计数/队列。它们证明初始化有关门控，不能证明延时推进。

优先调查实际协程MoveNext与队列执行器：

| 方法 | metadata method index | token | 候选VA |
| --- | --- | --- | --- |
| Scheduler.<_DoSchedule>d__117.MoveNext | 72199 | 0x6011a08 | 0x180953720 |
| Scheduler.<_DealWave>d__121.MoveNext | 72219 | 0x6011a1c | 0x180951ed0 |
| Scheduler.<_DealFragment>d__122.MoveNext | 72230 | 0x6011a27 | 0x180951a70 |
| Scheduler.<_DealBranchPhase>d__123.MoveNext | 72236 | 0x6011a2d | 0x180951450 |
| Scheduler.<_DoSpawn>d__126.MoveNext | 72248 | 0x6011a39 | 0x1809547a0 |
| DefaultWaveHandler.ExecuteActionQueue.MoveNext | 72193 | 0x6011a02 | 0x18094e650 |
| DefaultWaveHandler.WaitForPredelay.MoveNext | 72181 | 0x60119f6 | 0x180950f50 |
| DefaultWaveHandler.WaitForPostDelay.MoveNext | 72187 | 0x60119fc | 0x180950bb0 |

其它关键入口：`CheckActionEnabled 0x180912b50`、`_CheckWaveNotFinish 0x180919900`、`_CheckFinalNotFinish 0x1809196f0`、`_OnActionExecuted 0x18091baf0`、`_DealAction 0x180919fb0`、RoguelikeSchedulerPreprocessor.DoPreprocess `0x1808f8240`、RandomGroupSchedulerPreprocessor.DoPreprocess `0x18094a310`。

`_DealAction` 参数名明确为 `action, fragmentPreDelay, enemyMap, actionQueue, blockCounter, fromBranch`，很可能是计算queue time与计数的连接点，但其公式需由伪代码证明。现有Ghidra自动标签可能选中共享地址的其它方法名；例如Init中的 `0x1809427a0` 同时是BranchRuntime ctor候选，不能凭首个候选标签ActorStatusNone推断对象类型。

## 可运行时间轴的最低验收条件

1. 从MoveNext/DealAction/ExecuteActionQueue恢复时间基准、比较符号、同tick多事件顺序、frame更新与yield语义；采用已恢复FP原始整数运算，不以float累加替代。
2. 显式stage NORMAL/FOUR_STAR上下文和隐藏组来源；未恢复的预处理/随机选择给出具体闸门。允许外部提供候选选择时必须标注为external input，不能称为客户端随机结果。
3. wave门控只能由外部finish/kill/leak输入或真实恢复逻辑释放；原型不能自己编造伤害/死亡。外部事件必须记录时间和来源。
4. 支持当前图安全的SPAWN/EMPTY/ACTIVATE_PREDEFINED调度事件；激活记录不能冒充装置伤害或分支触发。
5. 无法自主确定分支时输出pending branch gate，保留extraRoute与phase上下文；没有证据时不自动触发。
6. reset/step时间轴与旧DeclarationProbeEnv保持独立；即使出怪时间轴可运行，也保持battle_ready=false直到完整战斗轨迹通过核验。
