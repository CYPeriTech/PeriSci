# 系统架构与分层边界 | Architecture and Layer Boundaries

本文档定义 PeriSci 的系统架构、分层边界与长期稳定的设计契约。
其目标是：在项目早期就建立清晰的“不可轻易改动”的边界，使系统能够在
教学/科研、工程应用与 AI 数据生产三条路线下持续生长而不失控。

This document defines the system architecture, layer boundaries, and long-term
design contracts of PeriSci. The goal is to establish a small set of **hard-to-change**
boundaries early, enabling sustainable growth for education/research, engineering
applications, and AI data production without architectural drift.

---

<a id="who_read"></a>

### 读者指南 | Who Should Read What

本架构文档面向不同类型的读者，其关注重点有所不同。
以下指南可帮助你快速定位最相关的章节。

This architecture document serves different audiences with different focuses.
The guide below helps you quickly identify the most relevant sections.

- **学生 / 初学者（学习与理解方法）| Students / Beginners (Learning and Understanding Methods)**  
  建议重点阅读：第 1、2、3 节  
  Focus on: Sections 1, 2, and 3

- **科研人员与工程用户（正确使用与结果可信）| Researchers and Engineering Users (with Correct Usage and Reliable Results)**  
  建议重点阅读：第 2、3、4、6 节  
  Focus on: Sections 2, 3, 4, and 6

- **贡献者与维护者（架构演进与长期维护）| Contributors and Maintainers (Architecture Evolution and Long-Term Maintenance)**  
  建议通读全文，尤其是第 4、5、6、7 节  
  Read the full document, especially Sections 4, 5, 6, and 7

---

<a id="toc"></a>

## 目录 | Table of Contents

