# 编码指南 | Coding Guide

> **Status**: Draft (v0.1.x)
>
> 本文档定义 PeriSci 项目的**编码层级原则与约定**，重点关注长期可维护性、架构一致性与治理边界。
>
> 本文档并非穷尽式规范，而是作为“方向性与约束性”的编码指南，细节可随版本演进逐步补充。
>
> 除本文档所述的编码原则外，PeriSci 还定义了一份项目级一致性对照表，用于约束目录结构、CMake target、公有头文件路径与 C++ 命名空间之间的对应关系。详见 [docs/specs/consistency_matrix.m](docs/specs/consistency_matrix.m)。
>
> 对于 v0.1.x 骨架阶段中临时 stub 实现的命名规范、内容约束与生命周期管理，项目定义了专门的阶段性规范文档。详见 [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md)。
>
> PeriSci 在 v0.1.x 阶段对公共头文件的命名设定了专门的项目级规范，用于约束接口语义的暴露范围，避免通过名称提前承诺未来能力。详见 [docs/specs/header_naming.md](docs/specs/header_naming.md)。
>
> This document defines the *project-level coding principles and conventions* for PeriSci.
> It focuses on long-term maintainability, architectural consistency, and governance boundaries.
>
> In addition to the coding principles described here, PeriSci defines a project-level consistency matrix covering directory layout, CMake targets, public include paths, and C++ namespaces. See [docs/specs/consistency_matrix.m](docs/specs/consistency_matrix.m) for details.
>
> PeriSci defines a dedicated phase-specific specification for naming, content constraints, and lifecycle management of temporary stub implementations during the v0.1.x skeleton phase. See [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md) for details.
>
> PeriSci defines a dedicated project-level specification for public header naming during v0.1.x, to constrain exposed interface semantics and avoid premature capability commitments through naming. See [docs/specs/header_naming.md](docs/specs/header_naming.md) for details.

------

## 1. 适用范围与目标 | Scope and Intent

### 1.1 本文档是什么 | What This Document Is

- 为 PeriSci 中 C++ 与 CMake 代码提供统一参考
- 将“隐含共识”显式化
- 防止长期演进中的编码风格与结构漂移
- A shared reference for contributors writing C++ and CMake code in PeriSci
- A place to make *implicit conventions explicit*
- A guardrail against long-term coding style and structural drift

### 1.2 本文档不是什么 | What This Document Is Not

- 不替代 `.clang-format` 或 `.editorconfig`
- 不构成 API 或详细设计文档
- 不作为 C++ / CMake 教程
- Not a replacement for `.clang-format` or `.editorconfig`
- Not a detailed API or design specification
- Not a tutorial on C++ or CMake usage

------

## 2. 通用编码原则 | General Coding Principles

### 2.1 清晰优先于技巧 | Clarity Over Cleverness

- 优先选择可读、直观的实现
- 避免不必要的模板元编程或宏技巧
- Prefer readable, explicit code over clever or condensed constructs
- Avoid unnecessary template metaprogramming or macro tricks

### 2.2 稳定优先于便利 | Stability Over Convenience

- 避免引入增加长期维护成本的实现方式
- 不以短期便利驱动架构决策
- Avoid introducing constructs that complicate long-term maintenance
- Short-term convenience should not dictate architectural decisions

### 2.3 明确边界 | Explicit Boundaries

- 明确模块依赖与职责边界
- 尽量避免跨层访问，必要时需有明确理由 （分层细节与调用方式参见 [ARCHITECTURE.md](ARCHITECTURE.md)）
- Dependencies and responsibilities must be explicit
- Cross-layer access should be minimized and justified （Details on layering and access methods, please refer to [ARCHITECTURE.md](ARCHITECTURE.md)）

------

## 3. C++ 语言约定 | C++ Language Conventions

### 3.1 语言标准 | Language Standard

- PeriSci 以 **C++17** 作为基准语言标准
- 不应擅自使用更新标准特性，除非形成明确共识
- PeriSci targets **C++17** as the baseline standard
- Newer language features should not be used unless explicitly agreed

### 3.2 头文件约定 | Header Files

