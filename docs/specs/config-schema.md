# config_schema 规范（v0.2.x 冻结版） 

# config_schema Specification (v0.2.x Frozen)

> 本文档定义 **PeriSci 中 config_schema 的权威地位、结构边界与演进规则**。
>
> 自 v0.2.x 起，`config_schema` 被冻结为：**系统中唯一合法的“物理意图（physical intent）表示形式”。**
>
> 任何新的物理假设、模型选择或求解/流程控制，若不能被表达为 schema 的一部分，则在架构层面被视为 *不存在*。
>
> This document defines the **authoritative role, structural boundaries, and evolution rules**
>of `config_schema` in PeriSci.
> 
> Starting from v0.2.x, `config_schema` is frozen as: **the only legitimate representation of physical intent in the system.**
>
> Any new physical assumption, model choice, or solver/procedure control that cannot be expressed as part of the schema is considered *non-existent* at the architectural level.

------

## 1. 目的与适用范围 | Purpose and Scope

### 1.1 目的 | Purpose

本规范的目的不是描述“如何写输入文件”，而是确立以下系统级事实：

- `config_schema` 是 **PeriSci 的权威输入契约（Authoritative Input Contract）**
- 它是系统理解“用户想算什么”的 **唯一入口**
- 它为：
  - `run_case`
  - `export_dataset`
  - 溯源 / 可复现性
  
  提供共同、稳定、可验证的语义基础

The purpose of this specification is not to describe “how to write an input file”, but to establish the following system-level facts:

- `config_schema` is the **Authoritative Input Contract** of PeriSci
- It is the **only entry point** through which the system understands “what the user wants to compute”
- It provides a shared, stable, and verifiable semantic foundation for:
  - `run_case`
  - `export_dataset`
  - provenance / reproducibility

### 1.2 非目标 | Non-Goals

本规范 **不**：
- 承诺任何数值完备性
- 定义具体算法实现
- 覆盖 GUI / CLI 表现形式

This specification does **not**:

- Promise numerical completeness
- Define concrete algorithm implementations
- Cover GUI / CLI presentation forms

------

## 2. 权威性声明 | Authoritativeness Statement

自 v0.2.x 起，PeriSci 明确采用以下规则：

- **所有物理意图必须显式存在于 config_schema 中**
- 任何不在 schema 中出现的“默认行为”，在架构上被视为非法
- 在实现 `run_case` 执行契约的各代码层级（包括 `core`、`apps`、`python` 目录）：
  - 不得引入新的物理语义
  - 只能 *解释、执行或映射* schema 中已存在的语义

> 换言之：**schema 不描述的，系统不理解；系统理解的，必须能被 schema 描述。**

Starting from v0.2.x, PeriSci explicitly adopts the following rules:

- **All physical intent must be explicitly present in `config_schema`**
- Any “default behavior” not appearing in the schema is considered architecturally illegal
- Within the code layers that implement the `run_case` execution contract (including the `core`, `apps`, and `python` directories):
  - No new physical semantics may be introduced
  - They may only *interpret, execute, or map* semantics already defined in the schema

> In other words:
> **What the schema does not describe, the system does not understand;
> what the system understands must be describable by the schema.**


------

## 3. schema 的最小顶层结构 | Minimal Top-Level Structure of the Schema

在 v0.2.x 阶段，`config_schema` 的顶层结构被冻结为以下逻辑分区：

In the v0.2.x stage, the top-level structure of `config_schema` is frozen as the following logical sections:

```text
config
├─ meta
├─ problem
├─ geometry
├─ material
├─ discretization
├─ solver
└─ output
```

### 3.1 meta 元信息 | Metadata

**职责 | Responsibility**：

- 标识配置本身，而非物理问题
- Identify the configuration itself, not the physical problem

**允许内容 | Allowed contents** ：

- schema_version
- config_id / name
- 创建时间、作者（可选）
- creation time, author (optional)

**约束 | Constraints**：

- `meta` 中的字段 **不允许影响数值结果**
- 仅用于追踪、标识与审计
- Fields in `meta` **must not affect numerical results**
- Used only for tracking, identification, and auditing

------

### 3.2 problem（问题定义）| (Problem Definition)

