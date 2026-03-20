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
- 违反或实质性改变已冻结的数值语义契约（例如四核求解器结构、装配无副作用、trial/commit 语义、模型演化边界等）
- 公共 API（如 `run_case`、`export_dataset`）的删除或语义改变
- 不再保证旧版本结果可复现

主版本号变化意味着：**已有配置文件、数据集或 AI 模型需要迁移或重新生成。**



The MAJOR version is incremented **only when breaking changes are introduced**.

Breaking changes include, but are not limited to:

- Incompatible changes to `config_schema`
- Incompatible changes to dataset directory structure or field semantics
- Changes in the physical meaning of simulation results under identical configurations
- Violations of, or substantive changes to, frozen numerical semantic contracts (e.g., the Four-Core Solver Structure, side-effect-free assembly, trial/commit semantics, or model-evolution boundaries)
- Removal or semantic changes of public APIs (e.g., `run_case`, `export_dataset`)
- Loss of reproducibility guarantees for results from previous versions

A MAJOR version bump indicates that **existing configuration files, datasets, or AI models may require migration or regeneration**.

> 说明：  
> 这里所谓“破坏性变更”不仅包括配置、数据集与公共 API 的显式结构变化，也包括数值语义层的破坏。  
> 如果某项修改虽然未改变接口形式，但破坏了已冻结的执行契约或数值语义约束（如四核结构、无副作用边界、试算/提交语义），则该修改同样应被视为 MAJOR 级变化。

> Note:  
> “Breaking change” here includes not only explicit structural changes to configuration, > datasets, and public APIs, but also semantic breakage at the numerical level.  
> If a change preserves interface shape but violates frozen execution contracts or numerical semantic constraints (such as the Four-Core structure, side-effect boundaries, or trial/commit semantics), it SHALL also be treated as a MAJOR-level change.

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

## 版本层级体系 | Versioning Layers

在 PeriSci 中，版本治理所对应的“契约”并不限于公共 API，而是覆盖输入契约、执行契约与输出/数据契约三层。  因此，本文件中的版本层级（Repository / Schema / Dataset）并不是普通软件版本号的并列列表，而是对不同契约层的分层治理。

In PeriSci, the “contract” governed by versioning is not limited to public APIs; it spans the input contract, execution contract, and output/data contract.  Therefore, the version layers defined in this file (Repository / Schema / Dataset) are not a flat list of software versions, but a layered governance system for different contract layers.

为避免在长期演进过程中产生版本语义混淆，本项目采用**分层版本体系**。
不同层级的版本号具有不同治理职责，彼此之间不可混用。
To prevent semantic confusion during long-term evolution, this project adopts a layered versioning system.
Each version layer carries a distinct governance responsibility and SHALL NOT be used interchangeably.

本规范在 v0.2 起正式冻结以下版本层级关系。
As of v0.2, the following version layer relationships are formally frozen.

------

### 1. 仓库版本 | Repository Version

即 Git Tag（`vMAJOR.MINOR.PATCH`）。
The Repository Version refers to the Git Tag (vMAJOR.MINOR.PATCH).

其职责：

- 标识源代码的整体状态
- 对应一个可长期复现的代码快照
- 用于论文、报告与工程系统引用

Its responsibilities are:

- To identify the overall state of the source code
- To represent a long-term reproducible code snapshot
- To serve as a citation reference in academic publications, reports, and engineering systems

仓库版本遵循本文件前述的 SemVer 规则。
The Repository Version follows the SemVer rules defined earlier in this document.

仓库版本**不等同于**数据集版本或 schema 版本。
The Repository Version SHALL NOT be considered equivalent to the Schema Version or the Dataset Version.

------

### 2. Schema 版本 | Schema Version

指 `config_schema` 的版本标识。
The Schema Version refers to the version identifier of `config_schema`.

其职责：

- 定义输入契约结构
- 约束物理意图的合法表达方式
- 决定配置文件的结构合法性

Its responsibilities are:

- To define the input contract structure
- To constrain the valid expression of physical intent
- To determine the structural validity of configuration files

规则：

- 不兼容修改必须提升主版本号
- 向后兼容新增字段可提升次版本号
- 不得通过默认值隐式修改语义

Rules:

- Incompatible modifications MUST result in a MAJOR version increment
- Backward-compatible additions MAY increment the MINOR version
- Semantic changes SHALL NOT be introduced implicitly via default values

Schema 版本用于判定配置文件是否可被当前执行边界接受。
The Schema Version is used to determine whether a configuration file can be accepted by the execution boundary.

Schema 版本**不得由仓库版本隐式承担**。
The Schema Version SHALL NOT be implicitly substituted by the Repository Version.

------

### 3. 数据集版本 | Dataset Version

定义于 `manifest.json` 中的 `dataset_version` 字段。
The Dataset Version is defined by the dataset_version field in manifest.json.

