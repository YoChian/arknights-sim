# 原生分析边界复核（2026-10-13）

对上一轮 43 个原生入口，直接读取原始 `GameAssembly.dll` 的 PE 异常目录及递归 `UNW_FLAG_CHAININFO`，35 个旧范围完整覆盖对应 unwind 组，8 个只覆盖首段。当前已实现的地图坐标访问和独立 LegacyRandom 涉及的 15 个入口全部是完整的单段 unwind 组，未受这一边界遗漏影响。

这是离线原始 PE/Capstone 证据；未运行或加载游戏、未运行 Ghidra、未改动旧分析或原型。元数据方法名称仍是候选关联。完整 unwind 组能确定分析范围，不能单独证明算法完全等价或热修补实际分派。

解析规则与 [Microsoft x64 exception handling](https://learn.microsoft.com/en-us/cpp/build/exception-handling-x64?view=msvc-170) 一致：3 个 image-relative ULONG 组成 RUNTIME_FUNCTION，unwind code 数量向偶数对齐后读取链式记录，递归追到 CHAININFO 清除的主记录；链式 unwind 既可描述不连续代码，也可描述 shrink-wrapping。实现额外要求链条中的完整 triple 与异常目录现存项精确相等，并检查所有环。

目标：`D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll`。SHA-256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`，与旧清单一致。PE 异常目录共 546,612 项，213,884 项有链式记录，归为 332,728 个递归根组；这些不是唯一的方法数量。

## 必须补齐的旧入口

所有范围都按半开区间 `[start,end)` 记录；JSON 中给出每一个经过递归验证的组件，不以最小到最大地址之间的连续跨度代替。

| 候选入口 | 地址 | 旧覆盖字节/组字节 | 组件数 |
| --- | --- | ---: | ---: |
| Torappu.Battle.BattleController.ResetSeed | `0x1806309d0` | 115/607 | 5 |
| Torappu.Battle.BattleController.ResetSeed | `0x180630750` | 290/627 | 3 |
| Torappu.Battle.BattleController.FixedUpdate | `0x180624800` | 152/332 | 4 |
| Torappu.Battle.BattleCostManager.UpdateCost | `0x180656130` | 172/548 | 9 |
| Torappu.Battle.BattleCostManager.InitCostForSide | `0x1806549b0` | 177/1229 | 6 |
| Torappu.Battle.BattleFormula.CalculateDamageInternal | `0x180656ba0` | 125/1197 | 5 |
| Torappu.Battle.BattleFormula.CalculateAttackInterval | `0x180656a50` | 124/331 | 3 |
| System.Random..ctor | `0x185ecf170` | 153/564 | 3 |

8 个首段都在允许 fallthrough 的指令上结束，下一个地址属于被遗漏的链式组件；其中 7 个首段另有显式直接分支到遗漏组件。因此旧脚本的 `decompile_completed=true` 不能作为完整边界的证明。旧伪代码可能自动延伸到范围之外：例如 Damage 的 `0x180657047`、System.Random 有种子构造的 `0x185ecf39e` 位于同一组的遗漏组件。ResetSeed、FixedUpdate、AttackInterval 的部分 `code_r` 标签甚至落在完整组外，属于需要另行检查的反编译扩展，不能将其自动认定为入口自身代码。

上一轮关于费用增长、伤害和攻击间隔的描述，应保留为初步静态观察，等待完整链段重新反编译与逐条核验；不要直接据此实施战斗算法。ResetSeed 的 RNG 创建及 FixedUpdate 的分派也要复核；这不否定已经完整覆盖的 factory 函数独立观察。

## 已实现组件的复核

地图两个 `get_Item`（`0x18241d270`、`0x18241d1e0`）和维度 getter（height `0x18241d300`、width `0x18241d330`）均为完整组。原始指令明确体现维度 0 的长度减逻辑 row 再减 1，以 signed short 查矩阵，再查 tiles；width 使用维度 1。非对称地图测试与 28 条路线的连通测试仍是合理的本地验证，不能提升为游戏寻路等价性。

LegacyRandom 的有种子构造 `0x186505240`、无种子构造 `0x186505460`、Sample `0x1860e0e90`、3 个 Next 和 NextDouble 全部为完整组。静态锚点确认 int32 算术、`inextp=31`、负采样加 INT_MAX 且没有额外 MBIG 减一分支、窄范围 <2 不消耗样本；binary64 常量的原始 8 字节也匹配 `2147483647.0` 与 `1.0/2147483647.0`。样本核心指令连续解码完整，没有链段缺口。当前 Python/C# 两份译写的精确比较依然是有用的跨语言检查，但两份译写不能替代真实客户端金标准。

两个 BattleRandomFactory 与两个 Torappu.RandomFactory 入口也均为完整单段组。默认 factory 选择 LegacyRandom 的静态观察不受这次链段遗漏影响。Factory 内存在跳转表数据，线性 Capstone 解码不足整个 raw 范围并不等同于 unwind 覆盖遗漏；完整 factory 控制流与运行时虚函数/热修补生效路径仍须分开验证。

## 可复用产物

- `audit.py`：独立 PE 解析、所有父记录 exact triple 相等和循环检查、43 项分类，可直接重跑。
- `audit.json`：全部入口、组件、首段缺口、直接分支、边界 fallthrough、旧伪代码超界标签。
- `disassembly.json`：所有确切组件的静态线性指令和字节；不是完整 CFG，包含标注的线性解码缺口。
- `component_anchors.json`：当前坐标/RNG 依赖入口的覆盖及关键指令、binary64 常量定位。
- `reanalysis_input.json`：8 个遗漏入口的精确链组件，兼容当前支持多 `ranges` 的新 Ghidra 分析脚本；本次没有运行它。
- `input_manifest.json`：只读输入的散列，round3 与原型钉住的 `f48a1ac56f11064265e0ebb7dbc12f7815f180e36a00e9d64a53a4febb568a72` 一致。

原始 `native_v2/focused_results*.json` 保留历史结果；本报告和 JSON 提供补充边界，不修改历史证据。
