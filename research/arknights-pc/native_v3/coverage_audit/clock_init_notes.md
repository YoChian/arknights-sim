# BattleController 时钟静态初始化（2026-10-13）

原始代码可以证明 `.cctor` 将 static fields `+0x48` 初始化为 **FP raw 0**。它没有给出有效战斗步长；当前不能从这个入口推定 `1/30`、`1/60` 或其他正常游戏时步。实际运行步长需要继续追踪后续赋值、driver 与热修补分派。

目标 SHA-256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。直接读取并校验 DLL，未运行或加载游戏。原始 PE 异常目录递归复核得到 `.cctor` 候选 `0x18063ef40` 的唯一组件 `[0x18063ef40,0x18063f265)`，unwind RVA `0x7f63a34`；全部 805 字节连续解码为 155 条指令。

## 原始代码的数据流

| 原始地址 | 指令 | 意义 |
| --- | --- | --- |
| `0x18063f0f0` | `xor edx,edx` | 清除隐藏参数寄存器 |
| `0x18063f0fc` | `xor ecx,ecx` | int 参数为 0 |
| `0x18063f0fe` | `call 0x1866fdac0` | 调用 int→FP 候选转换 |
| `0x18063f103` | `mov rcx,[rip+0x82e8c56]` | 原始有效地址 `0x188927d60`，与 BattleController getter 同一类型槽 |
| `0x18063f11a` | `mov rdx,[rcx+0xb8]` | static fields 指针 |
| `0x18063f121` | `mov [rdx+0x48],rax` | 写入转换返回值 raw 0 |

转换 helper `0x1866fdac0` 的原始 8 字节为 `4863c148c1e020c3`，恰好是 `movsxd rax,ecx; shl rax,32; ret`。这直接确认 raw 值为 `sign_extend(int32(0)) << 32 = 0`。使用该处原始指令证明，不依赖 FP 类型名或浮点近似。

在清除 ecx 与写入 `+0x48` 之间，仅这一 helper 调用会产生 rax；其后只有将数值 2 和 0x80 写到栈的操作，没有改动 rax，也没有条件分支跳过赋值。get_deltaPlayTimeFP 的 fallback 从同一类型槽的 static fields `+0x48` 读取，但 getter 有热修补替代路径，因此静态初始化值不能提升为真实对局值。

## Ghidra 警告的解释边界

`results_round3.json` 在 `0x18063f010`、`0x18063f0b1`、`0x18063f0e4`、`0x18063f189`、`0x18063f1f1` 报 Possible PIC construction，并把后续块视为 unreachable。然而原始字节在这些位置全部是直接 `call 0x18048b9e0`，**不是 call-to-next**。全范围原始 call-to-next 数量为 0。进一步逐条比对同一个 Ghidra 结果的 `direct_calls`，所有 raw 直接 CALL 地址/目标均相等，这五处的 listing 引用也都指向 `0x18048b9e0`。目前看到的是 decompiler 控制流建模限制，没有看到这些 CALL 的 raw/imported 目标不一致；没有导出整个 Ghidra imported memory 的字节，因此不能越过这一范围断言全部导入字节一致。

`0x18048b9e0` 在既有分析中被当作 IL2CPP write-barrier helper；本次只确认实际 call 目的地址，没有重新反编译其内部。由此不能把 Ghidra 警告解释为此入口实际包含 PIC 自定位操作，也不能使用删掉后段的伪代码判断时钟初始化。单独的 call/stack 推断错误、辅助函数建模或导入分析选项仍是需要后续 Ghidra 检查的解释，尚未证明具体原因。

原始构造还将 `+0x18`、`+0x20` 通过同一个 int→FP helper 初始化为 raw 0，`+0x14`、`+0x28`、`+0x40`、`+0x50` 清零，并创建两个 RNG 及对象池。它们不提供有效战斗 dt 常量。

## 产物

- `clock_init.py`：可重跑 raw PE/Capstone 审计，默认打印摘要，`--dump` 输出指令。
- `clock_init_disassembly.json`：完整指令字节、RIP 地址与静态载荷、原始 unwind 组件、转换 helper 和 `+0x48` 写入路径。

运行时正 dt 的来源仍为待恢复项；不要令模拟器自行采用经验帧率后声称与该客户端相符。
