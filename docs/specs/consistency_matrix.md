# 一致性对照表 | Consistency Matrix

> 本文档用于明确 **PeriSci v0.2.x 基线与 v0.3.x+ 阶段** 各核心模块在
> **目录结构 / CMake target / 公共头文件路径 / C++ 命名空间**等层面的对应关系。
>
> 本表最初形成于 v0.1.x 阶段，在 v0.2.x 中继续维护并扩展；在 v0.3.x+ 中继续作为新增 core/api/examples/cases 能力时的结构一致性基线。
>
> This document defines, for the **PeriSci v0.2.x baseline and v0.3.x+ stage**, the correspondence
> between **directory layout / CMake targets / public include paths / C++ namespaces** across core modules.
>
> The matrix was initially established in v0.1.x and extended in v0.2.x; in v0.3.x+ it continues to serve as the structural-consistency baseline for new core/api/examples/cases capabilities.

---

## 1. 文档目的与使用方式 | Purpose and How to Use

### 1.1 目的 | Purpose

- 防止项目在演进过程中出现命名与结构“自然长歪”
- 将当前已经达成的隐含一致性显式化、可检查化
- 为未来新增模块提供清晰、可复制的命名模板
- Prevent naming and structural drift as the project evolves
- Make implicit consistency explicit and reviewable
- Provide a clear, reproducible template for future modules

### 1.2 使用方式 | How to Use

- 任何新增模块、目录、target、命名空间，都应能在本表中找到对应关系
- 若新增内容无法自然映射到本表，应视为**潜在架构问题**，需重新审视设计
- Any new module, directory, target, or namespace should map cleanly into this table
- If a new element cannot be mapped naturally, it should be treated as a **potential architectural issue**

---

## 2. 核心一致性原则 | Core Consistency Principles

### 2.1 单一概念，多层投影 | One Concept, Multiple Projections

- 每一个“模块概念”在不同层面应保持同构：
  - 文件系统目录
  - CMake 构建 target
  - 对外 `#include` 路径
  - C++ 命名空间

- Each module concept must be isomorphic across layers:
  - Filesystem directory
  - CMake build target
  - Public `#include` path
  - C++ namespace

- 对于不参与编译或运行时调用链的结构（如 cases、docs 等），只需要保持目录语义一致，不要求 CMake target 或 C++ namespace。

- For structures that are not part of the build or runtime call chain (e.g., cases or documentation), only directory-level consistency is required.

### 2.2 不引入隐式别名 | No Implicit Aliases

- 避免为同一模块引入多个名字或缩写
- 不使用难以从名称推断来源与层级的别名
- Avoid multiple names or abbreviations for the same module
- Do not introduce aliases whose origin or layer cannot be inferred from the name

---

## 3. 模块一致性对照表 | Module Consistency Matrix

### 3.1 core 模块 | core Module

| 维度（中文）   | 定义                                 |
| -------------- | ------------------------------------ |
| 模块语义       | 最底层、稳定的基础设施与最小语义集合 |
| 目录路径       | `core/`                              |
| CMake target   | `perisci_core`                       |
| 公共头文件路径 | `perisci/core/*`                     |
| C++ 命名空间   | `perisci::core`                      |

| Dimension (English) | Definition                                                |
| ------------------- | --------------------------------------------------------- |
| Module semantics    | Lowest-level, stable infrastructure and minimal semantics |
| Directory           | `core/`                                                   |
| CMake target        | `perisci_core`                                            |
| Public headers      | `perisci/core/*`                                          |
| C++ namespace       | `perisci::core`                                           |

---

### 3.2 api 模块 | api Module

| 维度（中文）   | 定义                                     |
| -------------- | ---------------------------------------- |
| 模块语义       | 面向用户的稳定接口层，对 core 的受控封装 |
| 目录路径       | `api/`                                   |
| CMake target   | `perisci_api`                            |
| 公共头文件路径 | `perisci/api/*`                          |
| C++ 命名空间   | `perisci::api`                           |

| Dimension (English) | Definition                                   |
| ------------------- | -------------------------------------------- |
| Module semantics    | User-facing stable interface layer over core |
| Directory           | `api/`                                       |
| CMake target        | `perisci_api`                                |
| Public headers      | `perisci/api/*`                              |
| C++ namespace       | `perisci::api`                               |

---

### 3.3 examples 模块 | examples Module

| 维度（中文）   | 定义                       |
| -------------- | -------------------------- |
| 模块语义       | 可运行示例与最小用法演示   |
| 目录路径       | `examples/`                |
| CMake target   | `perisci_<example-name>`   |
| 公共头文件路径 | （无，对外不暴露）         |
| C++ 命名空间   | （通常不定义公共命名空间） |

**补充说明：**

`examples/` 下的示例通常以 `ex-XX-<name>` 的目录形式组织。其对应的 CMake target 通常采用 `perisci_<name>` 风格，而最终输出的可执行文件名可通过 `OUTPUT_NAME` 设置为 `perisci-<name>`。目录名、target 名与输出文件名不要求逐字一致，但应保持来源可追踪、语义清晰，并遵循统一命名规则。

