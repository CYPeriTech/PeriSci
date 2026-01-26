# Stub 约定与生命周期规范 | Stub Conventions and Lifecycle

> 本文档用于规范 **PeriSci v0.1.x 骨架阶段** 中 stub 文件的命名、用途与生命周期，
> 以避免临时实现演变为长期技术债。
>
> This document defines naming, usage, and lifecycle rules for stub files
> during the **PeriSci v0.1.x skeleton phase**, preventing temporary placeholders
> from turning into long-term technical debt.

------

## 1. 文档目的与适用范围 | Purpose and Scope

### 1.1 文档目的 | Purpose

- 明确什么是 stub，以及为什么在 v0.1.x 阶段允许存在 stub
- 为所有 stub 提供统一、不可争议的命名与使用规范
- 确保 stub 是**阶段性工具**，而非被默认接受的长期实现
- Clarify what constitutes a stub and why stubs are allowed in v0.1.x
- Provide a unified, non-controversial naming and usage convention
- Ensure stubs remain **phase-specific tools**, not long-term implementations

### 1.2 适用范围 | Scope

- 本规范适用于 PeriSci v0.1.x 阶段的所有 stub 文件
- v0.2.x 及以后阶段，stub 的存在应受到更严格的审视
- This specification applies to all stub files in PeriSci v0.1.x
- In v0.2.x and later, the presence of stubs should be more strictly reviewed

------

## 2. 什么是 Stub | What Is a Stub

### 2.1 Stub 的定义 | Definition

Stub 是一种**占位实现**，其主要目的在于：

- 使模块、库或可执行目标在语义上“存在”
- 保证项目能够顺利编译、链接与运行最小示例
- 在不提前承诺真实实现细节的前提下，固定结构与边界

A stub is a **placeholder implementation** whose purpose is to:

- Make a module, library, or executable *exist* semantically
- Allow the project to compile, link, and run minimal examples
- Fix structure and boundaries without committing to real implementations

### 2.2 Stub 不是 | What a Stub Is Not

- 不是半成品实现
- 不是临时解决方案被“默认保留”的借口
- 不是提前引入未来功能或复杂依赖的容器
- Not a partial or provisional implementation
- Not an excuse to keep temporary solutions indefinitely
- Not a container for future functionality or complex dependencies

------

## 3. Stub 命名规范 | Stub Naming Conventions

### 3.1 文件命名 | File Naming

- Stub 源文件必须以 `_stub` 作为后缀
  - 示例：`core_stub.cpp`、`api_stub.cpp`
- 禁止使用如下不明确的命名：
  - `*_temp.cpp`、`*_dummy.cpp`、`*_test.cpp`
- Stub source files must use the `_stub` suffix
  - Examples: `core_stub.cpp`, `api_stub.cpp`
- Ambiguous names are prohibited:
  - `*_temp.cpp`, `*_dummy.cpp`, `*_test.cpp`

### 3.2 头文件约定 | Header Files

- Stub 通常不引入新的公共头文件
- 若必须存在头文件，其命名也应明确反映 stub 性质
- Stubs should not introduce new public headers
- If a header is unavoidable, its name must clearly reflect stub nature

------

## 4. Stub 内容约束 | Constraints on Stub Contents

### 4.1 允许的内容 | Allowed Contents

- 最小可编译、可链接的函数或类定义
- 明确标注为占位的返回值或行为
- 清晰的 TODO 注释，指向未来替换计划
- Minimal function or class definitions needed for compilation and linking
- Clearly marked placeholder return values or behavior
- Explicit TODO comments pointing to future replacement

### 4.2 禁止的内容 | Prohibited Contents

- 复杂业务逻辑或算法实现
- 提前引入未来阶段的核心概念
- 引入重型第三方依赖
- Complex business logic or algorithms
- Premature introduction of future-stage core concepts
- Heavy third-party dependencies

------

## 5. Stub 生命周期管理 | Stub Lifecycle Management

### 5.1 生命周期原则 | Lifecycle Principles

- Stub 仅在 v0.1.x 骨架阶段被视为合理存在
- 一旦某能力进入 v0.2.x 的正式开发范围，应尽快替换对应 stub
- Stubs are considered acceptable only during the v0.1.x skeleton phase
- Once a capability enters v0.2.x active development, corresponding stubs should be replaced

### 5.2 替换与移除 | Replacement and Removal

- Stub 替换为真实实现时，应一并移除 `_stub` 命名
- 若 stub 被长期保留，应被视为技术债并显式记录
- When replacing a stub with a real implementation, the `_stub` suffix must be removed
- Long-lived stubs should be treated as technical debt and explicitly tracked

------

## 6. Review 与治理 | Review and Governance

### 6.1 Review 要点 | Review Checklist

在 code review 中，任何 stub 应至少回答以下问题：

- 为什么在当前阶段需要 stub？
- 它是否遵循最小实现原则？
- 是否存在清晰的替换路径？

During code review, any stub must answer:

- Why is a stub needed at this stage?
- Does it adhere to minimal implementation principles?
- Is there a clear replacement path?

### 6.2 治理接口 | Governance Interface

- Stub 相关的重要策略调整，应通过 ADR 记录
- 当 stub 影响架构边界时，必须进行显式讨论
- Significant changes to stub policy should be recorded via ADRs
- Stubs affecting architectural boundaries must be explicitly discussed

------

## 7. 结语 | Closing Notes

Stub 的价值在于为未来留出空间，而非占据未来。

The value of a stub lies in preserving room for the future, not occupying it.