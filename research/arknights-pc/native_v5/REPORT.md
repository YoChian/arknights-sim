# 原生移动、生命周期与场景规则阶段

2026-10-13。目标仍是本地 PC 客户端资源版本 `26-09-13-15-28-10-30688348` 的“猎犬病原”。原件只读；没有启动游戏、注入或连接游戏服务。执行的是我们自己的提取脚本、Ghidra静态分析和组件参考程序。

## 本轮交付

原型位于 `D:\Repo\arknights-sim`。新增：

- `runtime_movement.py`：完整显式 Tile/HoleTile 缓存、设备重写分支、方向游标、控制器加速度/避障、局部坐标取整和默认无目标路线移动。实际运行旗标与 prefab 参数必须明确。
- `lifecycle.py`：默认模式普通出生、漏怪、临时生命吸收、波次/最终成员关系、回收等待和逻辑结束请求。NPC/动态天赋、死亡状态机与Unity退场不在本组件支持范围。
- `route_runtime.py`：把单敌人的状态、路线移动、出口和回收自动接通。无需 external_resolve、external_release_wave 或 external_recycle。
- `devices.py`：自然SP的精确周期计时、确定性模拟协程分支的 preDelay、即时buff开始/结束顺序，以及祭坛伤害/模式切换请求。需要真实筛选与结算上下文才能应用到完整场景。
- `scene.py` 与 `scene-audit`：检查选定出怪、条件分支、隐藏预定义箱子、独立技能与NPC依赖，保留未知有效组件，阻止遗漏规则的整图运行。

`scripts/probe_route_lifecycle.py` 生成 `artifacts/route_lifecycle_component.json`。其开放格子、速度、初始生命、运行旗标和无天赋场景是明确的组件fixture，不能当作本图真实无人部署轨迹。默认示例会自动产生漏怪和逻辑结束请求，奖励仍为None。

## 原件覆盖与执行顺序

集中串行Ghidra三批：107、69、24个不重复地址，共200个选定入口、494个导入范围。所有条目的 decompile_completed 与 imported_memory_matches_source 为true，逐范围源字节校验均通过。计数只表示选择的函数体，不等于200种规则已恢复。

`core/results_round1..3.json` 保存完整选定结果；`core/input_round1..3.json` 保存入口与递归 UNW_FLAG_CHAININFO 范围。补充raw证据包括pool的 `raw_round4.json` 与 StartBattleCoroutine 的 `raw_round5.json`。线性反汇编可解码不证明每个字节属于实际执行CFG，函数名称亦需元数据与指令共同佐证。

`BattleController.OnTick` 的默认编译路径先增加帧与FP/Single时钟，再进行对象fixed、Map/脚本/操作/可选物理、协程、全局buff/environment和对象late。BC实例+0x68实际为global buff列表，不能当scheduler列表。ObjectManager以PriorityQueue的实际顺序各自采集 `borned && instanceUid!=0` 快照后再逐个调用；不能用alive或假定出怪顺序替代它。固定来源在 `core/frame_order_evidence.json`。

Unit/FSM阶段的MoveState先移动，Enemy随后处理cursor和出口。Born→Move当帧不会再调用新的MoveState。确定性分支会在FSM后把Transform.localPosition四位取整，再进入cursor检查；不能误读为世界坐标。

Entity.FinishMe的虚拟OnFinish完成后才调用模式DestroyEntity。普通漏怪链中，Unit的event6/波次释放和Enemy的生命/event7先执行，随后默认模式reason1选择延迟回收。零延迟和正延迟均需真实OnRecycle回调，不能把漏怪等同于立即解除最终成员。`useRecycleToFinishScheduler` 改变最终成员移除时点，必须显式给出。

Scheduler的event6/8处理函数及其数值效果已恢复，但反射订阅注册链尚未核验；单敌人逻辑后端显式绑定这些回调，不声称已经从真实启动流程自动建立监听。

## 影响正确性的修正

- 10个敌人MoveController的资源值是steering=8/maxForce=10/halfBodyWidth≈0.2，不能用构造值2.5/4覆盖。BattleOptions静态构造的STEERING_ENABLED为false，但实际开场设置仍需确认；组件两种分支都支持且不选择真实运行默认。
- TileData的advanced mask与playerSideMask是不同字段；HoleTile移动代价为1,000,000。祭坛的mode改格不能由tileKey或当前可见性推断。
- 零checkpoint路线会由BasicCursor构造启用稳定逐节点访问；这不是JSON三个visit flag的默认值。Enemy prefab的alwaysCheckCurrentPoint也需单独传入。
- 自然SP的timer以 `remaining < FP.EN5(raw42950)` 判断到期。当前资产dt下第一点在30帧，7点潜在210帧；这尚未确定AUTO→技能状态机的实际施放帧。
- ore_s/ore_buff的event1是ON_BUFF_FINISH；IMMEDIATELY的零寿命buff在OnStart之后同步Finish，不等下一帧。
- StartBattleCoroutine在deterministic=true且hotfix排除的分支调用CoroutineSimulator.StartCoroutine并同步prime；false分支调用Unity coroutine，不能当作已执行过的同一实现。
- Entity.OnFinish的间接slot118是ClearAbilities，不能把非虚拟RecycleSelfWithDelay套入该slot。最终顺序由真实FinishMe/DefaultGameMode.DestroyEntity指令和vtable身份共同复核。

## 完整场景清单与尚未完成的部分

`resources/rule_prefab_subtrees.json` 扩展到16个完整Transform预制体子树，覆盖动态扫描的Talents/Skills；原v4仅PPtr图不代表完整活跃组件。`scene_templates.json` 从21个字面根递归取得22个模板，无缺失字面引用，含空模板、NPC恢复/死亡、箱子反伤与模式效果。动态黑板构造的key仍需运行规则判断。

NPC `enemy_2133_shdopl` 会召唤 `enemy_3001_upeopl`、隐藏宿主并经子单位事件恢复；被召单位死亡可通过 `dead.value=-1` 扣生命。只统计波次初始出怪会漏掉这条链。场景还包含初始可见祭坛及8个隐藏箱子，不能因无干员而跳过它们。

完整“猎犬病原”仍需：祭坛真实target范围/side/admission与技能FSM、完整HP/死亡与mode属性变化、NPC召唤与宿主恢复、箱子激活/攻击/反伤/分支、PriorityQueue和多协程顺序、实际Rogue增益/初始生命/RNG上下文。然后才能核验完整无操作轨迹并加入基础干员。当前 `autonomous_route_ready=false`、`battle_ready=false`、`runtime_battle_validated=false`。

独立C#转写参考检查移动取整/避障/控制帧与生命周期数值边界。这些程序与Python共同依据静态原件，属于实现对照，不能代替真实客户端oracle。最终测试数和结果以 `arknights-sim/artifacts/verification.json`、`tests.txt` 为准；组件细节与固定来源见各自manifest/REPORT。

本轮最终全量验证：173项测试通过，0失败、0错误、0跳过；94个固定组件来源与9个帧顺序来源散列检查通过。7个主要客户端文件重新计算散列均与既有快照一致；这不代表遍历了所有客户端文件。独立设备C#参考另有71项有界比较通过。单敌人fixture在120帧自动完成回收与逻辑win，life从3变为2；真实完整关卡仍不开放执行。当前结果在本目录 `summary.json`。
