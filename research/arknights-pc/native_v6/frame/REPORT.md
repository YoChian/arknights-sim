# 共享帧与协程组件（静态证据）

本组件恢复 BObject 注册表和 deterministic CoroutineSimulator 的部分执行语义，未运行游戏。BattleController 初始化、Unity 对象身份与 activeInHierarchy、Map/Physics/dialog/global-buff 模块、实际初始时钟仍是外部上下文。

- `BObject.CompareTo` 0x180662560 / 0x1806625f0 比较 offset0x18 的 UInt32 instanceUid。0x185ee3720 的真实身份为 System.UInt32.CompareTo（metadata241404/token0x6000cbf），原件 JB/SETA 也是无符号比较。round2 的临时 `Int32_CompareTo` 标签错误；`identity_corrections.json` 明确更正，原始导出不被改写。
- `PriorityQueue<BObject>.Add` 的 source-bound 调用入口0x1851afc50按比较结果线性插入：new.CompareTo(existing)>0才继续，否则插在当前项之前。因此相等 UID 也插到旧项之前。不是堆，也不按 Python 注册顺序执行。BObject.get_priority0x180663070返回0，但该字段不是这条 Add 的排序键。
- ObjectManager.OnFixedUpdate0x1808d5300与OnLateFixedUpdate0x1808d54d0各自重新复制 validAndBorned 对象，再逐项虚拟调用；快照复制后的循环不重新检查 alive/UID/borned。validAndBorned0x180663080为borned且UID非0。Character额外注册表、已销毁的Unity对象别名不在本组件范围。
- CoroutineSimulator.StartCoroutine0x18065d200先分配 UInt64 handle，立即调用 RuntimeHandler.MoveNext，再将尚活跃的handler加入共享list/dict。嵌套启动会改变全局counter，外层仍返回之前分配的handle。
- SimulateTick0x18065d0a0先复制pendingList再循环。固定对象阶段启动的routine会在同帧协程阶段再次推进；协程阶段中新启动的routine只被立即prime，随后等待下次快照。
- RuntimeHandler.MoveNext0x18065ff70检查Unity owner存在和GameObject.activeInHierarchy。Entity.alive不等同于这两个条件。Stop0x180660310清空栈并置无效id，没有调用iterator.Dispose；StopCoroutine0x18065d580从pending集合删除。已被本帧快照复制的停止handler因空栈也不再推进。

`frame_runtime.py` 的 SelectedFrameLoop只连接明确的对象fixed、显式前置模块、协程、显式后置模块、对象late阶段。模块输入不能被当成已实现的完整BattleController。测试覆盖新增/移除对象、相等UID、UInt32边界、协程重入和当帧两次推进；它们是我们编写的行为测试，不能证明实际客户端逐帧一致。

`battle_ready=false`；`autonomous_route_ready=false`；`runtime_battle_validated=false`。
