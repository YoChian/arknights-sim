# 猎犬病原：敌人、符文和路线输入证据

本阶段已整理可以交给属性与移动恢复使用的精确资源输入和真实字段布局。全部检查只读取本地文件；没有启动游戏、执行目标代码、读取运行进程或连接游戏服务。本文的属性数值是资源声明，不是已经应用等级合并、难度符文、运行时增益后的战斗属性。

## 固定的来源

- PC 资源版本：`26-09-13-15-28-10-30688348`。
- `GameAssembly.dll` SHA-256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。
- `global-metadata.dat` SHA-256：`d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`，v29，客户端 type definition 为 92 字节。
- 关卡容器 `anon/caad29dcbd04e9fe792738e72138a607.bin`，资产 `dyn/gamedata/levels/obt/roguelike/ro6/level_rogue6_1-1.bytes`。原容器 SHA-256 `c6d00b3a1f6ba2d4827b2e84fd716a94cac88eda621aa5ff2f6f4cd8935639b5`；去掉 128 字节签名头的 16,824 字节 FlatBuffer SHA-256 `b12827d858fe120d3107599a299c7844742a3c14c1b08acd9ecf88aeddb7d771`。
- 敌人数据库容器 `anon/2cf2925f117519f466da84a2c0164de7.bin`，资产 `dyn/gamedata/levels/enemydata/enemy_databasea5b667.bytes`。原容器 SHA-256 `e41e9f8f3cdc754099aa4c478a8f13be917ea153fafa5373459cce58d03a9386`；2,178,056 字节 FlatBuffer SHA-256 `c7afd87c238e275565285ffb997d8ae13f5fdac09bdbf7784f2152f30f564c18`。

