# API 执行契约规范（v0.2.x 冻结版）

# API Execution Contract Specification (v0.2.x Frozen)

> 本文档定义 **PeriSci 中核心 API 的执行级契约**，重点冻结 `run_case` 与 `export_dataset` 在 v0.2.x 阶段的职责边界与可执行语义。
>
> 本规范关注的是：**执行边界是否清晰、可审计、不可被误用**，而非功能完备性或数值复杂度。

> This document defines the **execution-level contracts of the core APIs in PeriSci**, with a focus on freezing the responsibility boundaries and executable semantics of `run_case` and `export_dataset` in the v0.2.x stage.
>
> This specification is concerned with **whether execution boundaries are clear, auditable, and resistant to misuse**, rather than functional completeness or numerical complexity.

---

## 1. 规范目的与范围 | Purpose and Scope

### 1.1 目的 | Purpose

本规范用于确立以下系统级事实：

- `run_case` 是 **纯执行契约**（即只负责执行一次计算，不引入流程控制、状态积累或外部副作用） (说明：外部副作用是指通过写文件、修改全局状态等方式，在返回值之外对系统产生的隐式影响，比如改变任何的调度逻辑等)
- `export_dataset` 是 **权威输出与固化（资产化）契约**（“资产化”在此指的是将运行时的结果固化为可审计、可比较的数据集资产）
  > `run_case` 与 `export_dataset` 依次位于 A 梁（`config_schema`）之后，共同在数值内核（`core`）的前后形成包裹：
  > `run_case` 作为唯一合法的执行入口驱动 `core`，
  > `export_dataset` 作为唯一合法的结果出口固化 `core` 的执行产物。
  > 在架构治理层面，外界不得绕过 `run_case` 或 `export_dataset` 直接接触 `core`。

This specification establishes the following system-level facts:

- `run_case` is a **pure execution contract** (i.e., it is responsible only for executing a single computation, without introducing flow control, state accumulation, or external side effects) (Note: external side effects refer to implicit impacts on the system (for example, to change any scheduling logic) outside the return value, such as writing files or modifying global state)
- `export_dataset` is an **authoritative export and persistence (assetization) contract** (“persistence/assetization” here means solidifying runtime results into auditable, comparable dataset assets.)
  > `run_case` and `export_dataset` are sequentially positioned after Beam A (`config_schema`), together forming a front-and-back enclosure around the numerical core (`core`):  
  > `run_case` serves as the sole legitimate execution entry point that drives the `core`,  
  > while `export_dataset` serves as the sole legitimate result outlet that solidifies the execution products of the `core`.  
  > At the architectural governance level, external entities must not bypass `run_case` or `export_dataset` to directly access the `core`.

### 1.2 非目标 | Non-Goals

本规范 **不**：

- 定义具体数值算法
- 描述工作流（workflow）或调度逻辑
- 覆盖 GUI / CLI / Python 封装细节

This specification does **not**:

- Define concrete numerical algorithms
- Describe workflows or scheduling logic
- Cover GUI / CLI / Python wrapper details

### 1.3 术语与主语澄清（避免误读）| Terminology and Subject Clarification (to prevent misreading)

上述第1.2节中出现的表述“本规范不描述 workflow / 调度逻辑”，其“本规范”（相同的词也出现在第1.1节）**仅指本文档（api-contract.md）作为规范文本的覆盖范围**：本文档不会规定工作流编排、任务调度、批处理、GUI 交互等外层控制逻辑的具体形式或实现方式。

与此同时，本文档对 `run_case` 的契约条款也明确规定：`run_case` **不得承担 workflow / 调度职责**。这里的含义是：任何跨多次 `run_case` 调用的流程编排、条件分支、循环、重试、参数扫描、任务排队或资源分配，都必须由 `run_case` 之外的**显式 orchestration**（外层调用方控制逻辑）承担，而不得隐藏在 `run_case` 的内部状态或逻辑中。

为避免混淆，本文档约定：

- **执行逻辑（execution logic）**：发生在单次 `run_case` 调用内部的解释、构建执行上下文、驱动 core、收集 results 等行为（属于 `run_case` 的职责）。
- **工作流 / 调度逻辑（workflow / scheduling logic）**：跨多次调用的流程编排、任务管理与资源分配（不属于 `run_case` 的职责，亦不在本文档的描述范围内）。

In the above Section 1.2, the statement “this specification does not describe workflow / scheduling logic” uses “this specification” （the same word also appears in Section 1.1）**solely to refer to the scope of this document (api-contract.md) as a normative text**: this document will not prescribe the concrete form or implementation of outer control logic such as workflow orchestration, job scheduling, batch execution, or GUI interactions.

At the same time, this document also explicitly defines contractual rules for `run_case`: `run_case` **must not assume workflow / scheduling responsibilities**. This means that any process orchestration across multiple `run_case` invocations—such as conditional branching, loops, retries, parameter sweeps, job queuing, or resource allocation—must be handled by **explicit orchestration** outside `run_case` (i.e., caller-side control logic), and must not be hidden in `run_case`’s internal state or logic.

To avoid confusion, this document adopts the following definitions:

- **Execution logic**: behaviors within a single `run_case` invocation, including interpretation, execution-context construction, driving the core, and collecting results (these are `run_case` responsibilities).
- **Workflow / scheduling logic**: cross-invocation process orchestration, job management, and resource allocation (these are not `run_case` responsibilities, and are also outside the descriptive scope of this document).

---

在上述定义基础上，进一步澄清以下两组容易混淆但必须严格区分的概念：

