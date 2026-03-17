# PeriSci 路线图 | PeriSci Roadmap

---

## 0. 当前开发状态 | Current Development Status

### 当前阶段：v0.2.x（三梁执行结构冻结阶段）| Current Phase: v0.2.x (Three-Beam Execution Structure Freeze Stage)

PeriSci 当前处于 **v0.2.x 三梁执行结构阶段**。  
PeriSci is currently in the **v0.2.x Three-Beam Execution Structure stage**.

这一阶段的核心目标不是扩展功能数量，而是：

> 冻结三梁执行契约、明确系统边界、稳定治理结构。

The core objective of this stage is not to expand feature capabilities, but to:

> Freeze the Three-Beam execution contracts, clarify system boundaries, and stabilize the governance structure.

#### 已完成内容 | Completed Items

- Core / API 分层结构冻结  
- 三梁执行结构建立（配置梁 / 执行梁 / 输出梁）  
- CMake 依赖方向稳定（api → core）  
- CTest 自动契约门禁建立  
- `dataset_spec` 与 `manifest` 最小规范确立  
- 版本治理对齐（CMake / version.hpp / 构建输出）

- Core / API layered structure frozen  
- Three-Beam execution structure established (Config / Run / Export Beams)  
- Stable CMake dependency direction (api → core)  
- CTest-based automated contract gates established  
- Minimal specification for `dataset_spec` and `manifest` defined  
- Version governance aligned (CMake / version.hpp / build outputs)

#### 明确不包含 | Explicitly Not Included

- 具备物理意义的算例资产（计划于 v0.3 引入）  
- 完整物理求解器能力  
- 性能优化与并行能力  
- 生产级 CAE 功能体系  

- Physically meaningful case assets (planned for v0.3)  
- Complete physical solver capabilities  
- Performance optimization and parallel execution  
- Production-grade CAE functionality  

v0.2.x 是一个 **结构治理稳定里程碑**，而不是能力扩展版本。  
v0.2.x is a **structural governance stabilization milestone**, rather than a capability expansion release.

---

## 1. 路线图主线声明 | Guiding Principle of the Roadmap

> 本路线图以 **系统治理能力与可存活性** 的逐步解锁为主线，而非功能数量、算例规模或应用场景的堆叠。
> This roadmap takes the **progressive unlocking of system governance capability and survivability** as its main axis, rather than accumulating features, case scales, or application scenarios.

PeriSci 的版本演进，不以“功能堆叠”为目标，而以：

- 边界是否清晰
- 契约是否稳定
- 结构是否可治理
- 系统是否可长期存活

作为判断标准。

The evolution of PeriSci is not driven by “feature accumulation”, but judged by:

- Whether boundaries are clear
- Whether contracts are stable
- Whether structure is governable
- Whether the system can survive long-term

---

## 2. 架构演进路线（与里程碑对齐）| Architecture Evolution (Aligned with Milestones)

---

### v0.1.x（骨架与制度确立阶段） |  v0.1.x (Skeleton & Institutional Foundation Stage)

#### 阶段定位 | Positioning

- 已完成并冻结
- 系统级“宪法”和工程骨架已成立

- Completed and frozen
- System-level “constitution” and engineering skeleton established

#### 阶段目标 | Goals

- 让系统“站起来”，具备清晰、可约束、可治理的最小骨架
- Enable the system to “stand up” with a clear, constrained, and governable minimal skeleton

#### 已完成核心能力 | Completed Core Capabilities

- 明确分层结构（core / api / python / apps）
- 明确依赖方向与禁止反向依赖
- 建立最小可复现构建体系（CMake + toolchain）
- 建立 docs/specs / docs/adr / docs/releases 文档制度
- ARCHITECTURE.md / DESIGN_CONTRACT.md 冻结为宪法级文档
- examples / tests / docs 明确为质量门禁（Quality Gates）
> v0.1.x 阶段不再新增能力，仅允许维护性修订。

- Clear layered structure defined (core / api / python / apps)
- Dependency directions defined and reverse dependencies explicitly forbidden
- Minimal reproducible build system established (CMake + toolchain)
- Documentation mechanisms established: docs/specs / docs/adr / docs/releases
- ARCHITECTURE.md / DESIGN_CONTRACT.md frozen as constitutional-level documents
- examples / tests / docs explicitly defined as Quality Gates
> No new capabilities will be added in v0.1.x; only maintenance-level revisions are permitted.

---

### v0.2.x（三梁执行结构阶段）| v0.2.x (Three-Beam Execution Structure Stage)

#### 阶段定位 | Positioning

- 从“骨架成立”过渡到“系统可运行但不承诺物理完整性”
- 以执行契约、系统边界与治理规则冻结为核心目标

- Transition from “skeleton established” to “system runnable without committing to physical completeness”
- Focused on freezing execution contracts, system boundaries, and governance rules

---

#### 阶段目标 | Goals

- 让系统“能跑”，但更重要的是：
  - 误用被结构性约束
  - 语义漂移被契约机制阻止

- Make the system “runnable”, but more importantly:
  - Misuse is structurally constrained
  - Semantic drift is prevented by contract mechanisms

---

#### 核心里程碑 | Core Milestones

##### 1. 配置梁（Config Beam）：config_schema（权威输入契约）  
| Config Beam: config_schema (Authoritative Input Contract)

- schema 成为唯一物理意图载体  
- 明确字段语义、版本策略与兼容规则  
- 支持语义 diff / hash / 校验  

- The schema becomes the sole carrier of physical intent  
- Field semantics, versioning strategy, and compatibility rules clearly defined  
- Supports semantic diff / hashing / validation  

