- ## 架构演进路线（与里程碑对齐） | Architecture Evolution Path (Aligned with Milestones)

  > 本路线图以 **系统治理能力与可存活性** 的逐步解锁为主线，而非功能数量、算例规模或应用场景的堆叠。
  > 
  >This roadmap takes the **progressive unlocking of system governance and survivability** as its main axis, rather than accumulating features, case scales, or application scenarios.
  
  ------

  ### v0.1.x（骨架阶段） | Skeleton Phase

  **阶段定位 | Positioning**

  - 已完成并冻结
  - 系统级“宪法”和工程骨架已成立
  - Completed and frozen
  - System-level “constitution” and engineering skeleton have been established

  **阶段目标 | Goals**

  - 让系统“站起来”，具备清晰、可约束、可治理的最小骨架
  - Enable the system to “stand up” with a clear, constrained, and governable minimal skeleton

  **已完成核心能力 | Completed Milestones**

  - 明确分层结构（core / api / python / apps）
  
  - 明确依赖方向与禁止反向依赖
  
  - 建立最小可复现构建体系（CMake + toolchain）
  
  - 建立 docs/specs / docs/adr / docs/releases 文档制度
  
  - ARCHITECTURE.md / DESIGN_CONTRACT.md 冻结为宪法级文档
  
  - examples / tests / docs 明确为质量门禁（Quality Gates）
  
    
  
  - Clear layering established (core / api / python / apps)
  
  - Dependency directions defined, with reverse dependencies explicitly forbidden

  - Minimal reproducible build system established (CMake + toolchain)

  - Documentation Mechanism established: docs/specs / docs/adr / docs/releases
  
  - ARCHITECTURE.md and DESIGN_CONTRACT.md frozen as constitutional documents
  
  - examples / tests / docs explicitly defined as Quality Gates
  
  > v0.1.x 阶段 **不再新增能力**，仅允许维护性修订。
  >
  > In the v0.1.x phase, **no new capabilities are allowed**; only maintenance-level revisions are permitted.
  
  ------
  
  ### v0.2.x（三梁阶段） | Three-Beams Phase
  
  **阶段定位 | Positioning**
  
  - 从“骨架成立”过渡到“系统可运行但不承诺物理完整性”
  - 以 **契约、边界、制度冻结** 为核心目标
  - Transition from “skeleton established” to “system runnable without promising physical completeness”
  - Focused on **freezing contracts, boundaries, and institutional rules**
  
  **阶段目标 | Goals**
  
  - 让系统“能跑”，但更重要的是：
    - **不能被误用**
    - **不能悄然漂移**
  - Make the system “runnable”, but more importantly:
    - **Impossible to misuse**
    - **Impossible to drift silently**

  **核心里程碑 | Core Milestones**

  1. **A 梁：config_schema（权威输入契约）** | **Beam A: config_schema (Authoritative Input Contract)**
     - schema 成为唯一物理意图载体
     - 明确字段语义、版本策略、兼容规则
     - 支持 diff / hash / 校验
     - The schema becomes the sole carrier of physical intent
        - Field semantics, versioning strategy, and compatibility rules are explicitly defined
        - Supports diff / hash / validation
  2. **B 梁：run_case(config) -> results（纯执行闭环）**|  **Beam B: run_case(config) -> results (Pure Execution Loop)**
     - 不引入 GUI 或隐式状态
     - 输入仅接受 schema
     - 输出为结构化 results（非文件副作用）
     - No GUI or implicit state introduced
        - Inputs accept schema only
        - Outputs are structured results (no file-side effects)
  3. **C 梁：export_dataset(results, spec)（权威输出 + provenance）**| **Beam C: export_dataset(results, spec) (Authoritative Output + Provenance)**
     - 明确 dataset 目录结构与 manifest 规范
     - 记录 provenance（config / code / version / environment）
     - 为未来算例资产与回归测试提供制度基础
     - Dataset directory structure and manifest specification clearly defined
        - Provenance recorded (config / code / version / environment)
        - Provides an institutional foundation for future case assets and regression testing
  
  **明确的非目标 | Explicit Non-Goals**
  
  - 不承诺真实工程物理完备性
  - 不引入复杂插件或多物理场机制
  - 不将临时算例固化为“官方能力”
  - No commitment to full engineering-grade physical completeness
  - No introduction of complex plugin or multiphysics mechanisms
  - No solidification of temporary cases into “official capabilities”

  ------
  
  ### v0.3.x（学生 MVP / 算例资产起点） | Student MVP & Case Assets
  
  **阶段定位 | Positioning**

  - 从“契约成立”过渡到“能力被真实使用并反向验证”
  - 算例资产首次成为系统的一等公民
  - Transition from “contracts established” to “capabilities being genuinely exercised and validated”
  - Case assets become first-class citizens of the system for the first time
  
  **阶段目标 | Goals**
  
  - 让系统 **可教学、可验证、可复现、可回归**
  - Make the system **teachable, verifiable, reproducible, and regression-testable**
  
  **核心里程碑 | Core Milestones**
  
  - 至少 **一个完整算例资产（Case Asset）**：
    - config_schema
    - 可重复运行路径（run_case）
    - 结构化结果与数据集
    - 预期/基准结果
    - 溯源与失败记录
    
  - 教学级最小数值实现：
    - 基于 FEM 的线弹性问题
    - 为 FEM / PeriFEM 统一管线提供起点
    
  - 回归测试：
    - 锁定关键数值指标或不变量
    - 防止架构与数值语义回退
    
  - Python 层与 CLI：
    - 提供批量与教学友好的入口（非权威层）
    
      
  
  - At least **one complete Case Asset**:
    - config_schema
    - reproducible execution path (run_case)
    - structured results and dataset
    - expected / baseline results
    - provenance and failure records
  
  - Teaching-level minimal numerical implementation:
    - Linear elasticity based on FEM
    - Serves as the starting point for a unified FEM / PeriFEM pipeline
  
  - Regression testing:
    - Lock key numerical metrics or invariants
    - Prevent regression of architectural and numerical semantics
  
  - Python layer and CLI:
    - Provide batch-friendly and teaching-friendly entry points (non-authoritative layer)
  
  ------
  
  ### v0.x → v1.0（方向性展望，不构成承诺） | Directional, Non-Commitment
  
  以下内容属于 **长期方向性判断**，不构成任何版本承诺或时间表：
  
  - 更复杂的 PeriFEM / FEM 耦合机制
  - 多物理场与模型演化能力
  - 面向 AI / 自动化的系统化数据生产接口
  - 大规模算例资产库与社区协作机制
  - 长期治理、贡献者角色分化与维护策略
  
  The following items are **long-term directional judgments** and do not constitute
  any version commitment or schedule:
  
  - More advanced PeriFEM / FEM coupling mechanisms
  - Multiphysics and model evolution capabilities
  - Systematic data production interfaces for AI / automation
  - Large-scale case asset libraries and community collaboration mechanisms
  - Long-term governance, contributor role differentiation, and maintenance strategies
  
  
  
  > 所有进入 v1.0 的能力，都必须首先以“算例资产”的形式在 v0.x 阶段被反复验证。
  >
  > All capabilities entering v1.0 must first be repeatedly validated in the v0.x stage **in the form of case assets**.