- **执行上下文（execution context） vs 工作流 / 调度逻辑（workflow / scheduling logic）**
  - 执行上下文指在**单次 `run_case` 调用内部**，为完成一次计算而构建和使用的运行期对象与状态，例如：
    - 将 `config_schema` 解释为可执行的数据结构
    - 构建一次计算所需的网格、自由度、邻域关系等执行期对象
    - 初始化求解器参数、内存缓冲与中间状态
  - 执行上下文的生命周期**严格限定在一次 `run_case` 调用之内**，随该调用开始而创建，随该调用结束而销毁，不得跨调用保留。
  - 工作流 / 调度逻辑则指**跨多次 `run_case` 调用**组织计算的外层控制逻辑，例如：
    - 决定先运行哪个 case、后运行哪个 case
    - 根据前一次结果决定是否重算或进入下一阶段
    - 批量参数扫描、重试策略、任务排队或并发控制
  - 因此，`run_case` 内部构建执行上下文是其作为“纯执行契约”的必要组成部分，而不构成 workflow 或调度逻辑。
- **执行逻辑（execution logic） vs 调度逻辑（scheduling logic）**
  - 执行逻辑指在**一次 `run_case` 调用内部**，描述“如何完成一次计算”的逻辑，例如：
    - 如何驱动数值内核（core）
    - 如何推进求解过程
    - 如何在执行结束时收集并组织 `results`
  - 调度逻辑指在**多次调用层面**，描述“何时、以何种顺序、在何种资源条件下执行计算”的逻辑，例如：
    - 任务调度与资源分配
    - 并发度与执行顺序控制
    - 跨调用的条件分支或循环
  - 本文档明确约定：`run_case` 只包含执行逻辑，不得包含调度逻辑；调度逻辑必须存在于 `run_case` 之外的显式 orchestration 中。

Based on the definitions above, the following two pairs of concepts—commonly confused but requiring strict separation—are further clarified:

- **Execution context vs workflow / scheduling logic**
  - Execution context refers to the runtime objects and states constructed and used **within a single `run_case` invocation** in order to complete one computation, for example:
    - interpreting `config_schema` into executable data structures
    - constructing execution-time objects such as meshes, degrees of freedom, and neighborhood relations
    - initializing solver parameters, memory buffers, and intermediate states
  - The lifecycle of the execution context is **strictly bounded to a single `run_case` invocation**: it is created at invocation start and destroyed at invocation end, and must not be preserved across invocations.
  - Workflow / scheduling logic, by contrast, refers to outer control logic that organizes computation **across multiple `run_case` invocations**, for example:
    - deciding which case to run first and which to run next
    - conditionally re-running or advancing to the next stage based on previous results
    - parameter sweeps, retry strategies, job queuing, or concurrency control
  - Therefore, constructing an execution context inside `run_case` is a necessary component of its role as a “pure execution contract” and does not constitute workflow or scheduling logic.

- **Execution logic vs scheduling logic**
  - Execution logic refers to logic **within a single `run_case` invocation** that defines how one computation is carried out, for example:
    - how the numerical core (`core`) is driven
    - how the solving process is advanced
    - how `results` are collected and organized at execution completion
  - Scheduling logic refers to logic **at the multi-invocation level** that defines when, in what order, and under what resource conditions computations are executed, for example:
    - task scheduling and resource allocation
    - control of concurrency and execution order
    - cross-invocation conditional branching or loops
  - This document explicitly stipulates that `run_case` contains execution logic only and must not contain scheduling logic; scheduling logic must reside in explicit orchestration outside `run_case`.

---

## 2. run_case 执行契约 | run_case Execution Contract

### 2.1 契约角色与定位 | Role and Positioning

`run_case` 的系统定位是：

> **将 config_schema 中声明的物理意图与执行策略，解释并映射为一次确定的数值执行过程。**（其中“执行策略”指在 schema 中声明的、影响单次计算方式的数值与算法选择，而不涉及跨调用的流程或调度逻辑）

The system-level role of `run_case` is:

> **To interpret and map the physical intent and execution strategy declared in `config_schema` into a single, well-defined numerical execution process.** (where “execution strategy” refers to numerical and algorithmic choices declared in the schema that affect how a single computation is carried out, and does not involve cross-invocation workflows or scheduling logic)

在三梁执行结构中：

- `run_case` **不声明** 物理意图
- `run_case` **不固化** 执行结果
- `run_case` 仅负责：
  - 解释 schema
  - 驱动 core
  - 生成结构化 results

Within the Three-Beam Execution structure:

- `run_case` does **not declare** physical intent
- `run_case` does **not solidify** execution results
- `run_case` is only responsible for:
  - interpreting the schema
  - driving the core
  - producing structured results

> #### 概念澄清（解释性注释，不构成规范）
>
> 为避免对 `run_case` 在三梁执行结构中职责的误解，特此澄清以下三个相关但不同的概念：
>
> **物理意图（physical intent）**
>
> - 指“要计算什么”的声明性内容；
> - 例如：物理模型、控制方程类型、几何描述、边界条件等；
> - 物理意图完全由 A 梁（`config_schema`）声明，
>   `run_case` 不得修改或补充物理意图。
>
> **执行策略（execution strategy）**
>
> - 指在**不改变物理意图的前提下**，关于“这一次计算如何进行”的数值与算法性选择；
> - 例如：求解器类型（直接法 / 迭代法）、离散阶次选择、时间推进方式、收敛准则类型等；
> - 执行策略同样属于 **可在 `config_schema` 中声明的内容**，
>   用于影响单次计算的数值执行方式；
> - 执行策略不涉及跨调用的流程编排、调度或多步控制。
>
> **执行上下文（execution context）**
>
> - 指 `run_case` 在**一次调用内部**，将物理意图与执行策略具体化后，
>   构建并使用的运行期执行结构；
> - 例如：已展开的参数、构建完成的网格与自由度、初始化后的求解器实例、
>   内存中的状态容器与中间数据；
> - 执行上下文：
>   - 由 `run_case` 构建；
>   - 生命周期严格限定在一次 `run_case` 调用之内；
>   - 不可声明、不可持久化、不得跨调用保留。
>
> 三者之间的关系可以概括为：
>
> - **物理意图**：我要算什么；
> - **执行策略**：这一次怎么算；
> - **执行上下文**：现在用哪些具体对象来算。
>
> 换言之，`config_schema` 负责声明 _物理意图 + 执行策略_，
> 而 `run_case` 负责构建 _执行上下文_ 并驱动数值内核完成一次计算。

