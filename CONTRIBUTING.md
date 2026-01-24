# 贡献指南 | Contributing Guide

感谢你对 **PeriSci** 项目的关注与贡献意愿！

PeriSci 是一个以 **近场有限元法（PeriFEM）** 为核心的开源科学计算与工程仿真平台。  
我们欢迎来自学术界、工程界以及开源社区的理性、长期、建设性参与。

Thank you for your interest in contributing to **PeriSci**!

PeriSci is an open-source scientific computing and engineering simulation platform centered on the **PeriFEM (Peridynamics-based Finite Element Method)**.  
We welcome rational, long-term, and constructive contributions from
academia, industry, and the open-source community.

---

## 项目阶段说明 | Project Stage

PeriSci 当前处于 **早期开发阶段（v0.x）**。

在这一阶段：
- 软件架构仍在逐步完善
- 接口与实现可能发生演进
- 对贡献的重点是 **正确性、可复现性与设计一致性**

请在贡献前理解：  
**并非所有 Pull Request 都会被立即合并**，
但每一份合理的贡献都会被认真评审。

PeriSci is currently in an **early development stage (v0.x)**.

At this stage:
- The software architecture is still evolving
- APIs and implementations may change
- Contributions are evaluated primarily for **correctness,
  reproducibility, and architectural consistency**

Please note that **not all Pull Requests will be merged immediately**,  
but every reasonable contribution will be carefully reviewed.

---

## 贡献类型 | Types of Contributions

我们欢迎以下类型的贡献：|  We welcome the following types of contributions:

### 🧮 数值方法与物理模型 | Numerical Methods and Physical Models
- 近场有限元（PeriFEM）相关算法
- 损伤、断裂、多物理场耦合模型
- 数值稳定性与计算收敛性改进
- Algorithms related to PeriFEM
- Damage, fracture, and multiphysics coupling models
- Improvements in numerical stability and energy consistency

### 📚 教学与示例 | Education and Examples
- 教学算例与最小工作示例（MVP）
- 可复现的基准问题
- 面向学生的教程与说明
- Educational examples and minimal working cases
- Reproducible benchmark problems
- Tutorials and documentation for students

### 🧪 测试与验证 | Testing and Validation
- 单元测试与回归测试
- 数值结果一致性验证
- 性能与稳定性测试
- Unit and regression tests
- Verification of numerical consistency
- Performance and stability tests

### 🛠 工程化改进 | Engineering Improvements
- 构建系统（CMake）
- CI / 自动化测试
- 代码可读性与可维护性提升
- Build system (CMake)
- CI and automated testing
- Code readability and maintainability

---

## 不适合的贡献类型 | What Is Currently Out of Scope

在当前阶段，以下内容通常不会被接受：

- 大规模、无设计说明的重构
- 未经讨论的接口破坏性修改
- 与 PeriFEM 核心无关的功能堆叠
- 无物理或数值依据的经验性改动

如果你不确定某项工作是否合适，**请先提交 Issue 进行讨论**。

At the current stage, the following are generally out of scope:

- Large-scale refactoring without prior design discussion
- Breaking API changes without agreement
- Feature additions unrelated to the PeriFEM core
- Empirical changes without physical or numerical justification

If in doubt, **please open an Issue for discussion first**.

---

## 贡献流程 | Contribution Workflow

### 1) 提交 Issue（推荐）| Open an Issue (Recommended)
- 描述问题、想法或改进建议
- 尽量说明动机、背景和预期目标
- Describe the problem, idea, or proposed improvement
- Provide motivation, background, and expected outcomes

### 2) Fork 与分支 | Fork and Branch
- Fork 本仓库
- 从 `master` 主分支创建各种特色分支，例如：
  - `feat/xxx`	功能分支
  - `fix/xxx`          修复分支
  - `docs/xxx`        文档/示例分支
  - `refactor/xxx`  重构分支
  - `exp/xxx`           实验分支
  - `release/xxx`   发布分支
- Fork the repository
- Create various specialized branches from `master`, e.g.:
  - `feat/xxx`	feature branch
  - `fix/xxx`          bugfix branch
  - `docs/xxx`        docs branch
  - `refactor/xxx`  refactor branch
  - `exp/xxx`           experimental branch  (discardable any time)
  - `release/xxx`   release branch

### 3) 开发与提交 | Develop and Commit
- 保持提交信息清晰、聚焦
- 确保代码能够通过本地构建与测试
- Keep commits focused and well-described
- Ensure the code builds and tests pass locally

### 4) 提交 Pull Request | Submit a Pull Request
- 清晰描述改动内容与动机
- 说明是否涉及数值行为或物理意义变化
- 必要时提供最小示例或验证结果
- Clearly describe what was changed and why
- State whether numerical behavior or physical meaning is affected
- Provide minimal examples or validation results when appropriate

---

## 代码与设计原则 | Code and Design Principles

所有贡献应遵循以下基本原则：

- **物理一致性优先于性能优化**
- **可复现性优先于复杂技巧**
- **核心计算逻辑与用户接口分离**
- **明确区分实验性代码与稳定代码**

All contributions should follow these principles:

- **Physical consistency over premature optimization**
- **Reproducibility over clever tricks**
- **Separation of core computation and user interfaces**
- **Clear distinction between experimental and stable code**

---

## 审查与合并 | Review and Merging

- 所有 Pull Request 都需要审查
- 核心数值与架构相关修改将由维护者重点评估
- 合并策略以 **Squash and Merge** 为主
- 维护者有权请求修改或暂缓合并
- All Pull Requests are subject to review

- Changes affecting core numerics or architecture receive extra scrutiny
- **Squash and Merge** is the preferred merge strategy
- Maintainers may request revisions or defer merging

---

## 行为准则 | Code of Conduct

请在所有交流中保持：

- 尊重
- 专业
- 理性

PeriSci 致力于构建一个 **友好、理性、以科学与工程为导向的开源社区**。

Please maintain:

- Respect
- Professionalism
- Rational discussion

PeriSci is committed to building an **open, respectful, and
science- and engineering-driven community**.

---

## 联系方式 | Contact

如有不确定事项或合作意向，请通过以下方式联系：

- GitHub / Gitee Issues
- Pull Request 讨论区

For questions or collaboration inquiries, please contact us via:

- GitHub / Gitee Issues
- Pull Request discussions