**职责 | Responsibility**：

- 定义“算什么物理问题”
- Define “what physical problem is being solved”

**示例语义 | Example semantics**：

- 问题类型（静力 / 动力 / 演化）
- 维度（2D / 3D）
- 控制方程类别（概念级）
- Problem type (static / dynamic / evolutionary)
- Dimension (2D / 3D)
- Class of governing equations (conceptual level)

------

### 3.3 geometry（几何）| (Geometry)

**职责 | Responsibility**：

- 定义计算域的几何与拓扑来源
- Define the geometric and topological source of the computational domain

**说明 | Note**：

- geometry 描述的是“几何意图”，而不是网格实现细节
- `geometry` describes **geometric intent**, not mesh implementation details

------

### 3.4 material（材料 / 本构）| (Material / Constitutive Model)

**职责 | Responsibility**：

- 定义材料模型选择及其参数
- Define the choice of material models and their parameters

**约束 | Constraints**：

- 不允许隐藏默认材料参数
- 所有影响本构响应的量必须显式出现
- Hidden default material parameters are not allowed
- All quantities affecting constitutive response must be explicit

------

### 3.5 discretization（离散化）| (Discretization)

**职责 | Responsibility**：

- 描述连续问题如何被离散
- Describe how the continuous problem is discretized

**示例语义 | Example semantics**：

- FEM / PeriFEM 类型选择
- 形函数阶次 / 邻域半径（概念级）
- FEM / PeriFEM method selection
- Shape function order / neighborhood radius (conceptual level)

------

### 3.6 solver（求解控制）| (Solver Control)

**职责 | Responsibility**：

- 描述求解流程与控制参数
- Describe the solution procedure and control parameters

**说明 | Note**：

- solver 字段属于“执行策略”，而非物理定律
- `solver` fields belong to **execution strategy**, not physical laws

------

### 3.7 output（输出意图）| (Output Intent)

**职责 | Responsibility**：

- 声明用户希望观察、保存或导出的量
- Declare quantities the user wishes to observe, save, or export

**约束 | Constraints**：

- output 不得反向影响物理求解过程
- `output` must not feed back into the physical solution process

------

## 4. 字段语义与所有权规则 | Field Semantics and Ownership Rules

### 4.1 语义所有权 | Semantic Ownership

- 每一个 schema 字段必须明确：
  - 它描述的是 **物理意图** 还是 **执行策略**
- 不允许出现：
  - 同一字段同时承担多重语义
  - 通过字段组合“隐式推断”物理模型

- Each schema field must clearly specify whether it describes:
  - **physical intent**, or
  - **execution strategy**
- The following are not allowed:
  - A single field carrying multiple semantic roles
  - Implicit inference of physical models through field combinations

### 4.2 默认值策略 | Default Value Policy

- 在 v0.2.x 阶段：
  - 默认值应 **尽量少**
  - 若存在默认值，必须在 spec 中显式说明
- In the v0.2.x stage:
  - Default values should be **minimized**
  - If defaults exist, they must be explicitly documented in the spec

------

## 5. 哈希 / 语义差异比较 / 溯源 规则 | Hash / Diff / Provenance Rules

### 5.1 规范表示与输入格式 | Canonical Representation & Input Format

本节**继承并落实**《DESIGN_CONTRACT》中定义的规范表示规则；以下内容仅规定 `config_schema` 在校验、语义差异比较 与 `config_hash` 计算中的**执行细则**。

**规则（冻结）**：

- 在 v0.2.x 阶段，`config_schema` 的权威输入文件与其规范化表示**统一采用 JSON**。
- 所有用于 语义差异比较、`config_hash` 计算、溯源 绑定与缓存键生成的表示，**必须基于确定性的 canonical JSON 结构化对象**，而非原始文本内容。
- canonical JSON 的生成必须消除非语义差异（例如对象键顺序、无关格式差异），以保证等价配置产生等值 哈希。

**未来演进预留**：

- 未来版本可支持 YAML 等人类友好输入格式；但其输出必须被确定性转换为 canonical JSON；**也只有 canonical JSON 表示的对象，才允许作为权威输入参与 语义差异比较、哈希 计算、溯源 关联以及治理与冻结判定**。