> #### Concept Clarification (Explanatory Note, Non-Normative)
>
> To avoid misunderstandings regarding the responsibilities of `run_case` within the Three-Beam Execution structure, the following three related but distinct concepts are clarified:
>
> **Physical intent**
>
> - Refers to declarative content describing “what is to be computed”;
> - For example: physical models, types of governing equations, geometric descriptions, and boundary conditions;
> - Physical intent is entirely declared by Beam A (`config_schema`);
>   `run_case` must not modify or supplement physical intent.
>
> **Execution strategy**
>
> - Refers to numerical and algorithmic choices regarding “how this particular computation is carried out,” **without changing the physical intent**;
> - For example: solver type (direct / iterative), discretization order choices, time-integration schemes (steady-state / transient), and types of convergence criteria;
> - Execution strategy likewise belongs to content that **can be declared in `config_schema`**,
>   and is used to influence the numerical execution of a single computation;
> - Execution strategy does not involve cross-invocation process orchestration, scheduling, or multi-step control.
>
> **Execution context**
>
> - Refers to the runtime execution structures that `run_case` constructs and uses **within a single invocation**,
>   after concretizing physical intent and execution strategy;
> - For example: expanded parameters, constructed meshes and degrees of freedom, initialized solver instances,
>   in-memory state containers, and intermediate data;
> - The execution context:
>   - is constructed by `run_case`;
>   - has a lifecycle strictly bounded to a single `run_case` invocation;
>   - is not declarable, not persistable, and must not be retained across invocations.
>
> The relationship among the three concepts can be summarized as:
>
> - **Physical intent**: what is to be computed;
> - **Execution strategy**: how this computation is carried out;
> - **Execution context**: which concrete objects are used to carry it out.
>
> In other words, `config_schema` is responsible for declaring _physical intent + execution strategy_,
> while `run_case` is responsible for constructing the _execution context_ and driving the numerical core to complete a single computation.

---

### 2.2 输入约束 | Input Constraints

`run_case` 的输入 **必须且只能** 包含：

- 一个合法的 `config_schema` 实例

明确禁止：

- 接受散落的独立参数
- 接受运行期生成或修改后的 config
- 依赖隐式全局状态或环境变量（即未通过 `config_schema` 或函数参数显式声明、但可能影响执行结果的全局配置或运行环境设置）

**输入合法性要求**：

- schema 必须通过结构与版本校验
- 所有影响物理或数值语义的选择必须显式存在

The input to `run_case` **mush consist solely of**:

- one valid `config_schema` instance

Explicitly prohibited:

- accepting scattered independent parameters
- accepting runtime-generated or modified configurations
- relying on implicit global state or environment variables (i.e., global configuration or runtime settings that are not explicitly declared via `config_schema` or function arguments but may affect execution results)

**Input validity requirements**:

- the schema must pass structural and version validation
- all choices affecting physical or numerical semantics must be explicitly present

---

### 2.3 Results 结构 | Results Structure

`run_case` 的输出是一个 **结构化 results 对象**（即具有明确字段语义、稳定结构、可被程序化消费的结果集合，而非松散或临时拼接的数据），而不是副作用（即不通过写文件、修改全局状态等方式，在返回值之外对系统产生的隐式影响）。

results 的语义要求：

- 表达一次执行的：
  - 状态（如最终或阶段性的物理场状态，而非执行期内部缓存）
  - 关键数值量
  - 诊断信息
- 可被：
  - `export_dataset`
  - 回归测试（即用于检查在代码或实现修改之后，先前已经对外成立并被依赖的接口行为与结果结构，是否仍然保持不变）
  - 上层调用者稳定消费（即结果结构在版本演进中保持可预期，不因内部实现变化而破坏测试或上层调用逻辑）

明确禁止：

- 直接写文件
- 在 results 中混入 config 的副本并被修改

The output of `run_case` is a **structured results object** (i.e., a collection of results with explicit field semantics, stable structure, and programmatic consumability, rather than loosely or temporarily assembled data), and **not** a side effect (i.e., **No** implicit impacts on the system outside the return value, such as writing files or modifying global state).

Semantic requirements for results:

- they represent, for a single execution:
  - state (e.g., final or intermediate physical field states, rather than execution-time internal caches)
  - key numerical quantities
  - diagnostic information
- they can be stably consumed by:
  - `export_dataset`
  - regression tests (i.e., using existing test cases to verify that, after code changes, interfaces or results that previously worked well have not been inadvertently broken)
  - upper-level callers (i.e., the result structure remains predictable across version evolution and does not break tests or caller logic due to internal implementation changes)

Explicitly prohibited:

- directly writing files
- mixing modified copies of the config into results

