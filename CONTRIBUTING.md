# 贡献指南 | Contributing Guide

感谢你对 **PeriSci** 项目的关注与贡献意愿！

PeriSci 是一个以 **近场有限元法（PeriFEM）** 为核心的开源科学计算与工程仿真平台。  
我们欢迎来自学术界、工程界以及开源社区的理性、长期、建设性参与。

Thank you for your interest in contributing to **PeriSci**!

PeriSci is an open-source scientific computing and engineering simulation platform centered on the **PeriFEM (Peridynamics-based Finite Element Method)**.  
We welcome rational, long-term, and constructive contributions from
academia, industry, and the open-source community.

---

## 1. 项目阶段说明 | Project Stage

PeriSci 当前处于 **v0.2.x 阶段（接口冻结 / 架构稳定化阶段）**。

在这一阶段：

- 系统主架构与分层边界已基本确立
- 公共契约正在冻结，并以可复现、可验证为优先目标
- 接口与实现仍可能演进，但任何变更都应服从 **正确性、可复现性与设计一致性**

请在贡献前理解：**并非所有 Pull Request 都会被立即合并**，但每一份合理的贡献都会被认真评审。

PeriSci is currently in the **v0.2.x stage (interface-freeze / architectural stabilization stage)**.

At this stage:

- The system’s main architecture and layer boundaries have largely been established
- Public contracts are being frozen, with reproducibility and verifiability as the primary goals
- APIs and implementations may still evolve, but any change must remain consistent with **correctness, reproducibility, and architectural consistency**

Please note that **not all Pull Requests will be merged immediately**, but every reasonable contribution will be carefully reviewed.

---

## 2. 贡献类型 | Types of Contributions

我们欢迎以下类型的贡献：|  We welcome the following types of contributions:

### 🧮 2.1 数值方法与物理模型 | Numerical Methods and Physical Models
- 近场有限元（PeriFEM）相关算法
- 损伤、断裂、多物理场耦合模型
- 数值稳定性与计算收敛性改进
- Algorithms related to PeriFEM
- Damage, fracture, and multiphysics coupling models
- Improvements in numerical stability and energy consistency

### 📚 2.2 教学与示例 | Education and Examples
- 教学算例与最小工作示例（MVP）
- 可复现的基准算例（新增算例遵循 README的核心理念 中 算例驱动的生长模式）
- 面向学生的教程与说明
- Educational examples and minimal working cases
- Reproducible benchmark cases (The new cases follow the "case-driven growth model" as described in the README - Core Philosophy)
- Tutorials and documentation for students

### 🧪 2.3 测试与验证 | Testing and Validation
- 单元测试与回归测试
- 数值结果一致性验证
- 性能与稳定性测试
- Unit and regression tests
- Verification of numerical consistency
- Performance and stability tests

### 🛠 2.4 工程化改进 | Engineering Improvements
- 构建系统（CMake）
- CI / 自动化测试
- 代码可读性与可维护性提升
- Build system (CMake)
- CI and automated testing
- Code readability and maintainability