**禁止事项（治理红线）**：

- ❌ 基于原始配置文件文本直接计算 哈希值
- ❌ 同时将多种格式视为同等权威输入
- ❌ 允许隐式类型推断导致同一配置语义出现多种等价表示

This section **inherits and operationalizes** the **Canonical Representation Rule** defined in the *DESIGN_CONTRACT*. The following content specifies only the **execution details** for `config_schema` in validation, diff, and `config_hash` computation.

**Rules (Frozen):**

- During the v0.2.x phase, the authoritative input files for `config_schema` and their canonical representations **must use JSON exclusively**.
- All representations used for diff, `config_hash` computation, provenance binding, and cache key generation **must be based on deterministic canonical JSON structured objects**, rather than raw textual file content.
- Canonical JSON generation must eliminate non-semantic differences (e.g., object key ordering, irrelevant formatting differences) to ensure that equivalent configurations yield equivalent hashes.

**Future Evolution (Reserved):**

- Future versions may support human-friendly input formats such as YAML; however, their outputs must be deterministically converted into canonical JSON; and **only objects represented in canonical JSON are permitted to serve as authoritative inputs for diff, hash computation, provenance association, and governance and freeze determination**.

**Prohibited Practices (Governance Red Lines):**

- ❌ Computing hashes directly from raw configuration file text
- ❌ Treating multiple formats as equally authoritative inputs
- ❌ Allowing implicit type inference that results in multiple equivalent representations of the same configuration semantics

### 5.2 必须可 哈希 / 语义差异比较 的字段 | Fields Required to Support Hash / Diff

以下字段集合 **必须** 支持稳定的 哈希 / 语义差异比较：

- problem
- geometry
- material
- discretization
- solver

其 哈希 值构成：

- 结果可复现性的核心判据
- dataset 溯源 的关键索引

The following sections **must** support stable hash / diff behavior:

- problem
- geometry
- material
- discretization
- solver

Their hash values constitute:

- The core criterion for result reproducibility
- The key index for dataset provenance

### 5.3 溯源 强制字段 | Mandatory Provenance Fields

以下信息 **必须进入 溯源**：

- 完整 `config_schema` 内容（或其 哈希）
- schema_version
- PeriSci 版本

The following information **must** enter provenance records:

- Full `config_schema` content (or its hash)
- schema_version
- PeriSci version

------

## 6. 版本化与兼容策略 | Versioning and Compatibility Policy

### 6.1 schema_version | schema_version

- 每一份 config **必须** 显式声明 `schema_version`
- schema_version 与 PeriSci 版本解耦

- Every config **must** explicitly declare `schema_version`
- `schema_version` is decoupled from the PeriSci version

### 6.2 兼容性规则 | Compatibility Rules

- **向后兼容**：
  - 新字段引入，旧 schema 仍可解析
- **破坏性变更**：
  - 字段语义改变
  - 字段删除或重解释

> 任何破坏性变更：
>
> - 必须提升 schema_version
> - 必须伴随 ADR
> - 本规范仅定义 A 梁（输入契约）的版本演进规则；**涉及 C 梁输出资产的破坏性变更，其版本处理必须遵循 `dataset-spec` 中定义的 Versioning Red Line（C 梁）**。
>
> 新增顶层分区一律视为破坏性变更，需要 ADR + schema_version 提升

- **Backward compatible**:
  - New fields are introduced while old schemas remain parseable
- **Breaking change**:
  - Field semantics change
  - Fields are removed or reinterpreted

> Any breaking change:
>
> - Must increment `schema_version`
> - Must be accompanied by an ADR
> - This specification defines version evolution only for Beam A (input contracts); **version handling for breaking changes affecting Beam C output assets MUST follow the Versioning Red Line (Beam C) defined in the dataset-spec**.
>
> Adding a new top-level section is always considered a breaking change and requires both an ADR and a schema_version increment.


------

## 7. 验证与测试要求（v0.2.x 最小保证）| Validation and Testing Requirements (v0.2.x Minimum Guarantee)

在 v0.2.x 阶段至少要求：

- schema 解析与结构校验测试
- 非法字段 / 缺失字段被明确拒绝

