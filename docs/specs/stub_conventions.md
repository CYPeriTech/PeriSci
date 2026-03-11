# Stub 约定与生命周期规范 | Stub Conventions and Lifecycle

> 本文档规定 **PeriSci v0.2.x 阶段** 中 stub 文件的命名、用途与生命周期管理规则。
> Stub 在 PeriSci 中被视为一种 **受控的临时工程工具**，仅用于在特定开发阶段维持结构完整性，而不应成为长期实现的一部分。
>
> This document defines the naming, usage, and lifecycle rules for stub files in **PeriSci v0.2.x**.
> In PeriSci, stubs are treated as **controlled temporary engineering tools** used to maintain structural completeness during development, and must not become long-term implementations.

------

## 1. 文档目的与适用范围 | Purpose and Scope

### 1.1 文档目的 | Purpose

本规范的目标是：

- 明确 **stub 在 v0.2.x 阶段的合法使用场景**
- 防止临时实现演变为长期技术债
- 确保 stub 不会掩盖真实实现缺失
- 为 stub 的引入、审查与移除提供统一规则

The goals of this specification are to:

- Define **legitimate use cases of stubs during v0.2.x**
- Prevent temporary implementations from becoming technical debt
- Ensure stubs do not hide missing real implementations
- Provide unified rules for stub introduction, review, and removal

------

### 1.2 适用范围 | Scope

本规范适用于：

- PeriSci 项目中的 **C++ 源文件 stub**
- 用于维持模块结构完整性的 **占位实现**

不适用于：

- 单元测试 mock
- 示例代码
- 真实实现的最小版本

This specification applies to:

- **C++ source stubs** used in PeriSci
- Placeholder implementations used to preserve module structure

It does **not** apply to:

- Unit-test mocks
- Example code
- Minimal but real implementations

------

## 2. Stub 的历史背景 | Historical Context

### 2.1 v0.1.x Skeleton Phase

在 **v0.1.x 骨架阶段**，stub 被广泛使用，其目标是：

- 固定模块结构
- 允许最小系统编译运行
- 延迟真实实现

During the **v0.1.x skeleton phase**, stubs were widely used to:

- Establish module structure
- Allow the system to compile and run
- Defer real implementations

------

### 2.2 v0.2.x Development Phase

在 **v0.2.x 阶段**：

- 系统架构已经稳定
- 模块边界已经建立
- 真实功能开始实现

因此：

**stub 不再是默认允许的实现形式。**

Stub 仅允许在 **明确、受控且短期的开发场景中存在**。

In **v0.2.x**:

- The system architecture is already stable
- Module boundaries are defined
- Real functionality begins to be implemented

Therefore:

**stubs are no longer the default implementation form.**

They are allowed only in **explicit, controlled, short-lived development situations**.

------

## 3. 什么是 Stub | What Is a Stub

### 3.1 Stub 的定义 | Definition

Stub 是一种 **占位实现（placeholder implementation）**，其目的在于：

- 维持模块结构完整
- 保证构建系统能够成功编译
- 为未来真实实现预留接口位置

A stub is a **placeholder implementation** used to:

- Maintain module structural integrity
- Allow the project to compile successfully
- Reserve a location for future real implementations

------

### 3.2 Stub 不是 | What a Stub Is Not

Stub 不应被用于：

- 半成品实现
- 临时解决方案的长期保留
- 提前引入未来复杂逻辑
- 规避实现难度

A stub must **not** be used as:

- A partial implementation
- A long-term placeholder
- A container for future complex logic
- A workaround for unfinished design

------

## 4. Stub 使用条件 | Conditions for Using Stubs

在 v0.2.x 阶段，引入 stub **必须满足至少一个条件**：
During the v0.2.x phase, introducing a stub **MUST satisfy at least one of the following conditions**:

### 4.1 架构占位 | Architectural Placeholder

当模块结构已经确定，但实现尚未开始。
When the module structure has already been defined, but the actual implementation has not yet started.

