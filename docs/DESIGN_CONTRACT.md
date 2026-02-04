# 设计契约 | DESIGN_CONTRACT

> 本文档是 PeriSci 的“设计契约”（Design Contract）。  
> 它不是介绍性文档，而是**不可随意违反的工程宪法**：用于约束架构演进、代码评审与功能扩展。  
> 任何偏离本文档的实现，都应被视为**需要明确记录的设计决策（ADR：用于记录对设计契约的显式偏离或例外决策）**，而不是“顺手改改”。

> This document is the PeriSci **Design Contract**.  
> It is not an introduction; it is the **constitutional constraint** governing architecture evolution, code review, and feature growth.  
> Any deviation must be recorded explicitly as an **Architecture Decision Record (ADR is used to document explicit deviations from, or exceptions to, the Design Contract)**, not as an ad-hoc change.

---

## 0. 范围与目标 | Scope and Goals 
### 0.1 本契约约束什么 | What this contract constrains
- PeriSci 的系统架构必须遵循 **“三梁（Three-Beams）”**结构。  
- PeriSci 的数值内核必须遵循 **“四核（Four-Cores）”**结构。  
- PeriSci 的演进必须以 **“算例资产（Case Assets）”** 的累积作为核心工程机制。

- PeriSci’s system architecture **must** follow the **Three-Beams** structure.  
- PeriSci’s numerical core **must** follow the **Four-Cores** structure.  
- PeriSci’s evolution **must** accumulate **Case Assets** from day one as a core engineering mechanism.

------

### 0.2 本契约不讨论什么 | What this contract does not cover
- 不讨论具体物理模型（弹性、塑性、损伤、断裂等）的公式细节。  
- 不讨论外部库（deal.II / PETSc 等）的使用教程。  
- 不为短期 Demo 牺牲长期治理能力：**“能跑”不是“可存活”。**

- This document does not define specific constitutive models (elasticity, plasticity, damage, fracture, etc.).  
- It is not a usage tutorial for external libraries (deal.II / PETSc / …).  
- Long-term governance is not sacrificed for short-term demos: **“runs once” is not “survivable”.**

------

### 0.3 全局治理原则 | Global Governance Principles
#### 0.3.1 冻结、最小保证与演进预留的关系 | The Relationship Between Freeze, Minimum Guarantee, and Evolution Reserve

在 PeriSci 的契约与架构治理中，“冻结”“最小保证”“演进预留”并非相互排斥的三种状态，而是对同一规则在不同治理维度上的强调。

- **冻结（Freeze）**约束的是规则的变更方式：被冻结的契约在当前版本生命周期内不得因短期功能需求或实现便利性而被破坏；任何修改都必须通过显式的版本升级或 ADR 等可审计的治理路径完成。冻结并不意味着规则永不演进，而是禁止隐式、临时或无记录的破坏性变更。
  
- **最小保证（Minimum Guarantee）**约束的是当前阶段所承诺的行为下限：在给定版本阶段（例如 v0.2.x），规范中明确声明的“最小保证”表示系统在最保守条件下至少应满足的确定性、可复现性、完整性或副作用约束；最小保证是阶段性的强度承诺，而非对最终能力上限的限定。
  
- **演进预留（Evolution Reserve）**约束的是未来升级的合法路径：规范中对阶段性表述、可选增强或未来可能加强之处的明确标注，用于为后续版本提高标准、细化语义或引入新模式预留空间；任何此类演进必须通过版本升级或 ADR 显式声明，而不得在当前冻结版本中隐式发生。

上述三者可同时适用于同一条规则：  冻结保证规则在当前版本内的稳定性，  最小保证明确当前阶段对外承诺的行为下限，  演进预留确保未来升级具有清晰、可审计且不破坏信任的路径。

In PeriSci’s contract and architectural governance, “Freeze,” “Minimum Guarantee,” and “Evolution Reserve” are not mutually exclusive states, but rather different emphases on the same rule across distinct governance dimensions.

- **Freeze** constrains *how* a rule may be changed:  A frozen contract must not be violated within the current version lifecycle for short-term functional demands or implementation convenience.  Any modification must be carried out through explicit, auditable governance paths such as version upgrades or ADRs.  Freeze does not imply that a rule can never evolve; rather, it prohibits implicit, ad hoc, or unrecorded breaking changes.
  
- **Minimum Guarantee** constrains the *behavioral lower bound* promised at the current stage:  For a given version stage (e.g., v0.2.x), the “minimum guarantee” explicitly stated in the specification defines the least level of determinism, reproducibility, integrity, or side-effect constraints that the system must satisfy under conservative assumptions.  A minimum guarantee is a stage-specific commitment of strength, not a limitation on the system’s ultimate capabilities.
  
