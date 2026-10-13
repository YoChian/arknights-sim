已用原始 metadata、native Il2CppType/fieldOffsets/size tables 确认 `RestoreDeltaTimeScale` 默认分支的时钟来源，并取得安装资源中的初始步长。构造路径是 **FP.from_float32(UnityEngine.Time.fixedDeltaTime)**；它不是在 FP/BattleController cctor 里直接写入1/30。

## 原生槽身份与字段

目标 GameAssembly SHA256沿用 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。对应 metadata SHA256为 `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`。

三个文件中尚未runtime初始化的槽初值都满足 bit0=1、usage kind=`encoded >> 29`为1、source TypeIndex=`(encoded & 0x1fffffff) >> 1`。通过两项已知身份验证同一规则，再解第三项，而非猜名称：

| TypeInfo slot VA | 文件偏移 | 初值 | TypeIndex | 原生定义身份 |
|---|---:|---:|---:|---|
| 0x18885a700 | 142968064 | 0x20019f75 | 53178 | Torappu.FP，typeDef38268 |
| 0x188927d60 | 143809376 | 0x20015981 | 44224 | Torappu.Battle.BattleController，typeDef10068 |
| 0x1888ba140 | 143359808 | 0x2001ac4b | 54821 | Torappu.GlobalConsts，typeDef38137 |

`clock_fields.json`保留每一槽原8bytes、type pointer record、type结构12bytes和metadata定义对应关系。原生 type table 身份沿用此前唯一结构匹配并验证130813 pointers的表，不读取进程内存。

GlobalConsts真实fieldOffsets：static+0x40=`FIXED_DELTA_TIME_FP`；+0x48=`HALF_FIXED_DELTA_TIME_FP`；+0x08=`HALF_FIXED_DELTA_TIME`(Single)。BattleController static+0x48=`s_deltaPlayTimeFP`。因此 `results_round4.json / RestoreDeltaTimeScale` 的默认分支确实从GlobalConsts默认FP步长复制到BattleController，不是从FP.MaxValue或其他常量槽。

## cctor实际构造

`Torappu.GlobalConsts..cctor`：Torappu.Common.dll，metadata method219998，token0x6000128；候选 method table entry fileoffset146916552确切存入VA`0x1866e20d0`。PE精确CHAININFO三段共866bytes，169条已解码指令，body SHA256 `eb9ba07884a29608309546e7d7970a7dc76fbbcd84901c7e2a0e036985996b88`。本轮只用Capstone；父agent另将其纳入Ghidra round5。

| 指令VA | 静态读取行为 |
|---|---|
| 0x1866e219d | call0x186b70e10，UnityEngine.Time.get_fixedDeltaTime |
| 0x1866e21ac | MULSS常量0.5f（target0x186e3fda4/fileoffset115598756，bytes0000003f） |
| 0x1866e21c6 | 写GlobalConsts.static_fields+8，HALF_FIXED_DELTA_TIME |
| 0x1866e23aa | 再调用UnityEngine.Time.get_fixedDeltaTime，把Single结果保留xmm6 |
| 0x1866e23cc | call0x1866fdad0，已恢复的FP(float32) implicit转换 |
| 0x1866e23e2 | 写GlobalConsts.static_fields+0x40，FIXED_DELTA_TIME_FP |
| 0x1866e2406 | 从已核实FP.static_fields+0x30加载Half |
| 0x1866e240a | call0x1866fb870，FP正常multiply |
| 0x1866e2422 | 写GlobalConsts.static_fields+0x48，HALF_FIXED_DELTA_TIME_FP |

Unity.Time getter身份来自 `core/UnityEngine.CoreModule_candidate_method_map.json`：metadata method283169/token0x6000b34/VA0x186b70e10。setter是283170/token0x6000b35/VA0x186b712d0。本轮不执行这些地址。原始指令、RIP引用、range chain和pointer再校验保存在 `delta_ctor_disassembly.json`。

## 安装资源里的Unity初始值

`Arknights_Data/globalgamemanagers`：798508bytes，SHA256 `4b722650a29264488701bb438a8f6e310461f9dc4d14245a25fae0b6c0a64ac4`。UnityPy1.25.4已存在的局部依赖读取SerializedFile v22/Unity2021.3.39f1；只选择class5 TimeManager、path_id8、fileoffset788712、16bytes。资源没有embedded type tree；四项名称由已安装并pin SHA的UnityPy versioned TPK class5 schema解释，四个float完整消耗实际16bytes，另用`struct.unpack('<4f')`逐项核对。

16bytes原件为 `8088083dabaaaa3e0000803f8088083d`，SHA256 `8a3dc1ea729ba9bbd3891c5c37694ce21716e8a52d1a65a97bf9ae01626eaf71`。