例如：
```
api module defined
core functionality pending
```

For example:
```
api module defined
core functionality pending
```

------

### 4.2 构建系统需求 | Build System Requirement

为了：

- 保证 CMake target 可生成
- 保证 CI 可以通过

In order to:

- ensure that the **CMake target can be generated**
- ensure that the **CI pipeline can pass**

------

### 4.3 开发顺序解耦 | Development Order Decoupling

当两个模块存在开发顺序依赖时：

```
module A depends on B
but B not implemented yet
```

可以使用 stub 作为 **短期占位**。

When two modules have a development-order dependency:

```
module A depends on B
but B not implemented yet
```

In such cases, a stub may be used as a short-term placeholder.

------

## 5. Stub 命名规范 | Stub Naming Conventions

### 5.1 文件命名 | File Naming

Stub 源文件 **必须** 使用 `_stub` 后缀：
Stub source files **must** use the `_stub` suffix: 

```
core_stub.cpp
api_stub.cpp
solver_stub.cpp
```

禁止使用：
Ambiguous naming is prohibited: 

```
*_temp.cpp
*_dummy.cpp
*_test.cpp
*_placeholder.cpp
```

------

### 5.2 头文件约定 | Header Files

- Stub 通常不引入新的公共头文件
- 若必须存在头文件，其命名也应明确反映 stub 性质
- Stubs should not introduce new public headers
- If a header is unavoidable, its name must clearly reflect stub nature

------

## 6. Stub 内容约束 | Stub Implementation Constraints

### 6.1 允许的内容 | Allowed Contents

- 最小可编译、可链接的函数或类定义
- 明确标注为占位的返回值或行为
- 清晰的 TODO 注释，指向未来替换计划
- Minimal function or class definitions needed for compilation and linking
- Clearly marked placeholder return values or behavior
- Explicit TODO comments pointing to future replacement

------

### 6.2 禁止的内容 | Prohibited Contents

- 复杂算法实现
- 真实业务逻辑
- 提前引入未来阶段的核心概念
- 引入重型第三方依赖
- 隐式状态管理
- Complex algorithm implementations
- Real business logic
- Premature introduction of future-stage core concepts
- Heavy third-party dependencies
- hidden state

------

## 7. Stub 生命周期管理 | Stub Lifecycle Management

### 7.1 生命周期原则 | Lifecycle Principles

在 v0.2.x 中：

```
stub = 短期工程工具
```

必须遵循：

```
introduce → review → replace → remove
```

In **v0.2.x**:

```
stub = short-term engineering tool
```

The lifecycle must follow:

```
introduce → review → replace → remove
```


------

### 7.2 替换策略 | Replacement Strategy

当真实实现完成时：

```
*_stub.cpp → real implementation
```

并且：

```
必须移除 _stub 命名
```

When the real implementation is completed:

```
*_stub.cpp → real implementation
```

And:

```
the _stub naming must be removed
```


------

### 7.3 长期 stub 处理 | Long-lived Stubs

如果 stub 在代码库中存在时间较长：

必须：

- 在 issue tracker 中登记
- 标记为 **technical debt**

If a stub remains in the codebase for an extended period:

It must:

- be registered in the issue tracker
- be marked as **technical debt**


------

## 8. Review 与治理 | Review and Governance

### 8.1 Review 要点 | Review Checklist

在 code review 中，任何 stub 应至少回答以下问题：

- 为什么在当前阶段需要 stub？
- 它是否遵循最小实现原则？
- 是否存在清晰的替换路径？

During code review, any stub must answer:

- Why is a stub needed at this stage?
- Does it adhere to minimal implementation principles?
- Is there a clear replacement path?

### 8.2 治理接口 | Governance Interface

- Stub 相关的重要策略调整，应通过 ADR 记录
- 当 stub 影响架构边界时，必须进行显式讨论
- Significant changes to stub policy should be recorded via ADRs
- Stubs affecting architectural boundaries must be explicitly discussed