`inventory.json` 记录源文件、解析文件、schema、原件容器与脚本的路径和哈希。此前资源格式与验签证据保留在 `resources_v2`。schema 来自 [MooncellWiki/OpenArknightsFBS](https://github.com/MooncellWiki/OpenArknightsFBS/tree/dbbc98306982259956f271b71c7fb63a05cdd5d5)，commit `dbbc98306982259956f271b71c7fb63a05cdd5d5`；schema 字段名与运行语义分开验证。

本次重新对两个 FlatBuffer 的所有可达字段作边界、类型和未知字段检查：敌人库 128,838 个表、7,390 个向量、21,448 个字符串、87,255 个标量；没有已填充却不在 schema 的字段。关卡也完整通过原有严格 verifier。又从二进制直接读出本图全部关卡和 10 个敌人的 20 个等级记录，保留 Single 的原始位和字段是否真的存在线上数据中。与旧 flatc JSON 比较有 31 个十进制显示差异，但 0 个 float32 位差异。

## 敌人等级与可选字段

全部 10 个 `enemyDbRefs` 都是 `useDb=true`、`level=0`，且数据库中均精确存在该等级。

| 引用 | 序列中的等级 | 等级 0 的 HP / ATK / DEF / MR | 等级 0 的移速 / 攻速 / 基础间隔 |
|---|---|---|---|
| enemy_2001_duckmi | 0,1,2 | 18000 / 100 / 200 / 30 | 0.4 / 100 / 1 |
| enemy_2085_skzjxd | 0,1,2 | 50000 / 500 / **有效 0** / 50 | 0.35 / 100 / 1 |
| enemy_2002_bearmi | 0,1,2 | 30000 / 2000 / 200 / 50 | 0.5 / 100 / 3.5 |
| enemy_2034_sythef | 0,1,2 | 8000 / 300 / 150 / 20 | 0.8 / 100 / 2 |
| enemy_2152_shezlc | 0,1,2 | 10000 / 600 / 500 / 30 | 0.7 / 100 / 1 |
| enemy_2133_shdopl | 0 | 5000 / 320 / 100 / 20 | 1.5 / 100 / 1.4 |
| enemy_1034_laxe | 0 | 9000 / 850 / 230 / 30 | 0.7 / 100 / 3.5 |
| enemy_1085_sotiwz_3 | 0 | 7000 / 350 / 400 / 50 | 0.75 / 100 / 5 |
| enemy_3001_upeopl | 0 | 3500 / **有效 0** / 50 / **未定义** | 0.65 / 100 / **未定义** |
| enemy_2137_shsdgo | 0 | 18000 / 280 / 300 / 20 | 1.3 / 100 / 1.8 |

表内小数为方便阅读的表示，精确的 Single 值见 `exact_resource_inputs.json` 和 `wire_fields.json`。例如 0.4 实际为 `0.4000000059604645`。`enemy_3001_upeopl` 的 MR 与基础攻击间隔存储占位 0，却有 `m_defined=false`；不能据此产生有效零。其 ATK 的 `m_defined=true`，故 ATK=0 是有效输入。

数据库共有 2,181 个敌人 ID、2,445 个等级记录：1,940 个只有一级、218 个两级、23 个三级。所有列表的顺序恰为 `[0..n-1]`，无重复等级、乱序或缺级。这里验证的是资源可用性和顺序；原生 `GetComputedEnemyData` 的精确命中、按原序合并与提前结束规则由 `native_v4/attributes` 独立恢复，不从这个分布反推算法。

`inventory.json` 对每个敌人、每个等级提供全部 32 个 attribute 包装字段与 12 个顶层包装字段的定义矩阵，保留 `undefined`、`defined`、缺失包装对象、缺失引用值之间的区别。所选 20 行中有 28 个有效数值零及 29 个有效 Boolean false。这些值必须参与 `ApplyDefinedData`，不能用真假判断删除。FlatBuffer 未存放的标量 slot 采用 schema 的零默认；`wire_fields.json` 单独记录 `wire_present=false`，它与 `m_defined` 是不同层面的状态。

唯一有 `overwrittenData` 的引用是 `enemy_2133_shdopl`。它所有包装字段均未定义，甚至 name/description/prefabKey 有可读字符串仍标记未定义。然而它的非包装 `talentBlackboard` 存在：`summon.enemy_key` 的 `valueStr` 为 `enemy_3001_upeopl`，数字值为有效 wire/default 0。不能因包装字段全 false 就舍弃整个 overwrite。没有出现的 `skills` / `spData` 仍保留缺失状态。

## 普通与紧急符文输入

关卡资源有 3 条 rune，`optionalRunes` 缺失：

| difficultyMask | key | blackboard |
|---|---|---|
| FOUR_STAR | enemy_attribute_mul | atk=1.2，max_hp=1.4 |
| NORMAL | level_hidden_group_enable | key 的 valueStr=`normal`，数字值 0 |
| FOUR_STAR | level_hidden_group_enable | key 的 valueStr=`raid`，数字值 0 |

三条 rune 的 professionMask 都是 1023、buildableMask 都是 ALL。乘数的二进制 Single 分别为 `0x3f99999a`（`1.2000000476837158`）与 `0x3fb33333`（`1.399999976158142`）。原始 Options 的 `moveMultiplier=0.5`、`steeringEnabled=true`、`reachableCheckIgnoreStartTile=false`；这些是移动恢复的必要输入。

这个资源样本没有 NORMAL 的属性乘数条目。模式筛选、FP 转换、Clamp、其他模式或外部 rune 叠加和先后顺序需要原生证明，本文不把声明直接当成最终属性。

## 路线和 checkpoint

保留 38 条主 `routes` 和 2 条 `extraRoutes`，合计 134 个 MOVE 与 24 个 WAIT_FOR_SECONDS checkpoint。`inventory.json` 提供每条完整结构及 action 引用位置；`exact_resource_inputs.json` 保留原始关卡结构和精确浮点。

主 route 0..9 都是 `motionMode=E_NUM`，start/end `(row=0,col=0)`，没有 checkpoint 向量，对应主流程的 `ACTIVATE_PREDEFINED`。它们不能当作十条敌人移动路线。主 route 10 的 start `(3,6)`、end `(3,0)`，包含 MOVE `(3,6)`、WAIT_FOR_SECONDS 99 秒、MOVE `(3,1)`；WAIT 节点仍存有 `(0,1)` position，这个字段不能无条件当作移动目标。两个 extra route 都是 WALK：分别从 `(5,1)` 经 `(5,5)/(3,5)` 到 `(3,0)`，以及从 `(3,5)` 经 `(3,5)` 到 `(3,0)`。

本阶段确认结构与输入，不用 BFS 或普通浮点几何替代 SPFA、DirectionCursor、MoveCheckpoint 的客户端语义。tile/世界坐标、斜向速度、随机偏移、碰撞、steering、checkpoint 抵达阈值由移动恢复另行验证。

## 原生布局和虚表证据

`native_fields.json` 提供 89 个类型、2,326 个声明字段（包含 static/hotfix/literal）、120 个闭合泛型身份，以及 2,525 条方法记录。2,402 条非空候选方法指针与首 16 字节重新核对了 GameAssembly 原件。每个字段保留 metadata record、field offset record、native Il2CppType record、实际类型及 TypeDefinitionSizes。`field_offsets.json` 是精简的实例字段/继承布局视图。

数据类不能同名混配：

| TypeDef | 全限定类型 | 实例大小 | 关键 offsets |
|---|---|---:|---|
| 4501 | Torappu.EnemyDatabase.EnemyData | 0xb0 | attributes=0x40，prefabKey wrapper=0x30，notCount wrapper=0x90 |
| 4503 | Torappu.EnemyDatabase.AttributesData | 0xd0 | HP=0x10，ATK=0x18，DEF=0x20，MR=0x28，移速=0x40，攻速=0x48，间隔=0x50 |
| 4657 | Torappu.LevelData.EnemyData | 0x88 | key=0x20，attributes=0x28，notCount=0x40，lifePointReduce=0x50，runtimeData=0x80 |
| 4658 | Torappu.LevelData.EnemyDataDbReference | 0x30 | useDb=0x10，id=0x18，level=0x20，overwrite=0x28 |
| 4649 | Torappu.RouteData | 0x48 | motion=0x10，start=0x14，end=0x1c，checkpoints=0x38，diagonal=0x40 |
| 4648 | Torappu.RouteData.CheckpointData | 0x30 | type=0x10，time=0x14，position=0x18，offset=0x20，distance=0x2c |
| 10658 | Torappu.Battle.DirectionCursor | 0x80 | 继承 BasicCursor10657；visitedMap=0x60，offset=0x68，nextGrid=0x70，totalDist=0x7c |

Enemy11393 的全部继承链、BasicCursor/Checkpoint/MoveCheckpoint/WaitForSecondsCheckpoint、Route10670、PathRequest、SPFA、Map、MoveController 已导出。BasicCursor 的 parent 是 Object；DirectionCursor 才继承 BasicCursor。原先试图从 BasicCursor 的不存在基类寻找 GetNextDirection 是不正确的类型归属。DirectionCursor 的 GetNextDirection 候选 `0x180894f60`、CheckReached `0x180894d60`、OnTick `0x180895d70` 经 pointer/首字节核对。

GridPosition1624 是值类型：boxed size24，row=0x10、col=0x14；TSVector2(38273) boxed size32，x=0x10/y=0x18，均为 FP；TSVector3(38274) boxed size40，x/y/z=0x10/0x18/0x20。此处 IL2CPP 值类型 offset/size 含 16 字节 boxed header；要解释 unboxed 调用必须由具体指令证明，不能把表里的 0x10 当成 unboxed struct 起点。多维 array 原件也按 [Il2CppDumper 作者结构](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/Il2CppClass.cs) 的 Il2CppArrayType 解码，保存 rank/element 指针和原件 bytes。

运行时 Torappu.AttributesData4132 的数值字段实际为 ObscuredInt/ObscuredFloat；其布局、对应 wrapper 类型也已导出。它们不是把数字直接摆在字段起点的普通 int/float。开放泛型 Undefinable`1(4508) 的通用 offset 表为 0/0、instance size 为 0，这不是具体 `<Int32>/<Single>/<Boolean>` ABI。包装体的实际 member offset 要结合属性组原生指令，不能从开放定义得到。

七个 schema 表的实例字段名与顺序和 metadata 完全相同：DB EnemyData、EnemyLevel、AttributesData、EnemyDataDbReference、RouteData、CheckpointData、LegacyInLevelRuneData。Options schema 为 15 字段而 native 有 18 个实例字段，额外包括 enemyTauntLevelPow、deployCostPostDelta、deployCostPostDeltaMinCost；资源没有填充未知 slot，额外运行时字段不能自动注入为已恢复规则。

`virtual_slots.json` 验证 Enemy、Unit、Entity 的虚表 slot `0x28`（40）：原件 encoded method 为 `0x6002065b`，usage kind3、low29右移1后 index66349。它是 `Torappu.Battle.Entity.get_alive`，声明 slot 也为40，返回 Boolean，候选 VA `0x180701920`。Enemy 的 vtable record 文件 offset35987008；Unit36015784、Entity35901780 的相应项一致。因此 parent 的 DoSpawn slot40 有具体的存活 getter 候选，而不能按对象 offset0x28 猜字段。原生 trampoline 调用约定仍由 creation 分析负责。

`FinishMe` 的 slot 为 117：Entity method66633/VA`0x1806f3360`，Enemy override method76484/VA`0x180a6d0d0`。Enemy 的 slot117 encoded`0x60025589`/record35987316 精确指向 override；Unit 和 Entity 的相应项指向 base。`Torappu.Battle.Entity.FinishReason` 的客户端 metadata 常量为 NONE0、REACH_EXIT1、HP_ZERO2、FALLDOWN3、WITHDRAW4、DEADLIKE_WITHDRAW5、SILENT_WITHDRAW6、OTHER7、HP_ZERO_WITH_NO_SOURCE8、REPLACED9、RESPAWN_SELF10、MOVE_LIKE_RESPAWN_SELF11、MOVE_LIKE_RESPAWN_EXTERNAL12。不要和 `Ability.FinishReason` 混配。

## 属性 custom attribute 与方向常量

`attribute_meta.json` 直接解析 v29 `attribute_data/attribute_ranges`，保留每个原始 range、blob、构造方法、typed arguments 和 named assignments。全部选中 blob 精确读到末尾，参数数目与 constructor metadata 一致。解析方式参照 [作者的 CustomAttributeDataReader](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/CustomAttributeDataReader.cs) 和 [v29 compressed integer reader](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Extensions/BinaryReaderExtensions.cs)，不执行游戏 constructor。34 个数值字段有 AttributeMetaAttribute，11 个 Boolean 有异常免疫 meta，另两个静态字段 ZERO/s_fieldMetas 没有这类属性。

| 关键字段 | 真实 constructor 声明 |
|---|---|
| maxHp | MAX_HP、min=1 |
| atk | ATK、min=0 |
| def | DEF、min=0 |
| magicResistance | MAGIC_RESISTANCE、min=0、max=100 |
| moveSpeed | MOVE_SPEED、min=float32(0.1)，bits`0x3dcccccd` |
| attackSpeed | ATTACK_SPEED、min=20 |
| baseAttackTime | BASE_ATTACK_TIME、min=0 |

这张表恢复了声明输入；constructor 对 hasMin/hasMax 的写入及 GetRange/Clamp/FP 转换由原生分析佐证。DB EnemyData 的 prefabKey 还具有 `EnemyDataMetaAttribute.AssignName="key"`：原始 blob`01427a00000001000e066b657900`，零参数 ctor31298 和 named field25305。其余15字段没有该 attribute，这给出了真实的 prefabKey→runtime key 映射。

SourceApplyWay 的原件常量为 NONE0/MELEE1/RANGED2/ALL3，MotionMode 为 WALK0/FLY1/E_NUM2，EnemyLevelType 为 NORMAL0/ELITE1/BOSS2/E_NUM3。MotionMask 为 NONE0/WALK_ONLY1/FLY_ONLY2/ALL3。这些值来自客户端 metadata 常量，而非仅由 community schema 命名。

`shared_consts.json` 验证 TypeInfo slot`0x18894ebe0`→Torappu.SharedConsts38212，static_fields+8 对应 REVERSE_FOUR_WAYS。由 movement 恢复的 .cctor InitializeArray 的 FieldInfo slot`0x188898240`，原件 encoded`0x8000031b`→FieldRef397→PrivateImplementationDetails field320410，声明类型`__StaticArrayInitTypeSize=16`。其 default blob file offset22035496 的原始16字节`02000000030000000000000001000000`，对应 Int32 `[2,3,0,1]`；SHA-256恰等于该 field 的完整 hash 名称。Direction 真实枚举为 UP0/RIGHT1/DOWN2/LEFT3，ALL_DIRECTION_PASSABLE_MASK=15。

Route.Node10668/PathTarget10669 都是 value type，boxed size分别64/40，不能误当普通引用类。movement 原件的 Node stride48及字段偏移-16与 metadata 一致；PathTarget unboxed24字节。Tile.Options10710也是value type，unboxed24字节；嵌入Tile.cachedOptions+0x90之后，Tile+0x94为passableMask，Tile+0x98确切名为overrideObstacleLikeMoveCost。

## 敌人 prefab 延迟与源石祭坛

`prefab_inputs.json` 的 `enemies[id]` 可直接读取 `delay_to_born_float32`、`delay_to_born_bits`、`only_delay_on_start_tile`。每项有原始 source bundle hash、asset mapping、GameObject/Enemy component path ID、component bytes/hash、MonoScript CAB/path/source hash、shipped字段类型和对应native字段身份。共读取8个相关prefab bundle与一个MonoScript bundle，12个prefab的113个本地连通MonoBehaviour；没有导出网格、纹理或音频。

10 个 Enemy prefab 的 `_delayToBorn`：`enemy_2133_shdopl=1.0`、`enemy_2152_shezlc=1.0`，其余8个=0.0；所有 `_onlyDelayToBornOnTileStart=false`。前者是 shipped type tree float4B，后者是 UInt8/1B，metadata/native归属Torappu.Battle.Enemy/Boolean。原生字段offset分别0x310/0x314。

creation 原生恢复已连接 Scheduler._CreateEnemyItem 对临时 Enemy 的 `get_delayToBorn(0x180a7c370)` 读取。getter **仅在静态热修补override指针为null时** 使用上述原生分支；flagfalse时从0x310直接MOVSS，flagtrue才检查start tile。10个静态prefab都是false，但本阶段没有验证真实运行时override指针为null。因此已经取得正常原生分支的有效输入，仍不能声称任何现场客户端实例必然使用该值。`creation/raw_round3.json` 另存getter原件范围、指令和hash。

源石祭坛不能忽略：本图 `trap_011_ore#1` hidden=false、位置(5,6)、方向UP、level1/PHASE_0、skillIndex0/mainSkillLvl1。character记录明确引用 `sktok_ore`。技能为AUTO，SP随时间恢复，spCost7/initSp0/increment1，blackboard value=500。描述声明向周围双方造成真实伤害并强化特殊敌人；对应技能prefab实际为 CastSkill、AlwaysTrigger、AnimatedActionToTargetAbility、AdvancedSelector等组件。ability `_preDelay=0.6000000238418579`，引用 `ore_s` 与 `ore_buff` 两个active buff。

`ore_buff_templates.json` 只从8659个模板中提取这两项，源 `config/buff_template_holder.ab` SHA-256`12419ad8d1ea9f670cca214e525240c691cdf3796b82acc8050698d66c202a37`。纯JSON配置中 ore_s 的节点链为 CheckContainsBuff(ore_immune)→IfNot→FixedValueDamage(PURE,damageKey=value)；ore_buff 为 CheckContainsBuff(ore_listener)→SwitchMode(loadModeFromBlackboard=true)。这些是行为输入；event key、条件、目标、伤害与状态改变的执行仍需原生恢复。没有运行目标JSON反序列化。

祭坛Trap有 `_rewriteTileOptions=1`，TrapMode的tileOptions为buildableType0/passableMask2/overrideObstacleLikeMoveCost0/advancedBuildMask0/heightType0/forceSetHeightType0。不能仅按原始mapData认为这格的动态通行配置已还原。因此当前route/leak kernel与真实无干员idle战斗之间仍有祭坛及enemy talent/state machine缺口。

## 可复核结果与边界

运行 `verify_evidence.py`：15 项独立检查覆盖定义零/false与未定义、缺失引用、wire 缺失标量与存储零、Single原始位、无效 Boolean、截断、越界 field、实际资源矩阵与哈希、metadata类型/虚表、compressed integer边界、custom attribute原件blob、方向数组hash身份及prefab延迟与source pins。结果、输出及解析脚本/产物 pins 在 `verification_report.json`。

这些测试是资源reader与静态evidence的验证，不是真实游戏运行oracle。资源成员名、值、布局、原生分支输入与实际动态运行状态是不同保证层次。完整merge/rune、状态机、设备、talent、技能/伤害、寻路和leak执行由独立原生恢复与原型验证承接；未来版本、XLua热修补及实际运行设置仍不在这个静态快照的保证范围内。