- **Evolution Reserve** constrains the *legitimate path of future upgrades*:  Explicit markings of stage-specific wording, optional enhancements, or areas expected to be strengthened in future versions are intended to reserve space for raising standards, refining semantics, or introducing new modes in later releases.  Any such evolution must be explicitly declared through version upgrades or ADRs, and must not occur implicitly within the current frozen version.

These three aspects may simultaneously apply to the same rule:  Freeze ensures the rule’s stability within the current version,  Minimum Guarantee defines the behavioral lower bound promised at the present stage,  and Evolution Reserve ensures that future upgrades proceed through clear, auditable, and trust-preserving paths.

------

#### 0.3.2 规范表示规则 | Canonical Representation Rule

#### **0.3.2.1 定义 | Definitions**

**规范化表示（Canonical Representation）**是指在不改变语义的前提下，将结构化对象归一化为唯一、稳定的表示形式，用于治理、语义差异比较、哈希、溯源与冻结判定。其中，**语义差异比较（semantic diff 后续简记为 diff）**指在规范化表示基础上，对对象语义是否发生变化的比较，而非文本或格式差异。**溯源（Provenance）**用于描述算例或数据集生成的因果关系，包括配置、代码、执行路径与运行状态。

**Canonical Representation** refers to the process of normalizing structured objects into a unique and stable representation **without altering their semantics**, for the purpose of governance, **semantic diff** (hereafter referred to as diff), hashing, provenance, and freeze determination. Among these, **semantic diff** refers to the comparison of whether an object’s semantics have changed based on its canonical representation, rather than textual or formatting differences. **Provenance** is used to describe the causal relationships involved in the generation of a case or dataset, including configuration, code, execution paths, and runtime states.

------

#### **0.3.2.2 正向适用规则 | Applicability Rule**

本系统中所有参与**治理、契约、溯源与冻结判定体系**的结构化对象，必须具有**唯一的规范化表示**。
All structured objects that participate in the system’s **governance, contract, provenance, and freeze-determination framework** **MUST** have a **unique canonical representation**.

在 v0.2.x 阶段，该规范化表示**统一采用 JSON 作为唯一权威形式（canonical JSON）**。
During the v0.2.x phase, this canonical representation **uniformly adopts JSON as the sole authoritative form (canonical JSON)**.

canonical JSON 作为规范化表示，适用于但不限于：

- **A 梁**：`config_schema` 及其参与校验、语义差异比较、`config_hash` 计算的配置对象
  （其中，`config_hash` 是基于 canonical 配置对象计算的稳定标识，用于复现、缓存与治理判定）
- **B 梁**：任何作为接口契约或稳定输入输出的结构化定义（如适用）
- **C 梁**：数据集的 `manifest`（作为权威元数据入口，用于承载身份、结构、溯源与版本信息）、溯源与版本元数据

As a canonical representation, canonical JSON applies to, but is not limited to, the following:

- **Beam A**: `config_schema` and configuration objects that participate in validation, semantic diff, and `config_hash` computation
   (where `config_hash` is a stable identifier computed from canonical configuration objects, used for reproduction, caching, and governance determination)
- **Beam B**: any structured definitions that serve as interface contracts or stable inputs/outputs (where applicable)
- **Beam C**: a dataset’s `manifest` (serving as the authoritative metadata entry, carrying identity, structure, provenance, and version information), provenance, and version metadata

------

#### **0.3.2.3 输入格式与规范化转换 | Input Normalization**

未来版本中如支持 YAML 等人类友好格式，其地位仅限于**人工编写层**；任何此类输入 **必须在进入校验、哈希、溯源、版本与冻结判定之前，被确定性地转换为等价的 canonical JSON**。

In future versions, if human-friendly formats such as YAML are supported, their role SHALL be limited to the **human authoring layer**; any such inputs **MUST be deterministically transformed into equivalent canonical JSON before entering validation, hashing, provenance, version, and freeze determination processes**.

------

#### **0.3.2.4 规范表示红线 | Canonical Red Line**

**canonical JSON 是唯一参与语义差异比较、哈希、溯源绑定、版本判定与破坏性变更治理的权威形式，也是规范化表示的唯一具体格式。**

**规范化表示的强制适用对象，仅限于参与治理、契约、溯源与冻结判定的元数据与契约性对象**，包括但不限于：`config_schema`、配置对象、数据集的 `manifest`、溯源与版本元数据。

**执行期产生的数值结果或数据内容本体（例如数据集的 `results`）不得被要求或假定为 canonical JSON 表示**；其治理仅允许通过被 canonical 的元数据进行描述、索引与引用。

**Canonical JSON is the sole authoritative form that participates in semantic diff, hashing, provenance binding, version determination, and breaking-change governance, and is the only concrete format of canonical representation.**