| Dimension (English) | Definition                                         |
| ------------------- | -------------------------------------------------- |
| Module semantics    | Runnable examples and minimal usage demonstrations |
| Directory           | `examples/`                                        |
| CMake target        | `perisci_<example-name>`                           |
| Public headers      | (None, not exposed)                                |
| C++ namespace       | (Usually none)                                     |

**Additional note:**

Examples under `examples/` are typically organized as `ex-XX-<name>` directories. Their CMake targets typically follow the `perisci_<name>` style, while the final executable name may be set to `perisci-<name>` via `OUTPUT_NAME`. The directory name, target name, and output file name need not match literally, but the mapping should remain traceable, semantically clear, and follow a consistent naming rule.

---

### 3.4 apps 模块 | apps Module

| 维度（中文）   | 定义                                                  |
| -------------- | ----------------------------------------------------- |
| 模块语义       | 命令行工具与工程入口（CLI / runtime entry）           |
| 目录路径       | `apps/`                                               |
| CMake target   | `perisci-run` / `perisci-export` / `perisci-validate` |
| 公共头文件路径 | （无，对外不暴露）                                    |
| C++ 命名空间   | （通常不定义公共命名空间）                            |

| Dimension (English) | Definition                                          |
| ------------------- | --------------------------------------------------- |
| Module semantics    | CLI tools and runtime entry points                  |
| Directory           | `apps/`                                             |
| CMake target        | `perisci-run`, `perisci-export`, `perisci-validate` |
| Public headers      | (None, not exposed)                                 |
| C++ namespace       | (Usually none)                                      |

---

### 3.5 python 模块 | python Module

| 维度（中文）    | 定义                                         |
| --------------- | -------------------------------------------- |
| 模块语义        | Python 工作流层，用于脚本、自动化与 AI 调用  |
| 目录路径        | `python/`（Python 包位于 `python/perisci/`） |
| CMake target    | （无，Python 模块）                          |
| 公共头文件路径  | 不适用                                       |
| Python 命名空间 | `perisci`                                    |

| Dimension (English) | Definition                                                          |
| ------------------- | ------------------------------------------------------------------- |
| Module semantics    | Python workflow layer for scripting, automation, and AI interaction |
| Directory           | `python/` (the Python package is located at `python/perisci/`       |
| CMake target        | (None, Python module)                                               |
| Public headers      | Not applicable                                                      |
| Python namespace    | `perisci`                                                           |

---

### 3.6 cases 模块 | cases Module

| 维度（中文）   | 定义                                      |
| -------------- | ----------------------------------------- |
| 模块语义       | canonical simulation cases / 标准算例资产 |
| 目录路径       | `cases/`                                  |
| CMake target   | （无）                                    |
| 公共头文件路径 | 不适用                                    |
| C++ 命名空间   | 不适用                                    |

**补充说明：**
cases/ 不属于 runtime 调用链。
它是 PeriSci 的 canonical case repository，用于提供可复现的输入、期望输出以及 dataset 资产生成基础。

| Dimension (English) | Definition                       |
| ------------------- | -------------------------------- |
| Module semantics    | Canonical simulation case assets |
| Directory           | `cases/`                         |
| CMake target        | (None)                           |
| Public headers      | Not applicable                   |
| C++ namespace       | Not applicable                   |

**Additional note:**
The cases/ directory is not part of the runtime call chain.
It serves as the canonical case repository for reproducible simulation inputs and dataset generation.

---

### 3.7 tests 模块 | tests Module

| 维度（中文）   | 定义                                |
| -------------- | ----------------------------------- |
| 模块语义       | 构建与链接验证、回归测试            |
| 目录路径       | `tests/`                            |
| CMake target   | `perisci_test_*` 或内部 test target |
| 公共头文件路径 | （无，对外不暴露）                  |
| C++ 命名空间   | （测试内部自定义）                  |

| Dimension (English) | Definition                                   |
| ------------------- | -------------------------------------------- |
| Module semantics    | Build/link verification and regression tests |
| Directory           | `tests/`                                     |
| CMake target        | `perisci_test_*` or internal test targets    |
| Public headers      | (None, not exposed)                          |
| C++ namespace       | (Test-internal only)                         |

---

## 4. 一致性检查清单 | Consistency Checklist

在新增任何模块或主要目录前，请检查以下问题：

- 是否可以为该模块明确给出：目录 / target / include 路径 / 命名空间？
- 这些名称是否在语义上保持一致，且可被直观理解？
- 是否避免了与现有模块的命名冲突或语义重叠？

Before introducing any new module or major directory, check:

- Can directory, target, include path, and namespace be clearly defined?
- Are these names semantically consistent and intuitively understandable?
- Are naming conflicts or semantic overlaps with existing modules avoided?

---

## 5. 演进说明 | Evolution Notes

- 本对照表反映的是 **v0.2.x 基线与 v0.3.x+ 阶段的稳定共识**
- 新模块的引入或现有模块职责的变化，应首先更新本表
- 若变化涉及架构边界，应通过 ADR 正式记录
- This matrix reflects **stable consensus for the v0.2.x baseline and v0.3.x+ stage**
- Introduction of new modules or changes in responsibilities should update this table first
- Architectural boundary changes must be recorded via ADRs

---

## 6. 结语 | Closing Notes

一致性不是为了限制扩展，而是为了让扩展具备可预测性。

Consistency is not meant to limit growth, but to make growth predictable.