测试目标不是覆盖所有字段，而是验证 **schema 作为契约的可执行性**。

At minimum, the v0.2.x stage requires:

- Schema parsing and structural validation tests
- Explicit rejection of illegal or missing fields

The goal of testing is not full field coverage, but to verify **the executability of the schema as a contract**.

------

## 8. 非目标与禁止模式 | Non-Goals and Forbidden Patterns

本节用于**显式声明 config_schema 不得承担的职责与禁止出现的使用模式**。

其目的不是限制表达能力，而是防止在长期演进中出现：

- 作用域膨胀（scope creep）
- 语义漂移（silent semantic drift）
- 架构责任混淆

这些问题一旦出现，往往无法通过“重构”修复，只能通过**制度性禁止**提前止血。

This section explicitly declares responsibilities that  `config_schema` must not assume and usage patterns that are prohibited.

The purpose is not to limit expressiveness, but to prevent long-term issues such as:

- Scope creep
- Silent semantic drift
- Architectural responsibility confusion

Once these issues occur, they are often not fixable through refactoring and must be stopped in advance through **institutional prohibitions**.

------

### 8.1 明确的非目标 | Explicit Non-Goals

config_schema **不承担**、也**永远不应承担**以下职责：

`config_schema` does **not**, and must **never**, assume the following roles:

#### 8.1.1 不描述 GUI 或交互状态 | No GUI or Interaction State Description

- config_schema **不得**包含：
  - 窗口布局
  - 视角、相机位置
  - 可视化配色、显示选项
  - GUI 控件状态（勾选、展开、折叠等）
- `config_schema` must **not** contain:
  - Window layouts
  - View or camera positions
  - Visualization colors or display options
  - GUI widget states (checked, expanded, collapsed, etc.)

**原因 | Reason**：

- GUI 状态属于“人机交互上下文”，而非物理意图
- 将 GUI 状态写入 schema 会导致：
  - schema 不可复现
  - 与批量 / AI 调用场景直接冲突

- GUI state belongs to the human–machine interaction context, not physical intent
- Encoding GUI state in the schema leads to:
  - Non-reproducible schemas
  - Direct conflict with batch / AI-driven execution

------

#### 8.1.2 不承载隐式或推断式默认行为 | No Implicit or Inferred Default Behavior

- config_schema **不得依赖**：
  - "若未填写则系统自动选择"
  - "根据其他字段推断"
  - "运行时补全"
- `config_schema` must **not** rely on:
  - “Automatically chosen if not specified”
  - “Inferred from other fields”
  - “Completed at runtime”

**规则 | Rule**：

- 若某一物理或数值选择会影响结果，它 **必须显式存在于 schema 中**
- Any physical or numerical choice affecting results **must be explicitly present in the schema**

**允许的例外 | Allowed exceptions**：

- 与物理结果无关的显示或日志级别
- 已在 spec 中明确声明、且不影响 哈希 / 溯源 的元信息
- Display or logging options unrelated to physical results
- Metadata explicitly documented in the spec and not affecting hash / provenance

------

#### 8.1.3 不作为执行期状态的回写容器 | Not a Write-Back Container for Execution-Time State

- 严格禁止：
  - 在运行过程中修改 config_schema
  - 将计算中生成的状态、历史或统计信息写回 config
- Strictly prohibited:
  - Modifying `config_schema` during execution
  - Writing execution-generated state, history, or statistics back into config

**原因 | Reason**：

- config_schema 是“意图声明”，不是“状态快照”
- 执行期状态必须通过：
  - 结果
  - 数据集
  - 溯源
  
  进行表达

- `config_schema` is a declaration of intent, not a state snapshot
- Execution-time state must be expressed via:
  - results
  - dataset
  - provenance

------

#### 8.1.4 原则上不新增顶层分区（v0.x → v1.0）| No New Top-Level Sections by Default (v0.x → v1.0)

- v0.x → v1.0 期间，原则上 **不新增** 顶层逻辑分区（top-level sections）
- 新需求优先通过以下方式在既有分区内表达：
  - 在既有分区内新增字段
  - 使用枚举扩展
  - 增加可选子对象（必须同时明确其 哈希 / 溯源 规则）

