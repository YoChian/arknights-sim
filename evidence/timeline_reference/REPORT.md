协程和时间轴的独立 C# 参考检查已通过，未发现当前支持范围内的关键移植差异。它是跨语言 implementation check，**不是运行中的客户端 oracle**，也不证明完整战斗一致性。

此次仅新增本目录文件与 `tests/test_timeline_reference.py`，未修改 `coroutines.py`、`timeline.py`、`verify_snapshot.py` 或项目文档。既有Clock/FP证据保留。

## 参考来源与程序

`native_evidence.json`保留以下实际文件的原生函数结果、目标SHA与源报告SHA；不是凭一般Unity协程习惯猜测行为：

| 机制 | native候选VA | 来源 |
|---|---|---|
| RuntimeHandler.MoveNext，stack(bool first,IEnumerator) | 0x18065ff70 | results_round4 |
| CoroutineSimulator.StartCoroutine，立即prime | 0x18065d200 | results_round3 |
| WaitWhileFixed.MoveNext，先yield后测试 | 0x1806619a0 | results_round3 |
| WaitForFixedSeconds(float).MoveNext | 0x180661350 | results_round5 |
| DefaultWaveHandler.ExecuteActionQueue.MoveNext | 0x18094e650 | results_round5 |
| 原先误标CeilToInt的实际nearest ties-even helper | 0x18059e290 | results_round5 |