1. [PeriSci 的核心定位 | Core Positioning](#core-positioning)

2. [架构总览 | High-Level Architecture](#high-level-architecture)
   - 2.1 [架构分层示意 | Layered Architecture Illustration](#layered-architecture-illustration)
   - 2.2 [依赖方向与禁止规则 | Dependency Direction and Forbidden Coupling](#dependency-direction-and-forbidden-coupling)
   - 2.3 [职责与非职责 | Responsibilities vs Non-Responsibilities](#responsibilities-vs-non-responsibilities)
   - 2.4 [分层稳定性等级 | Layer Stability Levels](#layer-stability-levels)

3. [仓库组织与质量门禁 | Repository Organization and Quality Gates](#repository-organization-and-quality-gates)
   - 3.1 [core/ —— 数值内核的组织边界 | Organizational Boundary of the Numerical Kernel](#organizational-boundary-numerical-kerne)
   - 3.2 [api/ —— 契约与边界的组织载体 | Organizational Carrier of Contracts and Boundaries](#organizational-carrier-contracts-boundaries)
   - 3.3 [python/ —— 工作流代码的集中位置 | Centralized Location for Workflow Code](#centralized-location-workflow-code)
   - 3.4 [apps/ —— 工程与批处理入口的组织边界 | Organizational Boundary of Engineering and Batch Entry Points](#organizational-boundary-engineering-batch-entry-points)
   - 3.5 [cases/ —— 标准算例库 | Canonical Case Repository](#canonical-case-repository)
   - 3.6 [examples / tests / docs —— 质量门禁 | Quality Gates](#quality-gates)
   - 3.7 [根目录治理文件 | Root-Level Governance Files](#root-level-governance-files)

4. [不可轻易改动的设计边界 | Hard-to-Change Design Boundaries](#hard-to-change-design-boundaries)
   - 4.1 [Boundary 1 — API 契约三件套必须长期存在 | The API Contract Trio Must Persist](#api-contract-trio-must-persist)
   - 4.2 [Boundary 2 — config_schema 的语义稳定性优先 | Semantic Stability of config_schema](#semantic-stability-of-config_schema)
   - 4.3 [Boundary 3 — Dataset 规范必须可版本化且可追溯 | Dataset Specifications Must Be Versioned and Traceable](#dataset-specifications-must-be-versioned-and-traceable)
   - 4.4 [Boundary 4 — 数值内核（core）与上层完全解耦 | Strict Decoupling of the Numerical Kernel （core）from Upper Layers](#strict-decoupling-of-core-from-upper-layers)
   - 4.5 [Boundary 5 — 可复现性与可追溯性是发布版本的硬门槛 | Reproducibility and Provenance Are Release Requirements](#reproducibility-and-provenance-are-release-requirements)
   - 4.6 [Boundary 6 — 教学 / 工程 / AI 的入口一致性 | Entry-Point Consistency Across Use Cases](#entry-point-consistency-across-use-cases)
   - 4.7 [Boundary 7 — 标准算例库（cases）必须长期存在 | The Canonical Case Repository Must Persist](#canonical-case-repository-must-exist)

5. [变更管理与 ADR | Change Management and ADR](#change-management-and-adr)
   - 5.1 [何时必须使用 ADR | When ADRs Are Required](#when-adrs-are-required)
   - 5.2 [何时不需要 ADR | When ADRs Are Not Required](#when-adrs-are-not-required)
   - 5.3 [ADR 的基本内容 | Required Contents of an ADR](#required-contents-of-an-adr)
   - 5.4 [ADR 的存放与命名约定 | ADR Location and Naming Convention](#adr-location-and-naming-convention)
   - 5.5 [ADR 与版本策略的关系 | Relationship Between ADRs and Versioning](#relationship-between-adrs-and-versioning)

6. [可演进的“软边界” | Evolvable “Soft Boundaries”](#evolvable-soft-boundaries)
   - 6.1 [用户体验与入口形式 | User Experience and Entry Forms](#user-experience-and-entry-forms)
   - 6.2 [内部实现与性能优化 | Internal Implementation and Performance Optimization](#internal-implementation-and-performance-optimization)
   - 6.3 [扩展能力与插件式集成 | Extension Capabilities and Plugin-Based Integration](#extension-capabilities-and-plugin-based-integration)
   - 6.4 [文档、示例与测试体系 | Documentation, Examples, and Testing System](#documentation-examples-and-testing-system)
   - 6.5 [标准算例资产（cases） | Canonical Case Assets](#canonical-case-assets)
   - 6.6 [软边界与版本策略的关系 | Relationship Between Soft Boundaries and Versioning](#relationship-between-soft-boundaries-and-versioning)

7. [附：常见反模式（必须避免） | Appendix: Common Anti-Patterns](#appendix-common-anti-patterns)
   - 7.1 [Anti-Pattern 1 — 绕过 API 直接访问 core](#bypassing-the-api-to-access-core-directly)
   - 7.2 [Anti-Pattern 2 — 在入口层引入新的物理语义](#introducing-new-physical-semantics-at-entry-layers)
   - 7.3 [Anti-Pattern 3 — 将数据集当作物理真理来源](#treating-datasets-as-physical-ground-truth)
   - 7.4 [Anti-Pattern 4 — 为性能牺牲可复现性](#sacrificing-reproducibility-for-performance)
   - 7.5 [Anti-Pattern 5 — 将临时方案固化为架构](#freezing-temporary-workarounds-into-the-architecture)
   - 7.6 [Anti-Pattern 6 — 用路线图代替架构承诺](#treating-roadmaps-as-architectural-commitments)

---

<a id="core-positioning"></a>

## 1. PeriSci 的核心定位 | Core Positioning

- PeriSci 是以 **近场有限元法（PeriFEM）** 为中心的 CAE 开源平台。
- 目标是提供一个**物理可信的仿真基座**：可教学、可科研、可工程化、可被 AI 调用。
- 项目早期坚持“最小但正确”：优先稳定**接口契约与可复现性**，功能逐步生长。

- PeriSci is an open-source CAE platform centered on **PeriFEM**.
- It aims to provide a **physics-grounded simulation backbone** for education,
  research, engineering use, and AI integration.
- Early-stage strategy: “minimal but correct” — stabilize **contracts and reproducibility**
  first, grow features incrementally.

---

<a id="high-level-architecture"></a>

## 2. 架构总览 | High-Level Architecture

PeriSci 采用分层架构，核心思想是：

- **核心数值内核（core）** 不依赖上层工作流与语言绑定；
- **稳定 API（api）** 是项目“对外承诺”，上层一切以其为入口；
- **Python（python）** 是工作流层与生态层，用于教学与 AI；
- **工程应用（apps）** 提供工程化命令行入口；
- **标准算例库（cases）** 提供可复现的仿真输入与参考算例，作为 examples、tests 与数据生产工作流共享的基础输入来源；
- **examples/tests/docs** 承担教学、验证与规范的职责（采用算例驱动生长模式，参见 README的核心理念）。

PeriSci uses a layered architecture:

- **core**: numerical kernel independent of workflows and language bindings;
- **api**: stable public contracts — the only supported entry for upper layers;
- **python**: workflow and ecosystem layer for teaching and AI;
- **apps**: engineering-grade CLI entry points;
- **cases**: a repository of reproducible simulation cases providing canonical input configurations and reference problems shared by examples, tests, and dataset-generation workflows;
- **examples/tests/docs**: education, verification, and specifications (Adopt "case-driven growth model", refer to README - Core Philosophy).

---

<a id="layered-architecture-illustration"></a>

### 2.1 架构分层示意 | Layered Architecture Illustration

PeriSci 的整体架构采用**严格的分层设计（strict layering）**。
每一层都有清晰的职责边界、依赖方向和稳定性要求，以保证系统在长期演进中保持可维护性、可复现性与生态一致性。

PeriSci follows a **strict layered architecture**.
Each layer has clearly defined responsibilities, dependency directions, and stability requirements to ensure long-term maintainability, reproducibility, and ecosystem consistency.

---

PeriSci 的整体结构可以从“运行时架构、数值实验体系与治理层”三个互补层面，以及一个“长期稳定性结构”来理解。下图给出系统的概念总览：

The overall structure of PeriSci can be understood through three complementary aspects — the runtime architecture, the numerical experiment system, and the governance layer — together with a long-term stability structure. The following diagram gives a conceptual overview of the system:

```
PeriSci
├─ Runtime Architecture
│ └─ python / apps → api → core
│
├─ Numerical Experiment System
│ └─ examples
│ ├─ teaching / demonstration
│ └─ exploration / incubation → cases → tests
│
├─ Governance Framework
│ └─ AUTHORS / CITATION / LICENSE / CODE_OF_CONDUCT / CHANGELOG / VERSIONING / MAINTAINERS / CONTRIBUTING
│
└─ Long-term Stability Structure
  └─ core → api → cases
```

这张图并不是对仓库目录结构的逐项展开，而是对 PeriSci 架构逻辑的压缩表达。

其中：

- **Runtime Architecture** 描述系统能力如何被调用
- **Numerical Experiment System** 描述示例、算例与回归测试如何组织学习、实验与可复现资产
- **Governance Framework** 描述项目如何通过版本策略、协作规则与维护责任等治理文件维持长期演进。
- **Long-term Stability Structure** 描述系统长期稳定性依赖的关键结构：`core`、`api` 与 `cases`

This diagram is not a line-by-line expansion of the repository layout. Instead, it is a compressed view of the architectural logic of PeriSci.

In particular:

- **Runtime Architecture** describes how system capabilities are invoked
- **Experiment System** describes how examples, canonical cases, and tests organize learning, experiments, and reproducible assets
- **Governance Framework** describes how the project maintains long-term evolution through governance files such as versioning policies, contribution rules, and maintainer responsibilities.
- **Long-term Stability Structure** highlights the key elements that anchor long-term stability: `core`, `api`, and `cases`

> 需要进一步说明的是，`core → api → cases` 表示的是系统长期稳定性的锚点结构，而不是执行过程本身。  其中，`api` 层承载三梁执行结构在系统层面的对外契约形态；`core` 承载四核求解器结构及其数值语义；`cases` 则作为 canonical case assets，承担实验可复现性的稳定锚点与回归验证载体。
> It should be further clarified that `core → api → cases` represents the anchor structure of long-term system stability, rather than the execution process itself.  Within this structure, the `api` layer carries the outward contractual form of the Three-Beam execution structure, `core` carries the Four-Core solver structure and its numerical semantics, and `cases` serve as canonical case assets anchoring experiment reproducibility and regression validation.


>需要特别强调的是，`cases` 不是对外 API 契约本体，也不是运行时调用链的一部分；它作为 canonical case repository，承担的是实验可复现性的稳定锚点与契约验证载体的角色。
>It must be emphasized that `cases` is neither the public API contract itself nor part of the runtime call chain; as the canonical case repository, it serves as the stability anchor of experiment reproducibility and as a verification carrier of system contracts.

---

#### 运行时分层总览 | Runtime Layer Overview

下图进一步展开 Runtime Architecture 的主要分层关系；其中 `cases/` 作为标准算例资产，与运行时层交互，但不属于运行时调用链本身。

The following diagram further expands the major runtime layers. The `cases/` directory interacts with the runtime architecture as a canonical case asset layer, but it is not itself part of the runtime call chain.

```text
+====================================================================+
| Users | 用户
| - Students / Teachers (learning & teaching) |
| - Researchers / Engineers (problem solving) |
| - AI / Data workflows (dataset generation & training) |
+====================================================================+

            |                                 |
            |（工作流程与脚本）                   |（命令行界面与批处理/高性能计算）
            | (workflow & scripting)          | (CLI & batch / HPC)
            v                                 v

+======================================+  +======================================+
| python/ —— 工作流与生态层                  | apps/ —— 工程入口层
| Workflow & Ecosystem Layer              | Engineering Entry Layer
|                                         |
| - Tutorials / notebooks / scripts       | - perisci-run / perisci-export
|   （教程 / 笔记 / 脚本）                   |
| - Param sweep / automation              | - Batch jobs / HPC integration
|   （参数扫描 / 自动化）                     |   （批处理作业 / 高性能计算集成）
|                                         |
| - AI dataset generation helpers         | - Diagnostics / logging knobs
|   （数据集生成工具）                        |   （诊断 / 日志调节旋钮）
|                                         |
| - AI framework adapters                 |
|   （与 AI 框架的接口适配）                  |
|   (TensorFlow / MindSpore / PyTorch)    |
|                                         |
| * 快速演进层                              | * 工程稳定入口
|   Fast-evolving layer                   |   Engineering-stable entry layer
|                                         |
| * 不承诺长期稳定 API                       | * 不定义新的配置语义或物理语义
|   No long-term API stability            |   Must NOT define new configuration
|                                         |   or physics semantics
+======================================+  +======================================+

                |
                |（标准算例输入 / Standardized case inputs）
                v

+====================================================================+
| cases/ —— 标准算例库
| Canonical Simulation Cases
|
| - reproducible config inputs
|   （可复现的配置输入）
|
| - canonical simulation cases
|   （标准算例）
|
| - canonical cases for tests and dataset workflows
|   （tests / 数据生产流程使用的标准算例）
+====================================================================+

                |
                |（稳定的功能调用 / Stable function calls）
                v

+====================================================================+
| api/ —— 稳定对外契约层 | Stable Public Contract Layer
|
| - config_schema (versioned & validated)
|   作用：声明 case 输入 config 的结构、字段类型、含义与默认值
|
| - run_case(config) -> results
|   作用：执行一次完整仿真并返回标准化结果对象
|
| - export_dataset(results, spec) -> dataset_dir
|   作用：按照规范导出可复用的数据集目录
|
| * 对外“承诺层”（Contract layer）
| * 教学 / 工程 / AI 的共同入口
+====================================================================+

                |
                |（结构化数据与控制流程 / Structured data & control）
                v

+====================================================================+
| core/ —— 数值计算内核 | Numerical Kernel Layer
|
| - 近场有限元（PeriFEM）刚度计算与装配
| - 材料模型 / 损伤与断裂模型
| - 时间推进 / 求解驱动
| - 并行与高性能计算（MPI / OpenMP / GPU，逐步引入）
|
| * 物理与数值“真理源头”
|   Source of physical and numerical truth
|
| * 最慢演进、最稳定的层
|   Slowest-evolving and most stable layer
+====================================================================+
```

---

<a id="dependency-direction-and-forbidden-coupling"></a>

### 2.2 依赖方向与禁止规则 | Dependency Direction and Forbidden Coupling

PeriSci 采用**严格的单向依赖结构**。
该结构是系统可维护性与生态可扩展性的基础。

PeriSci follows a **strict unidirectional dependency model**.
This model is fundamental to long-term maintainability and ecosystem scalability.

---

#### 允许的依赖方向 | Allowed Dependency Direction

```
python/apps
     ↓
    api
     ↓
    core
```

- `python/` 与 `apps/` 是 **并列的上层入口**
- 二者都 **只能** 通过 `api/` 调用系统能力
- `api/` 是 `core/` 的 **唯一正式入口**
- `cases/` 提供系统级标准算例输入（canonical configs），通常用于回归测试、示例验证与数据生产流程。
- `python/` and `apps/` are **parallel top-level entry layers**
- Both **must** access system capabilities via `api/`
- `api/` is the **only official entry point** to `core/`
- `cases/` provides canonical simulation inputs (configs), typically used for regression tests, example validation, and dataset generation workflows.

---

#### 明确禁止的依赖 | Explicitly Forbidden Dependencies

以下依赖关系被视为 **架构违规（architecture violations）**：

- `core/` 依赖 `api/`、`python/` 或 `apps/`
- `api/` 依赖 `python/` 或 `apps/`
- `python/` 或 `apps/` 绕过 `api/` 直接调用 `core/`
- `apps/` 依赖 `python/`（反之亦然）
- `cases/` 不应依赖或调用 `python/`、`apps/` 或 `core/` 中的实现代码（cases 仅作为输入与算例资产存在）

The following dependencies are considered **architecture violations**:

- `core/` depending on `api/`, `python/`, or `apps/`
- `api/` depending on `python/` or `apps/`
- `python/` or `apps/` bypassing `api/` to call `core/`
- `apps/` depending on `python/` (or vice versa)
- `cases/` must not depend on or call implementation code in `python/`, `apps/`, or `core/` (cases exist only as input and reference assets)

---

#### 为什么必须禁止这些依赖 | Rationale for Forbidden Dependencies

- 防止物理内核被用户工作流“污染”
- 防止教学/AI 快速演进破坏工程稳定性
- 防止工程 CLI 被迫依赖 Python 运行环境
- 确保任何入口都遵循同一物理与数据契约
- 通过 `cases/` 统一管理标准算例输入，确保不同入口在相同物理配置下运行
- Prevent pollution of the numerical kernel by user workflows
- Prevent fast-evolving teaching/AI layers from destabilizing engineering usage
- Avoid forcing engineering CLI tools to depend on Python runtimes
- Ensure all entry points obey the same physics and data contracts
- Centralizing canonical simulation inputs in `cases/` ensures that different entry points operate under the same physical configurations

---

<a id="responsibilities-vs-non-responsibilities"></a>

### 2.3 职责与非职责 | Responsibilities vs Non-Responsibilities

本节明确 **每一层“必须做什么”以及“绝不能做什么”**。
这不是风格建议，而是 **架构边界定义**。

This section defines **what each layer must do and must not do**.
These are architectural boundaries, not stylistic suggestions.

---

#### core/ —— 数值计算内核 | **Numerical Kernel Layer**

**职责（Must / Should）：**

- 实现近场有限元法（PeriFEM）的数值算子、装配与求解流程
- 保证物理一致性、数值稳定性与（尽可能的）确定性
- 封装并行与高性能实现（MPI / OpenMP / GPU 等）
- 提供可被 `api/` 调用的稳定、低层数值接口
- Implement PeriFEM numerical operators, assembly, and solvers
- Ensure physical consistency, numerical stability, and determinism when possible
- Encapsulate parallel and HPC backends (MPI/OpenMP/GPU)
- Expose stable low-level numerical interfaces callable by `api/`

**非职责（Must NOT）：**

- 解析或理解用户配置文件格式（JSON/YAML）
- 决定输出目录结构或数据集组织方式
- 实现 CLI、教学流程或 AI 工作流逻辑
- 假设任何上层调用方式的存在
- Parse or interpret user configuration formats
- Decide output directory layout or dataset organization
- Implement CLI, teaching workflows, or AI pipelines
- Assume the existence of any specific upper-layer entry

---

#### api/ —— 稳定对外契约层 | **Stable Public Contract Layer**

**职责（Must / Should）：**

- 定义并维护稳定、版本化的对外接口
- 校验 `config`（通过 `config_schema`）
- 组织一次完整、可追溯的仿真执行（`run_case`）
- 将仿真结果规范化为 `results`
- 将 `results` 转换为可复用的数据资产（`export_dataset`）
- Define and maintain stable, versioned public interfaces
- Validate `config` via `config_schema`
- Orchestrate complete, traceable simulation runs (`run_case`)
- Normalize outputs into canonical `results`
- Transform `results` into reusable data assets (`export_dataset`)

**非职责（Must NOT）：**

- 暴露 core 内部类、内存布局或实现细节
- 承担教学脚本、参数扫描或 AI 训练流程
- 定义新的物理语义或配置含义
- 依赖 Python 生态或特定 CLI 形式
- Expose internal core classes or memory layouts
- Implement teaching scripts, parameter sweeps, or AI training workflows
- Define new physics semantics or configuration meanings
- Depend on Python ecosystems or specific CLI forms

---

#### python/ —— 工作流与生态层 | **Workflow & Ecosystem Layer**

**职责（Must / Should）：**

- 为学生与研究人员提供友好的教学与研究入口
- 为 AI 数据生产提供批量化、自动化工具
- 实现参数扫描、数据清洗、结果解析等工作流
- 适配主流 AI 框架（不改变物理语义）
- Provide user-friendly entry points for teaching and research
- Enable automated, large-scale dataset generation for AI
- Implement parameter sweeps, data processing, and analysis workflows
- Adapt to AI frameworks without altering physics semantics

**非职责（Must NOT）：**

- 绕过 `api/` 直接访问 `core/`
- 定义或修改 `config_schema` 的核心语义
- 假设 core 内部实现是稳定 API
- 成为工程/HPC 的唯一入口
- Bypass `api/` to access `core/` directly
- Define or modify core semantics of `config_schema`
- Treat core internals as stable APIs
- Act as the sole entry point for engineering/HPC usage

---

#### apps/ —— 工程入口层 | **Engineering Entry Layer**

**职责（Must / Should）：**

- 提供稳定、可脚本化的 CLI（如 `perisci-run`）
- 适配工程与 HPC 环境（批处理、作业系统）
- 暴露诊断、日志、性能相关选项（不改变物理）
- Provide stable, scriptable CLI tools (e.g., `perisci-run`)
- Integrate with engineering and HPC environments (batch schedulers)
- Expose diagnostics, logging, and performance options (without changing physics)

**非职责（Must NOT）：**

- 定义新的配置语义或物理语义
- 直接访问 `core/`
- 依赖 Python 工作流或解释器
- 成为教学或 AI 工作流的强制路径
- Define new configuration semantics or physics semantics
- Access `core/` directly
- Depend on Python workflows or interpreters
- Serve as the mandatory path for teaching or AI workflows

---

#### cases/ —— 标准算例库 | Canonical Case Repository

**职责（Must / Should）：**

- 定义系统共享的标准算例（canonical simulation cases used across the system）
- 定义标准化的仿真算例（standard simulation cases）
- 提供 **可复现的 config 输入**
- 作为 tests 与 dataset generation 的统一算例来源
- 每个 case 必须包含完整、可运行的 `input.json`
- cases define canonical simulation cases used across the system
- Define standardized simulation cases
- Provide **reproducible configuration inputs**
- Serve as the shared case source for tests and dataset generation
- Each case must contain a complete, runnable `input.json`

**非职责（Must NOT）：**

- 不包含工作流脚本
- 不包含数据后处理逻辑
- 不定义新的物理语义
- 不包含或调用任何实现代码
- Must not contain workflow scripts
- Must not contain data post-processing logic
- Must not define new physical semantics
- Must not contain or invoke implementation code

---

**说明 | Notes**

- `cases/` 是系统级的标准算例库
- 它确保 tests 与 AI 数据生产流程在相同的标准算例上运行
- `cases/` serves as the canonical repository of system-level simulation cases
- It ensures that tests and AI dataset workflows operate on the same canonical simulation cases

---

#### 三类用户如何共用同一分层 | How Three User Types Share the Same Layers

| 用户类型    | 实际接触层   | 说明                                  |
| ----------- | ------------ | ------------------------------------- |
| 学生 / 教学 | python → api | Python 提供友好入口，API 保证物理一致 |
| 工程 / 科研 | apps → api   | 稳定契约，适合批量、自动化与 HPC      |
| AI / 数据   | python → api | Python 组织数据生产，API 保证可追溯   |

**关键原则：**

> 用户体验可以不同，但**物理内核与契约必须相同**。

---

#### examples / tests / docs 在分层中的位置 | Role of examples / tests / docs in the Architecture

在 PeriSci 的架构中，`examples/`、`tests/` 和 `docs/` **不属于执行路径上的计算层**，
但它们是 **架构不可或缺的支撑层（supporting layers）**。

它们共同承担一个核心职责：  
**将 core/api 的“设计承诺”转化为可理解、可验证、可传承的形式。**

In the PeriSci architecture, `examples/`, `tests/`, and `docs/` do **not**
belong to the execution path of numerical computation.
However, they are **essential supporting layers** of the architecture.

Together, they serve one core purpose:  
**to make the design contracts of core/api understandable, verifiable, and sustainable.**

---

##### examples/ —— 架构的“可学习表达” | **Learnable Expression of the Architecture**

- examples 体现 **“如何正确使用系统”**
- 它们是教学与新用户理解 API 的第一入口
- examples 必须严格遵守 `api` 契约，而不是绕过它

- Examples show **how the system is intended to be used**
- They are the primary learning entry for students and new users
- Examples must strictly use the `api` contract and must not bypass it

**v0.3.x 入口规则 | v0.3.x Entry Rule**

- `examples/` 围绕教学目标组织代码，用于打磨方法表达、展示数值过程与解释核心概念。
- `examples/` 必须通过 `api/` 调用 `core/` 能力，不得直接 include 或调用 `core/`。
- `examples/` 不以 `run_case(config)` 作为默认入口；教学示例可以使用专门的、非冻结的 API 教学入口，以便清楚展示方法流程与四核结构。
- `examples/` 中出现的配置对象仅为教学与探索服务，不得被视为 canonical case config，也不得作为冻结的 `config_schema` 语义来源。
- `cases/` 围绕算例资产积累目标组织，只保存稳定输入、期望指标、说明与溯源信息，不包含实现代码。
- `cases/` 的执行必须统一通过 `api::run_case(config)` 完成；`run_case` 再受控地驱动 `core/`。
- 因此，`examples/` 与 `cases/` 可以共享同一套 `core/` 数值能力，但二者只能通过 `api/` 进入 `core/`，且入口职责不同：`examples` 服务教学，`cases` 服务资产化与回归。

- `examples/` organize code around teaching goals, method incubation, visible numerical
  workflows, and explanation of core concepts.
- `examples/` must access `core/` capabilities only through `api/`; they must not
  include or call `core/` directly.
- `examples/` do not use `run_case(config)` as their default entry point. Teaching
  examples may use dedicated, non-frozen API teaching entry points when this makes
  the numerical workflow and Four-Core structure easier to learn.
- Configuration objects used inside `examples/` are instructional and exploratory;
  they must not be treated as canonical case configs or as frozen semantic sources
  for `config_schema`.
- `cases/` organize around case-asset accumulation: stable inputs, expected metrics,
  notes, and provenance, with no implementation code.
- `cases/` must be executed uniformly through `api::run_case(config)`, which then
  drives `core/` in a controlled way.
- Therefore, `examples/` and `cases/` may share the same `core` numerical capabilities,
  but both enter `core` only via `api`; their entry responsibilities differ:
  `examples` serve teaching, while `cases` serve assetization and regression.

---

##### tests/ —— 架构的“可验证约束” | **Verifiable Constraints of the Architecture**

- tests 用于 **锁住架构承诺**：
  - 数值行为是否退化
  - API 契约是否被破坏
  - 结果是否仍可复现
- tests 是架构演进的“安全网”，而不是附属工具

- Tests are used to **enforce architectural guarantees**:
  - numerical behavior regression
  - API contract stability
  - reproducibility of results
- Tests are a safety net for architectural evolution, not auxiliary tools

---

##### docs/ —— 架构的“权威说明” | **Authoritative Description of the Architecture**

- docs 定义 **什么是“正确的设计边界”**
- docs 是判断变更是否合理的最终依据
- 当代码与文档冲突时，应优先修正文档或显式记录设计决策（ADR）

- Docs define **what the correct design boundaries are**
- Docs serve as the ultimate reference for evaluating changes
- When code and docs diverge, the divergence must be resolved or documented via ADRs

---

##### 关键原则 | Key Principle

> **如果一个设计无法通过 examples 被学习，  
> 无法通过 tests 被验证，  
> 无法通过 docs 被解释，  
> 那么它就不属于 PeriSci 的稳定架构。**

> **If a design cannot be learned through examples,  
> cannot be verified by tests,  
> and cannot be explained in docs,  
> then it does not belong to PeriSci’s stable architecture.**

---

<a id="layer-stability-levels"></a>

### 2.4 分层稳定性等级 | Layer Stability Levels

##### **core/**：最高稳定性 | Highest stability

- 修改成本最高
- 任何破坏性修改都必须极其慎重
- 主要通过长期设计演进与严格评审推进
- Highest cost of change
- Any breaking change must be treated with extreme caution
- Evolves slowly through careful design and strict review

---

##### **api/**：高稳定性（对外承诺层）| High stability (public contract layer)

- 面向所有上层（python/apps/未来服务）的统一契约
- 破坏性修改必须通过明确的版本策略（MAJOR bump）
- 必须提供迁移说明或兼容方案
- Unified contract for all upper layers (python/apps/future services)
- Breaking changes require explicit versioning (MAJOR bump)
- Migration notes or compatibility strategies are required

---

##### **cases/**：高稳定性（标准算例库） | High stability (canonical case repository)

- 定义系统共享的标准仿真输入
- 用于回归测试、示例与数据生产的统一算例来源
- 修改应保持可复现性与结果可追溯性
- 破坏既有算例行为的修改必须明确记录并审查

- Defines canonical simulation inputs shared across the system
- Serves as the common source of cases for tests, examples, and dataset generation
- Changes must preserve reproducibility and traceability
- Any modification that alters established case behavior must be explicitly reviewed

---

##### **apps/**：中等稳定性（工程入口层）| Medium stability (engineering entry layer)

- CLI 接口应保持相对稳定，以支持工程与批处理脚本
- 允许新增选项与改进用户体验
- 不应频繁破坏已有命令语义或调用方式
- CLI interfaces should remain relatively stable to support engineering and batch scripts
- New options and UX improvements are allowed
- Existing command semantics and invocation patterns should not be broken frequently

---

##### **python/**：低稳定性（快速演进层）| Low stability (fast-evolving layer)

- 作为教学、科研与 AI 工作流的实验与创新空间
- 允许频繁重构、接口调整与新工具尝试
- 不对外承诺长期 API 稳定性
- Serves as an experimentation and innovation space for teaching, research, and AI workflows
- Frequent refactoring, interface changes, and new tools are allowed
- Long-term API stability is not guaranteed

---

#### 架构设计的长期收益 | Long-term Benefits

这种分层设计带来的长期收益包括：

- 教学、工程、AI **不会形成三套系统**
- PeriFEM 内核可以被重复利用（甚至独立发布）
- AI 数据具有明确物理来源与可追溯性
- 标准算例库（cases）保证不同入口在同一物理配置下运行
- 清晰的代码归属与分层边界，降低新贡献者的理解成本

This layered design ensures:

- No divergence between teaching, engineering, and AI versions
- Reusable and replaceable PeriFEM kernel
- Physically grounded and traceable AI datasets
- The canonical case repository ensures that different entry points operate under identical physical configurations
- Clear code ownership and layer boundaries for new contributors

---

#### PeriSci 架构的长期稳定性原则 | Long-term Stability Principles of the PeriSci Architecture

PeriSci 的架构由三个长期稳定性原则支撑：

- 数值内核（core）保证物理与数值的真实性
- 公共接口（api）保证对外契约的稳定性
- 标准算例库（cases）保证数值实验与数据的可复现性

这三层分别稳定物理、接口与实验，从而使系统能够长期演进而不破坏整体结构。

这三条原则构建起清晰的**科学计算系统结构**：

```
Physics correctness        → core
Contract stability         → api
Experiment reproducibility → cases
```

PeriSci’s architecture is supported by three long-term stability principles:

- physics correctness in the numerical kernel (core)
- contract stability in the public API (api)
- numerical experiment reproducibility through canonical cases (cases)

These three layers respectively stabilize the physical, interface and experimental aspects, thus enabling the system to evolve over the long term without disrupting the system.

These three principles establish a clear **structural model for scientific computing systems**:

```
Physics correctness        → core
Contract stability         → api
Experiment reproducibility → cases
```

---

<a id="repository-organization-and-quality-gates"></a>

## 3. 仓库组织与质量门禁 | Repository Organization and Quality Gates

本节从**仓库组织（repository organization）**的角度，
说明 PeriSci 各目录在代码管理、协作与质量控制中的职责。

本节**不重复**第 2 节中已定义的架构分层语义，
而是强调这些架构角色在仓库中的**组织边界与工程约束**。

This section describes the responsibilities of directories from a
**repository organization** perspective, focusing on collaboration,
maintainability, and quality control.

Architectural semantics defined in Section 2 are not repeated here;
instead, we emphasize **organizational boundaries and engineering constraints**.

---

<a id="organizational-boundary-numerical-kerne"></a>

### 3.1 core/ —— 数值内核的组织边界 | Organizational Boundary of the Numerical Kernel

- `core/` 仅包含数值计算与物理模型相关代码
- 该目录不包含任何用户接口、脚本或工作流逻辑
- `core/` 的子模块组织应反映数值结构，而非使用场景

- `core/` contains only numerical computation and physics-related code
- It must not include user interfaces, scripts, or workflow logic
- Submodules should reflect numerical structure, not usage scenarios

**约束补充 | Constraints**

- 禁止在 `core/` 中引入：
  - CLI 解析
  - Python 绑定
  - 文件系统布局决策
- `core/` 的对外可见接口应仅通过 `api/` 暴露

**Constraints**

- `core/` must not include:
  - CLI parsing
  - Python bindings
  - File-system layout decisions
- Public access to `core/` must go through `api/` only

---

<a id="organizational-carrier-contracts-boundaries"></a>

### 3.2 api/ —— 契约与边界的组织载体 | Organizational Carrier of Contracts and Boundaries

- `api/` 组织所有对外稳定接口的实现
- 它是连接仓库内部实现与外部使用方式的“缓冲层”
- `api/` 中的代码应与 `docs/specs/` 中的契约保持一致

- `api/` organizes implementations of all stable public interfaces
- It acts as a buffer between internal implementation and external usage
- Code in `api/` must remain consistent with contracts in `docs/specs/`

**约束补充 | Constraints**

- `api/` 不应暴露 `core/` 的内部数据结构
- `api/` 不依赖 Python 或具体 CLI 实现
- 任何破坏性修改必须与版本策略和文档同步

**Constraints**

- `api/` must not expose internal data structures of `core/`
- `api/` must not depend on Python or specific CLI implementations
- Breaking changes must be synchronized with versioning and documentation

---

<a id="centralized-location-workflow-code"></a>

### 3.3 python/ —— 工作流代码的集中位置 | Centralized Location for Workflow Code

- `python/` 集中存放教学、科研与 AI 工作流相关代码
- 该目录强调**易用性与灵活性**，而非长期接口稳定性
- `python/` 中的代码应全部通过 `api/` 访问系统能力

- `python/` hosts teaching, research, and AI workflow code
- It prioritizes usability and flexibility over long-term API stability
- All system access must go through `api/`

**约束补充 | Constraints**

- 禁止在 `python/` 中绕过 `api/` 直接调用 `core/`
- 不应在 `python/` 中固化物理语义或配置含义
- 可根据教学或 AI 需求频繁调整组织结构

**Constraints**

- `python/` must not bypass `api/` to access `core/`
- Physics semantics and config meanings must not be hard-coded here
- Directory structure may evolve to support teaching or AI needs

---

<a id="organizational-boundary-engineering-batch-entry-points"></a>

### 3.4 apps/ —— 工程与批处理入口的组织边界 | Organizational Boundary of Engineering and Batch Entry Points

- apps/` 存放工程与 HPC 场景下使用的可执行入口
- 该目录强调**脚本化、可部署性与环境独立性**
- `apps/` 与 `python/` 在仓库结构上保持并列

- `apps/` contains executable entry points for engineering and HPC use
- It emphasizes scriptability, deployability, and environment independence
- `apps/` is organizationally parallel to `python/`

**约束补充 | Constraints**

- `apps/` 中的程序必须通过 `api/` 调用系统能力
- `apps/` 中的程序在运行时不得依赖 Python 解释器或 Python 包生态
- CLI 行为应与 `api` 契约保持一致

**Constraints**

- Programs in `apps/` must call system capabilities via `api/`
- Programs in `apps/` must not depend on the Python interpreter or Python package
- CLI behavior must remain consistent with `api` contracts

---

<a id="canonical-case-repository"></a>

### 3.5 cases/ —— 标准算例库 | Canonical Case Repository

- `cases/` 集中存放 PeriSci 的标准仿真算例（canonical simulation cases）
- 每个 case 定义一个**可复现的数值实验配置**
- 该目录为 examples、tests 与数据生产流程提供统一输入来源

- `cases/` hosts the canonical simulation cases of PeriSci
- Each case defines a **reproducible numerical experiment configuration**
- The directory provides shared inputs for examples, tests, and dataset generation workflows

**约束补充 | Constraints**

- 每个 case 必须包含完整且可运行的 `input.json`
- `cases/` 不包含实现代码、工作流脚本或数据处理逻辑
- 修改既有 case 行为必须保持可追溯并经过审查

**Constraints**

- Each case must contain a complete and runnable `input.json`
- `cases/` must not contain implementation code, workflow scripts, or data-processing logic
- Changes that alter established case behavior must remain traceable and reviewed

**设计说明 | Design Note**

- `cases/` 定义系统共享的标准仿真算例
- 它确保 examples、tests 与 AI 数据生产流程在相同物理配置下运行

- `cases/` defines canonical simulation cases shared across the system
- It ensures that examples, tests, and AI dataset workflows operate on the same canonical simulation cases

---

<a id="quality-gates"></a>

### 3.6 examples / tests / docs —— 质量保障层 | Quality Assurance Layers

`examples/`、`tests/` 与 `docs/` 共同构成 PeriSci 的质量保障体系。  
其中 `tests/` 构成 CI 的核心回归验证层，而 `examples/` 与 `docs/` 分别用于验证系统的可用性与设计一致性。

在仓库生命周期中，这三类目录与 `cases/` 之间形成如下关系：

- `examples/` 用于教学、示例展示与能力探索，其中一部分成熟稳定的示例可以被提升为 `cases/` 中的标准算例资产
- `cases/` 存放经过验证并冻结的标准算例，用于保证实验与数据的可复现性
- `tests/` 通常以 `cases/` 中的标准算例作为回归输入，用于验证数值行为与 API 契约在演进中的稳定性

The directories `examples/`, `tests/`, and `docs/` together form PeriSci’s quality assurance system.  
Among them, `tests/` serve as the core regression verification layer in CI, while `examples/` and `docs/` verify usability and design consistency.

During the repository lifecycle, these directories interact with `cases/` as follows:

- `examples/` support teaching, demonstrations, and capability exploration; some stable examples may later be promoted into canonical cases under `cases/`
- `cases/` store validated and frozen simulation cases to ensure experimental and dataset reproducibility
- `tests/` typically use canonical cases from `cases/` as regression inputs to verify numerical behavior and API contract stability

---

#### examples/ —— 教学、示例与探索层 | Teaching, Demonstration, and Exploration Layer

`examples/` 在系统中具有双重职责：

- 作为教学与示例层，帮助用户理解 API 的正确使用方式
- 作为探索与实验层，为潜在的标准算例提供数值实验起点

并非所有 examples 都会演进为 cases；只有在语义清晰、行为稳定且具备回归价值时，相关示例才可能被提升为 `cases/` 中的标准算例资产。

examples 用于验证：

- API 是否易于理解和正确使用
- 新用户是否能够完成基本任务

examples 必须始终保持可运行状态。

`examples/` therefore serve a dual role in the system:

- as a teaching and demonstration layer, helping users understand how to correctly use the API
- as an exploration and numerical experimentation layer that may incubate potential canonical cases

Not all examples are expected to evolve into cases. Only when an example becomes semantically clear, behaviorally stable, and suitable for regression use may it be promoted into a canonical case under `cases/`.

Examples verify:

- Whether APIs are understandable and usable
- Whether new users can complete basic tasks

Examples must remain runnable at all times.

**v0.3.x 补充原则 | v0.3.x Additional Principle**

`examples/` 与 `cases/` 都不得直接访问 `core/`，但它们的 API 入口职责不同：

- `examples/` 使用面向教学的 API 入口来展示方法流程、数值阶段和四核结构；它们不以 `run_case(config)` 作为默认入口。
- `cases/` 使用统一的 `api::run_case(config)` 入口来保证标准算例资产的执行一致性、可回归性与可追踪性。

Both `examples/` and `cases/` must not access `core/` directly, but their API entry
responsibilities differ:

- `examples/` use teaching-oriented API entry points to expose method workflows,
  numerical stages, and the Four-Core structure; they do not use `run_case(config)`
  as the default entry point.
- `cases/` use the unified `api::run_case(config)` entry point to guarantee
  consistent, regression-ready, and traceable execution of canonical case assets.

---

#### tests/ —— 回归与契约验证 | Regression and Contract Verification

Tests 锁定：

- 数值行为不被意外破坏
- API 契约持续成立
- 关键结果具备可复现性

Tests 是 CI 的核心组成部分。多数回归测试使用 `cases/` 中的标准算例作为输入来源。

Tests ensure:

- Numerical behavior is not accidentally broken
- API contracts remain valid
- Key results remain reproducible

Tests are a core component of CI. Most regression tests use canonical cases from `cases/` as their input sources.

---

#### docs/ —— 设计一致性验证 | Design Consistency Verification

- docs 用于验证：
  - 实现是否符合既定架构与契约
  - 新设计是否被明确记录与解释

- 文档滞后于实现被视为质量风险

Docs verify:

- Whether implementation aligns with defined architecture and contracts
- Whether new designs are properly documented and explained

Documentation lag is considered a quality risk.

---

#### 质量保障原则 | Quality Assurance Principle

> **任何变更，只有同时通过 examples、tests 与 docs，才能被视为 PeriSci 的可接受演进。**

> **A change is considered acceptable in PeriSci only if it passes examples, tests, and documentation simultaneously.**

---

#### 探索性示例到标准算例的演进关系 | Evolution from Exploratory Examples to Canonical Cases

在 PeriSci 的开发流程中，探索性示例、标准算例与回归测试之间形成一个清晰的演进路径：

examples → cases → tests

- `examples/` 用于教学展示与能力探索
- 部分成熟稳定的探索性示例可以被提升为 `cases/` 中的标准算例
- `tests/` 使用这些标准算例进行回归验证

In the development workflow of PeriSci, exploratory examples, canonical cases, and regression tests follow a clear evolution path:

examples → cases → tests

- `examples/` support teaching demonstrations and capability exploration
- some stable exploratory examples may be promoted into canonical cases under `cases/`
- `tests/` use these canonical cases to perform regression validation

这一结构确保：

- 新能力可以在 `examples/` 中自由探索
- 稳定数值实验通过 `cases/` 被固定为可复现算例
- 系统演进通过 `tests/` 持续受到保护

This structure ensures that:

- new capabilities can be explored freely in `examples/`
- stable numerical experiments are crystallized as canonical cases in `cases/`
- system evolution remains protected through regression tests

---

<a id="root-level-governance-files"></a>

### 3.7 根目录治理文件 | Root-Level Governance Files

除了代码目录外，PeriSci 的仓库根目录还包含一组
**不参与运行时计算、但对项目长期演进具有决定性作用的治理文件**。

这些文件共同定义了 PeriSci 的：

- 对外承诺
- 协作方式
- 版本与演进规则
- 法律与行为边界

In addition to code directories, the root of the PeriSci repository contains
a set of **governance files** that do not participate in runtime execution
but are critical to the long-term evolution of the project.

Together, they define PeriSci’s:

- External commitments
- Collaboration model
- Versioning and evolution rules
- Legal and behavioral boundaries

---

#### README.md —— 项目对外入口 | Project Entry Point

- README 是外部用户理解 PeriSci 的第一入口
- 它定义项目定位、核心理念、基本使用方式与入口指引
- README 的内容应与架构与 API 契约保持一致

- README is the first entry point for external users
- It defines project positioning, core ideas, and basic usage guidance
- Its content must remain consistent with the architecture and API contracts

---

#### VERSIONING.md / CHANGELOG.md —— 演进与承诺 | Evolution and Commitments

- VERSIONING.md 定义版本号的语义与破坏性修改的判定规则
- CHANGELOG.md 记录每个版本的可见变化
- 二者共同构成用户与贡献者的“演进预期管理”

- VERSIONING.md defines semantic versioning rules and breaking-change criteria
- CHANGELOG.md records visible changes per release
- Together, they manage expectations for users and contributors

---

#### CONTRIBUTING.md / CODE_OF_CONDUCT.md —— 协作与边界 | Collaboration and Boundaries

- CONTRIBUTING.md 说明如何参与项目、提交代码与讨论设计
- CODE_OF_CONDUCT.md 定义社区交流的行为边界
- 这些文件确保技术讨论在理性与尊重的环境中进行

- CONTRIBUTING.md explains how to participate, contribute code, and discuss design
- CODE_OF_CONDUCT.md defines behavioral boundaries for community interactions
- These files ensure rational and respectful technical collaboration

---

#### MAINTAINERS.md —— 技术治理 | Technical Governance

- MAINTAINERS.md 明确项目的维护责任与决策机制
- 它定义谁对核心架构与数值正确性拥有最终裁量权
- 该文件是处理设计分歧与长期演进的重要依据

- MAINTAINERS.md defines maintenance responsibilities and decision-making authority
- It specifies who has final authority over core architecture and numerical correctness
- It serves as a key reference for resolving design disagreements

---

#### AUTHORS —— 作者与贡献归属 | Authors and Contribution Attribution

- AUTHORS 文件列出项目的主要作者与核心贡献者
- 它用于：
  - 明确学术与工程成果的归属
  - 与 CITATION.cff 形成互补
- AUTHORS 不等同于维护者列表，而是侧重于**贡献事实的记录**

- AUTHORS lists the main authors and core contributors of the project
- It serves to:
  - Clarify attribution of academic and engineering contributions
  - Complement CITATION.cff
- AUTHORS is distinct from the maintainer list; it focuses on recording contribution facts

---

#### CITATION.cff —— 学术引用与成果归属 | Academic Citation and Attribution

- CITATION.cff 用于声明 PeriSci 在学术工作中的标准引用方式
- 它支持被 GitHub、文献管理工具与期刊系统自动识别
- 该文件确保：
  - 使用 PeriSci 的科研成果能够正确引用
  - 作者与贡献者的学术贡献得到规范承认

- CITATION.cff defines the standard citation format for PeriSci in academic publications
- It is automatically recognized by GitHub, reference managers, and journal systems
- This file ensures that:
  - Research using PeriSci can be properly cited
  - Authors’ and contributors’ academic contributions are formally acknowledged

---

#### LICENSE —— 法律边界 | Legal Boundary

- LICENSE 定义软件的使用、修改与再分发边界
- 所有架构与实现均必须在该许可证框架内进行
- 许可证选择影响社区参与方式与产业化路径

- LICENSE defines the legal boundaries for use, modification, and redistribution
- All architecture and implementation must comply with the license
- License choice affects community participation and industrial adoption

---

#### CMakeLists.txt —— 构建体系入口 | Build System Entry Point

- CMakeLists.txt 定义 PeriSci 的整体构建结构与模块组织方式
- 它是连接仓库结构与可执行/可链接产物的核心入口
- 顶层 CMakeLists.txt 只负责：
  - 项目声明
  - 全局构建选项
  - 子目录组织
- 具体编译逻辑应分散在各子目录中，以保持结构清晰

- CMakeLists.txt defines the overall build structure and module organization of PeriSci
- It is the central entry point connecting repository structure to buildable artifacts
- The top-level CMakeLists.txt should only:
  - Declare the project
  - Define global build options
  - Organize subdirectories
- Detailed compilation logic should reside in subdirectories to keep the structure clean

---

#### .gitignore —— 仓库卫生与协作基础 | Repository Hygiene and Collaboration Foundation

- .gitignore 定义哪些文件与目录不应进入版本控制
- 它确保：
  - 构建产物、运行输出与临时文件不污染仓库
  - 不同开发环境之间的协作一致性
- 对 PeriSci 而言，.gitignore 是长期协作与 CI 稳定运行的基础

- .gitignore specifies which files and directories must not be tracked by version control
- It ensures that:
  - Build artifacts, runtime outputs, and temporary files do not pollute the repository
  - Collaboration remains consistent across different development environments
- For PeriSci, .gitignore is a foundation for long-term collaboration and CI stability

---

#### 关键原则 | Key Principle

> **这些根目录文件共同构成 PeriSci 的“治理层”，它们与 core/api 一样重要，但作用在不同层面。**

> **These root-level files form the “governance layer” of PeriSci. They are as important as core/api, but operate at a different layer.**

---

<a id="hard-to-change-design-boundaries"></a>

## 4. 不可轻易改动的设计边界 | Hard-to-Change Design Boundaries

本节定义 PeriSci 的**架构硬边界（Hard Design Boundaries）**。这些边界构成系统长期稳定、可复现、可被 AI 利用的基础。

任何触及这些边界的修改，都必须同时满足：

- 明确的设计说明（docs/specs 或 ADR）
- 明确的版本策略（通常为 MAJOR bump）
- 必要时提供迁移路径或兼容方案

This section defines the **hard design boundaries** of PeriSci. These boundaries are foundational to long-term stability, reproducibility, and AI usability.

Any change touching these boundaries must include:

- Explicit design documentation (docs/specs or ADR)
- Explicit versioning strategy (typically a MAJOR bump)
- Migration or compatibility mechanisms when applicable

---

<a id="api-contract-trio-must-persist"></a>

### Boundary 1 — API 契约三件套必须长期存在 | The API Contract Trio Must Persist

**不可轻易改动：**

- `config_schema`（版本化配置规范）
- `run_case(config) -> results`
- `export_dataset(results, spec) -> dataset_dir`

**Must not be changed lightly:**

- `config_schema` (versioned configuration specification)
- `run_case(config) -> results`
- `export_dataset(results, spec) -> dataset_dir`

**原因：**
这是教学、工程与 AI 三条路线共同依赖的**最小系统骨架**。

**Rationale:**
This trio forms the **minimal system backbone** shared by education, engineering, and AI workflows.

---

<a id="semantic-stability-of-config_schema"></a>

### Boundary 2 — config_schema 的语义稳定性优先 | Semantic Stability of config_schema

**不可轻易改动：**

- 同一 schema 版本下，config 的物理语义必须保持一致
- 字段含义变化属于破坏性修改（MAJOR）
- 新增字段必须保持向后兼容（MINOR）

**Must not be changed lightly:**

- Within the same schema version, the physical semantics of a config must remain consistent
- Changes in field semantics are considered breaking changes (MAJOR)
- Newly added fields must remain backward compatible (MINOR)

**原因：**
配置是仿真、标准算例、结果与数据集**可复现性的唯一源头**。

**Rationale:**
Configuration is the **source of truth** for the reproducibility of simulations, canonical cases, results, and datasets.

---

<a id="dataset-specifications-must-be-versioned-and-traceable"></a>

### Boundary 3 — Dataset 规范必须可版本化且可追溯 | Dataset Specifications Must Be Versioned and Traceable

**不可轻易改动：**

- 数据集目录结构的核心语义
- manifest / metadata 中关键字段的含义
- 任何影响 AI 训练可复现性的变化

这些规范同样影响由 `cases/` 生成的数据资产与训练数据集。

**Must not be changed lightly:**

- Core semantics of the dataset directory structure
- Meanings of key fields in manifests and metadata
- Any change affecting reproducibility of AI training

These specifications also affect datasets generated from canonical cases under `cases/`.

**原因：**
AI 生态依赖的是**可复现的数据资产**，而不是临时输出文件。

**Rationale:**
AI ecosystems rely on **reproducible data assets**, not transient outputs.

---

<a id="strict-decoupling-of-core-from-upper-layers"></a>

### Boundary 4 — 数值内核（core）与上层完全解耦（依赖方向固定）| Strict Decoupling of the Numerical Kernel （core）from Upper Layers

**不可轻易改动：**

- `core/` 不依赖 `api/`、`python/` 或 `apps/`
- `api/` 不依赖 `python/` 或 `apps/`
- `python/` 与 `apps/` 只能通过 `api/` 调用内核能力

**Must not be changed lightly:**

- `core/` must not depend on `api/`, `python/`, or `apps/`
- `api/` must not depend on `python/` or `apps/`
- `python/` and `apps/` may access kernel capabilities only via `api/`

**原因：**
这是保证数值内核可复用、可移植、可维护的根本前提。

**Rationale:**
This is fundamental to the reusability, portability, and long-term maintainability of the numerical kernel.

---

<a id="reproducibility-and-provenance-are-release-requirements"></a>

### Boundary 5 — 可复现性与可追溯性是发布版本的硬门槛 | Reproducibility and Provenance Are Release Requirements

**不可轻易改动：**

- Tag 版本必须记录软件版本、schema 版本与运行/构建信息（尽可能）
- 结果必须能追溯到 config 与代码版本

**Must not be changed lightly:**

- Tagged releases must record software version, schema version, and execution/build information where possible
- Results must be traceable back to the corresponding config and code version

**原因：**
科研、工程与 AI 都需要**可解释、可审计的结果**。

**Rationale:**
Research, engineering, and AI all require **interpretable and auditable results**.

---

<a id="entry-point-consistency-across-use-cases"></a>

### Boundary 6 — 教学 / 工程 / AI 的入口一致性 | Entry-Point Consistency Across Use Cases

**不可轻易改动：**

- 不同入口（python / apps）必须共享同一 API 契约、数值内核与标准算例库（cases）
- 不允许出现语义分叉的“教学版 / 工程版 / AI 版”

**Must not be changed lightly:**

- Different entry points (python / apps) must share the same API contract, numerical kernel, and canonical cases
- Divergent “teaching”, “engineering”, or “AI” semantics are not allowed

**原因：**
防止系统分裂，避免维护成本指数级增长。

**Rationale:**
This prevents system fragmentation and avoids exponential growth in maintenance cost.

---

<a id="canonical-case-repository-must-exist"></a>

### Boundary 7 — 标准算例库（cases）必须长期存在 | The Canonical Case Repository Must Persist

**不可轻易改动：**

- 项目必须维护一个用于存放标准算例的目录 `cases/`
- `cases/` 中的算例配置必须保持语义稳定，并可用于长期复现数值实验
- `tests/` 的回归验证应以 `cases/` 中的标准算例作为主要输入来源
- `cases/` 的结构性删除、语义重定义或大规模迁移都属于架构级变更

**Must not be changed lightly:**

- The project must maintain a canonical case repository under `cases/`
- Configurations stored in `cases/` must remain semantically stable and suitable for long-term reproducible numerical experiments
- Regression tests in `tests/` should primarily use canonical cases from `cases/` as their inputs
- Structural removal, semantic redefinition, or large-scale relocation of `cases/` constitutes an architectural change

**原因：**

`cases/` 是 PeriSci 中用于保存**标准算例资产（canonical simulation cases）**的仓库。  
这些算例为系统提供稳定的实验基线，并被用于：

- 回归测试（regression tests）
- 可复现数值实验（reproducible numerical experiments）
- AI 数据生成（dataset generation）

因此，`cases/` 构成 PeriSci 架构中 **实验可复现性的稳定锚点**。

**Rationale:**

The `cases/` repository stores **canonical simulation cases** that serve as the stable experimental baseline of the system.  
These cases support:

- regression testing
- reproducible numerical experiments
- AI dataset generation

Therefore, `cases/` forms the **stability anchor for experimental reproducibility** in the PeriSci architecture.

---

### 总结 | Summary

> **这些设计边界定义了 PeriSci 的“不可退让区域”，它们不是实现细节，而是系统长期可信性的基石。**

> **These design boundaries define the non-negotiable regions of PeriSci. They are not implementation details, but foundations of long-term system credibility.**

---

<a id="change-management-and-adr"></a>

## 5. 变更管理与 ADR | Change Management and ADR (Architecture Decision Records)

本节定义当 PeriSci 的设计或实现 **涉及第 4 节所述“不可轻易改动的设计边界”时**，应遵循的变更管理机制。

ADR（Architecture Decision Record）不是一般性的设计笔记，而是用于**记录、审议并约束架构级决策的正式机制**。

This section defines the change management mechanism to be used when a proposed change **touches any of the hard design boundaries defined in Section 4**.

Architecture Decision Records (ADRs) are not casual design notes; they are a**formal mechanism for recording, reviewing, and constraining architecture-level decisions**.

---

<a id="when-adrs-are-required"></a>

### 5.1 何时必须使用 ADR| When ADRs Are Required

在以下情况下，**必须**创建 ADR：

- 修改或重定义第 4 节中任意一条 Hard Design Boundary
- 改变 API 契约三件套的语义或结构
- 引入可能影响标准算例（cases）可复现性、结果可追溯性或 AI 数据集一致性的机制
- 引入新的核心依赖或改变依赖方向
- 明确拒绝或替换已有架构原则

ADRs **must** be created when:

- Modifying or redefining any hard design boundary in Section 4
- Changing the semantics or structure of the API contract trio
- Introducing mechanisms that may affect reproducibility of canonical cases, provenance, or AI dataset consistency
- Introducing new core dependencies or changing dependency directions
- Explicitly rejecting or replacing an existing architectural principle

---

<a id="when-adrs-are-not-required"></a>

### 5.2 何时不需要 ADR | When ADRs Are Not Required

以下情况通常**不需要** ADR（但仍应通过正常代码评审）：

- 内部实现细节优化，不影响对外语义
- 性能改进且不改变数值或物理含义
- 新增或更新 examples、tests 或文档
- Python 工作流层的组织调整（不改变 API 契约或标准算例）

ADRs are typically **not required** for:

- Internal implementation refactoring without semantic changes
- Performance optimizations that preserve numerical and physical meaning
- Adding or updating examples, tests, or documentation
- Reorganizing the Python workflow layer without changing API contracts or canonical cases

---

<a id="required-contents-of-an-adr"></a>

### 5.3 ADR 的基本内容 | Required Contents of an ADR

每一份 ADR 至少应包含以下内容：

- **背景（Context）**
  - 为什么需要做出这个决策
  - 当前架构约束是什么

- **问题陈述（Problem Statement）**
  - 明确要解决的架构级问题

- **备选方案（Considered Options）**
  - 至少列出一个被否决的方案
  - 说明取舍理由

- **决策（Decision）**
  - 最终选择的方案
  - 是否影响第 4 节中的硬边界

- **影响与后果（Consequences）**
  - 对现有用户、数据、API、维护成本的影响
  - 是否需要迁移或兼容策略

Each ADR must include at least:

- **Context**
  - Why this decision is needed
  - What architectural constraints currently exist

- **Problem Statement**
  - A clear statement of the architecture-level problem

- **Considered Options**
  - At least one rejected alternative
  - Rationale for trade-offs

- **Decision**
  - The chosen option
  - Whether it affects any hard design boundary in Section 4

- **Consequences**
  - Impact on users, data, APIs, and maintenance cost
  - Migration or compatibility requirements, if any

---

<a id="adr-location-and-naming-convention"></a>

### 5.4 ADR 的存放与命名约定 | ADR Location and Naming Convention

- 所有 ADR 文件应存放于： `docs/adr/`
- 文件命名格式建议为：`NNNN-short-title.md`，其中 `NNNN` 为四位递增编号
- ADR 一经合并，不应被随意修改； 如需推翻，应新增 ADR 说明变更原因

All ADRs should be stored in:

- `docs/adr/`

Recommended file naming format:

- `NNNN-short-title.md` where `NNNN` is a four-digit incremental number

Once merged, ADRs should not be modified arbitrarily; revisions should be recorded via new ADRs explaining the change.

---

<a id="relationship-between-adrs-and-versioning"></a>

### 5.5 ADR 与版本策略的关系 | Relationship Between ADRs and Versioning

- 任何影响 Hard Design Boundaries 的 ADR，必须明确对应的版本影响（通常为 MAJOR）
- ADR 是 VERSIONING.md 与 CHANGELOG.md 的决策依据之一

Any ADR affecting hard design boundaries must explicitly state its versioning implications (typically MAJOR).

ADRs serve as part of the decision basis for VERSIONING.md and CHANGELOG.md.

---

### 总结 | Summary

> **第 4 节定义了什么是“不可轻易改动的”，本节定义了“如果必须改动，应该如何被记录、讨论与承担后果”。**

> **Section 4 defines what must not be changed lightly; this section defines how such changes must be recorded, discussed, and accounted for if they become unavoidable.**

---

<a id="evolvable-soft-boundaries"></a>

## 6. 可演进的“软边界” | Evolvable “Soft Boundaries”

与第 4 节定义的“不可轻易改动的设计边界”不同，本节定义 PeriSci 中 **允许随项目发展而逐步演进的设计区域**，即“软边界（Soft Boundaries）”。

软边界并不意味着随意变更，而是指这些方面 **可以在不破坏系统核心契约的前提下逐步调整与优化**。

In contrast to the “hard design boundaries” defined in Section 4, this section defines the **evolvable areas** of PeriSci, referred to as “soft boundaries”.

Soft boundaries do not imply arbitrary change. They indicate areas that **may evolve gradually without breaking the core architectural contracts of the system**.

---

<a id="user-experience-and-entry-forms"></a>

### 6.1 用户体验与入口形式 | User Experience and Entry Forms

**可演进内容：**

- Python 工作流的组织方式与辅助工具
- CLI（apps/）的命令选项、参数名称与交互形式
- 教学示例与探索性 examples 的组织与呈现方式

**约束：**

- 不得引入新的物理语义
- 不得绕过 API 契约
- 不得导致不同入口的语义分叉

**Evolvable aspects:**

- Organization of Python workflows and helper utilities
- CLI (apps/) command options, flags, and interaction styles
- Presentation and organization of tutorials, teaching examples, and exploratory examples

**Constraints:**

- Must not introduce new physical semantics
- Must not bypass the API contract
- Must not cause semantic divergence across entry points

---

<a id="internal-implementation-and-performance-optimization"></a>

### 6.2 内部实现与性能优化 | Internal Implementation and Performance Optimization

**可演进内容：**

- 内部算法实现细节
- 数据结构与内存布局优化
- 并行化与性能调优策略

**约束：**

- 不得改变对外可观察的数值语义
- 不得破坏既有 tests 或 canonical cases 的可复现性
- 性能优化必须通过 tests 验证

**Evolvable aspects:**

- Internal algorithmic implementation details
- Data structures and memory layout optimizations
- Parallelization and performance tuning strategies

**Constraints:**

- Must not change externally observable numerical semantics
- Must not break reproducibility of existing tests or canonical cases
- Performance changes must be validated by tests

---

<a id="extension-capabilities-and-plugin-based-integration"></a>

### 6.3 扩展能力与插件式集成 | Extension Capabilities and Plugin-Based Integration

**可演进内容：**

- 新的物理模型或本构关系（作为扩展模块）
- 与外部求解器、库或工具的集成
- 面向 AI 的数据导出形式与适配器

**约束：**

- 扩展不得侵入 core 的稳定接口
- 扩展必须通过 api 接入
- 插件机制的引入不得破坏既有配置语义

**Evolvable aspects:**

- New physical models or constitutive laws (as extensions)
- Integration with external solvers, libraries, or tools
- AI-oriented data export formats and adapters

**Constraints:**

- Extensions must not intrude into stable core interfaces
- Extensions must integrate through the api layer
- Plugin mechanisms must not break existing configuration semantics

---

<a id="documentation-examples-and-testing-system"></a>

### 6.4 文档、示例与测试体系 | Documentation, Examples, and Testing System

**可演进内容：**

- 文档结构与写作风格
- 示例覆盖范围、教学路径设计以及 examples 向 canonical cases 的演进组织
- 测试粒度、覆盖率与组织方式

**约束：**

- 文档必须与当前架构和 API 保持一致
- 示例必须可运行
- 测试失败不得被长期忽略

**Evolvable aspects:**

- Documentation structure and writing style
- Example coverage, teaching pathways, and the organization of example-to-case evolution
- Test granularity, coverage, and organization

**Constraints:**

- Documentation must remain consistent with current architecture and APIs
- Examples must remain runnable
- Failing tests must not be ignored over time

---

<a id="canonical-case-assets"></a>

### 6.5 标准算例资产（cases） | Canonical Case Assets

`cases/` 构成 PeriSci 的 **标准算例资产库（canonical simulation case assets）**。这些算例用于保证数值实验、数据集与回归测试的可复现性。它与 examples 与 tests 一起构成 PeriSci 的数值实验体系。

与 examples 不同，cases 通常代表 **经过验证并稳定的数值实验配置**，但算例库本身仍然允许随着项目发展逐步扩展与完善。

**可演进内容：**

- 新的标准算例加入
- 现有算例的说明文档（notes / metadata）完善
- 算例组织结构的优化
- 算例导出数据集规范的改进

**约束：**

- 不得改变既有算例的物理语义
- 修改算例必须保持可追溯性
- 任何影响算例数值行为的修改必须通过 tests 验证
- 算例变更不得破坏既有数据集或回归测试的可复现性

The `cases/` directory forms the **canonical simulation case asset library** of PeriSci. These cases ensure reproducibility of numerical experiments, datasets, and regression tests. Together with examples and tests, it forms the numerical experiment system of PeriSci.

Unlike examples, canonical cases typically represent **validated and stabilized numerical experiment configurations**, but the case library itself may evolve as the project grows.

**Evolvable aspects:**

- Adding new canonical cases
- Improving documentation (notes / metadata) of existing cases
- Refining the organizational structure of cases
- Improving dataset export specifications associated with cases

**Constraints:**

- Existing physical semantics of a case must not change
- Case modifications must remain traceable
- Any change affecting numerical behavior must pass tests
- Case updates must not break reproducibility of existing datasets or regression tests

---

<a id="relationship-between-soft-boundaries-and-versioning"></a>

### 6.6 软边界与版本策略的关系 | Relationship Between Soft Boundaries and Versioning

- 软边界内的演进通常对应 MINOR 或 PATCH 版本
- 当软边界的变化开始触及第 4 节定义的硬边界时，该变化必须升级为硬边界修改，并遵循 ADR 流程
- Evolution within soft boundaries typically corresponds to MINOR or PATCH releases
- When changes within soft boundaries begin to touch hard boundaries defined in Section 4, they must be treated as hard-boundary changes and follow the ADR process

---

### 总结 | Summary

> **软边界定义了 PeriSci “如何生长”，硬边界定义了 PeriSci “不能越界”。**

> **Soft boundaries define how PeriSci may grow; hard boundaries define what PeriSci must not cross.**

---

<a id="appendix-common-anti-patterns"></a>

## 7. 附：常见反模式（必须避免） | Appendix: Common Anti-Patterns (Must Be Avoided)

> **承接说明：**  
> 本节所列的反模式并非新的“硬边界”。它们是发生在“软边界”范围内、最常见、也最容易被忽视的错误实践。
>
> 这些反模式往往源于短期便利或局部优化，但若不加以避免，将逐步侵蚀第 4 节所定义的硬边界。

> **Transition note:**  
> The anti-patterns listed in this section are not new hard boundaries. They represent the most common and subtle pitfalls that occur **within soft boundaries**.
>
> These practices often arise from short-term convenience or local optimization, but if left unchecked, they will gradually erode the hard boundaries defined in Section 4.

本节列出在 PeriSci 的设计、实现与演进过程中**看似合理、但实际会破坏架构边界与长期可维护性的反模式**。

这些反模式通常源于短期便利、局部优化或经验迁移失当，但一旦出现，将导致系统逐步失去一致性与可控性。

This section lists **common anti-patterns** that may appear reasonable during development but will ultimately violate architectural boundaries and compromise long-term maintainability.

These anti-patterns often arise from short-term convenience, local optimizations, or inappropriate transfer of prior experience.

---

<a id="bypassing-the-api-to-access-core-directly"></a>

### Anti-Pattern 1 — 绕过 API 直接访问 core | Bypassing the API to Access core Directly

**表现形式：**

- 在 python 或 apps 中直接调用 core 的内部类或函数
- 为了“省事”暴露 core 内部实现细节

**为什么这是错误的：**

- 破坏 API 契约的权威性
- 使 core 难以演进和复用

**Symptoms:**

- Directly calling internal core classes or functions from python or apps
- Exposing core internals for convenience

**Why this is wrong:**

- Undermines the authority of the API contract
- Makes core evolution and reuse difficult

---

<a id="introducing-new-physical-semantics-at-entry-layers"></a>

### Anti-Pattern 2 — 在入口层引入新的物理语义 | Introducing New Physical Semantics at Entry Layers

**表现形式：**

- 在 python 或 CLI 中隐式修改物理参数含义
- 针对不同入口提供“特制版”物理行为

**为什么这是错误的：**

- 造成系统语义分裂
- 破坏可复现性与用户信任

**Symptoms:**

- Implicitly modifying physical parameter meanings in python or CLI
- Providing entry-specific “customized” physics behavior

**Why this is wrong:**

- Causes semantic fragmentation
- Breaks reproducibility and user trust

---

<a id="treating-datasets-as-physical-ground-truth"></a>

### Anti-Pattern 3 — 将数据集当作物理真理来源 | Treating Datasets as Physical Ground Truth

**表现形式：**

- 从 dataset 反推或修改物理含义
- 依赖数据导出格式解释物理行为
- 用 dataset 替代 cases 或 config 作为物理语义来源

**为什么这是错误的：**

- 混淆 results 与 dataset 的职责
- 对 AI 训练产生隐性偏差

**Symptoms:**

- Inferring or modifying physical meaning from datasets
- Letting data export formats dictate physics interpretation
- Using datasets as a substitute for canonical cases or configuration when interpreting physics

**Why this is wrong:**

- Blurs the responsibility between results and datasets
- Introduces hidden bias into AI training

---

<a id="sacrificing-reproducibility-for-performance"></a>

### Anti-Pattern 4 — 为性能牺牲可复现性 | Sacrificing Reproducibility for Performance

**表现形式：**

- 默认开启不可控的非确定性并行策略
- 为提速而忽略随机种子与运行记录

**为什么这是错误的：**

- 使科研结果不可验证
- 使工程结果不可审计
- 破坏 canonical cases 与 tests 的可复现性

**Symptoms:**

- Enabling uncontrolled nondeterministic parallelism by default
- Ignoring random seeds or execution records for speed

**Why this is wrong:**

- Makes scientific results unverifiable
- Makes engineering results unauditable
- Breaks reproducibility of canonical cases and regression tests

---

<a id="freezing-temporary-workarounds-into-the-architecture"></a>

### Anti-Pattern 5 — 将临时方案固化为架构 | Freezing Temporary Workarounds into the Architecture

**表现形式：**

- 为赶进度引入“临时接口”并长期保留
- 用注释而不是设计文档解释关键行为

**为什么这是错误的：**

- 技术债务快速累积
- 架构边界逐步腐蚀

**Symptoms:**

- Introducing “temporary” interfaces that persist indefinitely
- Explaining critical behavior via comments instead of design docs

**Why this is wrong:**

- Rapid accumulation of technical debt
- Gradual erosion of architectural boundaries

---

<a id="treating-roadmaps-as-architectural-commitments"></a>

### Anti-Pattern 6 — 用路线图代替架构承诺 | Treating Roadmaps as Architectural Commitments

**表现形式：**

- 以“未来会重构”为理由接受不合理设计
- 将阶段性计划当作架构保证

**为什么这是错误的：**

- 路线图会变化，架构边界不能
- 模糊当前系统的责任边界

**Symptoms:**

- Accepting poor design because “we will refactor later”
- Treating short-term plans as architectural guarantees

**Why this is wrong:**

- Roadmaps change; architectural boundaries must not
- Blurs responsibility boundaries of the current system

---

### 总结 | Summary

> **反模式并非“做不到”， 而是“做了之后系统会慢慢失控”。**
>
> **这些反模式通常首先破坏数值实验体系（examples、cases、tests），并最终侵蚀系统的架构边界。**

> **Anti-patterns are not things that cannot be done, but things that cause the system to gradually lose control if done. **
>
> **These anti-patterns often first damage the numerical experiment system (examples, canonical cases, and tests) before eventually eroding the architectural boundaries.**
