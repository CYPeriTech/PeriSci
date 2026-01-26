# 头文件命名规范 | Header Naming Conventions

> 本文档用于规定 **PeriSci v0.1.x 阶段** 公共头文件的命名规则与允许范围，以防止在骨架阶段过早引入概念性接口或破坏模块边界。
>
> This document defines naming rules and allowed scopes for public header files during **PeriSci v0.1.x**, preventing premature introduction of conceptual APIs or erosion of module boundaries.

------

## 1. 文档目的与适用范围 | Purpose and Scope

### 1.1 文档目的 | Purpose

- 明确哪些头文件名称在 v0.1.x 阶段是被允许的
- 防止 core 模块因头文件命名而隐式承诺未来能力
- 为后续版本的接口扩展保留足够设计空间
- Clarify which header names are allowed during v0.1.x
- Prevent the core module from implicitly committing to future capabilities
- Preserve sufficient design space for future interface evolution

### 1.2 适用范围 | Scope

- 本规范仅约束 **公共头文件**（public headers）
- 不约束 `src/` 下的私有实现文件
- This specification applies only to **public headers**
- Private implementation files under `src/` are not covered

------

## 2. 总体命名原则 | General Naming Principles

### 2.1 最小暴露原则 | Minimal Exposure Principle

- 公共头文件的命名即构成对外语义承诺
- v0.1.x 阶段应尽量减少此类承诺的数量与范围
- Public header names constitute semantic commitments
- During v0.1.x, such commitments should be minimized

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

### 3.2 v0.1.x 阶段允许的头文件名称 | Allowed Header Names in v0.1.x

以下为 **core 模块在 v0.1.x 阶段允许出现的典型头文件名称**：

- `version.hpp`（版本信息）
- `export.hpp`（符号导出与可见性控制）
- `platform.hpp`（平台与编译环境相关定义，如需要）
- `types.hpp`（基础类型别名，如确有必要）

The following are **typical header names allowed in the core module during v0.1.x**:

- `version.hpp` (version information)
- `export.hpp` (symbol export and visibility control)
- `platform.hpp` (platform/build environment definitions, if needed)
- `types.hpp` (basic type aliases, if strictly necessary)

> 注：上述列表为指导性示例，并非强制穷举；
> 任何新增名称都应接受严格审视。
>
> Note: The above list is illustrative, not exhaustive;
> any additional names require careful scrutiny.

### 3.3 明确禁止的头文件名称 | Explicitly Prohibited Names

在 v0.1.x 阶段，core 模块 **禁止** 出现如下类型的头文件名称：

- `mesh.hpp`
- `material.hpp`
- `solver.hpp`
- `config.hpp`
- `case.hpp`
- `results.hpp`

During v0.1.x, the following categories of header names are **explicitly prohibited** in the core module:

- `mesh.hpp`
- `material.hpp`
- `solver.hpp`
- `config.hpp`
- `case.hpp`
- `results.hpp`

这些名称通常意味着高层语义或对未来能力的提前承诺。

These names typically imply higher-level semantics or premature commitments.

------

## 4. api 模块头文件命名规则 | api Module Header Rules

### 4.1 api 模块的语义角色 | Semantic Role

- api 模块用于表达对外可见的执行意图与使用接口
- 允许出现描述“用例、配置、结果”等语义的头文件
- The api module expresses user-facing intent and usage interfaces
- Headers describing cases, configuration, or results are allowed

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

------

## 6. 结语 | Closing Notes

头文件命名是最早形成“技术承诺”的接口层。
在 v0.1.x 阶段保持克制，是为未来留下自由度。

Header naming is the earliest form of technical commitment.
Restraint during v0.1.x preserves freedom for future evolution.