The **mandatory applicability of canonical representation is strictly limited to metadata and contractual objects** that participate in governance, contracts, provenance, and freeze determination, including but not limited to: `config_schema`, configuration objects, a dataset’s `manifest`, provenance, and version metadata.

**Numerical results or data content bodies generated during execution (e.g., a dataset’s `results`) MUST NOT be required or assumed to have canonical JSON representations**; their governance is permitted **only** through description, indexing, and referencing via canonical metadata.

------

#### 0.3.3 代码治理 | Code Governance

**代码治理**：所有进入治理、契约、溯源与冻结判定体系的算例资产，**必须能够唯一且不可歧义地定位其生成所依赖的计算代码**。代码本体**不要求也不应被规范化为 canonical JSON 表示**；其治理应通过**被 canonical 的元数据与不可变引用**实现。

**Code Governance**: All case assets that enter the governance, contract, provenance, and freeze-determination framework **MUST be able to uniquely and unambiguously identify the computation code on which their generation depends**.
 The code body itself **MUST NOT be required nor assumed to be represented in canonical JSON**; code governance SHALL be achieved through **canonical metadata and immutable references**.

在 v0.2.x 阶段，代码治理的**最小强制保证**为：

- 必须记录可唯一定位代码状态的 **`code_version`**（例如提交哈希、不可变标签或等价标识；说明：code_version 用于唯一定位生成算例所依赖的代码状态，是代码治理与溯源的核心锚点）；
- 必须显式声明该代码状态是否存在未提交修改（例如 `dirty: true/false`）；
- 代码相关元数据必须以 canonical JSON 表示，并参与 溯源 绑定、版本判定与冻结治理。

**可选增强（演进预留）**：

- 可记录 `code_hash`（对关键代码范围或快照内容计算的稳定哈希）；
- 可采用代码快照模式，将只读代码副本作为 数据集 的一部分进行归档；
- 任一上述增强均不得削弱以元数据引用为核心的治理语义。

**治理红线**：

- ❌ 不得以“当前工作区”“本地未记录代码状态”等不可追溯方式生成算例资产；
- ❌ 不得要求或假定执行期计算代码本体具有 canonical JSON 表示；
- ❌ 不得在缺失代码版本信息的情况下将结果视为可冻结、可复用的算例资产。

During the v0.2.x phase, the **minimum mandatory guarantees** for code governance are:

- A **`code_version`** that uniquely identifies the code state MUST be recorded (e.g., commit hash, immutable tag, or equivalent identifier；Note: `code_version` is used to uniquely identify the code state on which a case depends for its generation, and serves as a core anchor for code governance and provenance);
- The presence or absence of uncommitted modifications in the working directory MUST be explicitly declared (e.g., `dirty: true/false`);
- Code-related metadata MUST be represented in canonical JSON and SHALL participate in provenance binding, version determination, and freeze governance.

**Optional Enhancements (Evolution Reserved):**

- A `code_hash` MAY be recorded (a stable hash computed over critical code ranges or snapshot contents);
- A code snapshot mode MAY be adopted, archiving a read-only copy of the code as part of the dataset;
- None of the above enhancements SHALL weaken the governance semantics centered on metadata-based referencing.

**Governance Red Lines:**

- ❌ Case assets MUST NOT be generated using non-traceable means such as “current working directory” or “locally modified but unrecorded code states”;
- ❌ Execution-time computation code bodies MUST NOT be required nor assumed to have canonical JSON representations;
- ❌ Results MUST NOT be treated as freezable or reusable case assets in the absence of code version information.

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

------

### 2.1 A 梁：config_schema（权威输入契约）| Beam A: config_schema (Authoritative Input Contract) 
**定义**：所有仿真任务必须由一个“权威配置对象（Authoritative Config）”定义，并可被机器校验。

**Definition**: Every simulation is defined by an authoritative, machine-validated config.

**必须满足 / Must have**
- **Schema 校验**：类型、范围、枚举、必填项必须可验证；非法配置必须 fail-fast。
- **语义稳定**：字段的物理含义必须稳定；任何变更必须通过版本号管理。
- **可版本化**：必须有 `schema_version`，并有明确的兼容/拒绝策略。
- **可 diff / 可 哈希**：配置必须可被规范化序列化并生成 `config_hash`，用于复现与缓存键。
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

------

### 2.2 B 梁：run_case（纯执行闭环）| Beam B: run_case (Pure Execution Loop)  
**定义**：仿真必须以可组合的“纯执行入口”存在，理想形式为： `run_case(config) -> results`

**Definition**: Simulation must exist as a composable execution entry point, ideally:  `run_case(config) -> results`

> 在三梁语义分工中，`run_case` 的职责是**解释并执行策略（strategy）**，而不是重新定义物理意图（intent）或固化执行期实现（realization）。
> In the Three-Beams semantic separation, `run_case` is responsible for **interpreting and executing strategies**, not for redefining physical intent or solidifying execution-time realizations.