> ### 示例与算例的命名与组织规范 | Naming and Organization of Examples and Cases
>
> PeriSci 采用 `examples/` 与 `cases/` 分离的组织方式：
>
> - `examples/`：用于教学、演示、探索与孵化；
> - `cases/`：用于标准化、可复现、可回归的标准算例资产（canonical case assets）。
>
> PeriSci uses a split organization between `examples/` and `cases/`:
>
> - `examples/`: for teaching, demonstration, exploration, and incubation;
> - `cases/`: for standardized, reproducible, regression-ready canonical case assets.
>
> #### `examples/` 的命名规则 | Naming Convention for `examples/`
>
> `examples/` 下的目录应体现“示例 / 教学用途”，推荐使用：
>
> ```text
> ex-XX-short-description
> ```
>
> 其中：
>
> - `ex` 表示 example；
> - `XX` 为两位或三位数字，用于表示推荐学习顺序；
> - `short-description` 为简要、稳定的语义描述，使用小写字母与连字符（kebab-case）。
>
> 示例：
>
> - `ex-00-hello`
> - `ex-01-minimal-run`
> - `ex-02-linear-elasticity-demo`
>
> Directories under `examples/` should reflect their teaching / demonstration role and are recommended to use:
>
> ```text
> ex-XX-short-description
> ```
>
> where:
>
> - `ex` denotes an example;
> - `XX` indicates the recommended learning order;
> - `short-description` provides a concise and stable semantic description.
>
> Examples include:
>
> - `ex-00-hello`
> - `ex-01-minimal-run`
> - `ex-02-linear-elasticity-demo`
>
> #### `cases/` 的命名规则 | Naming Convention for `cases/`
>
> `cases/` 下的目录表示正式 canonical case assets，推荐使用：
>
> ```text
> case-XX-short-description
> ```
>
> 其中：
>
> - `case` 表示正式标准算例资产；
> - `XX` 为两位或三位数字，用于表示推荐学习或扩展顺序；
> - `short-description` 为简要、稳定的算例语义描述，使用小写字母与连字符（kebab-case）。
>
> 示例：
>
> - `case-00-minimal`
> - `case-01-poisson`
> - `case-02-elasticity-uniform`
>
> Directories under `cases/` represent canonical case assets and are recommended to use:
>
> ```text
> case-XX-short-description
> ```
>
> where:
>
> - `case` denotes a canonical standardized case asset;
> - `XX` indicates the recommended learning or extension order;
> - `short-description` provides a concise and stable case description.
>
> Examples include:
>
> - `case-00-minimal`
> - `case-01-poisson`
> - `case-02-elasticity-uniform`
>
> #### 组织原则 | Organizational Principles
>
> - `examples/` 侧重“如何使用系统”的教学表达，不应被视为正式资产库；
> - `cases/` 侧重标注化的、可复现、可比较、可回归的标准算例资产；
> - 每个 `case` 应作为**独立、自包含、可治理的资产**存在；
> - `case` 目录中应包含清晰的输入文件、说明文档以及可用于回归测试的预期结果；
> - `case` 本身**不应引入特例化数值实现**，所有通用能力应抽象并合入核心库；
> - 新增 `case` 应扩展系统的通用能力，而不仅仅是增加目录数量。
>
> - `examples/` focus on the learnable expression of how the system is intended to be used, and should not be treated as the formal asset repository;
> - `cases/` focus on standardized, reproducible, comparable, and regression-ready canonical case assets;
> - Each `case` should exist as an **independent, self-contained, and governable asset**;
> - Each case directory should include clear input files, documentation, and expected results suitable for regression testing;
> - A case itself **should not introduce case-specific numerical implementations**; all general-purpose capabilities should be abstracted and incorporated into the core library;
> - Adding a new `case` should extend the system’s general capabilities, rather than merely increasing the number of directories.
>
> 详细设计理念请参阅仓库根目录 `README.md` 中的相关说明。
> For detailed design philosophy, please refer to the relevant sections of the repository root `README.md`.

---

## 3. 不适合的贡献类型 | What Is Currently Out of Scope

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

## 4. 贡献流程 | Contribution Workflow

### 4.1 提交 Issue（推荐）| Open an Issue (Recommended)
- 描述问题、想法或改进建议
- 尽量说明动机、背景和预期目标
- Describe the problem, idea, or proposed improvement
- Provide motivation, background, and expected outcomes

### 4.2 Fork 与分支 | Fork and Branch
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

### 4.3 开发与提交 | Develop and Commit
- 保持提交信息清晰、聚焦
- 确保代码能够通过本地构建与测试
- Keep commits focused and well-described
- Ensure the code builds and tests pass locally

### 4.4 提交 Pull Request | Submit a Pull Request
- 清晰描述改动内容与动机
- 说明是否涉及数值行为或物理意义变化
- 必要时提供最小示例或验证结果
- Clearly describe what was changed and why
- State whether numerical behavior or physical meaning is affected
- Provide minimal examples or validation results when appropriate

---

## 5. 开发环境与工具配置 | Development Environment and Tooling

本节描述的是 **PeriSci 在 Windows 平台上已验证、推荐的开发环境与工具配置**。  
其目的是帮助贡献者快速获得一致、可复现的开发体验，而**非强制要求唯一工具链**。

This section describes the **recommended and verified development environment for PeriSci on Windows**.  
Its goal is to provide a consistent and reproducible developer experience, **without enforcing a single mandatory toolchain**.

---

### 5.1 推荐组合 | Recommended Stack

在 Windows 平台上，PeriSci 推荐并已验证以下组合：

On the Windows platform, PeriSci recommends and has verified the following combinations:

- **编译器 | Compiler**：MinGW-w64（GCC / G++）
- **构建系统 | Build system**：CMake + Ninja（single-config）
- **编辑器 / IDE | Editor / IDE**：Cursor（VS Code 生态）
- **语言服务 | Language server**：clangd

该组合在以下方面表现稳定：

- 正确解析 C++17 语义（`std`、标准库头文件等）
- 自动应用项目级 `.clang-format`
- 与 CI / 构建行为保持一致

This stack has been verified to work reliably for:

- Correct C++17 semantic analysis (`std`, standard library headers)
- Automatic application of project-level `.clang-format`
- Consistency with build and CI behavior

---

### 5.2 构建系统说明 | Build Configuration

PeriSci 当前推荐使用 **Ninja 单配置构建模式**：

PeriSci currently recommends **single-config Ninja builds**：

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

项目已在顶层 `CMakeLists.txt` 中启用：

The project has been enabled in the top-level `CMakeLists.txt` file:

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

其中生成的 `compile_commands.json` 是 clangd 获取真实编译信息的关键，且为构建过程中自动生成的编译数据库文件，应由`build/`目录生成并使用，不应提交到版本控制仓库中。

PeriSci uses **single-config Ninja builds** during the v0.1.x phase.
The generated `compile_commands.json` serves as the authoritative source of compilation flags for clangd，and it is an automatically generated compilation database produced during the build process and should be generated from the `build/` directory; it must not be committed to the version control repository.

---

### 5.3 clangd 配置说明 | clangd Configuration Notes

PeriSci 推荐使用 **clangd** 作为 C++ 语言服务（补全 / 诊断 / 格式化）。

PeriSci recommends **clangd** as the C++ language server for code completion, diagnostics, and formatting.

#### 5.3.1 允许 clangd 查询 MinGW 的 C++ driver | Allowing clangd to query the MinGW C++ driver

由于安全策略原因，clangd 默认不会执行外部编译器来探测系统头文件路径。
 在使用 MinGW 时，**必须显式允许 C++ driver（`g++` / `c++`）**，否则可能出现：

- `#include <string>` 找不到
- `std` 未声明
- C++17 特性被误报为扩展

Due to security restrictions, clangd does not execute external compilers by default to discover system include paths.
 When using MinGW, **explicitly allowing the C++ driver (`g++` / `c++`) is required**, otherwise issues such as:

- Missing `<string>` or other standard headers
- Undeclared `std`
- C++17 features incorrectly reported as extensions

may occur.

该授权通过 **`clangd.arguments`** 完成。

This permission is granted via **`clangd.arguments`**.

> ⚠️ **关于配置位置的说明 | About configuration scope**
> `clangd.arguments` 可以放在：
>
> - **User Settings（用户级 settings.json）**：影响当前用户的所有项目
> - **Workspace Settings（`.vscode/settings.json`）**：仅影响当前仓库
>
> 本项目 **不强制** 使用 Workspace Settings，也不要求在仓库中提交 `.vscode/` 目录。
> 贡献者可根据个人偏好选择其一。

> ⚠️ **About configuration scope**
> `clangd.arguments` may be placed in:
>
> - **User Settings**: applies to all projects of the current user
> - **Workspace Settings (`.vscode/settings.json`)**: applies only to the current repository
>
> This project does **not** require the use of Workspace Settings, nor does it require committing a `.vscode/` directory to the repository.
> Contributors may choose either approach based on personal preference.

示例（User 或 Workspace settings.json 均可）| Example (valid in either User or Workspace `settings.json`):

```powershell
{
  "clangd.arguments": [
    "--query-driver=C:\\mingw64\\bin\\*.exe"
  ]
}
```

该配置用于授权 clangd 查询 MinGW 的 C++ 编译器，以正确获取标准库头文件路径。

This configuration allows clangd to query the MinGW C++ compiler
 to correctly resolve standard library include paths.

---

### 5.4 代码格式化 | Code Formatting

- PeriSci 在仓库根目录提供 **`.clang-format`**，它是 C / C++ 代码风格的**唯一权威来源**。  
  所有 `.c/.cpp/.hpp` 等文件应遵循该规则；代码风格不通过人工讨论解决，以工具输出为准。
- 在推荐环境中，C/C++ 文件的格式化通常由 clangd（基于 `.clang-format`）在编辑器内完成。  
  CI 可在未来通过独立 `clang-format` CLI 执行格式检查（`--dry-run --Werror`）作为门禁。