| 配置字段 | 原bits | 真实binary32值 |
|---|---:|---:|
| Fixed Timestep | 0x3d088880 | 0.03333330154418945 |
| Maximum Allowed Timestep | 0x3eaaaaab | 0.3333333432674408 |
| m_TimeScale | 0x3f800000 | 1.0 |
| Maximum Particle Timestep | 0x3d088880 | 0.03333330154418945 |

[Unity2021.3 Time settings文档](https://docs.unity3d.com/2021.3/Documentation/Manual/class-TimeManager.html)定义该配置面板的Fixed Timestep；[Time.fixedDeltaTime API](https://docs.unity3d.com/2021.3/Documentation/ScriptReference/Time-fixedDeltaTime.html)描述固定更新间隔。将安装资源初始值代入已验证native构造路径，得到 **FIXED_DELTA_TIME_FP.raw=143165440**、half.raw=71582720。这是 **serialized project default条件值**，不是本轮读取的live Unity变量。

不要以此前示例 `FP.from_float32(1/30).raw=143165584`替代这个asset默认值。若恢复此配置且未改写，30ticks raw4294963200，比One低4096；600ticks raw85899264000，比20秒低81920，第一次>=20秒为第601tick。真实Scheduler条件/时钟累加顺序仍由父agent恢复，这里只计算这一路原语的条件边界。

## 改写路径检查与界限

`inspect_time_accessors.py`扫描所有PE executable/file-backed sections里的E8 direct call，核对每个匹配必须处于真正Capstone call指令边界，并以pdata归到精确root。32条 getter/setter calls，0个未验证候选。其中唯一setter直接调用是：

- instruction `0x18154af02`；root `0x18154aee0`。
- metadata候选label `XLua.CSObjectWrap.UnityEngineTimeWrap._s_set_fixedDeltaTime`。

扫描没有找到其他native E8 setter调用。**它不排除Lua调用这个wrapper、间接call、native icall、启动配置或热修补改变Time值**，也不能证明GlobalConsts cctor初始化时刻。不触发游戏，不把安装资源值表述为live实测。相应数据在 `time_accessor_calls.json`。

## 调度字段映射及肉鸽上下文

`clock_fields.json`导出46types/1166 declared own fields，每个字段保留真实fieldOffsets记录文件偏移、nativeType bytes/tag/attributes、TypeDef身份和sizeof记录；`scheduler_field_offsets.json`提供instance/static的offset→name精简索引，包括Scheduler、ActionData、WaveData、FragmentData、DefaultWaveHandler、所有既有timeline coroutines、CoroutineSimulator/RuntimeHandler和BattleController。literal constants单独标识，不与static存储重叠。

例如：Scheduler +0x90/+0x98=`m_waveStartTime`/`m_fragmentStartTime`，FP；ActionData +0x20=`count`、+0x24=`preDelay`、+0x28=`interval`；FragmentData +0x10=`preDelay`、+0x18=`actions`；WaveData +0x10/+0x14/+0x18=`preDelay`/`postDelay`/`maxTimeWaitingForNextWave`。CoroutineSimulator.RuntimeHandler +0x10/+0x18/+0x20=`m_id`/`m_fakeHost`/`m_routines`。这些映射仅含own fields，继承字段需沿已导出的base_type继续跟踪。

同时给prototype核实：RoguelikeTopicDetail(type4954)+0x120=`gameConst`；RoguelikeGameConst(type5006)+0x70=`mimicEnemyIds`、+0x80=`goldChestTrapId`。

`RoguePreprocessor`构造参数TypeIndex69181=RoguelikeInput(type12420)。该输入+0x38的meta是inline VALUE TYPE BattleRoguelikeMeta(type9817)，不是对象引用。FP/RetainData getter与fieldOffsets证明boxed struct offsets需减16；真实sizeof进一步交叉验证：BattleRoguelikeMeta boxed184→unboxed168，Input instance224=0x38+168。

Meta的boxed字段topicId+0x10、chestCnt+0x20、goldTrapCnt+0x24换成unboxed0、+0x10、+0x14。因此构造函数直接读取input+0x38=meta.topicId，直接复制input+0x48的8bytes=(meta.chestCnt,meta.goldTrapCnt)；目标retainData的unboxed字段0/4为(mimicEnemyCnt,goldTrapCnt)。这是经布局与原生拷贝对应后的恢复，不把没有独立input+0x48字段误判为错位。

所有检查只读。没有修改fp.py/tests、游戏文件或全局配置，没有安装程序或运行目标。新增脚本/JSON仅写当前fixedpoint派生目录。
