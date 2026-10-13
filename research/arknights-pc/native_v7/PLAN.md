# v7 研究清单

目标：替换v6受控祭坛样例中的技能准备/层掩码/ALL顺序外部输入，并追查下一阶段NPC召唤链。完整关卡与训练接口仍需后续闭合。

| 问题 | 所需证据 | 本轮处理 |
| --- | --- | --- |
| sktok_ore准备后时间/SP | BasicSkill.AssignData、Ability.SetData/UpdateBlackboard/Attach、动画时间模式、实际资源/属性输入 | skill_preparation，新增有界组件 |
| 目标side/purpose/layer mask | SideTypes/Layers cctor、TagManager层表、TargetSelector初始化 | targeting，来源化初始化参数 |
| ALL顺序/membership | generic method/type身份、PriorityQueue<WeightedTarget<Entity>>、比较器、gap/extraMode | targeting，替换v6外部ALL输出 |
| HitRange | manager初始化/注册/reset与provider回调 | targeting，空provider或有证输入；不推断实际场景已为空 |
| Physics2D overlap/同步/姿态 | Unity原生物理、UBody/Collider/Transform及实际帧相位 | 未静态闭合前保留外部快照 |
| shdopl→upeopl | 资源buff/actions、Summon coroutine、隐藏/恢复/伤害/死亡/reborn/life修改 | npc，先明确执行接口和缺口 |

REA当前无打开的native会话；复用本机已校验CLI/Ghidra流程，每轮独占Java，原件只读。新增证据位于native_v7，不修改v5/v6来源pin。目标GameAssembly.dll散列与v6一致。

核验分别记录：原件字节一致、独立转写/参考一致、受控样例组件结果、真实客户端轨迹。前三项不证明第四项。battle_ready/autonomous_route_ready/runtime_battle_validated保持false。
