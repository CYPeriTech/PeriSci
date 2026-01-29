# 设计契约 | DESIGN_CONTRACT

> 本文档是 PeriSci 的“设计契约”（Design Contract）。  
> 它不是介绍性文档，而是**不可随意违反的工程宪法**：用于约束架构演进、代码评审与功能扩展。  
> 任何偏离本文档的实现，都应被视为**需要明确记录的设计决策（ADR）**，而不是“顺手改改”。

> This document is the PeriSci **Design Contract**.  
> It is not an introduction; it is the **constitutional constraint** governing architecture evolution, code review, and feature growth.  
> Any deviation must be recorded explicitly as an **Architecture Decision Record (ADR)**, not as an ad-hoc change.

---

## 0. 范围与目标 | Scope and Goals 
### 0.1 本契约约束什么 | What this contract constrains
- PeriSci 的系统架构必须遵循 **“三梁（Three-Beams）”**结构。  
- PeriSci 的数值内核必须遵循 **“四核（Four-Cores）”**结构。  
- PeriSci 的演进必须以 **“算例资产（Case Assets）”** 的累积作为核心工程机制。

- PeriSci’s system architecture **must** follow the **Three-Beams** structure.  
- PeriSci’s numerical core **must** follow the **Four-Cores** structure.  
- PeriSci’s evolution **must** accumulate **Case Assets** from day one as a core engineering mechanism.

---

### 0.2 本契约不讨论什么 | What this contract does not cover
- 不讨论具体物理模型（弹性、塑性、损伤、断裂等）的公式细节。  
- 不讨论外部库（deal.II / PETSc 等）的使用教程。  
- 不为短期 Demo 牺牲长期治理能力：**“能跑”不是“可存活”。**

- This document does not define specific constitutive models (elasticity, plasticity, damage, fracture, etc.).  
- It is not a usage tutorial for external libraries (deal.II / PETSc / …).  
- Long-term governance is not sacrificed for short-term demos: **“runs once” is not “survivable”.**

---

### 0.3 治理原则 | Governance Principles
#### 0.3.1 原则：冻结、最小保证与演进预留的关系

在 PeriSci 的契约与架构治理中，“冻结”“最小保证”“演进预留”并非相互排斥的三种状态，而是对同一规则在不同治理维度上的强调。

- **冻结（Freeze）**约束的是规则的变更方式：被冻结的契约在当前版本生命周期内不得因短期功能需求或实现便利性而被破坏；任何修改都必须通过显式的版本升级或 ADR 等可审计的治理路径完成。冻结并不意味着规则永不演进，而是禁止隐式、临时或无记录的破坏性变更。
  
- **最小保证（Minimum Guarantee）**约束的是当前阶段所承诺的行为下限：在给定版本阶段（例如 v0.2.x），规范中明确声明的“最小保证”表示系统在最保守条件下至少应满足的确定性、可复现性、完整性或副作用约束；最小保证是阶段性的强度承诺，而非对最终能力上限的限定。
  
- **演进预留（Evolution Reserve）**约束的是未来升级的合法路径：规范中对阶段性表述、可选增强或未来可能加强之处的明确标注，用于为后续版本提高标准、细化语义或引入新模式预留空间；任何此类演进必须通过版本升级或 ADR 显式声明，而不得在当前冻结版本中隐式发生。

上述三者可同时适用于同一条规则：  冻结保证规则在当前版本内的稳定性，  最小保证明确当前阶段对外承诺的行为下限，  演进预留确保未来升级具有清晰、可审计且不破坏信任的路径。

#### 0.3.1 Principle: The Relationship Between Freeze, Minimum Guarantee, and Evolution Reserve

In PeriSci’s contract and architectural governance, “Freeze,” “Minimum Guarantee,” and “Evolution Reserve” are not mutually exclusive states, but rather different emphases on the same rule across distinct governance dimensions.

- **Freeze** constrains *how* a rule may be changed:  A frozen contract must not be violated within the current version lifecycle for short-term functional demands or implementation convenience.  Any modification must be carried out through explicit, auditable governance paths such as version upgrades or ADRs.  Freeze does not imply that a rule can never evolve; rather, it prohibits implicit, ad hoc, or unrecorded breaking changes.
  