> #### 概念澄清（解释性注释，不构成规范）
>
> ##### a) 为避免对“上层调用者”这一表述的误解，特此说明：
>
> 在本文语境中，“上层调用者”指**任何位于 `run_case` 之上，通过接口调用来接收其 `results` 的外部代码或系统组件**。  
> 该术语描述的是一种“角色”，而非某个特定模块或架构层。
>
> 典型的“上层调用者”包括（重要）：
>
> - **显式 orchestration 逻辑**：
>   - 用于组织多次 `run_case` 调用的外层控制代码；
>   - 例如：参数扫描脚本、多阶段计算流程、条件分支或批量执行控制。
> - **测试代码**：
>   - 回归测试、smoke test、CI 验证逻辑；
>   - 通过检查 `results` 的结构与语义来验证系统行为。
> - **接口与封装层**：
>   - Python API 封装、CLI 命令实现；
>   - 将 `run_case` 作为可复用能力暴露给用户。
> - **结果处理与分析工具**：
>   - 在调用 `export_dataset` 之前，对 `results` 进行检查、分析或筛选的代码。
>
> 需要特别区分的是：
>
> - **显式 orchestration** 是“上层调用者”的一个子集，专指负责跨多次 `run_case` 调用进行流程编排与控制的逻辑；
> - 并非所有上层调用者都是 orchestration，例如单次调用的测试代码或简单 API 封装同样属于上层调用者，但不承担流程调度职责。
>
> 在第 2.3 节中强调“结果可被上层调用者稳定消费”，其目的在于保证 `results` 作为接口产物的结构与语义稳定性，而非暗示任何特定的工作流或调度模式。
>
> ---
>
> ##### b) 为避免对下述两种表述的误解，即 “`run_case`输出的`results`可被上层调用者稳定消费” 与 “`export_dataset` 作为唯一合法的结果出口（参见第1.1节）”，有必要区分以下两个不同层级的概念：
>
> **结果（results）**
>
> - 指 `run_case` 通过返回值产生的**内存态、结构化执行结果**；
> - 可被上层调用者直接读取、检查和处理，例如：
>   - 用于判断计算是否成功或是否收敛；
> - 用于在线分析、调试或可视化；
> - 用于回归测试断言；
> - 用于显式 orchestration 决定后续是否再次调用 `run_case`；
> - `results` 的“可被消费”并不意味着其已经成为可发布、可归档的数据资产。
>
> **结果出口（result outlet）**
>
> - 指将一次 `run_case` 的执行产物**从运行态固化为可留存、可审计的数据资产（dataset）**的制度化通道；
> - 在本架构中，这一职责**唯一**由 `export_dataset` 承担；
> - 结果出口关注的是：
> - 数据资产的结构与命名；
> - 完整性与可追溯性（provenance）；
> - 可比较性与可复现性；
> - 因此，“唯一合法的结果出口”指的是**资产级、落盘级输出通道的唯一性**，而非对运行态结果可见性的限制。
>
> **需要特别避免的反例（重要）**：
>
> 下列行为将破坏“唯一合法结果出口”的架构治理原则：
>
> - 在 `run_case` 内部直接写文件、生成目录或构造 dataset；
> - 在上层调用者中绕过 `export_dataset`，将 `results` 以临时或随意方式写入文件系统，并在项目中被视为正式或可复用的数据产物；
> - 通过其他函数或脚本绕开 `run_case` / `export_dataset`，直接从 `core` 或中间状态导出可留存结果。
>
> 上述反例并非限制对 `results` 的正常使用，而是明确区分“运行态结果的消费”与“资产态结果的固化”这两个层级，以防止结果出口在演进过程中被无意识地分裂或绕过。

> #### Concept Clarification (Explanatory Note, Non-Normative)
>
> ##### a) To avoid misunderstandings regarding the term “upper-level callers”, the following clarification is provided:
>
> In the context of this document, “upper-level callers” refers to **any external code or system component that resides above `run_case` and receives its `results` via interface invocation**.  
> This term describes a _role_, rather than a specific module or architectural layer.
>
> Typical “upper-level callers” include (important):
>
> - **Explicit orchestration logic**:
>   - Outer control code used to organize multiple `run_case` invocations;
>   - For example: parameter sweep scripts, multi-stage computation workflows, conditional branching, or batch execution control.
> - **Test code**:
>   - Regression tests, smoke tests, and CI validation logic;
>   - Verifying system behavior by inspecting the structure and semantics of `results`.
> - **Interface and wrapper layers**:
>   - Python API wrappers and CLI command implementations;
>   - Exposing `run_case` as a reusable capability to users.
> - **Result processing and analysis tools**:
>   - Code that inspects, analyzes, or filters `results` prior to invoking `export_dataset`.
>
> A critical distinction must be made:
>
> - **Explicit orchestration** is a subset of “upper-level callers”, specifically referring to logic responsible for cross-invocation process orchestration and control across multiple `run_case` calls;
> - Not all upper-level callers are orchestration. For example, single-invocation test code or simple API wrappers are also upper-level callers, but do not assume workflow or scheduling responsibilities.
>
> The emphasis in Section 2.3 that “results can be stably consumed by upper-level callers” is intended to ensure the structural and semantic stability of `results` as an interface artifact, rather than to imply any specific workflow or scheduling pattern.
>
> ---
>
> ##### b) To avoid misunderstandings between the following two statements — “the `results` output by `run_case` can be stably consumed by upper-level callers” and “`export_dataset` serves as the sole legitimate result outlet (see Section 1.1)” — it is necessary to distinguish between the following two conceptual layers:
>
> **Results**
>
> - Refers to the **in-memory, structured execution output** produced by `run_case` via its return value;
> - Can be directly read, inspected, and processed by upper-level callers, for example:
>   - to determine whether a computation has succeeded or converged;
>   - for online analysis, debugging, or visualization;
>   - for regression test assertions;
>   - for explicit orchestration to decide whether to invoke `run_case` again;
> - The fact that `results` are “consumable” does not imply that they have already become publishable or archivable data assets.
>
> **Result outlet**
>
> - Refers to the institutionalized channel that **solidifies the execution products of a single `run_case` invocation from runtime state into durable, auditable data assets (datasets)**;
> - In this architecture, this responsibility is **exclusively** carried by `export_dataset`;
> - The result outlet is concerned with:
>   - the structure and naming of data assets;
>   - completeness and traceability (provenance);
>   - comparability and reproducibility;
> - Therefore, “the sole legitimate result outlet” refers to the uniqueness of the **asset-level, persisted output channel**, rather than to any restriction on the visibility or usability of runtime results.
>
> **Counterexamples that must be explicitly avoided (important)**:
>
> The following behaviors would violate the architectural governance principle of a “sole legitimate result outlet”:
>
> - Writing files, creating directories, or constructing datasets directly within `run_case`;
> - Bypassing `export_dataset` in upper-level callers by writing `results` to the file system in ad hoc or temporary ways, while treating them as formal or reusable data products within the project;
> - Bypassing `run_case` / `export_dataset` via other functions or scripts to export durable results directly from the `core` or intermediate states.
>
> These counterexamples are not intended to restrict the legitimate use of `results`, but to clearly distinguish between “consumption of runtime results” and “solidification of asset-level outputs”, thereby preventing the result outlet from being unintentionally fragmented or bypassed as the system evolves.

