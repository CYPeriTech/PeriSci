## 架构演进路线（与里程碑对齐）| Evolution Path (Aligned with Milestones)
本路线图以 **系统能力的逐步解锁** 为主线，
而非功能数量或应用场景的堆叠。

This roadmap focuses on **progressive unlocking of system capabilities**,
rather than feature accumulation or application breadth.

---

### v0.1.x（骨架）|  (Skeleton)
**目标 | Goals**

- 让系统“站起来”，具备清晰、可约束的最小骨架  
- Establish a minimal, well-constrained system skeleton

**核心内容 | Core Milestones**

- 建立清晰的分层结构（core / api / python / apps）  
- 建立最小可用的构建体系（CMake + repo layout）  
- 建立 `docs/specs` 作为规范入口  
- 建立 `docs/adr` 作为架构决策记录（ADR）的正式存放位置  
- 建立最小 examples 与 tests（内容可为空，但结构就位）

- Establish clear layering (core / api / python / apps)  
- Set up minimal build system (CMake + repository layout)  
- Establish `docs/specs` as the specification entry  
- Establish `docs/adr` as the official location for Architecture Decision Records (ADRs)  
- Create minimal examples and tests (structure-first, content optional)

---

### v0.2.x（三梁）| (Three Pillars) 
**目标 | Goals**

- 让系统“会跑”，形成最小但完整的计算闭环  
- Enable the system to run end-to-end with a minimal closed loop

**核心内容 | Core Milestones**

- 落地 `config_schema`（明确、版本化）  
- 落地 `run_case(config) -> results`（可跑最小 case）  
- 落地 `export_dataset(results, spec)`  
  - 输出 manifest  
  - 记录 provenance（config / code / version）

- Implement versioned `config_schema`  
- Implement `run_case(config) -> results` for minimal runnable cases  
- Implement `export_dataset(results, spec)`  
  - Generate manifest  
  - Record provenance (config / code / version)

---

### v0.3.x（学生 MVP）| (Three Pillars)  
**目标 | Goals**

- 让系统“可教学、可验证、可复现”  
- Make the system teachable, verifiable, and reproducible

**核心内容 | Core Milestones**

- 至少一个完整、可复现的教学算例  
- 配套的教程文档（从 config 到 results / dataset）  
- 回归测试锁住关键指标  
- Python 层提供一键入口（可选，但推荐）

- At least one fully reproducible teaching example  
- Tutorial documentation (from config to results/dataset)  
- Regression tests locking key metrics  
- One-click entry via Python layer (optional but recommended)

---

### v0.x → v1.0（方向性，不作承诺）  
### v0.x → v1.0 (Directional, Non-Commitment)

以下内容属于**长期方向**，不构成阶段性承诺：

- 工程级算例与规模化计算  
- 多物理场耦合与插件机制  
- 面向 AI 的系统化数据生产与接口标准化  
- 社区化治理与长期维护策略

The following items are **long-term directions**, not milestone commitments:

- Engineering-scale cases and large-scale computation  
- Multiphysics coupling and plugin mechanisms  
- Systematic data production and standardized AI interfaces  
- Community governance and long-term maintenance strategy