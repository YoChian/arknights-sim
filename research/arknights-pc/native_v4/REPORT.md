# 猎犬病原：敌人属性、预制体与原生移动组件

2026-10-13。已将敌人默认/继承/覆写、数值属性运算、实际预制体出场延迟和独立原生路径组件接入 `D:\Repo\arknights-sim`。**当前有可运行的规则组件与条件时间轴；自动移动→漏怪→回收→整关结束尚未闭合，不能进行完整战斗训练。**

本机 PC 快照：`D:\Hypergryph Launcher\games\Arknights`，资源版本 `26-09-13-15-28-10-30688348`。`GameAssembly.dll` SHA-256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`；metadata SHA-256 `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`。

## 实际实现与验证

| 内容 | 本阶段结果 | 使用边界 |
| --- | --- | --- |
| 敌人数据 | 十个引用、20个数据库等级记录；45个解码值、34个Reset FP属性 | 动态entity effects与真实肉鸽全局修饰未应用 |
| 等级/覆写 | 精确命中、原序继承、默认构造、逐字段defined gate、BB/skill/sp合并 | 当前只开放本图 useDb=true |
| 选定乘数 | Single→FP multiply/clamp→Single/整数写回→Reset | 字段选择必须明确；Rune.Verify与实际run修饰选择未恢复 |
| 出场延迟 | 两种敌人1秒，其余八种0秒；从shipped prefab读出 | hotfix override为空、onlyDelayOnStartTile=false的默认分支 |
| 条件时间轴 | 新示例从DB/prefab导出delay与notCount | post-Init存活计数条件仍为明确外部fixture；无自动闸门解除 |
| 移动组件 | FP WAIT、Single局部几何/归格、weighted FIFO/SPFA、Bresenham/corner/mask、路线图编译 | 需要完整明确的缓存格子状态；不是完整移动控制器 |
| 验证 | 模拟器111项测试通过；资源15项测试通过；独立C#数值/路径对照通过 | 独立转写参考不是运行客户端oracle |

测试结果为 **111 passed、0 failures、0 errors、0 skipped**，记录在 [verification.json](../../../arknights-sim/artifacts/verification.json) 和 [tests.txt](../../../arknights-sim/artifacts/tests.txt)。数值参考629 cases；移动参考60组几何/480比较、29组路径/1080节点快照/348射线判断。此前FP、RNG、排序及协程参考也通过本次整体验证。

六份完成的 Ghidra 报告共161个选定唯一入口，346个导入范围与原件逐片字节散列一致。范围包括全部递归 `UNW_FLAG_CHAININFO` sibling，以及明确标记的有界leaf；名称仍是metadata/native候选关联。**161不是已恢复规则数，也不表示函数的所有依赖已闭合。** 中断的movement round1不参与统计，诊断记录保留。分析使用已配置Ghidra CLI及Capstone；这些输出不是REA MCP Evidence ID。原件七个固定文件重新核对全部一致，详情见 [summary.json](summary.json)。

## 决定实现方式的结论

`EnemyDB.TryGet`默认入口 `0x18200bb60` 先调用 `GetComputedEnemyData`，再对非null `overwrittenData`执行 `ApplyDefinedData`。非负等级必须精确存在，继承依资源原序并在更高等级处停止；不排序、不插值。未定义值跳过，定义的零/false仍覆盖。

`enemy_3001_upeopl` 的未定义法抗取构造默认0，基础攻击间隔取默认1。`enemy_2133_shdopl` 的关卡overwrite虽然包装字段全未定义，仍含有效 `summon.enemy_key=enemy_3001_upeopl`；此blackboard层必须应用。Runtime属性使用ObscuredInt/Float，数值转换经过Single；不能直接将数据库整数位移到FP。范围来自真实v29 AttributeMeta构造参数，HP最低1、移速最低Single(0.1)、MR限制0..100。

选定属性乘数使用原生FP路径，整数写回采用ties-to-even。例如3×0.5写成2，5×0.5也写成2；Single精度和CVTT int32溢出行为另有参考向量。紧急关卡BB的1.2/1.4是Single乘数输入；示例明确选择atk/maxHp，不宣称包含实际run所有修饰。

`Scheduler._CreateEnemyItem` `0x180919a20` 临时创建敌人预制体、clone数据、RuneManager预处理、game mode预处理、读取 `get_delayToBorn`，然后回收临时预制体。getter `0x180a7c370` 在onlyDelayOnStartTile=false且hotfix为空时读取Enemy+0x310。实际 `enemy_2133_shdopl`、`enemy_2152_shezlc`为1秒；八种其他敌人为0，十种flag均false。

预制体能读不等于实际创建后alive。普通 `Entity.get_alive`还要求StateMachine currentId>0且状态已注册，以及HP.raw>**42950**（MathUtil.EN5），不能只用HP>0。Entity.Init从虚表slot81的maxHp开始初始化HP。计数条件与Unity工厂/状态初始化仍需实际闭包或带来源fixture。

普通位置、路线方向和移动量主要使用Unity Vector2/Single；WAIT使用FP倒计时。当前资产dt下独立99秒WAIT需2971次减量，调度nearest舍入等待不能替换它。路径是加权反向FIFO relaxation，按严格小于更新，随后依原行列顺序平滑；corner和单向goto mask影响可达性，不等同四邻BFS或普通line-of-sight。

## 地图设备影响第一里程碑

本图 `trap_011_ore#1` 初始可见，坐标(row5,col6)，技能`sktok_ore`，声明时间SP成本7、value500，Ability preDelay为Single(0.6)。`ore_s`模板配置为检查ore_immune后纯伤害；`ore_buff`为特殊敌人mode切换。祭坛TrapMode还配置 `rewriteTileOptions=true`、`passableMask=2`。