目标GameAssembly SHA256为 `583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。StartCoroutine的输入range有4段，float Wait有3段，其余各1段；保留完整range记录，不把首段视为完整函数。

`TimelineReference.cs`用自有 `System.Collections.IEnumerator`、`Stack<StackItem>` 与C#生成器，独立重写这些已恢复的控制流。没有引用/加载/调用任何游戏二进制。它由已安装Framework64 csc以x64编译，运行时4.0.30319.42000；C# float除法的实际bits和Math.Round ToEven帧数都留在结果中。

输入是可审查的小DSL：event、ordinary marker、child IEnumerator、fixed wait、WaitWhile及serial queue。`tests/test_timeline_reference.py`把相同输入交给实际Python CoroutineRunner和helpers，对比每个tick的frame、call count、active、stack depth、event count及全部事件。两套实现都来自同一静态证据；一致性可发现移植错误，不能把相互一致升级为客户端运行实测。

## 范围与结果

- 106个协程场景，包含26个明确边界场景与固定seed `0x434f524f`生成的80个组合；共803个tick状态、340事件。
- 155组单精度delay/delta位模式，检查先binary32除法再最近偶数舍入、min1，以及各边界相邻bits。
- 6个kernel场景，共1827frame状态、71事件。三个人工空wave/fragment场景，三个当前真实地图的prepared queue场景。
- `tests.test_timeline_reference` 的8项测试全部通过，含source/input/vector/native evidence SHA pins和独立硬编码的关键边界断言。

已验证的边界：

1. 新进入的empty child首次MoveNext=false时，父协程仍在stack，但本tick立即结束；父在下一frame继续。三次empty sibling后续事件落在frame1/2/3。使用普通Python `yield from`会漏掉这些边界。
2. 已经yield过的child结束时，其first标记为false，Runner继续同tick推进父；filled child的child-after与root-after都在frame1。
3. root为空时首个prime即结束；event-only root在frame0产生日志。frame0 prime不增加时间，runner call count是1。
4. WaitWhile初始predicate已经false，仍先在frame0让出，frame1首次求值并继续父。true,true,false的求值frame为1/2/3。
5. delay=0或负delay仍min1。dt=.25时delay=.375/.625/.875分别得到2/2/4frames，确认2.5向偶数2，不是ceil3。
6. 相同计划时间仍serial执行；空executor与yield一次executor的a/b/c请求都落frame0/1/2。无效action可以跳过executor，但其计划时间仍更新，之前的正delay等待仍保留。
7. 队列只等待相邻planned time之差，不扣除executor消耗的帧。计划时间1→2秒、dt=.25、每executor消费2帧时，请求frame4→10，结束frame12。
8. 空队列fragment跳过ExecuteQueue并直接进入WaitWhile；这与原生DealFragment的queue.Count<1分支吻合。

## 地图kernel对照与外部输入

地图输入由当前 `compile_timeline` 产出的prepared queue写入 `reference_input.json`，C#独立验证其协程执行。**编译器的筛选、随机选择和native Quicksort排序本身不构成C#独立验证目标**；排序已经随prototype更新后刷新向量。没有自动生成一次真实肉鸽抽选。

这三组明确使用 `successfulCountedCreation=false` 的外部fixture，且在Python reset之后frame0显式输入 `external_final_complete`。所以没有真实alive敌人门控、死亡、释放或回收事件；不能将下面的结束帧用于真实战斗胜负。`extraSpawnDelay=0`和其他enemy flags同样是可审查的外部输入，而非EnemyDB最终运行属性。

| 输入fixture | 结果 |
|---|---|
| NORMAL，t1=0/t2=5/c1=4 | 前14spawn frame5–18，preview740/750，末spawn832；kernel结束841 |
| NORMAL，t1=1/t2=6/c1=1 | 前14spawn frame7–20，preview742/752与839/849；后spawn834/931；kernel结束936 |
| FOUR_STAR，t1=0/t2=5/c1=4 | 14spawn frame5–18，kernel结束28 |

每frame原始FP时钟与C#同样对照：serialized asset default dt raw143165440，frame0 time raw0，以unchecked raw add推进。该dt是静态资产条件值，live设置未验证。空kernel结束frame1；一个empty wave结束frame5；两wave/三empty fragments结束frame10。mode before/after schedule hooks明确排除，时钟原点为scheduler kernel start。

## 限制与发现

- 未执行游戏、读取进程或观察客户端/热修补状态。
- Runner仅重写合法且active fakeHost的核心stack路径；Unity对象销毁/禁用、host错误、取消、异常和dispose生命周期不在此次验证范围。
- ordinary非IEnumerator current在此只验证frame suspension；原生对某些unsupported marker的LogError副作用未建模。production NEXT_FRAME是诊断marker，没有Unity运行时类型身份。
- float wait helper的非finite、nonpositive delta和超支持int32范围输入在Python fail-closed。这是诊断边界，不声称与原生unchecked转换完全一致。
- C# kernel是已恢复main wave subset的第二实现，外部final gate/无计数创建fixture不能替代战斗生命周期、自然分支触发、敌人创建成功或自动门控。
- 完整List.Sort/compile/random/mode hooks的独立验证属于父agent与prototype的其他证据；本检查不重复宣称它们被C#验证。
- 唯一发现为证据注释的地址偏差：`wait_while`曾写0x1806619c0，实际保留MoveNext地址是0x1806619a0。已告知prototype修正文档；控制流结果无差异。

重现：

```powershell
& C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe /nologo /platform:x64 /optimize+ /r:System.Web.Extensions.dll /out:D:\Repo\arknights-sim\evidence\timeline_reference\TimelineReference.exe D:\Repo\arknights-sim\evidence\timeline_reference\TimelineReference.cs
& D:\Repo\arknights-sim\evidence\timeline_reference\TimelineReference.exe D:\Repo\arknights-sim\evidence\timeline_reference\reference_input.json D:\Repo\arknights-sim\evidence\timeline_reference\reference_vectors.json
Set-Location D:\Repo\arknights-sim
& C:\Users\YoChi\AppData\Local\Programs\Python\Python311\python.exe -X utf8 -m unittest tests.test_timeline_reference -v
```

`prepare_reference_input.py`可以重新生成输入，但会依赖当时compile_timeline行为；输入有变化时必须审查差异，并重新运行C#、更新经过审查的pins。不要为消除测试失败盲目覆盖参考向量。