**必须满足 / Must have**

- **单入口、闭环**：输入仅来自 config（以及显式 workdir）；输出仅通过 结果（和 export）。
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

>------
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

>------
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

------

### 2.3 C 梁：export_dataset（权威输出 + 溯源）| Beam C: export_dataset (authoritative outputs + provenance)
**定义**：输出不是“写几个 VTK 文件”。输出必须成为可审计、可比较、可积累的 数据集。

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

- ❌ 只输出图形文件而无结构化指标/溯源/质量标签  
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

------

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

------

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

------

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

------

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

## 5. 算例资产机制 | Case Assets Mechanism

### 5.1 定义 | Definition

**算例资产**是指满足本设计契约中治理、溯源、比较与冻结要求的最小可治理计算单元。**算例资产不是“输入文件集合”。**  

A Case Asset is defined as the minimal governable computational unit that satisfies the governance, provenance, comparability, and freeze requirements specified in this Design Contract. **Case assets are not input files.** 

算例资产是“可执行知识”：

> 问题描述（config） + 被反复验证的运行路径（run_case）  
>
> + 可对比的结果族（数据集） + 可信溯源与失败信息（溯源 & 失败模式）


They are executable knowledge:

> config + validated execution path + comparable result family + provenance & failure modes

------

### **5.2 算例资产的最小可治理构成 | Minimal Governed Composition of a Case Asset**

**算例资产不是“一次能跑通的计算结果”，而是一个在脱离运行环境后，仍然能够被唯一识别、比较、审计、复现并冻结治理的可执行资产。**
一个算例之所以能够被视为 **算例资产**，必须至少具备一组**治理层锚点对象**，使其在系统演进与回归中具备稳定身份与可比较语义。

A **case asset is not merely a computation that can run successfully**, but an executable asset that, after detachment from its runtime environment, can still be uniquely identified, compared, audited, reproduced, and governed through freeze mechanisms.
For a computation to be regarded as a **Case Asset**, it MUST possess at least a set of **governance-layer anchor objects**, ensuring stable identity and comparable semantics throughout system evolution and regression.

在 PeriSci 中，算例资产的**最小可治理构成**包括但不限于：

- **A 梁（Intent / Strategy 锚点）**：
  - `config_schema`（权威输入契约）；
  - 经 schema 校验并参与语义 语义差异比较 与 `config_hash` 计算的配置对象；
- **B 梁（Execution 锚点）**：
  - 受控、可重复调用的执行入口（`run_case`）；
  - 明确的执行策略解释路径，不引入隐含输入；
- **C 梁（Result / Asset 锚点）**：
  - `dataset_spec`（输出结构与语义契约）；
  - `manifest`（权威元数据入口），包含 溯源、版本元数据与结构化结果索引；
  - 对于 C 梁算例资产，凡是涉及输出结构、manifest 语义、溯源绑定或 canonical 治理规则的任何破坏性变更，必须通过提升 `dataset_version` 的主版本号（Major）来体现，其定义以 `dataset-spec` 为准。
  - 对于 C 梁算例资产，凡涉及破坏性变更的版本处理规则，**必须遵循 `dataset-spec` 中定义的 Versioning Red Line（C 梁）**
- **代码治理锚点（Code Governance）**：
  - 可唯一定位生成逻辑的代码标识（如 `code_version`，必要时附加 `dirty` / `code_hash`）；
  - 代码通过被 canonical 的元数据参与溯源、语义差异比较 与冻结治理，而非作为 canonical JSON 本体；
- **质量与可比较性锚点（Quality & Comparability）**：
  - 至少一组标准化质量门禁（如收敛性、平衡误差、能量/守恒检查；说明：质量门禁（Quality Gates）是用于判定算例结果是否满足最低可信与可比较要求的自动化检查机制）；
  - 至少一组可用于回归与对比的标准化指标（最小可为标量）；
- **失败与部分完成状态记录（Failure Modes）**：
  - 失败 / 部分完成 运行必须被结构化记录（**失败**表示执行失败且未产生可用结果；**部分完成**表示算例执行部分成功但未完全满足契约）；
  - 失败本身被视为资产的一部分，而非应被丢弃的噪声。

仅当上述治理层锚点齐备时，一个算例才允许被纳入算例资产体系，并参与系统的复用、比较、回归与长期演进冻结。

In PeriSci, the **minimal governed composition** of a Case Asset includes, but is not limited to:

- **Beam A (Intent / Strategy Anchors)**:
  - `config_schema` (authoritative input contract);
  - Configuration objects that pass schema validation and participate in **semantic diff** and `config_hash` computation;