- **Minimum Guarantee** constrains the *behavioral lower bound* promised at the current stage:  For a given version stage (e.g., v0.2.x), the “minimum guarantee” explicitly stated in the specification defines the least level of determinism, reproducibility, integrity, or side-effect constraints that the system must satisfy under conservative assumptions.  A minimum guarantee is a stage-specific commitment of strength, not a limitation on the system’s ultimate capabilities.
  
- **Evolution Reserve** constrains the *legitimate path of future upgrades*:  Explicit markings of stage-specific wording, optional enhancements, or areas expected to be strengthened in future versions are intended to reserve space for raising standards, refining semantics, or introducing new modes in later releases.  Any such evolution must be explicitly declared through version upgrades or ADRs, and must not occur implicitly within the current frozen version.

These three aspects may simultaneously apply to the same rule:  Freeze ensures the rule’s stability within the current version,  Minimum Guarantee defines the behavioral lower bound promised at the present stage,  and Evolution Reserve ensures that future upgrades proceed through clear, auditable, and trust-preserving paths.


---

## 1. 核心概念总览 | Core Concept Overview
PeriSci 的架构由三类“不可替代要素”组成：  
1) **三梁（系统宪法）**：保证系统可运行、可复现、可扩展、可自动化  
2) **四核（数值骨架）**：保证求解器扩展时不发生结构性重构  
3) **算例资产（价值积累机制）**：保证质量门禁、回归测试、方法对比与长期演进  

这三者构成闭环：  
- 执行方向：**三梁 → 四核 → 算例资产**  
- 治理方向：**算例资产 → 反向约束四核与三梁**

PeriSci’s architecture is built on three non-substitutable pillars:  
1) **Three-Beams (system constitution)**: runnability, reproducibility, extensibility, automation  
2) **Four-Cores (numerical skeleton)**: prevents structural refactors as physics expands  
3) **Case Assets (value accumulation)**: enables quality gates, regression, comparison, long-term evolution  

They form a loop:  
- Execution: **Three-Beams → Four-Cores → Case Assets**  
- Governance: **Case Assets → constrain and validate Four-Cores and Three-Beams**

---

## 2. 三梁（Three-Beams）系统结构 | Three-Beams System Structure
三梁不是目录结构，也不是“前处理/求解器/后处理”的换名。  
它是**系统层的宪法级治理约束**，必须以“宪法级强制”存在。

Three-Beams is not a folder layout, nor a renaming of “pre/solver/post”.  
It is a **constitutional, system-level governance contract**.

>------
>#### 解释性注解：Intent / Strategy / Realization 的语义分离
> 为避免在实现与扩展过程中混淆系统责任，
>  PeriSci 在理解三梁时，明确区分以下三种不同层次的语义角色：
>
> - **Intent（意图）**：描述“要解决什么物理问题”，包括问题类型、几何、材料与边界等。
> - **Strategy（策略）**：描述“系统如何执行该意图”，包括离散思想与求解控制策略。
> - **Realization（实现）**：描述执行过程中生成的具体计算对象与状态实例，例如网格、自由度、邻域关系与中间状态。
>
> 在 PeriSci 的三梁结构中：
>
> - **Intent** 由 **A 梁（config_schema）** 以声明性形式完整承载；
> - **Strategy** 由 **A 梁声明**，并由 **B 梁（run_case）** 负责解释与执行；
> - **Realization** 仅存在于 **B 梁的执行过程** 与 **C 梁（export_dataset）的输出结果** 中，不得回写至 config_schema。
>
> 该三层分离是一种**语义责任划分原则**，
>  用于解释三梁如何协同工作，
>  而**不构成新的系统层级或架构要素**。
>
>------
>#### Explanatory Note: Semantic Separation of Intent / Strategy / Realization
> To avoid responsibility confusion during implementation and extension,
>  PeriSci distinguishes three semantic roles when interpreting the Three-Beams structure:
>
> - **Intent**: what physical problem is to be solved, including problem type, geometry, materials, and boundaries.
> - **Strategy**: how the system chooses to execute that intent, including discretization concepts and solver control policies.
> - **Realization**: the concrete computational objects and state instances generated during execution, such as meshes, degrees of freedom, neighborhood relations, and intermediate states.
>
> Within the Three-Beams structure of PeriSci:
>
> - **Intent** is fully and declaratively carried by **Beam A (config_schema)**;
> - **Strategy** is declared in **Beam A** and interpreted and executed by **Beam B (run_case)**;
> - **Realization** exists only during **Beam B execution** and in **Beam C (export_dataset) outputs**, and must not be written back into the config_schema.
>
> This separation is a **semantic responsibility principle**
>  used to explain how the Three-Beams collaborate,
>  and **does not introduce a new system layer or architectural component**.