---

##### 2. 执行梁（Run Beam）：run_case(config) → results（纯执行闭环）  
| Run Beam: run_case(config) → results (Pure Execution Loop)

- 不引入 GUI 或隐式状态  
- 输入仅接受通过 schema 校验的配置对象（config）  
- 输出为结构化 results（无文件副作用）  

- No GUI or implicit state introduced  
- Input strictly accepts schema-validated configuration objects (config)  
- Output is structured results (no file-side effects)  

---

##### 3. 输出梁（Export Beam）：export_dataset(results, dataset_spec)（权威输出 + 溯源）  
| Export Beam: export_dataset(results, dataset_spec) (Authoritative Output + Provenance)

- 明确 dataset 目录结构与 manifest 规范  
- 记录 provenance（config / code / version / environment）  
- 为算例资产与回归测试提供制度基础  

- Dataset directory structure and manifest specification clearly defined  
- Provenance recorded (config / code / version / environment)  
- Provides the governance foundation for case assets and regression testing  

---

#### 明确的非目标 | Explicit Non-Goals

- 不承诺真实工程物理完备性  
- 不引入复杂插件或多物理场机制  
- 不将临时算例固化为“官方能力”  

- No commitment to full engineering-grade physical completeness  
- No introduction of complex plugin or multiphysics mechanisms  
- No solidification of temporary cases into “official capabilities”  

---

### v0.3.x（算例资产起点阶段）| v0.3.x (Case Asset Initiation Stage)

#### 阶段定位 | Positioning

- 从“契约成立”过渡到“能力被真实使用并反向验证”
- 算例资产首次成为系统的一等公民
- Transition from “contracts established” to “capabilities being genuinely exercised and validated”
- Case assets become first-class citizens of the system

#### 阶段目标 | Goals

- 让系统可教学、可验证、可复现、可回归
- Make the system teachable, verifiable, reproducible, and regression-testable

#### 核心里程碑 | Core Milestones

##### 至少一个完整算例资产（Case Asset）| At least one complete Case Asset

- config_schema
- 可重复运行路径（run_case）
- 结构化结果与数据集
- 预期 / 基准结果
- 溯源与失败记录
- config_schema
- Reproducible execution path (run_case)
- Structured results and dataset
- Expected / baseline results
- Provenance and failure records

##### 教学级最小数值实现 | Teaching-level minimal numerical implementation

- 一个结构清晰、可验证、可收敛的最小 PDE 示例
- 用于建立从 config → run_case → dataset 的完整闭环
- 为 FEM / PeriFEM 统一管线提供起点
- A structurally clear, verifiable, and convergent minimal PDE example
- Establish a complete loop from config → run_case → dataset
- Provide a starting point for a unified FEM / PeriFEM pipeline

##### 回归测试 | Regression testing

- 锁定关键数值指标或不变量
- 防止架构与数值语义回退
- Lock key numerical metrics or invariants
- Prevent regression of architectural and numerical semantics

##### Python 层与 CLI | Python layer and CLI

- 提供批量与教学友好的入口（非权威层）
- Provide batch-friendly and teaching-friendly entry points (non-authoritative layer)

---

### v0.x → v1.0（方向性展望，不构成承诺）| v0.x → v1.0 (Directional Outlook, Non-Commitment)

以下内容属于长期方向性判断，不构成任何版本承诺或时间表：

- 更复杂的 PeriFEM / FEM 耦合机制
- 多物理场与模型演化能力
- 面向 AI / 自动化的系统化数据生产接口
- 大规模算例资产库与社区协作机制
- 长期治理、贡献者角色分化与维护策略

> 所有进入 v1.0 的能力，都必须首先以“算例资产”的形式，在 v0.x 阶段被反复验证。

The following items represent long-term directional judgments, and do not constitute any version commitment or timeline:

- More complex PeriFEM / FEM coupling mechanisms
- Multiphysics and model evolution capabilities
- Systematic data production interfaces for AI / automation
- Large-scale case asset libraries and community collaboration mechanisms
- Long-term governance, contributor role differentiation, and maintenance strategies

> All capabilities entering v1.0 must first be repeatedly validated in the v0.x stage in the form of case assets.

---

## 3. 阶段性质对比 | Phase Comparison

| 版本   | 核心关注点       | 阶段性质     |
| ------ | ---------------- | ------------ |
| v0.1.x | 骨架与制度建立   | 宪法阶段     |
| v0.2.x | 契约与边界冻结   | 治理阶段     |
| v0.3.x | 算例资产验证能力 | 能力验证阶段 |
| v1.0   | 稳定计算核心     | 生产阶段     |

| Version | Core Focus                          | Phase Nature         |
| ------- | ----------------------------------- | ---------------------|
| v0.1.x  | Skeleton & institutional foundation | Constitutional stage |
| v0.2.x  | Contract & boundary stabilization   | Governance stage     |
| v0.3.x  | Case asset validation capability    | Capability validation stage |
| v1.0    | Stable computational core           | Production stage     |

---

## 4. 演进哲学 | Evolution Philosophy

PeriSci 的演进遵循：

1. 先稳定结构，再引入能力
2. 先定义契约，再实现算法
3. 执行与资产生成严格分离
4. 版本升级必须伴随治理增强
5. 所有能力必须先以算例资产形式验证

The evolution of PeriSci follows:

1. Stabilize structure before introducing capabilities
2. Define contracts before implementing algorithms
3. Strict separation between execution and asset generation
4. Every version upgrade must strengthen governance
5. All capabilities must first be validated in the form of case assets

---