- 统一使用 `#pragma once`
- 头文件应自包含，显式包含所需依赖
- Use `#pragma once` for all headers
- Headers should be self-contained and include what they use

### 3.3 include 顺序 | Include Order

推荐顺序：

1. C++ 标准库头文件
2. 第三方库头文件
3. PeriSci 项目头文件

不同分组之间应空行分隔。

Recommended order:

1. C++ standard library headers
2. Third-party library headers
3. PeriSci project headers

Each group should be separated by a blank line.

### 3.4 命名约定 | Naming Conventions

- 类型（类、结构体）：`PascalCase`
- 函数与变量：`snake_case`
- 常量：`kConstantName` 或 `UPPER_CASE`
- Types (classes, structs): `PascalCase`
- Functions and variables: `snake_case`
- Constants: `kConstantName` or `UPPER_CASE`

------

## 4. 错误处理与断言 | Error Handling and Assertions

### 4.1 错误处理原则 | Error Handling Philosophy

- 优先使用显式错误处理
- 在 v0.x 阶段，原则上避免使用异常，除非有充分理由
- Prefer explicit error handling over implicit behavior
- In v0.x, exceptions should be avoided unless clearly justified

### 4.2 断言 | Assertions

- 可使用 `assert` 表达与检查不变量
- 断言不应替代正常的错误处理逻辑
- `assert` may be used to document and enforce invariants
- Assertions should not replace proper error handling

------

## 5. 模块与分层边界 | Module and Layer Boundaries

### 5.1 core 层 | core Layer

- 不得依赖 `api`、`python` 或应用层代码
- 应尽量减少外部依赖
- Must not depend on `api`, `python`, or application-level code
- Should minimize external dependencies

### 5.2 api 层 | api Layer

- 作为 `core` 之上的稳定接口层
- 不应泄露 core 内部实现细节
- Serves as a stable interface over `core`
- Should avoid leaking internal core implementation details

------

## 6. CMake 约定 | CMake Conventions

### 6.1 基于 target 的设计 | Target-Based Design

- 优先使用 `target_*` 系列命令
- 避免使用全局 `include_directories()` 或编译选项
- Prefer `target_*` commands over global commands
- Avoid `include_directories()` and global compile options

### 6.2 可见性控制 | Visibility

- 合理使用 `PUBLIC`、`PRIVATE`、`INTERFACE`
- 依赖关系应准确反映实际使用情况
- Use `PUBLIC`, `PRIVATE`, `INTERFACE` appropriately
- Dependencies should reflect actual usage

### 6.3 构建配置 | Build Configuration

- 默认假设使用单配置生成器（如 Ninja）
- Debug/Release 在配置阶段确定
- Single-config generators (e.g. Ninja) are assumed
- Debug/Release selection is handled at configure time

------

## 7. 格式与工具 | Formatting and Tooling

### 7.1 格式化权威 | Formatting Authority

- `.clang-format` 是 C++ 格式的唯一权威
- `.editorconfig` 负责基础文本规范
- `.clang-format` is the single source of truth for C++ formatting
- `.editorconfig` governs basic text conventions

### 7.2 工具说明 | Tooling

- 编辑器与 IDE 为个人选择
- 项目规范不得依赖特定编辑器配置
- Editors and IDEs are user choice
- Project-level rules must not depend on editor-specific settings

------

## 8. 演进与治理 | Evolution and Governance

### 8.1 活文档 | Living Document

- 本指南将随 PeriSci 演进而更新
- 涉及架构方向的变更应通过 ADR 记录
- This guide may evolve as PeriSci matures
- Changes affecting architectural direction should be recorded via ADRs

### 8.2 克制优先 | Minimalism First

- 早期版本避免过度规范化
- 优先采用渐进式细化，而非僵硬规则
- Avoid over-specification in early versions
- Prefer incremental refinement over rigid rules

------

## 9. 结语 | Closing Notes

本文档旨在提供共同方向，而非限制有思考的贡献。
如有疑问，请优先考虑清晰性、可复现性与长期可维护性。

This document aims to provide shared direction, not restrict thoughtful contributions.
When in doubt, prioritize clarity, reproducibility, and long-term maintainability.