---

### 2.3.1 Results 的契约边界 | Contract Boundary of Results

`run_case` 返回的 `results` 是 **B 梁的权威运行态结果对象**。
The `results` returned by `run_case` are the **authoritative runtime result object of Beam B**.

它的职责是：

- 作为一次 `run_case` 调用的唯一结构化执行结果；
- 作为 `export_dataset` 的唯一合法上游结果输入；
- 作为回归测试与上层调用者可稳定消费的接口产物。

Their role is to:

- serve as the sole structured execution result of a single `run_case` invocation;
- serve as the sole legitimate upstream result input to `export_dataset`;
- serve as an interface artifact that can be stably consumed by regression tests and upper-level callers.

在 v0.2.x 阶段，`results` 的契约边界遵循以下规则：

- `results` 必须保持为**结构化、可程序化消费的对象**，而不是松散拼接的临时数据；
- `results` 中对外稳定暴露并被 `export_dataset`、测试或上层调用方依赖的字段语义，不得被隐式改变；
- 若 `results` 的稳定字段语义发生破坏性变更，则该变更必须通过显式治理路径处理（如版本升级或 ADR），不得以实现重构名义静默发生；
- `results` 只表达运行态执行结果，不承担数据集目录结构、文件命名或资产组织职责。

In the v0.2.x phase, the contract boundary of `results` follows these rules:

- `results` MUST remain a **structured, programmatically consumable object**, rather than loosely assembled temporary data;
- the semantics of fields in `results` that are stably exposed and relied upon by `export_dataset`, tests, or upper-level callers MUST NOT be changed implicitly;
- if the semantics of stable fields in `results` are changed in a breaking way, such changes MUST be handled through explicit governance paths (such as version upgrades or ADRs), and MUST NOT occur silently under the name of implementation refactoring;
- `results` express runtime execution outputs only, and do not assume responsibility for dataset directory structure, file naming, or asset organization.

---

### 2.3.2 可序列化性与导出适配要求 | Serializability and Export Adaptation Requirement

`results` **必须能够被稳定地序列化或等价地转换为可导出的结构化表示**，以支持 `export_dataset` 在不依赖隐式运行时状态的前提下完成数据资产固化。
`results` **MUST be stably serializable, or equivalently transformable into an exportable structured representation**, so that `export_dataset` can solidify them into data assets without relying on implicit runtime state.

这意味着：

- `results` 中被 `export_dataset` 消费的内容，必须以显式、可程序化访问的形式存在；
- `export_dataset` 不得依赖未暴露的内存对象、临时缓存或运行时上下文来“补全” `results`；
- 若某些执行期对象本身不可直接序列化，则 `run_case` 必须在 `results` 中提供与导出相关的等价结构化表示，而不得将该责任留给 `export_dataset` 在导出阶段隐式推断。

This means that:

- any part of `results` consumed by `export_dataset` MUST exist in an explicit and programmatically accessible form;
- `export_dataset` MUST NOT rely on hidden in-memory objects, transient caches, or runtime context to “complete” `results`;
- if certain execution-time objects are not directly serializable, `run_case` MUST provide an equivalent structured representation in `results` for export purposes, rather than leaving `export_dataset` to infer such information implicitly during export.

该要求的目的不是强制规定某一种具体序列化格式，而是确保：

- `results` 可以作为 B 梁到 C 梁之间的**稳定契约对象**；
- `export_dataset` 只负责资产化与结构组织，而不承担重新解释执行期内部状态的职责。

The purpose of this requirement is not to mandate any specific serialization format, but to ensure that:

- `results` can serve as a **stable contract object** between Beam B and Beam C;
- `export_dataset` is responsible only for assetization and structural organization, rather than reinterpreting internal execution-time state.

---

### 2.3.3 `run_case` 的 `results` 与 `manifest.results` 的区别 | Distinction Between `run_case` Results and `manifest.results`

需要明确区分以下两个对象：

- **`run_case` 的 `results`**：指 B 梁通过返回值产生的运行态、结构化执行结果对象；
- **dataset `manifest` 中的 `results` 对象**：指 C 梁数据集规范中用于描述 `results/` 目录结果文件结构索引的元数据对象。

The following two objects must be explicitly distinguished:

- **`run_case` `results`**: the runtime, structured execution result object produced by Beam B via return value;
- **the `results` object in the dataset `manifest`**: the metadata object defined by the Beam C dataset specification for describing the structural index of result files under the `results/` directory.

二者的关系是：

- 前者属于 **执行结果对象**；
- 后者属于 **资产级索引元数据**；
- 后者可以引用、组织、索引或描述由前者导出的结果文件；
- 后者**不得被视为前者的重新定义**，也不得取代前者作为 `run_case` 的接口结果对象。

换言之：