其职责：

- 表示数据资产的结构与治理语义状态
- 控制冻结语义与版本红线
- 作为 AI 训练与论文引用的核心标识

Its responsibilities are:

- To represent the structural and governance semantic state of the data asset
- To control freeze semantics and version red-line enforcement
- To serve as the core identifier for AI training workflows and academic citation

规则：

- 任何破坏性结构修改必须提升主版本号
- 不得通过 `tool_version` 替代 dataset_version
- dataset_version 的变更必须符合 dataset-spec 中的红线规则

Rules:

- Any breaking structural modification MUST increment the MAJOR version
- `tool_version` SHALL NOT substitute for `dataset_version`
- Changes to `dataset_version` MUST comply with the red-line rules defined in dataset-spec

数据集版本与仓库版本可以不同步，但必须在 provenance 中建立明确绑定关系。
The Dataset Version and the Repository Version MAY evolve independently, but a clear binding relationship MUST be established in provenance.

> 补充说明：  
> `cases/` 中的 canonical cases 并不直接等同于 `dataset_version` 所管理的数据资产版本，但它们构成了验证数据契约、执行契约与结果语义是否发生漂移的重要基准。  
因此，任何导致 canonical cases 行为语义变化的修改，都必须通过版本记录、回归验证与必要时的迁移说明加以治理。

> Additional note:  
> Canonical cases under `cases/` are not themselves identical to the data assets governed by `dataset_version`, but they form a critical baseline for validating whether data contracts, execution contracts, and result semantics have drifted.  
Therefore, any change that alters the semantic behavior of canonical cases MUST be governed through version records, regression validation, and migration notes where necessary.

------

### 4. 层级关系约束 | Layered Relationship Constraints

以下约束在 v0.2 起生效：

1. 仓库版本、Schema 版本、数据集版本必须在语义上相互一致；
2. 任何破坏性 schema 修改，若影响 C 梁输出结构，必须同步提升 dataset_version 主版本号；
3. 数据集生成时必须记录：
   - 仓库版本（Git Tag）
   - Schema 版本
   - Dataset 版本
4. 禁止仅通过仓库版本推断数据资产语义。

#### 4.1 Freeze 层级桥接规则（规范性澄清） | Freeze Layer Bridging Rule (Normative Clarification)

仓库版本 Tag 的创建 **不自动等同于** 数据集的冻结资格。
A Repository Version Tag **does NOT automatically imply** dataset freeze eligibility.

数据集是否可被冻结，仅由 `dataset-spec` 中定义的：

- 结构验证（L1）
- 溯源验证（L2）
- 一致性验证（L3）
- 冻结验证（L4）
- 以及版本红线规则

共同判定。

Dataset freeze eligibility is governed exclusively by the validation levels (L1–L4) and red-line rules defined in `dataset-spec`.

仓库版本 Tag 仅表示代码状态可引用；数据集冻结表示资产状态可治理。
A repository Tag indicates that the code state is citable; Dataset freeze indicates that the asset state is governance-eligible.

两者属于不同层级，不得混用或替代。
They belong to different governance layers and SHALL NOT be used interchangeably or as substitutes.

------

### 5. 强制引用规则 | Mandatory Citation Rules

在以下场景中，必须显式记录版本层级：

- 数据集发布
- AI 模型训练
- 学术论文引用
- 工程报告归档

The following scenarios REQUIRE explicit recording of version layers:

- Dataset publication
- AI model training
- Academic citation
- Engineering report archiving

最低引用要求为：

- 仓库版本（Git Tag）
- 数据集版本（dataset_version）

The minimum citation requirements are:

- Repository Version (Git Tag)
- Dataset Version (`dataset_version`)

当涉及配置结构或模型演进时，必须同时记录：

- Schema 版本

When configuration structure or model evolution is involved, the Schema Version MUST also be recorded.

禁止使用：

- 移动分支名（如 master）
- 未打 Tag 的提交哈希
- 省略 dataset_version 的引用

The following practices are prohibited:

- Referencing a moving branch name (e.g., `master`)
- Referencing an untagged commit hash
- Omitting `dataset_version`

版本引用不完整视为不可复现状态。
Incomplete version citation SHALL be considered a non-reproducible state.

------

### 6. ADR 触发与版本影响 | ADR Triggers and Version Impact

当某项变更：

- 触及架构硬边界
- 改变长期稳定锚点的治理语义
- 破坏冻结契约
- 改写长期技术路线

则该变更不仅需要版本标记，还应通过 ADR 明确记录其背景、决策理由、边界影响与迁移后果。

When a change:

- touches a hard architectural boundary
- changes the governance semantics of a long-term stability anchor
- breaks a frozen contract
- rewrites a long-term technical direction

it requires not only version marking, but also an ADR that explicitly records its context, rationale, boundary impact, and migration consequences.

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