---

### 2.1 A 梁：config_schema（权威输入契约）| Beam A: config_schema (Authoritative Input Contract) 
**定义**：所有仿真任务必须由一个“权威配置对象（Authoritative Config）”定义，并可被机器校验。

**Definition**: Every simulation is defined by an authoritative, machine-validated config.

**必须满足 / Must have**
- **Schema 校验**：类型、范围、枚举、必填项必须可验证；非法配置必须 fail-fast。
- **语义稳定**：字段的物理含义必须稳定；任何变更必须通过版本号管理。
- **可版本化**：必须有 `schema_version`，并有明确的兼容/拒绝策略。
- **可 diff / 可 hash**：配置必须可被规范化序列化并生成 `config_hash`，用于复现与缓存键。
- **Schema validation**: types, ranges, enums, required fields; fail-fast on invalid configs.
- **Stable semantics**: field meanings must be stable; any change requires versioning.
- **Versioning**: `schema_version` with explicit compatibility/rejection policy.
- **Diff/hashability**: canonical serialization and `config_hash` for reproduction/caching.

**禁止事项（红线） / Hard red lines**

> 这些禁止事项的根本目的，是确保 **物理意图（intent）** 不被执行策略或执行期实现（strategy / realization）所污染。
> These prohibitions exist to ensure that **physical intent** is not polluted by execution strategies or execution-time realizations.

- ❌ 依赖 GUI 状态、交互步骤或隐含默认值来补全问题描述  
- ❌ 将关键参数散落在代码常量、环境变量或文件系统路径中  
- ❌ schema 变更导致旧配置“悄悄还能跑但语义变了”（silent drift）
- ❌ relying on GUI state, interactive steps, or implicit defaults as “hidden inputs”
- ❌ scattering key parameters across code constants/env vars/file paths
- ❌ silent drift (old configs still run but semantics changed)

---

### 2.2 B 梁：run_case（纯执行闭环）| Beam B: run_case (Pure Execution Loop)  
**定义**：仿真必须以可组合的“纯执行入口”存在，理想形式为： `run_case(config) -> results`

**Definition**: Simulation must exist as a composable execution entry point, ideally:  `run_case(config) -> results`

> 在三梁语义分工中，`run_case` 的职责是**解释并执行策略（strategy）**，而不是重新定义物理意图（intent）或固化执行期实现（realization）。
> In the Three-Beams semantic separation, `run_case` is responsible for **interpreting and executing strategies**, not for redefining physical intent or solidifying execution-time realizations.

**必须满足 / Must have**

- **单入口、闭环**：输入仅来自 config（以及显式 workdir）；输出仅通过 results（和 export）。
- **可批量**：能够在脚本/CI/HPC 中循环调用上千次，互不污染。
- **确定性可控**：随机性必须显式（seed）；并行差异必须可记录并可解释。
- **无交互**：运行过程中不得需要人工输入，不依赖 GUI。
- **Single entry, closed loop**: inputs come only from config (and explicit workdir); outputs via results/export.
- **Batchable**: safe for thousands of runs in scripts/CI/HPC without cross-run contamination.
- **Controllable determinism**: explicit seeds; parallel variance recorded and explainable.
- **Non-interactive**: no human input, no GUI dependency.

**禁止事项（红线） / Hard red lines**