- **Beam B (Execution Anchors)**:
  - A controlled, repeatable execution entrypoint (e.g., `run_case`);
  - Explicit, interpretable execution strategy paths with no hidden inputs;
- **Beam C (Result / Asset Anchors)**:
  - `dataset_spec` (output structure and semantic contract);
  - `manifest` (authoritative metadata entry), containing provenance, version metadata, and structured result indexing;
  - For Beam C assets, any breaking change in output structure, manifest semantics, provenance binding, or canonical governance rules MUST be reflected by a major bump of dataset_version, as defined in dataset-spec；
  - For Beam C case assets, version handling for breaking changes **MUST follow the Versioning Red Line (Beam C) defined in the dataset-spec**；
- **Code Governance Anchors**:
  - Code identifiers capable of uniquely locating the generating logic (e.g., `code_version`, optionally augmented with `dirty` / `code_hash`);
  - Code participating in provenance binding, **semantic diff**, and freeze governance through canonical metadata rather than as canonical JSON bodies;
- **Quality & Comparability Anchors**:
  - At least one set of standardized quality gates (e.g., convergence, balance error, energy/conservation checks; Note: Quality Gates are automated validation mechanisms used to determine whether case results meet the minimum requirements for trustworthiness and comparability);
  - At least one set of standardized metrics suitable for regression and cross-case comparison (minimally scalar);
- **Failure Modes**:
  - `failed` / `partial` executions MUST be structurally recorded ( `failed` indicates that the execution has failed and produced no usable results; `partial` indicates that a case execution has partially succeeded but does not fully satisfy the contract);
  - Failures themselves are treated as part of the asset, not as discardable noise.

Only when the above governance-layer anchors are complete MAY a computation be admitted into the Case Assets system and participate in reuse, comparison, regression, and long-term evolutionary freeze governance.

------

### 5.3 早期策略（v0.2/v0.3）| Early strategy (v0.2/v0.3)

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

------

### 5.4 算例资产对三梁/四核的反向约束 | How case assets constrain Three-Beams/Four-Cores

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

本节的红线内容包含并补充了上述**规范表示红线**与**代码治理红线**。
The red lines in this section incorporate and supplement the aforementioned **Canonical Red Line** and **Code Governance Red Line**.

以下行为在 PeriSci 中视为架构违规，除非有明确 ADR 记录：

1) **在装配循环中更新历史变量**（damage/plastic strain/crack state 等）  
2) **在装配循环中重构离散对象**（mesh/DoF/neighborhood/constraints）  
3) **绕过 config_schema** 引入隐含输入（文件、环境变量、GUI 状态）  
4) **只输出可视化文件**，不输出结构化 结果/溯源/质量标签  
5) **让遍历顺序决定结果**（顺序依赖、并行非确定性不可解释）  
6) **silent drift**（表示配置或语义发生变化但未被显式识别与治理，导致结果悄然改变的风险）

Unless explicitly recorded via ADR, the following are violations:

1) Updating history variables inside assembly loops (damage/plastic strain/crack state, etc.)
2) Rebuilding discretization inside assembly loops (mesh/DoF/neighborhood/constraints)
3) Bypassing config_schema via hidden inputs (files/env/GUI state)
4) Visualization-only outputs without structured results/provenance/quality tags
5) Order-dependent results (unexplained non-determinism)
6) Silent drift (refers to the risk that configuration or semantic changes occur without being explicitly identified or governed, resulting in unintended and unnoticed changes in outcomes)

---

## 7. PR / Code Review 检查清单（最小版）| PR / Code Review Checklist (Minimal)

每个 PR 至少回答以下问题（建议写入 PR 模板）：

Each PR should at least answer the following questions (suggested to be included in the PR template):

### 7.1 三梁检查 | Three-Beams

- [ ] A：是否新增/修改了 config 字段？是否更新 schema_version？是否有校验与默认值？
- [ ] B：是否保持 `run_case` 纯执行契约？是否引入隐含输入/输出？
- [ ] C：是否输出或更新了结构化指标、溯源 与质量标签？
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

> 本检查清单用于评估一个 PR / 变更是否引入、修改或影响 **算例资产**，以及该算例是否满足《5.2 算例资产的最小可治理构成》所定义的治理要求。
>  **凡涉及 算例资产 的 PR，必须逐条通过以下检查项；未通过者不得合并。**

> This checklist is used to evaluate whether a PR or change introduces, modifies, or affects a **Case Asset**, and whether that case satisfies the governance requirements defined in *5.2 Minimal Governed Composition of a Case Asset*.
> **Any PR involving Case Assets MUST pass all checks below; failure to do so SHALL block merging.**

------

#### 7.3.1 A 梁：意图与输入治理（对应 5.2 · A 梁）| Beam A: Intent & Input Governance (corresponding to 5.2 · Beam A)