- During v0.x → v1.0, adding new top-level logical sections is **prohibited by default**
- New requirements should be expressed within existing sections via:
  - Adding new fields
  - Enum extensions
  - Optional sub-objects (with explicit hash / provenance rules)

**唯一允许例外（需要 ADR）| The only allowed exception (ADR required)**：

- 某需求无法自然归属任何既有分区，且若强行放入将导致：
  - 跨越多个分区的语义缠绕
  - 字段职责不清、难以审计
- A requirement cannot be naturally assigned to any existing section,
   and forcing it would result in:
  - Cross-section semantic entanglement
  - Unclear field responsibility or poor auditability

在该例外情况下：

- 必须提出新增顶层分区
- 必须通过 ADR 记录动机、备选方案与破坏性评估

In such cases:

- A new top-level section must be proposed
- An ADR must document the motivation,
   alternatives considered, and breaking-change assessment

------

### 8.2 禁止模式 | Forbidden Patterns

以下模式在架构层面被视为 **非法**：

The following patterns are considered **architecturally illegal**:

#### 8.2.1 通过缺省值隐式改变物理语义 | Implicitly Changing Physical Semantics via Defaults

- 示例（非法）：
  - 未指定材料模型时默认选择某一模型
  - 未指定维度时根据几何文件自动推断
- Examples (illegal):
  - Defaulting to a material model when none is specified
  - Inferring dimensionality from geometry files

**要求  | Requirement**：

- 所有影响物理响应的选择必须显式声明
- All choices affecting physical response must be explicitly declared

------

#### 8.2.2 利用字段组合“暗示”模型行为 | “Suggesting” Model Behavior via Field Combinations

- 示例（非法）：
  - 通过某两个参数的组合暗示启用某一损伤模型
  - 通过 solver 选项间接改变本构行为
- Examples (illegal):
  - Enabling a damage model through a specific parameter combination
  - Indirectly changing constitutive behavior via solver options

**规则 | Rule**：

- 模型选择必须是：
  - 显式
  - 单义
  - 可枚举
- Model selection must be:
  - Explicit
  - Unambiguous
  - Enumerable

------

#### 8.2.3 通过 schema 承担 workflow 或 orchestration 逻辑 | Encoding Workflow or Orchestration Logic in the Schema

- config_schema **不得**：
  - 描述多步计算流程
  - 表达条件分支、循环或依赖关系
- `config_schema` must **not**:
  - Describe multi-step computation workflows
  - Express conditionals, loops, or dependencies

**说明 | Note**：

- workflow 属于 orchestration 层责任
- schema 仅描述“单次物理意图”
- Workflow belongs to the orchestration layer
- The schema describes only **a single physical intent**

------

### 8.3 守护规则 | Guardrails

为确保上述非目标与禁止模式长期有效，系统必须遵循以下守护规则：

To ensure long-term effectiveness of the above non-goals and prohibitions, the system must follow these guardrails:

- 新字段引入时，必须明确：
  - 它是否影响物理语义
  - 它是否进入 哈希 / 溯源
- 若无法明确回答上述问题：
  - 该字段 **不得进入 schema**
- When introducing a new field, it must be clear:
  - Whether it affects physical semantics
  - Whether it enters hash / provenance
- If these questions cannot be clearly answered:
  - The field **must not enter the schema**

------

## 9. 冻结声明 | Freeze Statement

自 v0.2.x 起：

- `config_schema` 的结构、职责与权威性被冻结
- 新的物理意图 **不得绕过 schema 注入系统**
- 对 schema 的任何修改：
  - 必须显式
  - 必须可追溯
  - 必须通过版本或 ADR 体现

> 本文档是 v0.2.x 阶段的 **冻结规范**，其稳定性优先级高于任何单一算例或实现需求。

Starting from v0.2.x:

- The structure, responsibilities, and authority of `config_schema` are frozen
- New physical intent **must not bypass the schema** to enter the system
- Any modification to the schema:
  - Must be explicit
  - Must be traceable
  - Must be reflected via versioning or ADR

> This document is the **frozen specification** for the v0.2.x stage, and its stability has higher priority than any individual case or implementation demand.