- ❌ `run_case` 内部“偷偷读其他文件/目录”作为隐含输入  
- ❌ 固定输出文件名导致并发覆盖  
- ❌ 失败只靠 stdout 日志，无法结构化判别失败类型
- ❌ hidden reads of external files/dirs as implicit inputs in `run_case`
- ❌ fixed output filenames causing collisions under concurrency
- ❌ failures only in stdout logs without structured status/reason

>-----
>#### 【以下内容为解释性注释（仅用于方便理解，不构成规范）】
> 为帮助理解 B 梁（`run_case`）的职责边界，可以采用如下类比（**仅为形象说明，不构成规范定义**）：
>
> `run_case` 可以被理解为一名乡村大厨。
>
> - 客户提出的宴请需求与预算，对应 **`config_schema` 中声明的物理意图和策略**；
> - 大厨将这些需求翻译为菜谱、采购清单与备菜方案，对应 `run_case` 将 schema 解释为一次计算所需的执行上下文；
> - 洗菜、切菜、预处理与下锅炒菜的过程，对应计算在执行过程中生成并使用的各类执行期对象与状态；
> - 最终在大厨的指导下，炒出一锅一锅的大锅菜，对应 `run_case` 返回的**结构化 `results`**。
> 
> - **大锅菜分别装盘、并端菜上席** 并不由大厨`run_case`负责，而对应由 **`export_dataset`（C 梁）** 将结果固化为可审计的数据资产（即装盘后端上桌的菜）；
> - 并且，大厨只负责 **一席菜**，即 `run_case` 的一次调用对应一个完整、原子的生命周期；
>- `run_case` 并不是“流水席”，不应在内部维持跨调用的长期状态或隐藏的执行流程。
> 
>再次提醒：该类比仅用于辅助理解三梁之间的职责分工，不应作为任何接口或实现层面的依据。

>-----
>#### 【Non-normative Note below (For Intuition Only, Not Part of the Specification)】
> To help clarify the responsibility boundary of Beam B (`run_case`), the following analogy may be used (**for illustrative purposes only and not a normative definition**):
>
> `run_case` can be understood as a village chef.
>
> - The client’s banquet requirements and budget correspond to the **physical intent and strategy declared in `config_schema`**;
> - The chef translating these requirements into recipes, shopping lists, and preparation plans corresponds to `run_case` interpreting the schema into an execution context required for a single computation;
> - Washing, cutting, preprocessing, and cooking correspond to the various execution-time objects and states that are generated and used during computation;
> - Under the chef’s guidance, cooking large dishes batch by batch corresponds to the **structured `results`** returned by `run_case`.
> 
> - **Plating the dishes and serving them to the tables** is not the responsibility of the chef `run_case`, but instead corresponds to **`export_dataset` (Beam C)**, which solidifies results into auditable data assets (i.e., dishes that have been plated and served);
> - Moreover, the chef is responsible for **one single meal**, meaning that one invocation of `run_case` corresponds to a complete and atomic lifecycle;
>- `run_case` is not a “continuous banquet service” and must not maintain long-lived state or hidden execution flows across invocations.
> 
> Reminder: this analogy is intended solely to assist in understanding the division of responsibilities among the Three Beams, and must not be used as a basis for any interface or implementation-level decisions.

---

### 2.3 C 梁：export_dataset（权威输出 + 溯源）| Beam C: export_dataset (authoritative outputs + provenance)
**定义**：输出不是“写几个 VTK 文件”。输出必须成为可审计、可比较、可积累的 dataset。

**Definition**: Output is not “just some VTK files”. It must become an auditable, comparable dataset.

> 在语义上，`export_dataset` 是 **执行期实现（realization）** 的唯一制度化出口，用于将其固化为可审计、可比较的结果，而不是反向影响配置意图。
> Semantically, `export_dataset` is the only institutionalized outlet for execution-time realizations, preserving them as auditable and comparable results without feeding back into configuration intent.

**必须满足 / Must have**

- **结构化结果**：除可视化文件外，必须有结构化 `Results`（关键标量、字段清单等）。
- **Provenance（溯源）**：输出必须绑定 `config_hash / schema_version / code_version / solver_settings / runtime_info`。
- **质量标签（Quality Gates）**：必须记录收敛性、平衡误差、能量/守恒检查等。
- **可比较**：至少提供一组标准化标量用于回归对比；逐步扩展到误差范数/场对比。
- **Structured results**: besides visualization, produce structured `Results` (key scalars, field manifest).
- **Provenance binding**: `config_hash / schema_version / code_version / solver_settings / runtime_info`.
- **Quality gates**: convergence, balance errors, energy/conservation checks, etc.
- **Comparability**: at least standardized scalars for regression; expand to norms/field comparisons over time.

