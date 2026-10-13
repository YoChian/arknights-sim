本轮已恢复本地 Windows 客户端 `Torappu.Common.dll / Torappu.FP` 足够调度使用的算术，完成 Python 组件与独立 C# x64 参考验证。证据来自静态读取安装文件，没有启动客户端、加载 GameAssembly 执行、访问服务或检查运行时热修补。

## 输入与身份

- `D:\Hypergryph Launcher\games\Arknights\GameAssembly.dll`：218,523,112 bytes，SHA256 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`，image base `0x180000000`。
- `global-metadata.dat`：45,805,368 bytes，SHA256 `d3fede171f92740a6f5dc053c58c7013d3c962db764ad1f05cbe977c074fcd1f`。v29/custom 92-byte type definition。
- FP declaration：type definition index 38268，image `Torappu.Common.dll`，70 methods / 42 fields；存储字段 `_serializedValue` 的原生 Il2CppType tag 是 `0x0a`（Int64）。
- 元数据方法 token RID → codegen module method-pointer table → file-backed executable bytes 的候选映射沿用 `core/Torappu.Common_candidate_method_map.json`。本轮又核对 PE unwind 和实际指令，不将名称本身当成行为证据。

## 完整函数范围修复

首次反编译 FP division 只覆盖首个 `.pdata` 项，长度仅 50 bytes；它只包括 prologue / 零除分支，不能证明非零除法。该结果保留为 `fp_results_truncated_prior.json`，不得作为完整函数恢复报告。

修复版精确解析 `UNWIND_INFO`：flags=`byte0 >> 3`，count=`byte2`，chain tail=`4 + align4(count*2)`。当 `UNW_FLAG_CHAININFO=4` 时，末尾三个 DWORD 构成父 `RUNTIME_FUNCTION`，递归归根并汇集所有同根范围，不使用相邻方法地址猜测。此结构与 [Microsoft x64 exception handling](https://learn.microsoft.com/en-us/cpp/build/exception-handling-x64?view=msvc-170) 的链式展开说明一致。

Division `0x1866fd730` 的实际四段（右端 exclusive）：

| 范围 | unwind flags | 父关系 |
|---|---:|---|
| 0x1866fd730–0x1866fd762 | 0 | 根，unwind RVA 0x7f64860 |
| 0x1866fd762–0x1866fd890 | 4 | 根 triplet `(0x66fd730,0x66fd762,0x7f64860)` |
| 0x1866fd890–0x1866fd8e1 | 4 | 同上 |
| 0x1866fd8e1–0x1866fd907 | 4 | 同上 |

以上 471 bytes 的 SHA256 为 `08aa1870a3aa7e13d94764f0ba269839fd0be405b4f19437afc81e5c7d70537e`。`fp_unwind.json` 保留原始记录、文件偏移和 chain bytes。此次 45 unique VA 函数全完成反编译：18 unwind functions / 21 `.pdata` components，27 leaf functions。后者边界由解码后的 INT3 对齐填充确定，证据弱于 unwind；45 函数的 91 个已解码直接跳转均留在各自范围内（`control_flow_coverage.json`）。本轮不是全库数学函数恢复。

## 确认的数值行为

原生存储是一个 signed int64，32 fractional bits，value=`raw/2^32`。整数部分含 31 位数量位和 1 位符号，常见表述为 signed Q32.32（包含符号）或 Q31.32（不包含符号）。本报告以位数定义为准。

| 行为 | token / VA | 实测静态指令与结果 |
|---|---|---|
| int64→FP | 0x600031a / 0x1866fdae0 | SHL 32，超范围 wrap64 |
| int32→FP | 0x6000321 / 0x1866fdac0 | sign extend，然后 SHL 32 |
| float32→FP | 0x600031c / 0x1866fdad0 | MULSS `2^32`，CVTTSS2SI，截断到零 |
| `FromFloat` | 0x600032a / 0x1866fba30 | 初始化检查后，同一 MULSS/CVTTSS2SI |
| double→FP | 0x600031e / 0x1866fdaf0 | MULSD `2^32`，CVTTSD2SI，截断到零 |
| FP→整数 | 0x600031b / 0x1866fd910 | SAR 32；负小数向下取整 |
| FP→float32 | 0x600031d / 0x1866fd9e0 | CVTSI2SS，然后 MULSS `2^-32` |
| FP→double | 0x600031f / 0x1866fd920 | CVTSI2SD，然后 MULSD `2^-32` |
| + / - | 0x60002fa / 0x184624db0；0x60002fd / 0x1866fba10 | unchecked raw64 add/sub，溢出 wrap |
| * | 0x6000301 / 0x1866fb870 | signed-high / unsigned-low 32-bit limb 运算；等价 wrap64((x*y)>>32)，负积向下舍入 |
| / | 0x6000305 / 0x1866fd730 | unsigned abs 長除，33-bit shift budget，商+1后 SHR1，再加符号；常规半值远离零；超移位分支取静态 MaxValue/MinValue |
| % | 0x6000306 / 0x1866fdb00 | signed IDIV remainder，符号随左值；MIN/-1 特判0，0 divisor仍是硬件除零路径 |
| 一元负/Abs | 0x6000308 / 0x1866fdb40；0x60002f5 / 0x1866faa10 | MIN(raw=-2^63) 特判返回静态 MaxValue，其余通常取负/绝对值 |
| Floor / Ceiling | 0x60002f7 / 0x1866fba20；0x60002f8 / 0x1866fb460 | 清低32位；Ceiling有小数时加One（wrap） |
| Round | 0x60002f9 / 0x1866fc8d0 | 最近整数、half ties-to-even，末尾加法wrap |
| 比较 | `op_GreaterThan` 等 | signed raw64 CMP/SETcc |

float32 scale constant 地址 `0x187101c84`（file offset118490244），bytes `0000804f`，确切值4294967296；double `0x187101c78` 值相同。倒数常量为 `0x187101c50` / `0x187101078`，确切 `2^-32`。所有 RIP 引用原字节在 `fp_disassembly.json`。

特别边界：

- **FP division 任意 x / 0 返回 raw `0xffffffff00000000`，即 -1.0**；与 `% 0` 不同。
- Division 并非一般数学 clamp：中间 uint64 累加、`+1` 都保持 wrap。`raw=INT64_MAX` 除以 One 可以产生 PositiveInfinity sentinel；`raw=INT64_MIN` 除以 One 则走 overflow→MinValue。Python保留原循环。
- `OverflowAdd` / `OverflowSub` 是另外的方法，饱和到 `INT64_MAX` / `INT64_MIN`（sentinel bit patterns）；不能据此把正常 `+/-` 改为饱和。OverflowMul原生已反编译，但未加入本轮调度组件。
- `from_float32(-0.1)` raw=-429496736；`from_double(-0.1)` raw=-429496729；两者 as_int 都为-1。不要用 Python 双精度计算代替 Single路径。
- `FP.from_float32(1/30)` raw143165584，累加30次raw4294967520，较One高224。此例验证转换/累计差异，不主张客户端实际帧步长是1/30。
- IEEE invalid-masked转换（NaN/Infinity/out-of-range）按 integer-indefinite raw `INT64_MIN` 模型处理。转换指令见 [Intel Instruction Set Reference](https://cdrdv2-public.intel.com/774492/325383-sdm-vol-2abcd.pdf)。普通浮点算术/转换的 nearest-even MXCSR，以及 masked exception，是参考程序观察与模型假设；游戏 live MXCSR未读取。

## 类型指针与静态常量证据

根据 [Il2CppDumper 作者的 Il2CppClass.cs 布局](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/Il2CppClass.cs)，找到唯一结构匹配 `Il2CppMetadataRegistration`：VA`0x187c26040`，file offset130172992。typesCount130813，所有130813 type pointers file-backed；types table VA`0x187c88de0`，file offset130577888。50,926 class/value-type byval declaration 全部指向对应 metadata index，16 System primitive tags全部一致，0错；另有两项不属这些校验类别。fieldOffsetsCount/typeDefinitionsSizesCount均50944，等于元数据定义总数。这是静态结构验证，未执行注册例程。

`53178/53179/53187`均 Torappu.FP（tag0x11,data38268），只有 attrs=0 / 1(private field) / 0xb6(public static readonly) 不同。`75036/75037`均Single（tag0x0c），后者attrs1，**不是byref**。因此 Scheduler wave/fragmentStartTime字段是FP，branch coroutine currentTime字段是Single。

fieldOffsets table VA`0x1884e8000` / file offset139353600；FP条目指向 `0x186eb9430`。真实静态field offsets把cctor写入值对应到以下名称，而非依赖声明排列猜测：

| 名称 | static offset | raw |
|---|---:|---:|
| MaxValue | 0x10 | 0x7ffffffffffffffe |
| MinValue | 0x18 | 0x8000000000000002 |
| One | 0x20 | 0x100000000 |
| Ten | 0x28 | 0xa00000000 |
| Half | 0x30 | 0x80000000 |
| Zero | 0x38 | 0 |
| PositiveInfinity | 0x40 | 0x7fffffffffffffff |
| NegativeInfinity | 0x48 | 0x8000000000000001 |
| NaN | 0x50 | 0x8000000000000000 |

`IsNaN`/`IsInfinity`只比较raw sentinel值，算术没有自动IEEE传播。实例 `_serializedValue` 的field offset表值16属于boxed对象头；unboxed getter/ctor直接读取/写入[rcx]8字节。Const literals（大写MAX_VALUE等）不占真实static存储，不可混淆。

作者原版 [Fix64.cs](https://github.com/asik/FixedMath.Net/blob/master/src/Fix64.cs) 的 limb/长除结构与本地原生高度相似，这是来源关系推断。原版正常+/-/*饱和且0除抛异常；本地正常+/-/* unchecked、0除返回-1、并另外提供Overflow方法与特殊sentinels。故不能直接复制上游替代实测实现。

## 组件与验证

- `D:\Repo\arknights-sim\arknights_probe\fp.py`：immutable FP(raw)，from_raw/int32/int64/float32/double，as_int/long/float/double，+ - * / %，一元负/abs，raw比较，floor/ceiling/round，独立overflow_add/sub，binary32辅助。
- `tests/test_fp.py`：8 tests通过。7,073 raw pairs×6算术/2比较类路径，81 unary边界，93 binary32 bit patterns，92 binary64 bit patterns，并验证证据SHA、链范围、零除、ties/overflow/sentinel。
- `evidence/fp/FPReference.cs` 独立C#重写。乘法同时用原生limb与BigInteger宽乘法恒等式验证。Division保留精确unchecked unsigned算法，不把无限精度有理数当极限行为oracle。
- 编译器：已有 `C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe`，`/platform:x64 /optimize+ /r:System.Numerics.dll /r:System.Web.Extensions.dll`；运行时4.0.30319.42000 / pointer64。仅运行自建reference，没有加载任何游戏文件。
- 证据在 `arknights-sim/evidence/fp` 包含native_report、native_disassembly、native_types、metadata_declarations与参考向量；FP_EVIDENCE列出SHA pins。

重现最小验证：

```powershell
Set-Location D:\Repo\arknights-sim
& C:\Users\YoChi\AppData\Local\Programs\Python\Python311\python.exe -X utf8 -m unittest tests.test_fp -v
```

仍未确认：运行中客户端/hotfix解释器是否替换这些方法；live MXCSR；时钟真实delta、ManualFrameTick快进/暂停/重入条件；battle向量/三角数学/LUT；全部可能runtime泛型与异常分派。调度时间转换路径由父agent的Scheduler恢复结果另证，本轮只提供Single/FP类型身份与原语，不单独宣称完整战斗一致性。