- [ ] 存在明确的 `config_schema`，且 schema 本身未被隐式绕过或弱化（对应 5.2 · A 梁 · `config_schema`）
- [ ] 所有新增或修改的配置对象均通过 schema 校验（对应 5.2 · A 梁 · 配置对象）
- [ ] 配置变更可通过语义 差异比较 明确解释（非文本 差异比较）（对应 5.2 · A 梁 · 语义 差异比较）
- [ ] 配置对象参与稳定的 `config_hash` 计算，且 哈希 变化与语义变化一致（对应 5.2 · A 梁 · `config_hash`）

- [ ] A clear `config_schema` exists, and the schema itself is not implicitly bypassed or weakened (5.2 · Beam A · `config_schema`)
- [ ] All newly added or modified configuration objects pass schema validation (5.2 · Beam A · configuration objects)
- [ ] Configuration changes can be explicitly explained via **semantic diff** (not text diff) (5.2 · Beam A · semantic diff)
- [ ] Configuration objects participate in stable `config_hash` computation, and hash changes align with semantic changes (5.2 · Beam A · `config_hash`)

------

#### 7.3.2 B 梁：执行路径与接口稳定性（对应 5.2 · B 梁）| Beam B: Execution Path & Interface Stability (corresponding to 5.2 · Beam B)

- [ ] 执行入口（如 `run_case`）明确、可重复调用，不依赖隐含输入或运行时侧信道（对应 5.2 · B 梁 · 执行入口）
- [ ] 执行逻辑变更未破坏接口契约，或已明确声明为破坏性变更（对应 5.2 · B 梁 · 执行策略约束）
- [ ] PR 不引入不可解释的隐式执行分支（如环境依赖、隐藏默认值）（对应 5.2 · B 梁 · 可解释执行路径）

- [ ] Execution entrypoints (e.g., `run_case`) are explicit, repeatable, and free from hidden inputs or runtime side channels (5.2 · Beam B · execution entrypoint)
- [ ] Execution logic changes do not violate interface contracts, or are explicitly declared as breaking changes (5.2 · Beam B · execution strategy constraints)
- [ ] The PR does not introduce unexplained implicit execution branches (e.g., environment dependence, hidden defaults) (5.2 · Beam B · interpretable execution paths)

------

#### 7.3.3 C 梁：结果资产与输出治理（对应 5.2 · C 梁）| Beam C: Result Assets & Output Governance (corresponding to 5.2 · Beam C)

- [ ] 存在或更新了 `dataset_spec`，且输出结构与语义未脱离契约约束（对应 5.2 · C 梁 · `dataset_spec`）
- [ ] `manifest` 作为权威元数据入口被正确生成或更新（对应 5.2 · C 梁 · `manifest`）
- [ ] manifest 中包含完整的 溯源、版本元数据与结构化结果索引（对应 5.2 · C 梁 · 溯源 / 版本元数据）
- [ ] 结果内容（`results`）未被错误地当作治理层对象或要求 canonical JSON 表示（对应 5.2 · C 梁 + 规范化表示红线（参见0.3.2节））

- [ ] `dataset_spec` exists or has been updated, and output structure and semantics remain within contractual constraints (5.2 · Beam C · `dataset_spec`)
- [ ] `manifest` is correctly generated or updated as the authoritative metadata entry (5.2 · Beam C · `manifest`)
- [ ] The manifest contains complete provenance, version metadata, and structured result indexing (5.2 · Beam C · provenance / version metadata)
- [ ] Result contents (`results`) are not erroneously treated as governance-layer objects nor required to have canonical JSON representations
  (5.2 · Beam C + **Canonical Red Line**, see Section 0.3.2)

------

#### 7.3.4 代码治理与可回溯性（对应 5.2 · 代码治理）| Code Governance & Traceability (corresponding to 5.2 · Code Governance)

- [ ] manifest / 溯源 中记录了可唯一定位代码状态的 `code_version`（对应 5.2 · 代码治理锚点）
- [ ] 明确声明生成算例时代码是否存在未提交修改（`dirty` 状态）（对应 5.2 · 代码治理锚点）
- [ ] 代码未被错误地视为 canonical JSON 对象，其治理通过元数据引用完成（对应 5.2 · 代码治理锚点 + 代码治理红线（参见0.3.2节））

- [ ] `code_version` uniquely identifying the code state is recorded in the manifest / provenance (5.2 · Code Governance Anchors)
- [ ] The presence or absence of uncommitted code modifications (`dirty` state) is explicitly declared (5.2 · Code Governance Anchors)
- [ ] Code is not erroneously treated as a canonical JSON object; its governance is achieved through metadata-based referencing
  (5.2 · Code Governance Anchors + **Code Governance Red Line**, see Section 0.3.2)

