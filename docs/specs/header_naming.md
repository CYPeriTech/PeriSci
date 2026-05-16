# 头文件命名规范 | Header Naming Conventions

> 本文档用于规定 **PeriSci v0.2.x 基线与 v0.3.x+ 阶段** 公共头文件的命名规则与语义边界，以确保对外接口在演进过程中保持稳定、清晰且可治理。
> This document defines naming rules and semantic boundaries for public header files in the **PeriSci v0.2.x baseline and v0.3.x+ stage**, ensuring that external interfaces remain stable, clear, and governable during system evolution.
>
> 在 v0.3.x+ 阶段，公共头文件继续承担稳定接口层职责，同时开始承载由真实教学示例牵引出来的可复用 core 能力。因此，其命名必须反映明确语义，并避免引入示例专属、短期或误导性的概念。
> In the v0.3.x+ stage, public headers continue to form the stable interface layer, and they also begin to carry reusable core capabilities driven by real teaching examples. Therefore, their naming must reflect explicit semantics and avoid example-specific, short-lived, or misleading concepts.

------

## 1. 文档目的与适用范围 | Purpose and Scope

### 1.1 文档目的 | Purpose

- 明确 v0.2.x 基线与 v0.3.x+ 阶段公共头文件的命名原则
- 防止头文件命名破坏既有模块边界
- 避免通过名称引入未经设计讨论的概念
- 为接口稳定性与未来版本演进提供清晰约束
- Define naming principles for public headers in the v0.2.x baseline and v0.3.x+ stage
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

自 v0.2.x 起，并在 v0.3.x+ 中继续适用，这些承诺应：

- 与已建立的模块职责保持一致
- 反映稳定的接口语义
- 避免泄露内部实现结构

Starting from v0.2.x, and still applying in v0.3.x+, these commitments must:

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

- core 模块承载长期稳定、可复用的底层数值基础能力
- core 可以包含 mesh、material、assembly、boundary、linear_algebra、solver 等跨 examples/cases 复用的基础语义
- core 不应包含示例专属、case 专属或配置入口专属的语义
- The core module carries long-term stable and reusable low-level numerical capabilities
- Core may contain reusable foundational semantics such as `mesh`, `material`, `assembly`, `boundary`, `linear_algebra`, and `solver`
- Core must not contain example-specific, case-specific, or configuration-entry semantics

### 3.2 v0.2.x 基线与 v0.3.x+ core 头文件 | Core Headers in the v0.2.x Baseline and v0.3.x+

在 v0.2.x 阶段，core 模块的公共头文件保持最小集合，主要承载基础设施语义。
在 v0.3.x+ 阶段，core 开始接收由真实教学示例牵引出的可复用数值能力，因此允许出现稳定、通用、跨问题复用的数值基础头文件。

典型示例包括：

- version.hpp（版本信息）
- export.hpp（符号导出与可见性控制）
- platform.hpp（平台相关定义）
- types.hpp（基础类型定义）
- error.hpp（基础错误类型，如需要）
- mesh.hpp（通用离散对象与简单网格构造）
- material.hpp（通用材料/参数容器与基础属性表达）
- assembly.hpp（通用贡献汇总/矩阵向量装配入口）
- boundary.hpp（边界条件施加的通用工具）
- linear_algebra.hpp（小型线性代数数据结构与操作）
- solver.hpp（通用求解器基础能力）

上述头文件应表达稳定的基础能力，而不是某个示例的完整算法。示例专属名称（例如 `poisson_basic`）不应进入 core。

In v0.2.x, public headers in the core module remain minimal and mainly carry infrastructure semantics.
In v0.3.x+, core begins to receive reusable numerical capabilities driven by real teaching examples, so stable and problem-independent numerical foundation headers are allowed.

Typical examples include:

- version.hpp (version information)
- export.hpp (symbol export and visibility control)
- platform.hpp (platform-related definitions)
- types.hpp (basic type definitions)
- error.hpp (basic error types, if necessary)
- mesh.hpp (generic discrete objects and simple mesh construction)
- material.hpp (generic material/parameter containers and foundational property representation)
- assembly.hpp (generic contribution accumulation / matrix-vector assembly entry points)
- boundary.hpp (generic tools for applying boundary conditions)
- linear_algebra.hpp (small linear algebra data structures and operations)
- solver.hpp (generic solver foundations)

These headers should express stable foundational capabilities rather than the full algorithm of one example. Example-specific names such as `poisson_basic` must not enter core.

> 注：上述列表为指导性示例，并非强制穷举；任何新增名称都应接受严格审视。
> Note: The above list is illustrative, not exhaustive; any additional names require careful scrutiny.

### 3.3 不应出现在 core 模块中的语义 | Concepts Not Belonging to core

以下类型的语义通常不属于 core 模块职责，因此不应在 core 的公共头文件中出现：

- config.hpp
- case.hpp
- results.hpp
- run_poisson_basic.hpp
- poisson_basic.hpp

这些名称通常代表更高层语义，应由上层模块（如 api 或 future domain modules）承担。

The following semantic concepts generally do not belong to the responsibility of the core module and therefore should not appear as public headers in core:

- config.hpp
- case.hpp
- results.hpp
- run_poisson_basic.hpp
- poisson_basic.hpp

These names typically represent higher-level semantics and should be owned by upper modules such as api or future domain modules.

------

## 4. api 模块头文件命名规则 | api Module Header Rules

### 4.1 api 模块的语义角色 | Semantic Role

- api 模块用于表达系统对外可见的执行意图与使用接口。
- 在 v0.3.x+ 阶段，api 模块继续作为 core 的唯一对外调用边界，并承载 examples 与 cases 的不同入口职责。
- The api module expresses user-visible execution intent and usage interfaces.
- In the v0.3.x+ stage, the api module continues to be the only external calling boundary for core, and it carries the different entry responsibilities of examples and cases.

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
