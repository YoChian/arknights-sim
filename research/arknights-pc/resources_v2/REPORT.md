# PC 规则资源解码结果

2026-10-13 完成离线资源适配。原始第一轮证据保留在 `../resources`，游戏文件没有被修改或执行。所有输出位于本目录。

**目前已经从当前本地安装中拿到了可读的肉鸽地图、干员、技能、敌人数据库、肉鸽主题规则，以及资产索引和一个 Lua 源码样本。** 资源版本固定为 `26-09-13-15-28-10-30688348`。

## 格式适配和验证

内容压缩码 4 对应本地实测的一种 LZ4 变体：token 的低半字节表示 literal 长度，高半字节表示 match 长度，match offset 使用大端。`ark_bundle.py` 实现独立适配，检查输入长度、输出上限、回溯范围和最终精确解压尺寸，不修改游戏或 UnityPy 库文件。

150 个匿名资源包全部解析成功：2,184 个压缩块，116,585,716 bytes 压缩内容还原为 275,495,328 bytes；实际读取 12,628 个 TextAsset。另选 common 配置、buff 模板、敌人 prefab 和 ro6 场景包，分别成功读取 106、1、1,431、144 个 MonoBehaviour 类型树。8 个针对越界、错误长度和非法回溯的反例均被拒绝。

7 个表/关卡样本及资源索引的 128-byte 前缀，经作者公布的 RSA 公钥及 PKCS#1 v1.5/MD5 验证成功。去掉前缀后得到明文 FlatBuffer。旧肉鸽表与 Lua 样本同样验签成功，随后按作者提供的资源 AES-CBC 算法成功解码。这里验证的是当前本地样本；没有把历史兼容性当成当前结果。报告和 probe 日志仅记录参数标签，不展示 token 原值，下载的模块没有执行。

FlatBuffers 转换使用 Google 官方 `flatc 25.12.19`，下载资产 SHA-256 已与 GitHub release digest 核对；Schema 固定到 OpenArknightsFBS 提交 `dbbc98306982259956f271b71c7fb63a05cdd5d5`。8 个 FlatBuffer 的全部可达 table、vector、string、scalar 经过额外的边界和 UTF-8 检查，未发现 Schema 缺失的已填充字段。

## 资源映射和数据覆盖

资源索引还原出 13,326 个 bundle、129,285 个 asset-to-bundle 映射。bundle 名称均出现在热更新清单，全部资产/依赖索引合法，12,683 个匿名包容器路径与索引映射一致，0 项差异。因此匿名 `.bin` 不再阻碍按规则路径选择文件。

| 数据 | 当前安装中解析出的数量 |
| --- | ---: |
| 干员/召唤物等 character 记录 | 1,382 |
| skill 记录 | 1,820 |
| enemy database 记录 | 2,181 |
| 集成战略主题 | 6 |
| 肉鸽关卡规则资产 | 593 |
| ro6 关卡规则资产 | 68 |
| ro6 stage 记录，含普通/紧急等条目 | 105 |
| ro6 藏品记录 | 371 |
| ro6 choices 记录 | 402 |
| ro6 choiceScenes 记录 | 345 |
| ro6 zones 记录 | 27 |
| ro6 difficulties 记录 | 17 |
| Lua 资产映射 | 346 |

第一轮的 986 个场景 `.ab` 包含 lightingdata 等伴随资源，不等于 593 个关卡规则资产，也不等于 stage 条目数。

## 一张实际地图和最小输入样本

解出的 `level_rogue6_1-1` 对应“沉沦者的黑流树海”中的 **猎犬病原**，主题表同时有普通 `ro6_n_1_1` 与紧急 `ro6_e_1_1` 两个 stage 条目。

- 地图 7 行 × 11 列，77 个 tile；矩阵长度和 tile 索引边界均合法。
- 读取到初始费用 15、费用上限 99、部署数量上限 6、费用增长时间 1.0、moveMultiplier 0.5；这些是资源字段值，完整运行时规则还需核心代码验证。
- 38 条路线，3 个 wave，4 个 fragment，38 个 action：27 SPAWN、10 ACTIVATE_PREDEFINED、1 EMPTY。
- 原始 SPAWN count 求和为 27，**不能直接视为一局敌人数**，因为存在 hiddenGroup、随机组、分支、预置单位和难度选择。
- 10 个 enemyDbRefs 均在当前本地敌人数据库找到；敌人覆盖数据的 `m_defined=false` 是未定义状态，不应把其占位值当作真实的零值。

