# 随机组预处理：静态追踪

> 调查时点记录。后续已恢复 weighted helper、binary32 Range、epsilon 比较和 getter，并建立独立组件；最新实现及保留的上下文限制见 [阶段报告](../REPORT.md) 和原型能力记录。

当前更新：Round4/5与getter原始指令已补齐；下文保留Round2调查记录，列出的“待恢复”不要当作当前状态。独立实现已在`D:\Repo\arknights-sim\arknights_probe\preprocess.py`，调度入口仍使用明确外部原actionIndex选择，不能把独立seed实验当真实对局的RNG状态。

已证明weighted helper `0x1845951b0`按Single累加、Range float `0x181a96e30`先把NextDouble转binary32，再分别binary32减/乘/加；逐项判`draw <= binary32(weight + binary32(1e-5))`，否则binary32减weight，最后回落last。空helper列表仍消费NextDouble，但Rogue外层先检查候选非空，因此过滤后空组不消费。权重getter `0x1808eb4c0`是int32→binary32，`0x1808eb4d0`直接读取已累计float。

DefaultSchedulerPreprocessor默认原生无热补时no-op；General调用的`0x18001bd60`是generic virtual dispatch bridge，不是另一个已证明的weighted core。独立实现只支持当前Rogue/ALWAYS/无pack组，不能把它冒充General或其他refresh语义。

分类来自topic.gameConst.mimicEnemyIds与goldChestTrapId，经GetPredefinedTokenKey只扫描predefines.tokenInsts别名。RoguelikeInput.meta是内嵌value type（input+0x38），构造把meta.chestCnt/goldTrapCnt（input+0x48的8字节）复制为retainData.mimicEnemyCnt/goldTrapCnt；不能解引用meta或推断计数初始值。两计数和group_order均为强制外部输入。

独立测试包含epsilon边界、float staging、空/零权重消费与preserve过滤；mimic_count=0/gold_count=0会将c1四个mimic候选移除，仅EMPTY留存；mimic_count=1时EMPTY仍可胜出，不能声称保留组就保证出场。没有实际client/hotfix/RNG消费轨迹对照。

以下为历史Round2记录。原件nested_types互证的37类型字段/参数见`metadata_declarations.json`。

## 共有行为

RoguelikeSchedulerPreprocessor.DoPreprocess（0x1808f8240）与RandomGroupSchedulerPreprocessor.DoPreprocess（0x18094a310）遍历waves→fragments→actions。参与组的类型为原生0/6/13（本图SPAWN/ACTIVATE_PREDEFINED/EMPTY），且randomSpawnGroupKey非空。**组键为(waveIndex,fragIndex,randomKey)**，不能跨wave或fragment合并同名字符串。

RandomActionPtr记录actionIndex、weight、isEmpty（action.key空值检查）、递增order。原生action weight读取+0x58、key+0x18、组字符串+0x40。通用RandomGroup版本复制packKey(+0x48)；Rogue版本此处不复制packKey并有初值true的retainFlag。字段对应关系由元数据交叉核对，偏移来自具体读写，不按字段排列猜测。

每个普通非空候选列表抽一个指针。selected.isEmpty=false时先从候选列表移除这个指针，余下全部加入待删除列表。因此选中非空key项会留下，而选中空key项会令整组声明删除。这是**动作数据筛选**，并不代表已经发生SPAWN。随后反向遍历wave/fragment/action并删去原索引，必要时替换actions数组；待删除列表排序与容器枚举顺序仍需helper核验。

## Rogue路径

随机源是RoguelikeGameMode.randomRogueScheduler，不是BattleController.randomImp。retainData为mimicEnemyCnt与goldTrapCnt两个int。

任一retain计数为负时进入一般组选择：`FUN_1845951b0(rng,list,MethodInfo)`返回选中ptr。尚未读到helper，无法确定整数/浮点累计、阈值边界、零总权重/null语义及采样次数。

两计数非负时还有分层处理：从聚合mimicEnemyGroups/goldTrapGroups按totalWeight抽取指定数目的组，每次移除所选组并加入集合；根据“是否mimic敌人/是否goldTrap/所在组是否入选”写retainFlag，将false项移出列表后，再回到一般组选择。不能简化为t1/t2/c1原权重的一次抽样。

分类由CheckIsMimicEnemy(key)、GetPredefinedTokenKey(levelData,action)、CheckIsGoldTrap(characterKey)决定。判别函数和retainData构造来源仍待恢复，不能按名字把所有箱子或稀有敌人归入这些类别。入口有XLua替代路径，默认原生分支未代表真实客户端的当前分派。

## 通用RandomGroup路径

开头调用DefaultSchedulerPreprocessor.DoPreprocess（0x1809457d0），默认runtime字段/过滤规则需先确认。随后获取BattleController.randomImp并调用`FUN_18001bd60(MethodInfo,rng,list)`。

删除带非空packKey的候选时，把packKey加入集合，再删同fragment具有该packKey的其它action；最后遍历所有fragment移除空action.key。当前图缺少packKey字段，不代表完整算法可以忽略它。

两入口主体都未直接读取randomType(+0x50)或refreshType(+0x54)。本图均ALWAYS；不能认定PER_DAY/NEVER等无效，它们可能由默认预处理或调用层处理。ActionData.Duplicate/ctor与DefaultPreprocessor待证。

## 本图影响

组为(0,0,t1)、(0,0,t2)、(2,0,c1)，原索引分别0..4、5..9、0..4，原weight总1040/1040/105。空key哨兵参与选择且可能令组无动作，不能先删去哨兵再选。

这些证据支持后续独立预处理组件，或者标注来源的external choices保留控制；不能把外部选择冒充客户端RNG输出。代码的局部遍历顺序也不能代表整个游戏的RNG消耗顺序；Rogue专用随机源初始状态和其它模块消费未知。

## 最小下一批需求

| 地址/方法 | 待回答问题 |
| --- | --- |
| 0x1845951b0，无CodeGenModule别名 | Rogue带权核心：累计精度、阈值、随机调用次数 |
| 0x18001bd60，无CodeGenModule别名 | 通用RandomGroup的generic桥接实际callee |
| DefaultSchedulerPreprocessor.DoPreprocess 0x1809457d0 | runtime初值、randomType/refreshType处理 |
| RoguePreprocessor.ctor 0x1808f9a40 (idx71835) | retainData与topic来源 |
| GetPredefinedTokenKey 0x1808f98f0 (idx71837) | 别名→预定义characterKey |
| CheckIsMimicEnemy 0x180d095f0 (idx85538)；CheckIsGoldTrap 0x180d094f0 (idx85539) | 特殊候选分类 |
| RandomActionPtr.get_weightValue 0x1808eb4c0；RandomGroupWeightData.get_weightValue 0x1808eb4d0 | 权重接口精度 |
| RandomActionPtr.CompareTo 0x1808eb470 | order与删除顺序 |
| ActionData.Duplicate 0x182416340 (idx31530)；ctor 0x1824163f0 (idx31531) | Clone与runtime字段初值 |
| get_randomRogueScheduler 0x180c57e50 (idx82788) | 随机源实例/种子路径，不只getter名字 |

lookup.py查询前两地址在四个核心CodeGenModule候选图中无别名，需显式VA+PE unwind范围定位，不能编造方法身份。