------

#### 7.3.5 质量门禁与可比较性（对应 5.2 · 质量与可比较性）| Quality Gates & Comparability (corresponding to 5.2 · Quality & Comparability)

- [ ] 至少定义并执行了一组质量门禁（如收敛性、平衡/守恒检查）（对应 5.2 · 质量锚点）
- [ ] 存在至少一组标准化指标，可用于跨算例对比或回归分析（对应 5.2 · 可比较性锚点）
- [ ] 指标语义稳定，且未被“只在 README 中描述而未结构化记录”（对应 5.2 · 可比较性锚点）

- [ ] At least one set of quality gates (e.g., convergence, balance/conservation checks) is defined and executed (5.2 · Quality Anchors)
- [ ] At least one set of standardized metrics exists for cross-case comparison or regression analysis (5.2 · Comparability Anchors)
- [ ] Metric semantics are stable and not merely described in README without structured recording (5.2 · Comparability Anchors)

------

#### 7.3.6 失败与部分完成算例处理（对应 5.2 · 失败模式）| Failure & Partial Case Handling (corresponding to 5.2 · Failure Modes)

- [ ] 失败/ 部分完成 运行被显式记录，而非静默丢弃（对应 5.2 · 失败模式）
- [ ] 失败状态包含可用于回溯的最小 溯源 信息（对应 5.2 · 失败模式）
- [ ] 失败算例未被错误地排除在 算例资产 治理体系之外（对应 5.2 · 失败模式）

- [ ] `failed` / `partial` executions are explicitly recorded rather than silently discarded (5.2 · Failure Modes)
- [ ] Failure states contain minimal provenance information sufficient for traceability (5.2 · Failure Modes)
- [ ] Failed cases are not erroneously excluded from the Case Assets governance system (5.2 · Failure Modes)

------

#### 7.3.7 审查结论（必填）| Review Conclusion (Required)

- [ ] 该 PR 引入或修改的算例满足 5.2节 定义的 算例资产 最小可治理构成
- [ ] 若不满足，已明确标注为“非 算例资产 / 实验性变更”，不进入资产库

- [ ] The PR introduces or modifies cases that satisfy the **minimal governed composition of a Case Asset** defined in Section 5.2
- [ ] If not satisfied, the change is explicitly labeled as “non–Case Asset / experimental” and excluded from the asset registry

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

- **三梁（Three-Beams）**：A 梁 `config_schema` / B 梁 `run_case` / C 梁 `export_dataset`
  **Three-Beams**: Beam A `config_schema` / Beam B `run_case` / Beam C `export_dataset`

- **四核（Four-Cores）**：离散对象 / 局部相互作用 / 贡献汇总 / 状态推进
  **Four-Cores**: Discrete Objects / Local Interactions / Accumulation / State Advancement

- **算例资产（Case Asset / Case Assets）**：可执行、可复现、可比较、可溯源、可冻结治理的算例；复数形式指算例资产集合
  **Case Asset / Case Assets**: executable cases that are reproducible, comparable, provenance-aware, and governed through freeze mechanisms

- **规范化表示（Canonical Representation）**：用于治理、语义差异比较、哈希、溯源与冻结判定的唯一、稳定表示形式
  **Canonical Representation**: the unique, stable representation used for governance, semantic diff, hashing, provenance binding, and freeze determination

- **canonical JSON**：在 v0.2.x 阶段采用的规范化表示具体形式
  **canonical JSON**: the concrete canonical representation format adopted in v0.2.x

- **规范表示红线（Canonical Red Line）**：规范化表示的强制适用边界；执行期数据内容（如 结果(results)）不得被 canonical
  **Canonical Red Line**: the applicability boundary of canonical representation; execution-time data contents must not be canonicalized

- **manifest**：数据集的权威元数据入口，用于承载身份、结构、溯源与版本信息
  **manifest**: the authoritative metadata entry of a dataset, carrying identity, structure, provenance, and version information

- **config_schema**：权威输入契约，用于声明物理意图与策略并进行机器校验
  **config_schema**: the authoritative input contract declaring physical intent and strategy, subject to machine validation

- **语义差异比较（semantic diff / diff）**：在规范化表示基础上，对对象“意义是否改变”的比较，而非文本差异
  **semantic diff / diff**: comparison of semantic changes based on canonical representations, not textual differences

- **config_hash**：对规范化配置对象计算的稳定哈希，用于复现、缓存与治理判定
  **config_hash**: a stable hash computed from canonical configuration objects for reproduction, caching, and governance

- **代码版本（code_version）**：用于唯一定位生成逻辑的不可变代码标识
  **code_version**: an immutable identifier uniquely locating the generating code state

