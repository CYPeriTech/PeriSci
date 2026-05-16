# 编码指南 | Coding Guide

> **Status**: Active Draft (v0.3.x+)
>
> 本文档定义 PeriSci 项目的**编码层级原则与约定**，重点关注长期可维护性、架构一致性与治理边界。
>
> 本文档并非穷尽式规范，而是作为“方向性与约束性”的编码指南，细节可随版本演进逐步补充。
>
> 除本文档所述的编码原则外，PeriSci 还定义了一份项目级一致性对照表，用于约束目录结构、CMake target、公有头文件路径与 C++ 命名空间之间的对应关系。详见 [docs/specs/consistency_matrix.md](docs/specs/consistency_matrix.md)。
>
> 对于历史 stub 实现的命名规范、内容约束、生命周期管理，以及 v0.3.x+ 中逐步替换 stub 的要求，项目定义了专门规范文档。详见 [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md)。
>
> PeriSci 对公共头文件的命名设定了专门的项目级规范，用于约束接口语义的暴露范围，避免通过名称提前承诺未来能力。详见 [docs/specs/header_naming.md](docs/specs/header_naming.md)。
>
> This document defines the *project-level coding principles and conventions* for PeriSci.
> It focuses on long-term maintainability, architectural consistency, and governance boundaries.
>
> In addition to the coding principles described here, PeriSci defines a project-level consistency matrix covering directory layout, CMake targets, public include paths, and C++ namespaces. See [docs/specs/consistency_matrix.m](docs/specs/consistency_matrix.m) for details.
>
> PeriSci defines a dedicated specification for naming, content constraints, lifecycle management of historical stubs, and their gradual replacement in v0.3.x+. See [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md) for details.
>
> PeriSci defines a dedicated project-level specification for public header naming, to constrain exposed interface semantics and avoid premature capability commitments through naming. See [docs/specs/header_naming.md](docs/specs/header_naming.md) for details.

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

### 3.4 命名约定（v0.3.x+）| Naming Conventions for v0.3.x+

从 v0.3.x 开始，PeriSci 进入真实 `core/api/examples/cases` 能力生长阶段。
命名规则不再只是骨架阶段的临时风格，而是长期可读性、教学一致性与开源协作的基础约束。

Starting from v0.3.x, PeriSci enters the stage where real `core/api/examples/cases`
capabilities begin to grow. Naming conventions are no longer temporary skeleton
style choices; they are baseline constraints for readability, teaching consistency,
and open-source collaboration.

#### 3.4.1 C++ 符号命名 | C++ Symbol Naming

| 对象 | 规则 | 示例 |
| --- | --- | --- |
| 命名空间 | `lowercase` | `perisci::core`, `perisci::api` |
| 类型 / `struct` / `class` | `UpperCamelCase` | `Mesh`, `FiniteElementSpace`, `GridFunction`, `LinearSystem` |
| 函数 / 自由函数 | `lower_snake_case` | `make_structured_quad_mesh`, `conjugate_gradient` |
| 成员函数 | `lower_snake_case` | `num_dofs`, `residual_norm` |
| 局部变量 | `lower_snake_case` | `cells_per_axis`, `residual_norm` |
| 成员变量 | `lower_snake_case` | `num_cells`, `center_value` |
| 普通 C++ 常量 / `constexpr` 变量 | `lower_snake_case` | `gauss_point`, `relative_tolerance` |
| 宏常量 / 编译开关 | `UPPER_CASE` | `PERISCI_USE_EXPERIMENTAL_FEATURE` |
| 枚举类型 | `UpperCamelCase` | `Status`, `ElementType` |
| 枚举值 | `lower_snake_case` | `success`, `partial`, `failed` |

普通 C++ 常量、`constexpr` 变量和数值参数常量与普通变量采用相同的
`lower_snake_case` 规则。PeriSci 不采用 `kConstantName` 作为默认常量命名风格；
`UPPER_CASE` 仅保留给宏常量、预处理器符号和编译开关。

这个约定的核心考虑是：在有限元、近场动力学和耦合模型代码中，许多常量本质上是数学参数。
例如 `young_modulus`、`poisson_ratio`、`relative_tolerance`、`time_step`。
它们使用 `lower_snake_case` 更接近公式和教学叙事，也避免在数值表达中引入不必要的工程前缀。

Ordinary C++ constants, `constexpr` variables, and numerical parameter constants
follow the same `lower_snake_case` rule as ordinary variables. PeriSci does not
use `kConstantName` as the default constant naming style; `UPPER_CASE` is reserved
for macro constants, preprocessor symbols, and compile-time feature switches.

The rationale is that many constants in finite element, peridynamics, and coupled
modeling code are mathematical parameters. Names such as `young_modulus`,
`poisson_ratio`, `relative_tolerance`, and `time_step` read more naturally in
teaching code and numerical formulas than engineering-prefixed alternatives.

#### 3.4.2 文件、target 与可执行文件命名 | File, Target, and Executable Naming

| 对象 | 规则 | 示例 |
| --- | --- | --- |
| C++ 头文件 | `lower_snake_case.hpp` | `linear_algebra.hpp`, `finite_element_space.hpp` |
| C++ 源文件 | `lower_snake_case.cpp` | `linear_algebra.cpp`, `assembly.cpp` |
| CMake target | `perisci_<feature>` | `perisci_poisson_basic` |
| 可执行文件输出名 | `perisci-<feature>` | `perisci-poisson-basic` |
| example 目录 | `ex-XX-keyword` | `ex-03-poisson-basic` |
| case 目录 | `case-XX-keyword` | `case-01-poisson-2d-basic` |