- `run_case` 的 `results` 用于运行态消费；
- `manifest.results` 用于导出后数据集的结构化索引；
- 二者名称相同，但语义层级不同，必须严格区分。

Their relationship is:

- the former is an **execution result object**;
- the latter is **asset-level indexing metadata**;
- the latter may reference, organize, index, or describe result files exported from the former;
- the latter **must not be treated as a redefinition of the former**, nor replace the former as the interface result object of `run_case`.

In other words:

- `run_case` `results` are for runtime consumption;
- `manifest.results` are for post-export dataset structural indexing;
- the two share the same name, but belong to different semantic layers and MUST be kept strictly distinct.

---

### 2.4 生命周期 | Lifecycle Semantics

`run_case` 的执行生命周期被规范为三个逻辑阶段：

1. **初始化（init）**
   - 校验 schema
   - 初始化所需的执行上下文（“执行上下文”参见第2.1节概念澄清）
2. **运行（run）**
   - 执行一次完整的数值计算
   - 不跨调用保留隐藏状态（即不得在一次 `run_case` 调用结束后，保留任何未通过输入参数显式声明、且会影响下一次调用行为的内部状态）
3. **完成（finalize）**
   - 整理 results（即将执行过程中产生的关键数值结果、状态与诊断信息，从内部执行对象中提取并组织为对外稳定的结构化输出）
   - 释放执行期资源

The execution lifecycle of `run_case` is defined as three logical stages:

1. **init**
   - validate the schema
   - initialize the required execution context
2. **run**
   - perform one complete numerical computation
   - do not retain hidden state across calls (i.e., do not preserve any internal state after a `run_case` invocation that is not explicitly declared via input parameters and that may affect subsequent invocations)
3. **finalize**
   - organize results (i.e., extract key numerical results, states, and diagnostic information generated during execution from internal execution objects and assemble them into a stable, externally visible structured output)
   - release execution-time resources

**约束 | Constraints**：

- 生命周期对调用者是原子的（即对外表现为一次不可分割的操作：调用者只能观察到完整成功或整体失败，而不存在可见的中间阶段）
- 多次调用之间 **不得** 共享隐式状态（包括但不限于通过全局变量、静态对象或单例缓存传递的执行期信息）
- the lifecycle is atomic from the caller’s perspective (i.e., externally observable only as a single indivisible operation: the caller can observe either complete success or complete failure, with no visible intermediate stages)
- multiple invocations **must not** share implicit state (including, but not limited to, execution-time information passed via global variables, static objects, or singleton caches)

---

### 2.5 副作用与状态约束 | Side-Effect and State Constraints

在 v0.2.x 阶段，`run_case`：

- **不得** 读写文件系统
  - 除非通过 `export_dataset`
- **不得** 修改输入的 config_schema
- **不得** 在内部维护跨调用的执行状态（即在一次调用结束后仍被保留、并可能影响后续 `run_case` 调用行为的内部状态）

> 换言之：`run_case` 是一个**可重复调用的、无副作用的执行边界**。

In the v0.2.x stage, `run_case`:

- **must not** read from or write to the file system
  - except via `export_dataset`
- **must not** modify the input `config_schema`
- **must not** maintain execution state across calls (i.e., internal state that is preserved after one invocation and may affect subsequent `run_case` invocations)

> In other words, `run_case` is a **repeatedly callable, side-effect-free execution boundary**.

---

### 2.6 确定性与可复现性（v0.2.x 最小保证）| Determinism and Reproducibility (v0.2.x Minimum Guarantees)

本节定义 `run_case` 在 v0.2.x 阶段**必须提供的最小确定性与可复现性保证**。

该保证的目标不是追求所有情况下的 bitwise 完全一致（即逐比特完全相同的数值结果），而是明确：

- **哪些条件下结果应当一致**
- **哪些差异是被允许且必须被记录的**

This section defines the **minimum determinism and reproducibility guarantees** that `run_case` must provide in the v0.2.x stage.

The goal of these guarantees is not to pursue bitwise complete identity in all cases (i.e., numerical results that are identical at the level of every binary digit), but rather to clearly specify:

- **under which conditions results should be consistent**
- **which differences are allowed and must be recorded**

---

#### 2.6.1 必须保证一致性的条件 | Conditions Requiring Consistency

在满足以下条件时，`run_case` 的输出结果 **应当保持一致性**：

- 使用 **完全相同的 `config_schema` 内容**（或等价 hash）
- 使用 **相同的 PeriSci 代码版本**
- 使用 **相同的数值内核实现**（core）
- 在 **相同执行模式** 下运行（例如：串行 / 确定性并行）

在上述条件下：

- 关键数值结果 **应当在数值容许范围内一致**（该范围由具体数值模型或测试准则定义）
- 在未引入并行或非确定性算子的情况下，**允许实现提供 bitwise identical 的结果（即浮点数的每一个二进制位都完全一致）**

> 注：v0.2.x 阶段不强制要求 bitwise identical，但若实现声称支持，则必须稳定成立。

When the following conditions are met, the output of `run_case` **should remain consistent**:

- exactly the same `config_schema` content is used (or an equivalent hash)
- the same PeriSci code version is used
- the same numerical core implementation is used
- execution occurs under the same execution mode (e.g., serial / deterministic parallel)

Under these conditions:

- key numerical results **should be consistent within acceptable numerical tolerances** (with tolerances defined by the specific numerical model or testing criteria)
- in the absence of parallelism or non-deterministic operators, implementations **may provide bitwise identical results** (i.e., every binary digit of floating-point values is exactly the same)

> Note: bitwise identity is not mandatory in v0.2.x, but if an implementation claims to support it, it must do so reliably.

---

#### 2.6.2 允许差异的因素（需显式记录）| Allowed Sources of Variation (Must Be Explicitly Recorded)