- **溯源（Provenance）**：描述结果生成因果关系的元数据，包括配置、代码、求解器与运行环境
  **Provenance**: metadata describing causal traceability across config, code, solver, and runtime

- **质量门禁（Quality Gates）**：自动化质量检查，如收敛性、平衡误差、能量/守恒检查
  **Quality Gates**: automated quality checks (convergence, balance error, energy/conservation, etc.)

- **部分完成（partial）**：运行部分成功，产生部分有效结果但未完全满足契约
  **partial**: partially completed execution producing valid but incomplete results

- **失败（failed / failure）**：执行失败，未产生可用结果
  **failed / failure**: execution failure producing no usable results

- **silent drift**：配置或语义发生变化但系统未显式报错、结果悄然改变
  **silent drift**: semantic changes without explicit versioning, causing silent behavior changes

- **ADR（Architecture Decision Record）**：对偏离设计契约的决策进行显式记录的治理文档
  **ADR (Architecture Decision Record)**: a governance document recording explicit deviations from the design contract

---

### **附录 A：三梁对象、语义与治理对照表（权威性解释视图）**

**Appendix A: Three-Beams Objects, Semantics, and Governance Matrix (Authoritative View)**

------

#### **附录说明 | Appendix Note**

> 本附录以对照表形式，汇总并澄清 PeriSci 体系中 **三梁（A / B / C）** 各类核心对象在**语义角色、治理能力与 canonical 表示**方面的差异。
>
> 本表为**权威性解释视图（Authoritative View）**，用于防止在实现、评审或扩展过程中，对以下问题产生误解：
>
> - 哪些对象可以被实例化
> - 哪些对象参与校验、语义差异比较、哈希与溯源
> - 哪些对象必须或不应采用 canonical JSON
>
> 本附录**不引入新的规范性约束**，其内容应与正文中的 规范表示规则、规范表示红线 及 代码治理红线 保持一致。

> This appendix presents an **authoritative comparative view** of core objects across the **Three-Beams (A / B / C)** in the PeriSci system, clarifying their **semantic roles, governance participation, and canonical representation requirements**.
>
> The table is provided to prevent misinterpretation during implementation, review, or extension, particularly regarding:
>
> - Which objects can be instantiated
> - Which objects participate in validation, semantic diff, hashing, and provenance
> - Which objects MUST or MUST NOT adopt canonical JSON
>
> This appendix **does not introduce new normative constraints** and SHALL be interpreted consistently with the Canonical Representation Rule, Canonical Red Line, and Code Governance Red Line defined in the main body.

------

#### **三梁对象、语义与治理对照表 | Three-Beams Objects, Semantics, and Governance Matrix**

| 梁 / Beam | 核心对象 / Core Object       | 它是什么 / What It Is     | 谁写 / 产生 / Authored By | 是否可实例化 / Instantiable | 是否参与校验 / Validation | 是否参与 diff  | 是否参与 hash      | 是否参与 provenance | canonical JSON 的角色 / Role of Canonical JSON |
| --------- | ---------------------------- | ------------------------- | ------------------------- | --------------------------- | ------------------------- | -------------- | ------------------ | ------------------- | ---------------------------------------------- |
| **A 梁**  | **`config_schema`**          | 权威输入规范（规则/契约） | 系统设计者                | ❌                           | 用来校验他人              | ❌              | ❌                  | ❌                   | 自身以 JSON 表示，作为权威规则                 |
| **A 梁**  | **配置对象** (config object) | 某次运行的配置实例        | 用户 / pipeline           | ✅                           | ✅                         | ✅（语义 diff） | ✅（`config_hash`） | ✅                   | **必须 canonical JSON 后才能参与治理**         |
| **B 梁**  | **API / 接口契约**           | 输入输出结构约定          | 系统设计者                | ❌                           | 用来校验请求/响应         | ❌              | （可选）           | （间接）            | JSON 作为稳定接口格式                          |
| **C 梁**  | **dataset-spec**             | 输出结构与语义规范        | 系统设计者                | ❌                           | 用来校验 dataset          | ❌              | ❌                  | ❌                   | 自身以 JSON / Markdown 固化                    |
| **C 梁**  | **manifest（元数据对象）**   | dataset 的权威语义入口    | 系统自动生成              | ✅                           | ✅                         | ✅（结构 diff） | ✅（可选）          | ✅（核心）           | **权威 canonical JSON**                        |
| **C 梁**  | **results 内容对象**         | 实际输出结果              | 系统自动生成              | ✅                           | （间接）                  | （可选）       | （可选）           | ✅（被引用）         | 通常不强制 canonical                           |
| **C 梁**  | **case asset（未来）**       | 可审计、可复现案例        | 系统组合生成              | ✅                           | ✅                         | ✅              | ✅                  | ✅                   | canonical JSON 作为治理 glue                   |