**禁止事项（红线） / Hard red lines**

- ❌ 只输出图形文件而无结构化指标  
- ❌ 不记录版本与配置，使数据无法审计  
- ❌ 将未收敛结果当作“正常数据”混入资产库且不打标签
- ❌ visualization-only output without structured metrics/provenance/quality tags
- ❌ no version/config binding (non-auditable data)
- ❌ mixing unconverged results into the asset store without labels

---

## 3. 四核（Four-Cores）数值结构 | Four-Cores Numerical Structure 
四核是求解器内核的“不可变骨架”：
1) **离散对象（Discrete Objects）**  
2) **局部相互作用（Local Interactions）**  
3) **贡献汇总（Accumulation / Assembly）**  
4) **状态推进（State Advancement / Stepping）**

Four-Cores is the solver’s immutable skeleton:  
1) **Discrete Objects**  
2) **Local Interactions**  
3) **Accumulation / Assembly**  
4) **State Advancement / Stepping**

---

### 3.1 核 1：离散对象 | Core 1: Discrete Objects 
**含义**：描述“世界是什么样”的静态结构与数据布局，例如：

**Meaning**: static structures describing “what the world is”:

- mesh / dof / constraints
- neighborhood graph（PeriFEM）
- FE space / quadrature / mapping
- 边界与区域标记（作为数据结构的一部分）
- mesh / dof / constraints
- neighborhood graph (PeriFEM)
- FE space / quadrature / mapping
- boundary/region markers as data

**关键原则 | Principles：**

- **阶段内静态、阶段间可变**：在一次求解阶段（一次装配/一次 Newton 迭代）内必须冻结；允许在明确的“重建阶段”更新。
- **重建必须显式**：例如 `rebuild_discretization_if_needed()`，禁止隐式发生。
- **Static within a solve stage, mutable between stages**: frozen during assembly/Newton iteration; updated only in explicit rebuild stages.
- **Rebuild must be explicit** (e.g., `rebuild_discretization_if_needed()`).

---

### 3.2 核 2：局部相互作用 | Core 2: Local Interactions 
**含义**：给定局部状态，计算局部贡献的“物理与数学规则”：

**Meaning**: local physics/math rules computing local contributions:

- 本构（应力-应变/损伤演化的局部计算）
- 键力/通量/局部残差
- 切线/雅可比的局部贡献（隐式）
- constitutive evaluation
- bond forces/fluxes/local residuals
- local tangents/Jacobians (implicit)

**关键原则 | Principles：**

- **尽量纯函数（side-effect free）**：局部计算应避免写全局状态与历史变量。
- **局部计算只负责“算贡献”，不负责“改变世界”。**
- **Prefer side-effect free**: avoid writing global state/history.
- Local computation computes contributions, **not** “changes the world”.

---

### 3.3 核 3：贡献汇总 | Core 3: Accumulation / Assembly 
**含义**：将局部贡献通过 scatter/reduction 汇总为全局对象：

**Meaning**: scatter/reduce local contributions into global objects:

- 全局残差/内力向量
- 全局刚度/雅可比矩阵（隐式）
- 显式中的节点力汇总（即使不组装 K，也仍存在“贡献汇总”语义）
- global residual/internal force
- global stiffness/Jacobian (implicit)
- explicit force accumulation (even without assembling K)

**关键原则 | Principles：**

- **装配阶段必须无副作用**：不得更新损伤/断裂等历史变量，不得改变离散对象拓扑。
- **遍历顺序不应影响物理结果**：避免顺序依赖与并行非确定性。
- **Assembly must be side-effect free**: no history updates, no topology changes.
- **Traversal order must not define physics**: avoid order dependence and unexplained non-determinism.

---

### 3.4 核 4：状态推进 | Core 4: State Advancement / Stepping 
**含义**：推进主状态（u, v, a, …）及其收敛控制：