- PeriSci ships a root-level **`.clang-format`** file as the **single source of truth** for C / C++ code style.  
  All `.c/.cpp/.hpp` files must follow it; code style is resolved by tooling output rather than manual discussion.
- In the recommended setup, formatting is typically performed in-editor via clangd (using `.clang-format`).  
  CI may later enforce formatting via a standalone `clang-format` CLI (`--dry-run --Werror`) as a gate.

---

### 5.5 非代码文件格式化 | Non-Code File Formatting

- PeriSci 使用 **`.editorconfig`** 来统一跨编辑器、跨平台的**基础文本规范**， 以消除与语义无关的格式差异（如换行符、编码、行尾空格等）。

- PeriSci uses **`.editorconfig`** to enforce **basic, cross-editor text conventions**,  eliminating non-semantic differences such as line endings, encoding, and trailing whitespace.

#### 5.5.1 设计原则 | Design Principles

- `.editorconfig` 仅用于 **基础文本层面的规范**（编码、换行符、缩进宽度、行尾空格等）
- **不承担结构化代码格式化职责**
- 默认规则适用于所有文件，仅在存在明确语义需求时才引入例外

- `.editorconfig` is used only for **basic text-level conventions** (encoding, line endings, indentation width, trailing whitespace)
- It does **not** perform structural or language-aware formatting
- Global rules apply to all files, with exceptions added only when clearly justified

#### 5.5.2 与 `.clang-format` 的职责边界 | Responsibility Boundary with `.clang-format`

- **`.editorconfig`**：
  - 适用于所有文本文件（包括 `.txt`、`.md`、`.cmake`、`.json`、`.yaml` 等）
  - 负责统一：
    - UTF-8 编码
    - LF / CRLF 行结尾
    - 是否保留行尾空格
    - 基础缩进风格

- **`.clang-format`**：
  - 仅适用于 C / C++ 源文件（`.c` / `.cpp` / `.hpp` 等）
  - 负责完整的、语言感知的代码排版规则
  - 是 C++ 代码风格的**唯一权威来源**

- **`.editorconfig`**:
  - Applies to all text files (including `.txt`, `.md`, `.cmake`, `.json`, `.yaml`, etc.)
  - Governs:
    - UTF-8 encoding
    - Line endings (LF / CRLF)
    - Trailing whitespace handling
    - Basic indentation style

- **`.clang-format`**:
  - Applies only to C / C++ source files
  - Provides full, language-aware code formatting
  - Serves as the **single source of truth** for C++ code style

#### 5.5.3 关于 `.txt` 文件的说明 | Notes on `.txt` Files

- `.editorconfig` 中的全局规则（`[*]`）已自动适用于 `.txt` 文件，  因此 **不需要** 为 `*.txt` 单独编写规则。

- A separate `*.txt` section is **not required**, as `.txt` files already inherit all global rules defined under `[*]`.

- 仅当某类文件具有明确且不同的语义需求时，才应引入单独的规则覆盖。

- Additional per-file-type rules should be introduced **only when a clear semantic need exists**.

#### 5.5.4 编辑器支持 | Editor Support

- Cursor / VS Code 原生支持 `.editorconfig`
- 为确保行为一致，推荐安装 **EditorConfig** 扩展
- `.editorconfig` 在保存文件时自动生效，无需手动触发
- Cursor / VS Code provide native `.editorconfig` support
- Installing the **EditorConfig** extension is recommended for consistent behavior
- Rules are applied automatically on file save

---

### 5.6 结构化文件格式化（JSON / YAML）| Structured File Formatting (JSON / YAML)

- **结构化格式化**（如 JSON 的缩进与排版）：推荐使用 **Prettier**（编辑器扩展或 CLI）  
- **YAML 文件**：在当前 Cursor 编辑器环境中，**尚无法稳定实现保存时自动格式化**；  但可通过 YAML 语言支持扩展获得 **schema 绑定、语法校验与语义提示**

- **Structural formatting** (e.g. JSON indentation and layout): **Prettier** is recommended (editor extension or CLI)  
- **YAML files**: in the current Cursor editor environment, **reliable format-on-save is not available**;  however, **schema association, syntax validation, and semantic hints** are supported via YAML language extensions

#### 5.6.1 Prettier（推荐）| Prettier (Recommended)

