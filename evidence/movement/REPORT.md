# 静态移动组件与跨语言参考验证

当前交付已恢复 FP 等待点、float32 几何、默认 WALK 的带权 FIFO 寻路、Bresenham 平滑和 MOVE 路线图编译。**完整敌人移动、漏怪及战斗结束仍未接入，`autonomous_route_ready=false`、`battle_ready=false`。**

## 使用接口

```python
from arknights_probe.movement import (
    WaitCheckpoint, LocalVector2, NativeTileSnapshot,
    NativeWalkPathGrid, WalkRouteSpec, compile_walk_route,
)

# 必须提供完整、可追踪来源的逻辑坐标地块快照；逻辑 row 从底部起。
tiles = [[NativeTileSnapshot(3, 15, False, False) for col in range(3)]
         for row in range(2)]
grid = NativeWalkPathGrid(tiles, source="explicit synthetic cached-tile fixture")
nodes = grid.next_map((1, 2))
grid.generate_next_turns(nodes, (1, 2))
```

`NativeTileSnapshot` 的四个输入分别是缓存通行 mask、WALK 四方向 goto mask、障碍成本覆盖开关、障碍类判定。后二者是不同原生字段：成本覆盖产生 1000/1；raycast 检查障碍类。禁止按地块名称、可部署性或高度直接推断。`WalkRouteSpec.from_json(..., height=..., width=...)` 严格识别当前本图默认分支，其他运动模式、访问中心分支、随机范围/偏移和未知字段会失败。`compile_walk_route` 为 MOVE 与终点创建原生 next map，WAIT 位置保持 `None`；它输出路径图与带权距离，不输出移动时间或轨迹。

## 证据与实际运算

原件 GameAssembly SHA256：`583b04ff4d1b1a4b35eaf09d77d936408c25447c9e345ef0463d814b6a123fc5`。

| 组件 | 原生入口或证据 |
|---|---|
| WAIT binary32→FP、减 dt、max0、<=0 | `0x1808a8a20`, `0x1808a8a90`, `0x1808a89c0` |
| float32 GetNormalized / ClampMagnitude / Magnitude | `0x180535530`, `0x1805e7770`, `0x180535480` |
| CheckDistance / IsZero / safe normalize | `0x1866e3dc0`, `0x1866e5620`, `0x1866e5e20` |
| GridPosition local (col,row)、最近偶数归格 | `0x182104010`, `0x182103900` → `0x18059e290` |
| 四邻顺序 (1,0),(0,1),(-1,0),(0,-1) | GridPosition.cctor `0x182103c00` |
| 反向 direction 索引 [2,3,0,1] | SharedConsts.cctor `0x1866ea8c0` + metadata InitializeArray blob |
| SPFA weighted FIFO、平滑、corner/goto raycast | `0x1808a5860`, `0x1808a5fe0`, `0x1808a6290` |
| MOVE 反向 map 与 next-turn 编译 | `0x1808a3060`, `0x1808a3a10`, `0x1808a3ee0` |

每次 float 运算显式按原生 MULSS/ADDSS/DIVSS 的 binary32 顺序执行，先单精度平方和，再提升 double sqrt，再转回 Single 后逐轴除法。不是 Python double `hypot` 或统一 FP 位置。浮点假设为 SSE exceptions masked、nearest-even MXCSR；非 finite 输入及超支持范围会 fail closed。

`native_evidence.json` 是最小核验清单：`files` 数组包含 `{path, sha256}`，相对路径相对于本目录，其他路径为本机静态原生证据的绝对路径。共 15 文件 pins；三个原生报告的所有 imported ranges 都与原件匹配。`tests.test_movement_reference` 同时固定参考源码、输入、输出和这个清单本身的 SHA。更新 pins 必须审查差异，不自动接受新散列。

早期 overload/slot 误认已纠正并保留于清单：`0x180ad3e60` 是 GridPosition SetPosition；Enemy Vector2 实际调用 `0x180ad3dc0`。控制器虚槽 7/8 是 `_CalculateSteeringForce` / `CalculateIsHanging`，`CalculateTotalForce` 非虚。调查说明位于 `native_v4/movement/NOTES.md`，其中初始 pending 条目由 followups 部分更新。

## 验证结果

- 20 项 movement/reference tests 通过。
- 自有 C# x64 编译运行：60 几何输入，480 输出断言逐项一致，包含 float bits、归格、半径、归一化阈值和负 max-length 原生行为。
- 29 路径场景：1080 个完整节点快照与 348 次 raycast 一致，覆盖 cost1000 绕路、相同距离 FIFO 顺序、单向掩码、FLY_ONLY 终点、禁止拐角穿墙、方向平滑和 next-turn。
- `static_tile_fixture.json` 是显式条件 fixture：从真实资源通行声明取得 mask，但 goto=15、cost=1、obstacleLike=false；祭坛 prefab 重写与动态箱子未应用。`path_inventory.json` 用它编译 28 真实 WALK 路线，均可达。它证明编译器能消费真实路线结构，**不证明这个 fixture 是客户端实际缓存地图**。

C# 未引用、加载或调用游戏二进制。两套实现都来自同一静态证据，对照可发现移植差异；这是独立跨语言实现检查，**不是 native/client runtime oracle**。没有恢复整局 RNG 消耗顺序，也没有生成死亡、奖励或胜负。

## 当前边界与下一步

原生 controller 的速度、steering、hanging/avoid correction、tickers、foot/body offsets、状态与位置赋值链虽已拿到部分 body，尚未形成完整闭包。`Tile.Init` 缓存属性、祭坛 `TrapMode._tileOptions` 重写时序、动态箱子、敌人 canMove/buff 状态、gameMode exit permission 与 recycle timing 都未接入。当前原型继续使用显式外部生命周期输入，不能当作完整无操作战斗模拟。

最直接的下一步是恢复 Tile.Init/TrapMode 的真实地图上下文，随后闭合 controller/cursor tick 和 exit/recycle 生命周期。当前路径组件不降级到 BFS，未知机制也不静默套用任意 epsilon 或速度公式。

复现：

```powershell
& C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe /nologo /platform:x64 /optimize+ /r:System.Web.Extensions.dll /out:D:\Repo\arknights-sim\evidence\movement\MovementReference.exe D:\Repo\arknights-sim\evidence\movement\MovementReference.cs
& D:\Repo\arknights-sim\evidence\movement\MovementReference.exe D:\Repo\arknights-sim\evidence\movement\reference_input.json D:\Repo\arknights-sim\evidence\movement\reference_vectors.json
Set-Location D:\Repo\arknights-sim
python -X utf8 -m unittest tests.test_movement tests.test_movement_reference -v
```