**Meaning**: advance primary states and control convergence:

- 显式时间积分
- 隐式 Newton 迭代与线性求解
- 步进控制、收敛判据
- explicit integration
- implicit Newton + linear solve
- step control and stopping criteria

**关键原则 | Principles：**

- **推进控制权统一**：推进策略是“控制器”，调用装配/求解，不允许装配阶段自行推进状态。
- **Trial/Commit 语义清晰**：历史变量与模型演化必须区分试算与提交。
- **Unified control**: stepping strategy orchestrates assembly/solve; assembly must not advance states.
- **Clear trial/commit semantics** for history variables and model evolution.

---

## 4. 两个时间尺度与更新规则 | Two Time Scales and Update Rules
PeriSci 必须区分两个时间尺度：

1) **数值求解时间尺度（Solver Time Scale）**：一次装配、一次 Newton 迭代、一次时间步  
2) **模型演化时间尺度（Model Evolution Scale）**：损伤/断裂、网格/DoF 重构、耦合区更新

PeriSci must distinguish:

1) **Solver time scale**: assembly, Newton iteration, time step  
2) **Model evolution scale**: damage/fracture, mesh/DoF rebuild, coupling region updates

**更新规则 | Update Rules：**

- 在 solver time scale 内，离散对象冻结，装配无副作用。
- 模型演化只能发生在明确阶段边界（例如一次收敛后），形成：
  - `solve -> evolve_model -> solve -> ...` 的外层一致性循环

- Within solver time scale: discrete objects frozen; assembly side-effect free.
- Model evolution happens only at explicit stage boundaries, enabling:
  - `solve -> evolve_model -> solve -> ...` outer consistency loops.

> 这些时间尺度规则的核心目的，是约束 执行期实现（realization） 的生成与演化边界，避免其在不受控阶段影响物理意图或数值语义。
> The core purpose of these time-scale rules is to constrain when execution-time realizations may be generated or evolved, preventing them from affecting physical intent or numerical semantics outside controlled stages.

---

## 5. 算例资产（Case Assets）机制 | Case Assets Mechanism

### 5.1 定义 | Definition

**算例资产不是“输入文件集合”。**  
算例资产是“可执行知识”：

> 问题描述（config） + 被反复验证的运行路径（run_case）  
>
> + 可对比的结果族（datasets） + 可信溯源与失败信息（provenance & failure modes）

**Case assets are not input files.**  
They are executable knowledge:

> config + validated execution path + comparable result family + provenance & failure modes

### 5.2 早期策略（v0.2/v0.3）| Early strategy (v0.2/v0.3)

- **少而硬**：优先 5–10 个“高密度”算例，而非大量松散样例。
- 每个核心算例至少具备：
  - 可复现运行
  - 标准化指标输出
  - 至少一条回归基准
  - 至少一种失败模式被记录（失败也是资产）

- **Small but hard**: prioritize 5–10 high-density cases, not many loose examples.
- Each core case should have:
  - reproducible run
  - standardized metrics
  - at least one regression baseline
  - at least one recorded failure mode (failures are assets)

### 5.3 算例资产对三梁/四核的反向约束 | How case assets constrain Three-Beams/Four-Cores

- 任意内核修改都必须通过资产库回归（regression）
- 任意新增功能必须伴随：
  - 新算例或旧算例的扩展
  - 明确的质量门禁指标
  - 可比较的对照（至少标量）

- Any core change must pass the regression suite.
- Any new feature must come with:
  - a new case or an extension of an existing one
  - explicit quality metrics
  - comparable outputs (at least scalars)

---

## 6. “禁止事项（Hard Red Lines）”总表 | Hard Red Lines Summary 

以下行为在 PeriSci 中视为架构违规，除非有明确 ADR 记录：

1) **在装配循环中更新历史变量**（damage/plastic strain/crack state 等）  
2) **在装配循环中重构离散对象**（mesh/DoF/neighborhood/constraints）  
3) **绕过 config_schema** 引入隐含输入（文件、环境变量、GUI 状态）  
4) **只输出可视化文件**，不输出结构化 results/provenance/quality  
5) **让遍历顺序决定结果**（顺序依赖、并行非确定性不可解释）  
6) **silent drift**：配置语义变更但旧配置仍能跑、结果悄悄变