- 建议安装 **Prettier - Code formatter**，并在保存时自动格式化 JSON 等文件。  
- 在 Cursor/VS Code 生态中，是否支持对 YAML 的格式化可能因版本与扩展组合而异，因此本项目不强制要求编辑器内 YAML 自动格式化。

- Installing **Prettier - Code formatter** is recommended to format JSON (and similar structured files) on save.  
- YAML formatting support may vary across Cursor/VS Code versions and extension combinations, so the project does not mandate in-editor YAML auto-formatting.

#### 5.6.2 YAML 语言支持（推荐）| YAML Language Support (Recommended)

- 建议安装 **YAML** 扩展以获得 YAML 的 schema 绑定、校验与补全能力。  
- 注意：schema/校验属于“语义提示”，不等同于“格式化”。

- Installing a **YAML** extension is recommended for schema association, validation, and completion.  
- Note that schema/validation provides semantic assistance and is not equivalent to formatting.

---

### 5.7 关于工具配置的治理原则 | Tooling Governance Principles

- 与构建、复现无关的编辑器配置 **不强制写入仓库**
- 项目文档描述的是 **机制与推荐路径**，而非个人偏好
- 当某类工具配置需要成为项目共识时，应通过 ADR 明确其必要性
- Editor- or tool-specific configuration that does not affect build or reproducibility
  is intentionally not enforced at the repository level
- Project documentation describes **mechanisms and recommended paths**, not individual preferences
- When a tooling configuration needs to become a project-wide agreement,
  it should be formalized through an ADR

---

## 6. 代码与设计原则 | Code and Design Principles

### 6.1 首要原则 | Primary Principles

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

### 6.2 命名与编码原则 | Naming and Coding Principles

- 有关目录结构、CMake target、公有头文件路径与 C++ 命名空间之间项目级一致性的约定，请参阅 [docs/specs/consistency_matrix.md](docs/specs/consistency_matrix.md)。
- 关于 v0.1.x 骨架阶段中 stub 文件的命名、用途与生命周期约定，请参阅 [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md)。
- 关于 v0.1.x 阶段公共头文件的命名规则与允许范围，以及如何避免通过头文件名称提前承诺未来能力，请参阅 [docs/specs/header_naming.md](docs/specs/header_naming.md)。
- 有关项目级的 C++ 与 CMake 编码原则与约定，请参阅 [docs/CODING_GUIDE.md](docs/CODING_GUIDE.md)。
- For project-level consistency across directory structure, CMake targets, public include paths, and C++ namespaces, please refer to [docs/specs/consistency_matrix.md](docs/specs/consistency_matrix.md).
- For naming, usage, and lifecycle conventions of stub files during the v0.1.x skeleton phase, see [docs/specs/stub_conventions.md](docs/specs/stub_conventions.md).
- For project-level C++ and CMake coding principles and conventions, please refer to [docs/CODING_GUIDE.md](docs/CODING_GUIDE.md).
- For naming rules and allowed scopes of public header files during v0.1.x, and for avoiding premature capability commitments through header names, see [docs/specs/header_naming.md](docs/specs/header_naming.md).

---

## 7. 审查与合并 | Review and Merging

- 所有 Pull Request 都需要审查
- 核心数值与架构相关修改将由维护者重点评估
- 为确保构建过程的可复现性，持续集成（CI）流程仅依赖于版本控制仓库中已提交的文件；任何被 `.gitignore` 忽略的生成文件或本地缓存，都不应作为构建或测试流程的前提条件。
- 合并策略以 **Squash and Merge** 为主
- 维护者有权请求修改或暂缓合并
- All Pull Requests are subject to review

- Changes affecting core numerics or architecture receive extra scrutiny
- To ensure build reproducibility, the continuous integration (CI) process relies solely on files committed to the version-controlled repository; any generated artifacts or local caches ignored via `.gitignore` must not be prerequisites for build or test workflows.
- **Squash and Merge** is the preferred merge strategy
- Maintainers may request revisions or defer merging

---

## 8. 行为准则 | Code of Conduct

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

## 9. 联系方式 | Contact

如有不确定事项或合作意向，请通过以下方式联系：

- GitHub / Gitee Issues
- Pull Request 讨论区

For questions or collaboration inquiries, please contact us via:

- GitHub / Gitee Issues
- Pull Request discussions