#### 3.4.3 core 命名原则 | core Naming Principles

`core/` 中的名称必须表达可复用数值能力，而不是表达某个具体 example。

Names in `core/` must express reusable numerical capabilities, not individual examples.

推荐方向：

```text
mesh
finite_element_space
grid_function
assembly
linear_algebra
solver
boundary
```

避免方向：

```text
poisson_basic
poisson_error
poisson_refinement
```

也就是说，`ex-03-poisson-basic`、`ex-04-poisson-error` 和
`ex-05-poisson-refinement` 应复用同一组 core 能力，而不是在 core 中各自形成同名实现文件。

In other words, `ex-03-poisson-basic`, `ex-04-poisson-error`, and
`ex-05-poisson-refinement` should reuse the same core capabilities instead of
creating example-named implementation files in `core`.

#### 3.4.4 风格来源 | Style Sources

PeriSci 的命名风格综合吸收两类经验：

- 类型名吸收 MFEM 的清晰对象语言，例如 `Mesh`、`FiniteElementSpace`、`GridFunction`；
- 函数名吸收 deal.II 的可读流程表达，例如 `make_grid`、`setup_system`、`assemble_system`。

因此，PeriSci 的总体风格是：

```text
类型像 MFEM 一样语义直接；
函数像 deal.II 一样 lower_snake_case、清楚可读；
examples 和 cases 的目录按教学与资产职责命名；
core 按可复用数值能力命名。
```

PeriSci naming draws from both MFEM and deal.II:

- type names follow MFEM-like clear object language, e.g. `Mesh`,
  `FiniteElementSpace`, and `GridFunction`;
- function names follow deal.II-like readable workflow language, e.g. `make_grid`,
  `setup_system`, and `assemble_system`.

The resulting project style is:

```text
types are semantically direct like MFEM;
functions are lower_snake_case and readable like deal.II;
examples and cases are named by teaching and asset responsibilities;
core is named by reusable numerical capabilities.
```

### 3.5 注释与文档语言规则（v0.3.x+）| Comment and Documentation Language Rules

PeriSci 同时服务两个目标：中文教学友好，以及面向开源生态的长期协作。
因此，代码注释、示例说明和架构规范不采用同一种语言策略，而是按职责分层。

PeriSci serves two goals at the same time: Chinese-first teaching accessibility
and long-term collaboration in an open-source ecosystem. Therefore, code comments,
example explanations, and architecture specifications follow different language
rules according to their responsibilities.

#### 3.5.1 C++ 代码注释 | C++ Code Comments

C++ 源文件和头文件中的注释应以英文为主。

C++ source and header comments should be English-first.

推荐：

```cpp
// Apply homogeneous Dirichlet boundary conditions.
```

不推荐在每一条代码注释中机械地中英文双写。代码注释应短、清楚、贴近实现，
用于解释局部意图、边界条件或不容易直接从代码读出的数值处理。

Avoid mechanically duplicating every code comment in both Chinese and English.
Code comments should be short, clear, and close to the implementation. They should
explain local intent, boundary conditions, or numerical details that are not
obvious from the code itself.

#### 3.5.2 公共 API 与长期概念 | Public APIs and Long-Term Concepts

当注释定义 PeriSci 长期概念、架构边界或项目特有术语时，可以采用中英文并列，
但应保持克制，避免把代码文件变成完整教程。

When comments define long-term PeriSci concepts, architectural boundaries, or
project-specific terminology, bilingual wording may be used, but it should be
used sparingly. Source files should not become full tutorials.

适用场景包括：

- 三梁 / Three-Beam execution structure；
- 四核 / Four-Core numerical structure；
- `examples -> api -> core` 与 `cases -> run_case -> core` 的边界；
- public API 的稳定语义说明。

Typical cases include:

- Three-Beam execution structure;
- Four-Core numerical structure;
- `examples -> api -> core` and `cases -> run_case -> core` boundaries;
- stable semantics of public APIs.

#### 3.5.3 examples README | examples README Files

`examples/*/README.md` 应采用中文优先，以服务教学、学习路径和中文用户理解。
必要时可以保留英文术语、API 名称、数学符号和命令行文本。

`examples/*/README.md` should be Chinese-first to support teaching, learning
paths, and Chinese readers. English terms, API names, mathematical notation, and
command-line text may be retained when appropriate.

#### 3.5.4 架构与规范文档 | Architecture and Specification Documents

`docs/` 中涉及长期架构、契约、治理、版本、规范和 ADR 的文档，原则上应采用中英文并列。
这样既保留中文语义，又逐步稳定英文概念，方便后续开源协作、引用和评审。

Documents under `docs/` that define long-term architecture, contracts, governance,
versioning, specifications, or ADRs should generally be bilingual. This preserves
Chinese semantics while gradually stabilizing English terminology for future
open-source collaboration, citation, and review.

#### 3.5.5 推荐分层 | Recommended Layering

```text
C++ source/header comments      English-first
public API concept comments     English-first, bilingual when defining long-term PeriSci concepts
examples README                 Chinese-first
architecture/spec docs          bilingual Chinese + English
```

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