`minimal_fixture.json` 保存完整地图、两个 stage 条目、10 个敌人引用对应数据库、玫兰莎/芬/克洛丝/安赛尔及对应 4 个技能。SHA-256 为 `d50f6046d31598c9602c8210ebab51bf2e06055e28a49377624c1806d6b9dadf`。完整导出的表在 `normalized/`，类型树及转换前输出在 `decoded/`。

注意坐标约定：本关 `matrix_data` 的首行索引是 66..76，末行是 0..10。路线 `(row=1,col=10)` 对应 `tiles` 逻辑行中的 `tile_start`，直接用矩阵显示行会错误落到 `tile_forbidden`。静态数据支持逻辑行从底部计数、显示矩阵从顶部排列；原型应显式转换，并继续与核心方法/运行轨迹核验。

同日后续核心分析已恢复两个 `MapData.get_Item` 的候选原生入口，均为 `matrix[height-row-1,col]` 后索引 `tiles`。因此坐标访问方向现已由静态原生代码支持，原型默认采用这一方向；完整运行轨迹和寻路仍未验证。证据见 [后续进展](../PROGRESS-2026-10-13.md) 和 `../native_v2/focused_results_round2.json`。

## 元数据交叉核验与剩余问题

本地 metadata v29 的字段名和顺序，与 Schema 中 MapData、RouteData、CharacterData、RoguelikeTopicTable 完全一致。LevelData、Options、TileData、ActionData、ResourceManifest 的 Schema 字段是本地声明的有序子序列；额外 runtime 字段（例如 runtimeData、advancedBuildableMask、useExtraRoute）已记录到 `schema_metadata_comparison.json`，没有声称这些字段的行为已被解释。

Lua 样本 `decoded/UIPatch.lua` 已解为 1,906 bytes UTF-8 源码，含 `ApplyUIHotPatch`。这是 UI 热修复样本，未执行，不能证明集成战略的战斗或随机地图生成逻辑在 Lua。旧 `roguelike_table` 已解为有效 JSON，当前六主题规则应优先采用 `roguelike_topic_table`。

现在已经具备编写小范围离线原型的真实数据基础。准确训练模拟器仍要解决核心方法行为：状态更新和结算顺序、随机数、随机出怪组、隐藏组、路径与阻挡、攻击/技能/目标选择、祭坛和箱子机制、肉鸽节点/事件/藏品实际生效过程，以及服务器未下发的生成状态。应逐项用核心代码与实际轨迹核验，不能把“数据可读”直接当成“规则完全重构”。

## 复查入口与来源

- `summary.json`：结构化结论；`sample_provenance.json`、`index_provenance.json`：本地文件/样本/body SHA-256。
- `anon_inventory.json`、`index_validation.json`：匿名容器和完整资产映射。
- `verification.json`、`codec_bounds.json`、`nontext_verification.json`：格式和边界检查。
- `published_cipher_probe.json`：当前样本验签/已知算法解码的成功与失败边界；`cipher_reference_provenance.json`：固定作者源码提交及散列。
- `fixture_summary.json`、`coordinate_validation.json`：地图样本和坐标证据。
- [LZ4 作者格式规范](https://github.com/lz4/lz4/blob/dev/doc/lz4_Block_format.md)：标准 LZ4 的对照依据。
- [Google FlatBuffers 格式文档](https://flatbuffers.dev/internals/) 和 [flatc 文档](https://flatbuffers.dev/flatc/)：二进制结构与转换依据。
- [OpenArknightsFBS 固定提交](https://github.com/MooncellWiki/OpenArknightsFBS/tree/dbbc98306982259956f271b71c7fb63a05cdd5d5/FBS)：社区作者从游戏结构生成的 Schema，已与当前数据/元数据交叉检查。
- [资源算法作者源码固定提交](https://github.com/djpadbit/Arknights-RE/blob/d7661a89e32040ad10f0b3f253471226890d2749/pyknights/converter.py)：资源前缀验证和 AES 解码依据；仅解析所需常量，未执行该模块或涉及游戏服务。