------

## 9. 架构治理 | Architectural Governance

Stub 的存在不应改变系统的架构语义，也不应被用作绕过既有设计契约的手段。
The existence of stubs must not alter the architectural semantics of the system, nor should they be used as a means to bypass established design contracts.

在 PeriSci 中，stub 仅被视为一种**工程层面的临时实现工具**，其作用是维持模块结构的完整性，而不是参与架构设计或接口决策。
In PeriSci, stubs are treated strictly as **temporary engineering tools at the implementation level**. Their role is to preserve the structural integrity of modules, not to participate in architectural design or interface decisions.

因此，stub 的引入与使用必须遵循以下原则：
Therefore, the introduction and use of stubs must follow the principles below.

### 9.1 不改变架构语义 | No Changes to Architectural Semantics

Stub 不得：

- 改变既有模块的职责边界
- 引入新的模块依赖关系
- 改变既定的调用方向或层级关系

换言之，stub 只能占据**已经确定的结构位置**，而不能创造新的架构结构。

A stub must not:

- change the responsibility boundaries of existing modules
- introduce new module dependency relationships
- alter the established direction of calls or layering relationships

In other words, a stub may only occupy an **already defined structural position**, and must not create new architectural structure.

------

### 9.2 不隐含接口设计决策 | No Implicit Interface Design Decisions

Stub 不得：

- 提前定义尚未讨论或确认的公共接口
- 通过占位实现暗示未来 API 形态
- 固化尚未稳定的接口命名或参数结构

接口设计应通过正常的设计讨论与评审流程确定，而不是通过 stub 的形式隐式形成。

A stub must not:

- define public interfaces that have not yet been discussed or confirmed
- imply future API shapes through placeholder implementations
- prematurely solidify interface names or parameter structures that are not yet stable

Interface design must be determined through the normal design discussion and review process, rather than implicitly emerging through stubs.

------

### 9.3 不引入新的架构假设 | No Introduction of New Architectural Assumptions

Stub 不得：

- 假定未来模块实现方式
- 假定未来数据结构或算法形式
- 假定未来系统扩展路径

Stub 的实现应保持**最小语义**，避免对未来架构演进施加隐含约束。

A stub must not:

- assume how future modules will be implemented
- assume future data structures or algorithmic forms
- assume the future system extension path

Stub implementations should maintain **minimal semantics**, avoiding implicit constraints on future architectural evolution.

------

### 9.4 架构影响的治理路径 | Governance Path for Architectural Impact

如果某个 stub 的引入：

- 影响模块边界
- 影响系统分层
- 涉及接口设计方向
- 或可能改变系统架构语义

则该变更不应仅通过代码提交完成，而必须通过 **ADR（Architecture Decision Record）** 进行显式记录与讨论。

通过 ADR 的方式，可以确保：

- 架构决策具有可追溯性
- 设计演进具有明确记录
- 临时实现不会隐式改变系统结构

If the introduction of a stub:

- affects module boundaries
- affects system layering
- involves interface design direction
- or may alter the architectural semantics of the system

then the change must not be introduced solely through a code commit.
Instead, it must be explicitly recorded and discussed through an **ADR (Architecture Decision Record)**.

Using ADR ensures that:

- architectural decisions remain traceable
- design evolution is explicitly documented
- temporary implementations cannot implicitly change system structure

------

### 9.5 治理原则总结 | Governance Principle Summary

简而言之：

```
stub 用于维持结构，而不是定义架构
```

当 stub 开始影响架构语义时，它就不再只是 stub，而应被视为一次正式的架构决策。

In short:

```
stubs preserve structure, they do not define architecture
```

When a stub begins to affect architectural semantics, it is no longer merely a stub, but should instead be treated as a formal architectural decision.

------

## 10. 结语 | Closing Notes

Stub 的价值在于为未来留出空间，而非占据未来。
The value of a stub lies in preserving room for the future, not occupying it.