这些是实际资源配置证据，执行时机、范围、modifier结算和缓存更新尚未恢复。**没有干员仍有设备战斗与地图变化。** 条件静态tile fixture排除了祭坛和箱子，只用于独立路径核验；其中28条主WALK路线可编译不表示真实缓存地图或无人操作战斗已一致。38条主路线中的前10条E_NUM仍只作合法占位处理；另有2条extra WALK路线。

Enemy.FinishMe(REACH_EXIT=1)、game-mode漏怪回调、生命Modifier、事件消费和延迟回收属于不同环节。当前level maxLifePoint99也不能当作真实肉鸽run剩余生命；不得在漏怪时直接杜撰final解除或胜利。

## 继续实现入口

已接受的顺序继续保留：敌人/创建→无人操作自动关卡→基础干员战斗→轨迹验证/训练接口→技能与肉鸽战略层。当前优先闭合Tile.Init/cache及设备改格、移动控制器/真实位置赋值、cursor/出口许可、漏怪/生命/回收与最终门控。随后接部署、阻挡、普通攻击和伤害。`battle_ready=false`、`autonomous_route_ready=false`维持到对应行为接通并核验。

代码与证据：

- [enemy_data.py](../../../arknights-sim/arknights_probe/enemy_data.py)、[属性报告](attributes/REPORT.md)、[数值证据](../../../arknights-sim/evidence/enemy_data/REPORT.md)。
- [enemy_rules.py](../../../arknights-sim/arknights_probe/enemy_rules.py)、[enemy_creation_inputs.py](../../../arknights-sim/arknights_probe/enemy_creation_inputs.py)、[输出属性](../../../arknights-sim/artifacts/enemies_resolved.json)。
- [movement.py](../../../arknights-sim/arknights_probe/movement.py)、[移动证据报告](../../../arknights-sim/evidence/movement/REPORT.md)、[路径条件清单](../../../arknights-sim/evidence/movement/path_inventory.json)。
- [资源/真实布局报告](resources/REPORT.md)、[prefab_inputs.json](resources/prefab_inputs.json)、[ore_buff_templates.json](resources/ore_buff_templates.json)。
- [README](../../../arknights-sim/README.md)、[HANDOFF](../../../arknights-sim/docs/HANDOFF.md)。

全程没有启动游戏、注入或修改客户端、执行目标反序列化代码、连接游戏服务。只执行自有分析与参考/原型程序；所有本阶段拥有的Ghidra运行已结束，无目标运行时会话待关闭。
