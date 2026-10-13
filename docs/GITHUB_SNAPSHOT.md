# GitHub 暂存快照：v9

这是当前研究代码、测试、规则快照与分析证据的私有备份。完整「猎犬病原」和训练接口仍未完成；battle_ready=false，reward=None。

已保存：Python 组件与探针、C# 独立对照源码/向量及自有小型对照程序、历史固定清单、阶段报告、验证产物、清单引用的外部分析依赖与 normalized 规则表。超过5MB的外部文本文件使用 gzip 保存，恢复后与原件 SHA256 完全一致。

游戏 EXE/DLL、global-metadata.dat、原始 AB/FlatBuffer 载荷和第三方工具安装目录不包含在仓库中。它们的本地路径仍保留在旧证据中；具体缺项见 research/snapshot_manifest.json 的 excluded_dependencies。不要把保存的468项测试结果当作一台新机器已验证成功。

## 恢复

为了保持旧证据和源码中的绝对路径，请克隆到 `D:\Repo\arknights-sim`，使用 Python3.11或更高版本。

~~~powershell
python -X utf8 scripts/restore_research_snapshot.py --verify-only
python -X utf8 scripts/restore_research_snapshot.py
~~~

默认还原到旧分析目录 `D:\Repo\.rea-tools\arknights-pc`。已有相同文件复用；存在不同内容时停止，绝不覆盖。`--research-root`可用于另行解包审阅，但不会改写旧清单或解决源码中的绝对路径依赖。

原客户端快照目录为 `D:\Hypergryph Launcher\games\Arknights`，本地资源版本26-09-13-15-28-10-30688348。完整旧证据核验还需对应客户端原件及列明的本地工具/原始载荷，安装新版客户端不能替代旧文件哈希。

依赖恢复后：

~~~powershell
python -X utf8 scripts/probe_npc_pipeline.py
python -X utf8 scripts/verify_v9_snapshot.py
~~~

原有证据和346项v9文件pin未为上传而修改。`.gitattributes`禁止Git自动改换行，避免冻结文件的字节哈希发生变化。

当前能力见[CAPABILITIES](../CAPABILITIES.md)，最新状态见[HANDOFF](HANDOFF.md)，最近验证见[verification_v9](../artifacts/verification_v9.json)。归档报告在 research/arknights-pc/native_v9/REPORT.md。
