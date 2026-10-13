# 猎犬病原：v9 NPC 创建、Buff 容器、受击反应与回收

本轮继续恢复 PC 客户端的选定默认原生路径。新增四轮串行静态分析，共 **49 个入口、109 段精确 PE 范围**，导入字节均与原件匹配；已有 v5–v8 证据复用并保持固定清单不变。没有启动、注入、修改游戏或连接游戏服务。元数据名字仍是原生地址候选，不是客户端运行时身份证明。

## 可运行的新组合

执行 `D:\Repo\arknights-sim\scripts\probe_npc_pipeline.py`，结果为 `artifacts/npc_pipeline.json`。总核验脚本为 `scripts/verify_v9_snapshot.py`，完整测试和新旧原件核验统计在 `artifacts/verification_v9.json`。验证不自动重建 pins。

- 宿主是明确已初始化 MOVE1 的 fixture。容器注册 passive 后由真实 Start0 执行共享召唤和隐藏。宿主从完整工厂出生的路径尚未纳入此组合。
- 第 1 帧共享召唤经过新工厂 allocate→AssignData/Init hooks→BORN6，使用原图 upeopl 引用和真实资源数据，HP3500、出生延迟0；工厂、Buff 和生命周期共享同一个对象引用。
- Init hooks 时 BObject.inited(+24)仍为 false，出生时已经 true/full HP，borned(+25)直到 OnBorn 链最后才写 true。第 2 帧 BORN 剩余 FP 时间减去 dt、按原生 raw≤0 转 MOVE1，本帧不重入 Move；首次 Buff Tick 启动尚未 started 的 talent Buff。Common ability 在 Unit.OnBorn 的 Attach 阶段创建 Buff，owner 已 initialized，因此 Start0 即时执行。第 3 帧才调用明确的静止 Move provider。
- Entity.OnTick 的源码顺序是 FSM→BuffContainer.Tick→后序动作/属性/能力。Buff 容器执行 priority、UID 会员、共享 snapshot、双向迭代/Dispose、启用/MarkFinish/Finish/移除、嵌套 OwnerFinish、Clear 和受击派发；不由外部回调提供会员顺序。
- 第 10 帧提供已解码的 HP damage modifier/value500 和 NPC 当前格(3,5)/路线进度4。选定 Entity/Unit 受击反应自然调用容器，finish Buff 的动作恢复宿主并触发 Finish7。OwnerFinish 重入产生第二次恢复；lock保持0、后置 Clear 节点不执行、生命保持3。
- Finish7 在同帧执行 event6→UID24写0→event8→原始池 provider。Scheduler 按同一 Enemy 对象引用移除 final，召唤对象不增加 killed/finished 计数。Unity 对象仍存在、池后 active=false 是明确 receipt，不把 UID0 当作 Unity 销毁。
- Entity 受击的 mode_finalize/event12 和未取消时 Unit animator 回调在上述同步回收后继续，观察到 UID0；没有补入源码不存在的 alive 门控。取消伤害仍派发 Buff 受击事件，只有 disappeared 分支在 Cancel0 后提前返回。
- 独立 death2 fixture 执行 Dead.value=-1，life3→2、一次恢复，第10帧 event6 后 final仍为1；明确保留的 Single0.6 回收延迟经共享协程在第28帧写UID0/event8清final。音频 CreateBuff、动画和实际池操作仍为具名外部 provider。

## 本轮更正

`BuffContainer.OnOwnerBorn`→`Buff.OnOwnerBorn`仅事件 **12**，不是事件0，也不执行 Start。Start0由已初始化 owner 的注册路径或首次 Buff Tick 触发。早期“出生 Buff 直接在 BORN 状态发起隐藏”的推测不成立；工厂分别表示出生通知与 Start，旧固定证据不重写。

`Scheduler.OnGameReset`直接绑定 BattleEvent6 的 `_OnUnitDestroyed`，仅 useRecycleToFinishScheduler=true 时绑定 event8 的 `_OnEnemyRecycled`。精确 MethodInfo/泛型委托身份已恢复；采用首次 reset、fresh pool、固定配置的选定同步后端，不宣称整个 EventPool/bootstrap 已复现。

`Enemy.MarkUnharmful`只更新 Options 首 Boolean；它不是 BObject.isDisappeared，也不是 NPC 伤害免疫。完整 ApplyModifier 的前序 hooks、HP 写和后序 hooks 仍未闭合；本轮不会把数值500直接从 NPC HP 扣除。death2 fixture 是明确的 finish 输入，不是假造自然 HP 死亡。

## 证据与边界

子报告：`buff_container/REPORT.md`、`enemy_factory/REPORT.md`、`npc_lifecycle/REPORT.md`、`npc_damage/REPORT.md`。原件 byte proof、独立自有 C# 向量、行为检查和固定清单均由最终总验证核验；C# 对照执行的是自有转写，不是 client oracle。

仍需外部输入的主要部分：Unity allocation/Awake/reset/controller/Transform/Collider query/filter/sync、非空 runtime route、Buff Reset/filter/runtime override/attribute效果、mode/global上下文、动画/audio/Tween/原始pool/注册副作用。工厂禁止输入已 MOVE 的 actor；出生剩余时间和 Buff lifetime/remainingTime 是不同计时器。

root 组合检查覆盖创建身份/状态、受击取消、同步回收后的回调、死亡延迟、恢复下一帧、分段与 reset；全部检查结果以最终总核验文件为准。旧普通敌人的 NPC 拒绝门控保留。

**battle_ready=false，autonomous_route_ready=false，runtime_battle_validated=false，reward=None。** 完整无人操作关卡仍未完成，不能据 NPC final 清理生成全图 win 或训练奖励。后续仍需关闭物理/完整伤害与 NPC 初始化剩余边界，恢复箱子、ore_listener、自动 branch、格子改写及 run/RNG/global 上下文，再推进基础干员和训练接口。
