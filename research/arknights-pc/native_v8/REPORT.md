# v8：NPC 动作/召唤/消失恢复与物理查询接口

本阶段将静态节点调查推进为可执行的受限组件，保持 v5/v6/v7 的代码和证据清单不变。目标仍是 level_rogue6_1-1“猎犬病原”的无人操作战斗环境，但全图尚未闭合。所有验证只运行我们自己的 Python/C# 程序；没有启动游戏、注入、修改客户端或访问游戏服务。

两轮串行 Ghidra：round1 61 入口/117精确范围，round2 11入口/19范围；72入口/136范围全部成功反编且导入字节与原件一致。真实元数据、原始指针表和递归 PE unwind 支持候选身份；不把候选名称当作运行时身份。两个含内嵌跳表的泛型mode dispatcher未满足bounded-leaf规则而被拒绝，记录在core/rejected_round1.json，没有扩大猜测函数范围。

## 新执行组件

- npc_actions.py：ObjectPtr UID有效性（与alive独立）、Context栈复制/恢复、ActionRunner previousResult与条件、黑板List<DataPair>有序赋值/查找及prefix绑定、Finish7/Death/ReachExit事件选择。实际BB GetInt是floor(Single)，不是旧敌人属性写回的nearest-even。Buff优先级即时插入已恢复；完整double-buffered BuffContainer遍历/修改、所有动态模式和任意节点未闭合。
- npc_restore.py：UID/setter门控、Disappear状态11、float版0.3秒等待、两个Append 0.15秒颜色segment、停协程/移除modifier/出现、DEFAULT0→默认Move1、恢复NPC当前格子和路线进度。Tween/Move hooks与FSM admission/Unity父链active/事件modifier提供者明确；不执行通用DOTween。空CP准备路线可执行，非空CP构建Reset等依赖须明确提供。
- npc_summon.py：捕获origin route/progress/UID→FP等待→allow/可选host gate→counter/Options→RouteData逐字段及checkpoint深复制→显式route/factory→progress/hostUid→scheduler列表→position/face/buffs/mode callback。零delay至少1帧，shipped false stopIfHostDead不添加alive取消，managed/dontBlockWave只入final；Unity-null创建早退不调用mode-after。随机offset/特殊route分支严格拒绝。
- physics_context.py：五个实际prefab的Transform/Rigidbody2D/collider声明和128项buffer、两次Unity bounds→OverlapArea-to-Box参数、TransformVector(radius,0,0)→Single magnitude、filter初始字节、查询阶段契约与版本化external结果绑定。Circle中心分支取决于实际CircleColliderOverlapFixed marker，独立Rigidbody2D声明不能代替该marker；已按精确MethodSpec纠正初始泛型helper误认。它不生成Unity world bounds、TransformVector、CheckConsistency、命中、Simulate或SyncTransforms结果。UnityPlayer内507项名称/地址平行数组尚未证明注册配对，候选不是引擎oracle。

## 可重现组合

运行 D:/Repo/arknights-sim/scripts/probe_npc_component.py。初始化actor/buff与零CP route是explicit fixture；第0帧passive触发共享召唤和隐藏，第1帧创建NPC，第9帧宿主SetActive(false)。第10帧提供NPC当前格子(3,5)/进度4及ON_TAKE_DAMAGE10信号后，宿主恢复至该格/route/progress；显式同步finish7/event4会员回调使这个fixture恢复两次，lock仍0、Clear不执行、life3不变。第11帧退出DISAPPEAR并激活，第12帧才调用Move provider。独立reason2信号通过Dead/dead.value=-1使life3→2并恢复一次。这不是一般BuffContainer固定两次恢复的证明，也不是自动伤害/完整NPC生命周期：NPC HP/physics、真实factory/birth/mode/pool、native会员派发均外部，final保留1个待回收成员，不伪造胜利。

运行 scripts/probe_physics_altar.py。在原v7来源化准备祭坛样例中加入explicit bounds/filter/hit receipts与查询epoch。仪表化第一query为第210帧objects_fixed，首次伤害仍227帧；18 query/18×500，第4325帧普通laxe死亡，第4343帧回收。query可以发生在Simulate之前。receipt必须对应同一参数fingerprint、frame/phase/transformRevision/sceneRevision，否则拒绝；hits仍是明示fixture。

## 验证与继续

全量入口 scripts/verify_v8_snapshot.py，固定证据在 evidence/v8/manifest.json，最新统计以 artifacts/verification_v8.json 为准。代码不自动repin，pin_v8_evidence.py仅用于已复审文件。每个子组件报告/证据分别在npc_actions、npc_restore、summon、physics_context目录。

battle_ready=false、autonomous_route_ready=false、runtime_battle_validated=false、reward=None继续保持。下一步需关闭真实Unity query/sync/pose/过滤结果、NPC factory/模式回收与完整Buff事件、非空路线检查点；再接箱子/ore_listener/自动branch/格子改写和scheduler/run/RNG/global上下文，获得完整无人操作轨迹后再加基础干员和训练接口。
