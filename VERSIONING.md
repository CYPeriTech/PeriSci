# 版本管理规范 | Versioning Policy

本项目采用一种 **面向科学计算、CAE 软件与 AI 物理仿真平台的 SemVer 改进版本管理策略**。

版本 Tag 代表一个 **可以长期复现、可以被引用的稳定状态**，适用于：

- 学术论文引用
- 仿真数据集生成
- 工程分析与报告
- AI 模型训练与验证



This project adopts an **enhanced Semantic Versioning (SemVer) strategy** tailored for scientific computing, CAE software, and AI-oriented physics simulation platforms.

A version tag represents a **stable state that is reproducible over the long term and suitable for citation**, including but not limited to:

- Academic publications
- Simulation dataset generation
- Engineering analysis and reports
- AI model training and validation

---

## 版本号格式 | Version Format

所有正式版本均采用以下格式：| All official releases follow the format:

    vMAJOR.MINOR.PATCH

示例（Examples）：
- v0.1.0
- v0.2.0
- v0.2.1
- v1.0.0

---

## 版本号含义 | Meaning of Version Numbers

### 主版本号（MAJOR）| Major Version

**仅当发生破坏性变更（Breaking Change）时，才递增主版本号。**

破坏性变更包括（但不限于）：

- `config_schema` 的不兼容修改
- 数据集目录结构或字段语义的不兼容修改
- 相同配置下仿真结果物理意义发生改变
- 公共 API（如 `run_case`、`export_dataset`）的删除或语义改变
- 不再保证旧版本结果可复现

主版本号变化意味着：**已有配置文件、数据集或 AI 模型需要迁移或重新生成。**



The MAJOR version is incremented **only when breaking changes are introduced**.

Breaking changes include, but are not limited to:

- Incompatible changes to `config_schema`
- Incompatible changes to dataset directory structure or field semantics
- Changes in the physical meaning of simulation results under identical configurations
- Removal or semantic changes of public APIs (e.g., `run_case`, `export_dataset`)
- Loss of reproducibility guarantees for results from previous versions

A MAJOR version bump indicates that **existing configuration files, datasets, or AI models may require migration or regeneration**.

---

### 次版本号（MINOR）| Minor Version

在 **保持向后兼容的前提下新增功能** 时，递增次版本号。

典型场景包括：
- 新增物理模型（损伤模型、耦合项等）
- 新增求解器或分析模式
- `config_schema` 新增字段（旧字段仍然有效）
- 数据集新增字段（旧数据仍可读取）
- 新增用户入口（教学 / 工程 / AI）

旧版本的配置文件与数据集 **必须仍然可以使用**。



The MINOR version is incremented when **new features are added while maintaining backward compatibility**.

Typical scenarios include:

- Addition of new physical models (e.g., damage models, coupling terms)
- Addition of new solvers or analysis modes
- New fields added to `config_schema` (existing fields remain valid)
- New fields added to datasets (existing datasets remain readable)
- Introduction of new user entry points (education / engineering / AI)

Configuration files and datasets from previous versions **must remain usable**.

---

### 补丁版本号（PATCH）| Patch Version

用于 **不改变接口与物理语义的修复与改进**。

典型场景包括：
- Bug 修复
- 性能优化（不影响结果含义）
- 文档更新
- 测试与 CI 改进

补丁版本升级应当是 **安全升级**。



The PATCH version is used for **fixes and improvements that do not alter interfaces or physical semantics**.

Typical scenarios include:

- Bug fixes
- Performance optimizations (without affecting result interpretation)
- Documentation updates
- Improvements to testing and CI

Patch upgrades are expected to be **safe upgrades**.

---

## Tag 创建规则 | Tagging Rules

- 版本 Tag **只能在 `master` 分支上创建**
- 功能分支（`feat/*`）必须先合并到 `master`
- Tag 一经创建，**不得删除或重写**
- Tag 表示维护者愿意对外长期支持和推荐使用的状态
- Version tags **must be created on the `master` branch only**
- Feature branches (`feat/*`) must be merged into `master` before tagging
- Once created, tags **must not be deleted or rewritten**
- A tag represents a state that maintainers are willing to recommend and support for long-term external use

---

## 何时创建 Tag | When to Create a Tag

满足以下条件时，应创建版本 Tag：
- 一个阶段性里程碑已经完成
- `master` 分支 CI 全部通过
- 示例与教程可以正常运行
- 仿真结果具备可复现性与可追溯性
- 该状态适合被论文或数据集引用

并非每次合并都需要创建 Tag。



A version tag should be created when all of the following conditions are met:

- A milestone has been completed
- All CI checks on the `master` branch have passed
- Examples and tutorials run successfully
- Simulation results are reproducible and traceable
- The state is suitable for citation in papers or datasets

Not every merge requires the creation of a version tag.

---

## Tag 与分支的关系 | Relationship Between Tags and Branches

- `master` 为持续向前发展的主干分支
- Tag 是 `master` 的不可变快照
- 当需要长期维护旧版本时，未来可能引入 `release/x.y.z` 分支
- `master` is the continuously evolving main branch
- A tag is an immutable snapshot of `master`
- If long-term maintenance of older versions is required, `release/x.y.z` branches may be introduced in the future

---

## 可复现性与可追溯性 | Reproducibility and Traceability

每一个版本 Tag 必须支持：
- 完整重建仿真输入
- 精确追溯到源代码提交
- 对结果含义的一致解释

在数据集与 AI 工作流中，**必须记录版本 Tag，而不是使用移动分支名。**



Each version tag must support:
- Complete reconstruction of simulation inputs
- Precise traceability to the source code commit
- Consistent interpretation of result semantics

In datasets and AI workflows, **the version tag must be recorded instead of a moving branch name**.

---

## v1.0.0 之前的版本说明 | Pre-1.0 Versions

在 v1.0.0 之前：

- API 与配置可能持续演化
- 向后兼容为“尽力保证”
- 破坏性变更将被清晰记录



Before v1.0.0:

- APIs and configurations may continue to evolve
- Backward compatibility is provided on a best-effort basis
- Breaking changes will be clearly documented

---

## 引用建议 | Citation Recommendation

在论文或报告中引用本项目时，建议使用：| When citing this project in papers or reports, the following format is recommended:

    Simulation performed using <ProjectName> vX.Y.Z