Unless explicitly recorded via ADR, the following are violations:

1) Updating history variables inside assembly loops (damage/plastic strain/crack state, etc.)
2) Rebuilding discretization inside assembly loops (mesh/DoF/neighborhood/constraints)
3) Bypassing config_schema via hidden inputs (files/env/GUI state)
4) Visualization-only outputs without structured results/provenance/quality tags
5) Order-dependent results (unexplained non-determinism)
6) Silent drift: semantics change without versioning and failure

---

## 7. PR / Code Review 检查清单（最小版）| PR / Code Review Checklist (Minimal)

每个 PR 至少回答以下问题（建议写入 PR 模板）：

Each PR should at least answer the following questions (suggested to be included in the PR template):

### 7.1 三梁检查 | Three-Beams

- [ ] A：是否新增/修改了 config 字段？是否更新 schema_version？是否有校验与默认值？
- [ ] B：是否保持 `run_case` 纯执行契约？是否引入隐含输入/输出？
- [ ] C：是否输出或更新了结构化指标、provenance 与质量标签？
- [ ] A:  any config change? schema_version updated? validation/defaults updated?
- [ ] B:  run_case contract preserved? any hidden I/O introduced?
- [ ] C:  structured metrics/provenance/quality tags updated as needed?

### 7.2 四核检查 | Four-Cores

- [ ] 是否明确指出本次改动主要影响哪一核（离散/局部/汇总/推进）？
- [ ] 是否把“状态更新”误写进装配？
- [ ] 是否把“离散对象重构”误写进求解阶段？
- [ ] Which core does this change primarily affect?
- [ ] Any history/state update moved into assembly accidentally?
- [ ] Any discretization rebuild introduced inside solve stage?

### 7.3 算例资产检查 | Case Assets

- [ ] 是否新增/更新了算例或回归基准？
- [ ] 是否新增了可比较的指标（至少标量）？
- [ ] 是否记录失败模式或边界条件？
- [ ] new/updated case or baseline?
- [ ] comparable metrics added (at least scalars)?
- [ ] failure modes or boundary conditions recorded?

---

## 8. 最小接口建议（非强制，但推荐）| Suggested Minimal Interfaces (Recommended)

为保持三梁可落地，推荐以下最小接口形态：

- `Config load_config(path) -> Config`
- `void validate_config(const Config&)`
- `Results run_case(const Config&, const RunContext&)`
- `Dataset export_dataset(const Config&, const Results&, const ExportContext&)`
- `Comparison compare(const Dataset&, const Dataset&)`（可逐步实现）

To ensure that the three beams can be lowered, the following minimum interface configuration is recommended:

- `Config load_config(path) -> Config`
- `void validate_config(const Config&)`
- `Results run_case(const Config&, const RunContext&)`
- `Dataset export_dataset(const Config&, const Results&, const ExportContext&)`
- `Comparison compare(const Dataset&, const Dataset&)`

---

## 9. 术语表 | Glossary

- **三梁（Three-Beams）**：A config_schema / B run_case / C export_dataset  
- **四核（Four-Cores）**：离散对象 / 局部相互作用 / 贡献汇总 / 状态推进  
- **算例资产（Case Assets）**：可执行、可复现、可比较、可溯源、可积累的算例体系  
- **Provenance**：溯源信息（版本、配置哈希、求解设置、运行环境等）  
- **Quality Gates**：质量门禁（收敛、平衡、能量等自动检查）  
- **silent drift**：语义漂移但系统不报错、结果悄然改变
- **Three-Beams**: A config_schema / B run_case / C export_dataset  
- **Four-Cores**: Discrete Objects / Local Interactions / Accumulation / State Advancement  
- **Case Assets**: reproducible, comparable, provenance-aware, accumulative executable cases  
- **Provenance**: config/code/solver/runtime traceability  
- **Quality Gates**: automated checks (convergence, balance, energy, etc.)  
- **Silent drift**: semantics change without explicit versioning, causing silent behavior changes