以下因素可能导致结果在数值层面出现差异，在 v0.2.x 阶段被视为**允许但必须可追溯**：

- 浮点舍入误差
- 并行执行顺序差异（线程 / 进程）
- 底层数学库或硬件差异

The following factors may lead to numerical differences in results and are considered **allowed but must be traceable** in the v0.2.x stage:

- floating-point rounding errors
- differences in parallel execution order (threads / processes)
- differences in underlying math libraries or hardware

**约束 | Constraints**：

- 上述差异 **不得** 改变结果的物理或语义解释
- 差异来源 **必须通过 元信息 被显式记录**
- such differences **must not** alter the physical or semantic interpretation of results
- sources of variation **must be explicitly recorded via metadata**

---

#### 2.6.3 结果结构中的溯源元信息 | Provenance Metadata in Results Structure

为支撑确定性与可复现性，`run_case` 产生的 results **必须包含最小溯源元信息集合**，至少包括：

- 使用的 `schema_version`
- `config_schema` 的 hash 或唯一标识
- PeriSci 版本
- 执行模式标识（如 serial / parallel）

这些元信息：

- 不参与数值计算
- 但必须作为 results 的结构化组成部分存在

To support determinism and reproducibility, the results produced by `run_case` **must include a minimal set of provenance metadata**, at least:

- the `schema_version` used
- a hash or unique identifier of the `config_schema`
- the PeriSci version
- an execution mode identifier (e.g., serial / parallel)

These metadata:

- do not participate in numerical computation
- but must exist as structured components of results

---

#### 2.6.4 最小测试要求（Determinism Smoke Test）| Minimum Testing Requirements (Determinism Smoke Test)

> 此处所称的“确定性冒烟测试”，指的是一种**最小化的测试**，其目的在于检测确定性行为中是否出现了明显的回归（即本来“跑得好好的”，在修改之后却开始出现不该有的不稳定或不一致行为），而**并非**用于穷尽性地证明系统在所有情况下都具备完全的可复现性。
>
> Here, a “Determinism Smoke Test” refers to a minimal test intended to detect obvious regressions (i.e., behavior that previously worked as expected but, after modifications, begins to exhibit instability or inconsistency that should not occur) in deterministic behavior, rather than to exhaustively prove full reproducibility.

v0.2.x 阶段至少要求：

- 一个 `test_run_case_smoke`
- 验证：相同输入在相同条件下，不会产生语义级差异的输出

该测试的目的在于：

- 防止 run_case 在演进中引入隐式非确定性（即未在接口或结果中显式声明、却可能导致相同输入产生不同输出的行为），而不是覆盖所有数值路径

In the v0.2.x stage, at minimum:

- one `test_run_case_smoke` is required
- it must verify that: under identical inputs and conditions, no semantic-level differences are produced in the output

The purpose of this test is to:

- prevent the introduction of implicit non-determinism during the evolution of `run_case` (i.e., behaviors that are not explicitly declared in the interface or results but may cause identical inputs to produce different outputs), rather than to cover all numerical execution paths

---

### 2.7 非目标与禁止模式（run_case）| Non-Goals and Forbidden Patterns (run_case)

`run_case` **不** 承担以下职责：

- 不作为 workflow / pipeline / GUI glue（即不在 `run_case` 内部承担多步骤流程编排、数据流式处理链（一个步骤输出直接作为下一个步骤输入），或为图形界面交互而混入的粘合逻辑（为了“按钮点一下就能跑”，把 UI 状态、交互逻辑硬塞进 `run_case` ））
- 不表达多步执行、条件分支或循环
- 不根据执行结果反向改变行为（此处“改变行为”指在一次 `run_case` 调用过程中，根据中间或最终执行结果，反向修改原本由 `config_schema` 或显式 orchestration 决定的执行策略、执行路径或控制逻辑，而不仅仅是更新执行上下文中的中间状态。）

`run_case` does **not** assume the following responsibilities:

- it must not act as workflow / pipeline / GUI glue (i.e., it must not internally undertake multi-step process orchestration, data-stream pipelines in which one step’s output directly feeds the next, or UI-driven glue logic introduced solely to enable “one-click execution” by embedding UI state or interaction logic into `run_case`)
- it must not express multi-step execution, conditional branching, or loops
- it must not change its behavior retroactively based on execution results (Here, “changing its behavior” refers to modifying, during a single `run_case` invocation, the execution strategy, execution path, or control logic originally determined by the `config_schema` or explicit orchestration, based on intermediate or final execution results, rather than merely updating intermediate state within the execution context.)

**规则 | Rule**：

- 任意多步执行或复杂流程
  - 必须由显式 orchestration 层（即位于 `run_case` 之外、负责组织多次调用顺序、条件与依赖关系的外层控制逻辑）完成，不得隐藏在 `run_case` 内部状态或逻辑中
- any multi-step execution or complex process
  - must be performed by an explicit orchestration layer (i.e., outer control logic located outside `run_case` that explicitly organizes invocation order, conditions, and dependencies across multiple calls)，and must not be hidden within `run_case`’s internal state or logic

---

## 3. export_dataset 权威输出与固化（资产化）契约 | Authoritative Export and Persistence (Assetization) Contract

### 3.1 契约角色与定位 | Role and Positioning

`export_dataset` 的系统定位是：

> **将一次 `run_case` 的执行结果，固化为可审计、可比较、可复现的数据资产。**

它是：

- 执行期实现（realization）的唯一制度化出口（即系统层面唯一被允许、被支持、被审计的结果固化与导出通道）

The system-level role of `export_dataset` is:

> **To solidify the execution results of a single `run_case` invocation into auditable, comparable, and reproducible data assets.**

It is:

- the only institutionalized outlet for execution-time realizations (i.e., the only system-level allowed, supported, and auditable channel for result solidification and export)

