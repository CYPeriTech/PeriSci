# 头文件命名规范 | Header Naming Conventions

> 本文档用于规定 **PeriSci v0.2.x 阶段** 公共头文件的命名规则与语义边界，以确保对外接口在演进过程中保持稳定、清晰且可治理。
> This document defines naming rules and semantic boundaries for public header files in **PeriSci v0.2.x**, ensuring that external interfaces remain stable, clear, and governable during system evolution.
>
> 在 v0.2.x 阶段，系统架构与模块边界已经建立，公共头文件不再只是骨架占位，而是逐步形成稳定接口层。因此，其命名必须反映明确语义，并避免引入模糊或误导性的概念。
> In the v0.2.x phase, the system architecture and module boundaries have already been established. Public headers are no longer merely skeleton placeholders, but gradually form a stable interface layer. Therefore, their naming must reflect explicit semantics and avoid introducing vague or misleading concepts.

------

## 1. 文档目的与适用范围 | Purpose and Scope

### 1.1 文档目的 | Purpose

- 明确 v0.2.x 阶段公共头文件的命名原则
- 防止头文件命名破坏既有模块边界
- 避免通过名称引入未经设计讨论的概念
- 为接口稳定性与未来版本演进提供清晰约束
- Define naming principles for public headers in v0.2.x
- Prevent header naming from eroding established module boundaries
- Avoid introducing undeclared concepts through header names
- Provide clear constraints for interface stability and future evolution

### 1.2 适用范围 | Scope

- 本规范仅约束 **公共头文件**（public headers）
- 不约束 `src/` 下的私有实现文件
- This specification applies only to **public headers**
- Private implementation files under `src/` are not covered

------

## 2. 总体命名原则 | General Naming Principles

### 2.1 最小暴露原则 | Minimal Exposure Principle

公共头文件的命名即构成对外语义承诺。
Public header names constitute semantic commitments to external users.

在 v0.2.x 阶段，这些承诺应：

- 与已建立的模块职责保持一致
- 反映稳定的接口语义
- 避免泄露内部实现结构

In v0.2.x, these commitments must:

- remain consistent with established module responsibilities
- reflect stable interface semantics
- avoid exposing internal implementation structures

### 2.2 名称即概念 | Names Imply Concepts

- 头文件名应直接反映其稳定职责
- 禁止通过模糊或泛化名称隐藏真实意图
- Header names should directly reflect stable responsibilities
- Do not hide intent behind vague or overly generic names

------

## 3. core 模块头文件命名规则 | core Module Header Rules

### 3.1 core 模块的职责边界 | Responsibility Boundary

- core 模块仅承载最底层、长期稳定的基础设施语义
- 不应表达具体物理、数值或求解层概念
- The core module carries only lowest-level, long-term stable infrastructure
- It must not express physical, numerical, or solver-level concepts

### 3.2 v0.2.x 阶段推荐的基础头文件 | Recommended Core Headers in v0.2.x

在 v0.2.x 阶段，core 模块的公共头文件应仍然保持最小集合，但允许在基础设施层面逐步形成稳定接口。

典型示例包括：

- version.hpp（版本信息）
- export.hpp（符号导出与可见性控制）
- platform.hpp（平台相关定义）
- types.hpp（基础类型定义）
- error.hpp（基础错误类型，如需要）

上述头文件仅用于表达基础设施语义，不得引入领域层或求解层概念。

In v0.2.x, public headers in the core module should still remain minimal, but stable infrastructure interfaces may gradually emerge.

Typical examples include:

- version.hpp (version information)
- export.hpp (symbol export and visibility control)
- platform.hpp (platform-related definitions)
- types.hpp (basic type definitions)
- error.hpp (basic error types, if necessary)

These headers are limited to infrastructure semantics and must not introduce domain or solver-level concepts.

> 注：上述列表为指导性示例，并非强制穷举；任何新增名称都应接受严格审视。
> Note: The above list is illustrative, not exhaustive; any additional names require careful scrutiny.

### 3.3 不应出现在 core 模块中的语义 | Concepts Not Belonging to core

以下类型的语义通常不属于 core 模块职责，因此不应在 core 的公共头文件中出现：

- mesh.hpp
- material.hpp
- solver.hpp
- config.hpp
- case.hpp
- results.hpp

这些名称通常代表更高层语义，应由上层模块（如 api 或 future domain modules）承担。

The following semantic concepts generally do not belong to the responsibility of the core module and therefore should not appear as public headers in core:

- mesh.hpp
- material.hpp
- solver.hpp
- config.hpp
- case.hpp
- results.hpp

These names typically represent higher-level semantics and should be owned by upper modules such as api or future domain modules.

------

## 4. api 模块头文件命名规则 | api Module Header Rules

### 4.1 api 模块的语义角色 | Semantic Role

- api 模块用于表达系统对外可见的执行意图与使用接口。
- 在 v0.2.x 阶段，api 模块逐步形成稳定的用户接口层。
- The api module expresses user-visible execution intent and usage interfaces.
- In the v0.2.x phase, the api module gradually forms a stable user-facing interface layer.

因此，api 模块的公共头文件允许出现描述以下语义的名称：

- 用例（case）
- 配置（config）
- 结果（results）

这些名称表达的是用户可见的接口语义，而不是内部实现结构。

Therefore, public headers in the api module may use names that express the following semantics:

- case
- configuration
- results

These names represent user-visible interface semantics rather than internal implementation details.

### 4.2 命名指导原则 | Naming Guidance

- 名称应聚焦于接口语义，而非内部实现细节
- 避免在 v0.1.x 阶段过度细分接口文件
- Names should focus on interface semantics, not implementation details
- Avoid over-fragmenting API headers during v0.1.x

------

## 5. 审查与演进 | Review and Evolution

### 5.1 Review 要点 | Review Checklist

在引入新的公共头文件前，应至少回答以下问题：

- 该名称是否隐含了对未来能力的承诺？
- 是否属于 core / api 的合理职责？
- 是否可以延后到更高版本再引入？

Before introducing a new public header, reviewers should ask:

- Does this name imply future capability commitments?
- Does it belong to core or api responsibilities?
- Can it be deferred to a later version?

### 5.2 与架构治理的关系 | Relation to Governance

- 头文件命名的重大变化可能影响架构边界
- 此类变化应通过 ADR 正式记录
- Significant changes to header naming may affect architectural boundaries
- Such changes should be recorded via ADRs

当头文件命名变化影响 API 稳定性或模块职责划分时，必须通过 ADR 进行显式架构决策记录。
If a header naming change affects API stability or module responsibility boundaries, it MUST be recorded as an ADR.

------

## 6. 结语 | Closing Notes

头文件命名是最早形成“技术承诺”的接口层。
Header naming is one of the earliest layers where technical commitments emerge.

一个公共头文件的名称不仅表达其语义职责，也隐含了对外接口的长期稳定性预期。
The name of a public header not only expresses its semantic responsibility, but also implies expectations of long-term interface stability.

因此，公共头文件名一旦被发布，应视为稳定接口的一部分。
Therefore, once a public header name is released, it should be treated as part of the stable interface.

对公共头文件的重命名通常属于潜在破坏性变更，必须通过版本策略或 ADR 进行治理与记录。
Renaming a public header is typically a potentially breaking change and must be governed through versioning policies or recorded via ADRs.