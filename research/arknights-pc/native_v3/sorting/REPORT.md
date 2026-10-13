# 调度队列排序恢复（2026-10-13）

已按本地原生代码恢复比较器排序的 **中点 pivot、双指针 Quicksort**。相同时间的事件也会交换，因此既不能用 Python stable sort，也不能假设长度 ≤16 时保留插入顺序。本次排序恢复不再需要 16 个元素的限制。

目标 `D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll`，SHA-256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。所有处理只读、关闭默认整包自动分析；Ghidra 使用独立 sorting-project，三个运行均已结束并丢弃临时项目。未执行游戏，未修改游戏或原型；仅运行我们自己编写的 C#参考程序。

## 原生调用链与范围

| 地址 | 静态用途 | exact code bytes | 边界依据 |
| --- | --- | ---: | --- |
| `0x184543930` | `_DealFragment`、`_DealBranchPhase` 调用的 wrapper | 167 | 完整单段 PE unwind 组 |
| `0x184544810` | wrapper 的尾跳转目标，长度 >1 时调用排序主体 | 342 | 完整单段 PE unwind 组 |
| `0x184547860` | comparator Quicksort 主体 | 1061 | 完整单段 PE unwind 组 |
| `0x180950a00` | 从 lhs/rhs tuple `+8` 读取 float，调用 CompareTo | 29 | 完整单段 PE unwind 组 |
| `0x185ed0a10` | Single.CompareTo 返回 -1/0/1 | 56 | 小型 leaf；所有分支目标及 RET 完整，随后 INT3 填充 |

5 个入口的 exact 范围，共 1655 字节，均逐片计算原文件 SHA-256 并与 Ghidra currentProgram memory SHA-256 匹配。完整 PE unwind 链与范围生成保留在 `input_round*.json`；浮点 leaf 的边界与 unwind 范围分开标注。原始字节和地址见 `raw_disassembly.json`，伪代码与导入校验见 `results_round*.json`。

wrapper 原件在 `0x18454398d` 尾跳转 `0x184544810`。后者检查比较器非空、请求长度 >1 与集合元素数 >1 后，以 `[0,count-1]` 调用主体。主体首先判断 left<right，使用 `left+(right-left)/2` 处完整 tuple 的值作为 pivot；扫描条件为 `compare(queue[i],pivot)<0` 与 `compare(pivot,queue[j])<0`；i≤j 时进行交换（包括相等的键），然后 i++、j--。先递归左区间，再迭代右区间。主体完整控制流没有 Introsort depth、heap fallback 或 insertion threshold 16；本结论限定此调用链，不能推广到整个游戏全部排序。

## 比较器与相同时间顺序

本地元数据候选映射中 `<_DealFragment>b__122_0` 与 `<_DealBranchPhase>b__123_0` 都指向 `0x180950a00`；另有其他编译合并 aliases，不能将候选名称当成恢复的原始符号。原始指令从两份 tuple 的 `+8` 取单精度 float，直接调用 `0x185ed0a10`；mscorlib 元数据候选将后者关联 `System.Single.CompareTo`。

CompareTo 原始 `COMISS/UCOMISS`、parity 分支和三个返回值进一步确认普通大小比较、NaN<非NaN、NaN==NaN、-0==+0。这不是仅根据方法名推测。Ghidra 丢失 caller 返回类型时生成 void，但原始 caller 在 call 后没有改动 eax；sort 主体直接用比较器 eax 的符号判断。

只有相同时间键的 2、3、4 个元素，id 原始顺序 `[0,1,...]`，排序结果依次为 `[1,0]`、`[2,1,0]`、`[2,3,0,1]`。不要另加 action id 或插入序号作为 tie breaker。真实队列必须在执行排序前保留原始追加顺序；autoPreview 等系统产生的记录也参与排序，因此错误稳定性会改变同时间事件先后。

## 实现与验证

`native_queue_sort.py` 提供 `native_queue_sort(items,key)`，返回新 list、保留 item identity、原输入不变。key 一次 round 到 binary32，模仿队列记录中已经储存的 Single；相等时间直接沿恢复算法交换。当前模块 SHA-256 `1d74539adbd9c5efbba5d62124b091988ea651ebef320ec4855e0b0ea78a6028`。

独立 C# 译写参考通过 152 个队列案例、5616 个 identity 的精确顺序比较、81 个 Single.CompareTo pair。尺寸 0..129，包括 15/16/17，覆盖全相等、递增/递减、重复键、单个异常低值、binary32 rounding 碰撞以及 NaN/infinity/±0。另校验 item identity、原输入不变、结果元素不重复丢失以及单精度全序单调性。同输入的宿主 .NET `List.Sort` 在 56 个案例中顺序不同，直接将宿主排序当成游戏排序参考会出错。

这两份译写的跨语言比较有助于发现移植错误，**不是执行原生游戏代码的金标准，也不是热修补后的真实对局 oracle**。目前恢复的是此客户端快照的静态排序路径；时间积累、queue 生成顺序以及实际热修补分派需要调度重建自己的证据与验证。

参考源 SHA-256 `93068657ebbc01ce4b020df63b24e83127bfa7e905bdb2e4b825ec5110d78456`；vectors SHA-256 `3788877f048fc8cf06df84429885d3ffc760601891385cd4bcc0b3bce1c8626d`。`verify_reference.py` 可重跑精确比较，输出 `reference_comparison.json`；`evidence.json` 保留入口、组件、候选 aliases、模块和参考 pins。
