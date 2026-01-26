# Architecture Decision Records (ADR)

# 架构决策记录（ADR）

本目录用于存放 **PeriSci** 项目中的 **Architecture Decision Records（架构决策记录）**。

ADR 用于记录那些：

- 具有长期影响的关键技术或工程决策
- 会影响架构边界、演进路径或治理方式的选择
- 需要被未来贡献者理解、引用或复盘的判断

This directory contains the **Architecture Decision Records (ADRs)** for the **PeriSci** project.

ADRs capture decisions that:

- Have long-term impact on the project
- Affect architectural boundaries, evolution paths, or governance
- Should be understood, cited, or revisited by future contributors

------

## 什么是 ADR？ | What is an ADR?

**ADR（Architecture Decision Record）** 是一份简短的、结构化的文档，用于记录：

- 当时面临的背景与问题（Context）
- 所做出的决策（Decision）
- 决策的理由（Rationale）
- 被考虑但未采用的方案（Alternatives）
- 决策带来的影响与约束（Consequences）

An **ADR (Architecture Decision Record)** is a short, structured document that records:

- The context and problem at the time of the decision
- The decision that was made
- The rationale behind the decision
- Alternatives that were considered but not chosen
- The consequences and constraints introduced by the decision

ADR 的目标不是证明“这是最优解”，而是：

> **让未来的人知道：为什么当时是这样决定的。**

The goal of an ADR is not to prove that a decision was optimal, but to:

> **Explain why this decision made sense at that time.**

------

## ADR 在 PeriSci 中的角色 | Role of ADRs in PeriSci

在 PeriSci 中，ADR 被视为：

- 架构与工程层面的**正式记忆**
- 比代码更稳定、比 Roadmap 更具体
- 对“硬边界”与关键方向的权威解释

In PeriSci, ADRs are treated as:

- The **official memory** of architectural and engineering decisions
- More stable than code, and more specific than the roadmap
- The authoritative explanation of hard boundaries and key directions

ADR 与其他文档的关系：

- `ARCHITECTURE.md`：定义**当前生效的架构边界与原则**
- `ROADMAP.md`：描述**可能的未来方向（不构成承诺）**
- **ADR**：解释**为何形成当前架构与原则**

Relationship to other documents:

- `ARCHITECTURE.md`: defines the **current architectural boundaries and principles**
- `ROADMAP.md`: describes **possible future directions (non-binding)**
- **ADR**: explains **why the current architecture and principles exist**

------

## 何时需要新增 ADR？ | When to Add a New ADR?

当出现以下情况之一时，应考虑新增 ADR：

- 引入或修改**架构硬边界**
- 确定或否决一条**长期技术路线**
- 选择某种工具链、构建方式或工程范式
- 明确“为什么现在不做某件事”

You should consider adding a new ADR when:

- Introducing or modifying **hard architectural boundaries**
- Choosing or rejecting a **long-term technical direction**
- Selecting a toolchain, build system, or engineering paradigm
- Explicitly deciding **not** to do something (yet)

不需要为以下情况编写 ADR：

- 局部实现细节
- 可随时回滚的实验性改动
- 纯粹的 bug 修复或重构

You do **not** need an ADR for:

- Local implementation details
- Easily reversible experimental changes
- Pure bug fixes or routine refactors

------

## ADR 文件命名与编号 | Naming and Numbering

ADR 文件采用以下命名规则：

```
0001-short-decision-title.md
```

- 编号为四位递增数字（从 `0001` 开始）
- 编号一旦分配，**永不复用**
- 文件名使用简短的英文描述（kebab-case）

ADR files follow this naming convention:

```
0001-short-decision-title.md
```

- Four-digit incremental number (starting from `0001`)
- Once assigned, a number is **never reused**
- File name uses a short English description in kebab-case

------

## ADR 状态 | ADR Status

每个 ADR 必须包含状态字段（Status）：

- **Proposed**：已提出，尚未达成共识
- **Accepted**：已接受，作为当前决策依据
- **Deprecated**：已被新决策取代，但保留用于历史参考
- **Superseded**：已被明确替代（应指向新的 ADR）

Each ADR must include a Status field:

- **Proposed**: proposed but not yet agreed upon
- **Accepted**: accepted and serves as the current decision
- **Deprecated**: no longer recommended, kept for historical context
- **Superseded**: explicitly replaced by a newer ADR

------

## ADR 索引 | ADR Index

| 编号 | 标题                                                         | 状态     | 日期       |
| ---- | ------------------------------------------------------------ | -------- | ---------- |
| 0001 | Windows 构建工具链与生成器选择（Ninja 单配置）Windows Toolchain & Generator Selection (Ninja Single-Config) | Accepted | 2026-01-24 |

------

## 模板 | Template

新增 ADR 时，请基于以下模板：

When adding a new ADR, please base it on the following template:

- `0000-template.md`

（见本目录中的模板文件）

(See the template file in this directory.)

------

## 维护原则 | Maintenance Principles

- ADR 是**追加式**的：不要修改已 Accepted 的内容来“改写历史”
- 如决策发生变化，应新增 ADR，并在旧 ADR 中标注 `Superseded`
- ADR 的价值在于**解释当时的判断**，而不是预测未来
- ADRs are **append-only**: do not rewrite accepted ADRs to change history
- When a decision changes, add a new ADR and mark the old one as `Superseded`
- The value of an ADR lies in **explaining past reasoning**, not predicting the future

------

> ADR 是 PeriSci 架构治理的一部分，与代码同等重要。
>
> ADRs are a core part of PeriSci's architectural governance, as important as the code itself.