---

### 3.2 输入约束 | Input Constraints

`export_dataset` 的输入必须包含：

- 一个 `run_case` 产生的 results
- 明确的 数据集 规范（dataset spec）

明确禁止：

- 跳过 results 直接从 core 或中间状态导出
- 在导出过程中重新解释物理意图

The input to `export_dataset` must include:

- results produced by `run_case`
- an explicit dataset specification (dataset spec)

Explicitly prohibited:

- exporting directly from the core or intermediate states while bypassing results
- reinterpreting physical intent during export

---

### 3.3 输出与副作用 | Outputs and Side Effects

`export_dataset`：

- **允许** 产生文件系统副作用
- **必须** 按 dataset spec 生成结构化输出（其中 dataset spec 明确规定数据资产的结构、命名、元信息与组织方式）

其输出应：

- 可独立理解（即在脱离运行时内存状态和临时上下文的情况下，仅凭导出的数据与元信息即可被解析和理解）
- 不依赖运行时上下文
- 不反向影响任何执行逻辑

`export_dataset`:

- **is allowed** to produce file-system side effects
- **must** generate structured outputs according to the dataset spec (where the dataset spec explicitly defines the structure, naming, metadata, and organization of data assets)

Its outputs must:

- be independently understandable (i.e., interpretable solely from the exported data and metadata, without reliance on runtime memory state or transient context)
- not depend on runtime context
- not feed back into any execution logic

> **解释性注释（不构成规范）**
>
> 上述所说的“文件系统副作用”，指在程序执行过程中对文件系统产生的**持久性影响**，例如创建、修改或删除文件与目录，或将数据写入磁盘以供后续使用。
>
> 在本架构中，文件系统副作用本身并非被一概禁止，而是被**集中、制度化地约束**：
>
> - 在 `run_case` 中，文件系统副作用被明确禁止，以确保其作为纯执行契约，不承担结果固化或资产生成职责；
> - 在 `export_dataset` 中，文件系统副作用被**显式允许**，因为其职责正是将运行态的 `results` 固化为可留存、可审计的数据资产（dataset）。
>
> 因此，这里的“允许产生文件系统副作用”，并不意味着任意写文件都是合理的，而是指：**只有在履行数据导出与结果固化职责的语境下，且通过 `export_dataset` 这一受控通道，文件系统写入才是合法且期望的行为。**

> **Explanatory Note (Non-Normative)**
>
> As mentioned above, “file system side effects” refers to **persistent effects** on the file system produced during program execution, such as creating, modifying, or deleting files and directories, or writing data to disk for subsequent use.
>
> In this architecture, file system side effects are not categorically forbidden; instead, they are **centralized and institutionally constrained**:
>
> - Within `run_case`, file system side effects are explicitly prohibited, in order to ensure that it remains a pure execution contract and does not assume responsibilities for result solidification or asset generation;
> - Within `export_dataset`, file system side effects are **explicitly permitted**, because its responsibility is precisely to solidify runtime `results` into durable, auditable data assets (datasets).
>
> Therefore, “allowing file system side effects” here does not imply that arbitrary file writing is acceptable. Rather, it means that **file system writes are legitimate and expected only when performed through the controlled channel of `export_dataset`, and only in the context of fulfilling its data export and result solidification responsibilities.**

---

### 3.4 非目标与约束 | Non-Goals and Constraints

`export_dataset` **不**：

- 重新运行计算
- 修正或补全 config_schema
- 承担调度或批处理逻辑

它只负责：

- 固化
- 记录
- 归档

`export_dataset` does **not**:

- re-run computations
- modify or complete the `config_schema`
- assume scheduling or batch-processing responsibilities

It is only responsible for:

- solidification
- recording
- archiving

---

## 4. 冻结声明 | Freeze Statement

自 v0.2.x 起：

- `run_case` 与 `export_dataset` 的执行边界被冻结
- 执行逻辑与执行结果的职责被严格分离
- 任意对该契约的修改：
  - 必须显式
  - 必须可审计
  - 必须通过 ADR 或版本变更体现

Starting from v0.2.x:

- the execution boundaries of `run_case` and `export_dataset` are frozen
- the responsibilities of execution logic and execution results are strictly separated
- any modification to this contract:
  - must be explicit
  - must be auditable
  - must be reflected via ADR or version changes

> 本文档整体自 v0.2.0 起作为 **执行契约冻结规范** 生效，其稳定性优先级高于任何单一功能或实现便利性（即不得因短期功能需求而破坏已冻结的执行契约）。  
> 文中仅在少数条款中出现“在 v0.2.x 阶段”等表述，用于标注这些条款在当前阶段所承诺的**最小保证**（例如确定性、可复现性或副作用约束的最小要求），而不意味着本文档的其他冻结条款可以被弱化、忽略或视为非冻结。 是否在后续版本中对这些阶段性最小保证进行调整、细化或强化，须通过明确的版本升级或 ADR 过程声明，而不得在 v0.2.x 生命周期内以隐式方式变更。
>
> This document as a whole takes effect as a **frozen execution contract specification** starting from v0.2.0, and its stability takes precedence over any single feature or implementation convenience (i.e., the frozen execution contract must not be violated for short-term functional demands).  
> Only a limited number of clauses in this document explicitly use expressions such as “in the v0.2.x stage”; these are used to indicate the **minimum guarantees** promised at the current stage (e.g., minimal requirements for determinism, reproducibility, or side-effect constraints), and do not imply that other frozen clauses in this document may be weakened, ignored, or treated as non-frozen. Whether these stage-specific minimum guarantees are adjusted, refined, or strengthened in subsequent versions must be declared through explicit version upgrades or ADR processes, and must not be altered implicitly within the v0.2.x lifecycle.
