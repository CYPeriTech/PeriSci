# PeriSci

**An Open-source PeriFEM-based CAE Platform for Scientific Computing and Engineering Simulation**  
**开源近场有限元（PeriFEM）科学计算与工程仿真平台**

> **当前开发状态 | Development Status**
>
> PeriSci 当前处于 **v0.2.x 稳定化阶段**，重点在于架构边界稳定与契约体系确立。详细阶段说明请参阅 `docs/ROADMAP.md`。
> PeriSci is currently in the **v0.2.x stabilization stage**, focusing on architectural boundary stabilization and contract enforcement. See `docs/ROADMAP.md` for detailed evolution plans.

---

<a id="overview"></a>

## 项目简介 | Overview

**PeriSci** 是一款面向科学计算与工程仿真的开源 CAE 软件平台，用于模拟多物理场耦合与极端条件下结构的变形与破坏行为。

该平台以 **近场有限元方法（PeriFEM, Peridynamics-based Finite Element Method）** 为核心数值框架，将非局部力学与有限元离散方法结合，用于描述断裂、损伤及复杂材料行为的数值模拟。

除了作为仿真工具之外，**PeriSci 同时也是一个用于探索科学计算平台架构的实验工具**，包括运行时执行结构、数值实验体系以及面向可复现计算研究的软件长期稳定性设计。

PeriSci 是近场有限元软件生态体系 **PERISOFT** 中的开源软件品牌，目标是构建一个 **可教学、可研究、可工程化、可被 AI 调用的物理可信仿真基座**。

---

**PeriSci** is an open-source CAE software platform for scientific computing and engineering simulation, designed to model structural deformation and failure under extreme conditions and multiphysics coupling.

The platform is built around the **Peridynamics-based Finite Element Method (PeriFEM)**, a numerical framework that integrates nonlocal mechanics with finite element discretization to enable robust simulation of fracture, damage, and complex material behavior.

Beyond providing a simulation tool, **PeriSci also serves as an experimental tool for exploring architectures of scientific computing platforms**, including runtime execution structures, numerical experiment systems, and long-term software stability design for reproducible computational research.

PeriSci is part of the **PERISOFT** ecosystem for PeriFEM-based scientific software. The project aims to establish a **physically trustworthy simulation foundation that is teachable, research-oriented, engineering-ready, and callable by AI agents**.

---

<a id="toc"></a>

## 目录 | Table of Contents

- [核心理念 | Core Philosophy](#core-philosophy)
- [架构宪法 | Architecture Constitution](#archi-const)
- [主要功能 | Key Capabilities](#capabilities)
- [面向用户 | Target Users](#target-users)
- [项目结构 | Repository Structure](#repository-structure)
- [构建与运行 | Build & Run](#build-run)
- [版本管理 | Versioning](#versioning)
- [参与贡献 | Contributing](#contributing)
- [开源协议 | License](#license)
- [项目状态 | Project Status](#project-status)
- [联系与交流 | Contact & Community](#contact-community)
- [学术引用说明 | Citation Notice](#citation-notice)

---

<a id="core-philosophy"></a>

## 核心理念 | Core Philosophy

- **以近场有限元法为核心（PeriFEM-core）**
- **物理可信优先于经验拟合（Physics-first）**
- **复杂性由系统承担，而非用户承担**
- **长期可复现性与可追溯性（Reproducibility-by-design）**
- **面向未来 AI–CAE 融合的开放接口**
- **采用算例驱动的生长模式：**每一个算例均被视为一等资产，并同时承担教学示例、回归基准与数据生成单元的功能。

---

- **PeriFEM as the central numerical paradigm**
- **Physics-first instead of purely data-driven fitting**
- **System-level complexity hidden from end users**
- **Reproducibility and traceability by design**
- **Open interfaces for future AI–CAE integration**
- **Case-driven growth model: **each case is regarded as a first-class asset and serves simultaneously as a tutorial, a regression benchmark, and a data-generation unit.

---

<a id="archi-const"></a>

## 架构宪法 | Architecture Constitution

PeriSci 采用 **三梁执行结构（Three-Beam Execution Structure）** 与 **四核求解器结构（Four-Core Solver Structure）** 作为系统的长期治理基础。
PeriSci adopts a **Three-Beam Execution Structure** and a **Four-Core Numerical Skeleton** as the long-term governance foundation of the system.

三梁不是目录划分，也不是“前处理 / 求解器 / 后处理”的命名替代，而是一种用于科学计算平台的**执行契约结构（execution contract structure）**，用于定义输入、执行与结果资产之间的责任边界。

- **配置梁（Config Beam，Beam A：`config_schema`）**  
  唯一合法的物理意图与执行声明载体（权威配置契约，Authoritative Configuration Contract）

- **执行梁（Run Beam，Beam B：`run_case`）**  
  纯执行边界（schema in → structured results out），不依赖隐式输入来源（Pure Execution Boundary）

- **输出梁（Export Beam，Beam C：`export_dataset`）**  
  唯一资产级结果出口（结果资产化、溯源、冻结与版本化，Dataset Materialization and Provenance）

The Three-Beam structure is neither a directory layout nor a renaming of “pre-processing / solver / post-processing”.  
It is an **execution contract structure** for scientific computing platforms, defining clear responsibility boundaries between configuration, execution, and dataset materialization.

- **Config Beam (Beam A: `config_schema`)**  
  The sole authoritative carrier of physical intent and execution declaration (Authoritative Configuration Contract)

- **Run Beam (Beam B: `run_case`)**  
  A pure execution boundary (schema in → structured results out), with no implicit input sources (Pure Execution Boundary)

- **Export Beam (Beam C: `export_dataset`)**  
  The only asset-level result outlet (dataset materialization, provenance, freeze determination, and versioning)

四核结构定义数值内核的最小稳定骨架，包括离散对象、局部相互作用、贡献汇总与状态推进。
The Four-Core structure defines the minimal stable skeleton of the numerical kernel, including discrete objects, local interactions, accumulation (assembly), and state advancement.

上述架构为 PeriSci 的宪法级约束，其完整定义见：

> ```
> docs/DESIGN_CONTRACT.md
> ```

该文档构成架构与治理层面的权威来源。

The above architecture constitutes a constitutional-level constraint of PeriSci.
Its complete definition is provided in:

> ```
> docs/DESIGN_CONTRACT.md
> ```

This document serves as the authoritative source for architectural and governance-level definitions.

---

<a id="capabilities"></a>

## 主要功能 | Key Capabilities

### 当前与规划中的能力 | Current & Planned

- ✅ 近场有限元法（PeriFEM）结构分析
- ✅ 动态 / 静态损伤与断裂模拟
- 🚧 热–力耦合多物理场分析
- 🚧 自适应耦合近场有限元与经典有限元计算
- 🚧 面向计算流体动力学、离散单元法等的插件式接口
- 🚧 面向 AI 的仿真数据集生成与接口规范

---

- ✅ PeriFEM-based structural analysis
- ✅ Static and dynamic damage / fracture simulation
- 🚧 Thermo-mechanical multiphysics coupling
- 🚧 Adaptive Coupling between PeriFEM and classical FEM
- 🚧 Plugin-based interfaces for CFD, DEM, etc.
- 🚧 AI-oriented simulation dataset generation and APIs

---

<a id="target-users"></a>

## 面向用户 | Target Users

### 👩‍🎓 教师与研究生（学习与研究）| Teacher and Graduate Students

- 学习近场有限元法与结构损伤与断裂建模
- 通过简化接口与算例理解近场动力学及其耦合建模思想
- 用于课程教学、方法验证与学术论文研究

---

- Learn PeriFEM-based modeling for structural damage and fracture
- Understand peridynamics and its coupling modeling through simplified interfaces and examples
- Use PeriSci for coursework, methodological studies, and academic research

---

### 🧑‍🔬 科研与工程人员（问题求解）| Researchers and Engineering Users

- 面向复杂结构破坏与极端工况的数值分析
- 提供可复现、可诊断、可批量运行的仿真流程
- 面向高性能计算平台部署

---

- Perform numerical analysis of complex structural failure under extreme conditions
- Access reproducible, diagnosable, and batch-oriented simulation workflows
- Deploy simulations on high-performance computing platforms

---

### 🤖 AI 与数据驱动建模人员 | AI and Data-driven Modeling Users

- 获取基于物理模型的高可信度仿真数据
- 构建 AI–CAE 混合模型与代理模型（surrogates）
- 通过标准化接口将 PeriSci 作为 AI 调用的物理仿真基座

---

- Obtain high-fidelity, physics-based simulation datasets
- Develop AI–CAE hybrid models and surrogate predictor
- Use PeriSci as a physics-grounded simulation backend for AI workflows

---

<a id="repository-structure"></a>

## 项目结构 | Repository Structure

```text
PeriSci/

# Runtime Architecture | 运行时架构
├── core/          		 # PeriFEM 数值内核（算子、装配、材料/损伤、求解驱动等）| Numerical kernel
├── api/           		 # 稳定对外契约层：run_case / export_dataset / config入口 | External contract layer
├── python/        		 # Python 绑定与工作流层（教学、AI数据生产、脚本接口）| Workflow layer
├── apps/          		 # 可执行程序/CLI（工程入口、批处理、校验、工具）| Executable program layer

# Numerical Experiment System | 数值实验体系
├── examples/      		 # 教学与参考算例（hello/最小示例、教程、benchmark）| Examples layer
├── cases/         		 # 标准算例资产（稳定的可复现数值实验，用于回归测试与数据生产）| Canonical case assets
├── tests/         		 # 单测/回归（保证核心与契约层不退化）| Testing layer

# Documentation and Design Records | 文档与设计记录
├── docs/          		 # 技术文档（含specs/规范、adr/架构决策记录等、架构说明、路线图等）| Technical Documents
├── README.md            # PeriSci 开源软件项目介绍（中英双语）| Project introduction

# Governance Framework | 治理框架
├── VERSIONING.md        # 版本与承诺规则 | Version rules
├── CHANGELOG.md         # 版本变更历史 | Version change history
├── CONTRIBUTING.md      # 参与贡献规则 | Contribution rules
├── CODE_OF_CONDUCT.md   # 行为准则 | Code of conduct
├── MAINTAINERS.md       # 项目治理与责任 | Project maintenance rules
├── AUTHORS.md   		 # 作者与贡献者信息 | Contributor information
├── CITATION.cff       	 # 说明学术出版物中如何引用 PeriSci 软件 | Citation information
├── LICENSE              # 开源协议（法律文件）| Open-source license

# Build and Repository Configuration | 构建与仓库配置
├── CMakeLists.txt		 # 跨平台编译和管理 | Compilation rules
├── .clang-format        # 代码格式化 | Code formatting
├── .editorconfig		 # 非代码文件格式化 | Non-code file formatting
└── .gitignore		 	 # 版本控制规避文件清单 ignoring files checklist
```

---

<a id="build-run"></a>

## 构建与运行 | Build & Run

> ⚠️ 说明：PeriSci 当前尚未发布可供用户直接使用的最小稳定版本。
> 本节所示构建流程主要用于说明项目的工程组织方式与未来使用方式，
> 示例代码与可执行程序仍在开发与完善过程中。

> ⚠️ Note: PeriSci has not yet released a minimal stable version for end users.
> The build instructions below are provided to illustrate the intended
> engineering workflow and future usage. Example codes and executables
> are still under active development.

> 当前处于早期开发阶段（v0.x）。以下命令以 **CMake + C++** 的最小构建为例。  
> 如你使用的是 Windows 或特定 HPC 环境，请根据实际编译器与依赖调整。

### 0) 环境准备 | Prerequisites

PeriSci v0.1.5 采用 **CMake + C++17** 的最小工程骨架。建议使用 **out-of-source build**，
并优先使用 **Ninja（单配置生成器）** 以获得更一致的构建/测试体验（尤其在 Windows 下）。

#### Windows（推荐：Ninja 单配置）

你需要以下工具，并将其加入系统环境变量的`PATH`：

- **GCC / G++（MinGW-w64）**  
  例如：`x86_64-15.2.0-release-posix-seh-ucrt-rt_v13-rev0`
- **CMake**  
  例如：`cmake-4.2.2-windows-x86_64`
- **Ninja**  
  例如：`v1.13.2`

安装完成后可用以下命令检查：

```bash
g++ --version
cmake --version
ninja --version
```

---

### 1) 获取代码 | Clone

选择一个远端仓库克隆（Gitee 为主仓，GitHub 可作为镜像）：

**Gitee（推荐）**

```bash
git clone https://gitee.com/CYPeriTech/perisci
```

**Github（镜像）**

```bash
git clone https://github.com/CYPeriTech/PeriSci
```

**进入仓库目录：**

```bash
cd perisci
```

### 2) 配置与编译 | Configure & Build (CMake)

建议使用 out-of-source 构建（保持仓库根目录干净）。

#### 方式 A（推荐）：Ninja 单配置（Debug）

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

#### 方式 B：Ninja 单配置（Release）

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

> 若你使用 Visual Studio / Xcode 等 **多配置生成器**，构建与测试需要显式指定配置：
> `cmake --build build --config Debug`，以及 `ctest --test-dir build -C Debug`。

---

### 3) 运行最小示例 | Run the Minimal Example

v0.1.5 提供一个最小示例用于验证“能编译、能链接、能运行”。

在使用上述 Ninja 单配置构建后，可执行文件通常位于：

```bash
./build/bin/perisci-hello
```

预期输出类似：

```bash
Hello, PeriSci!
Version: 0.2.0
Build: PeriSci (api) v0.2.0
```

---

### 4) 运行测试 | Run Tests

在 Ninja 单配置（single-config）下测试命令如下：

```
ctest --test-dir build --output-on-failure
```

---

### 常见问题 | Common Issues

- **Q: 找不到可执行文件路径？**
  A: 不同 CMake 组织方式生成路径可能不同。你可以在 `build/` 下查找：

  ```
  find build -maxdepth 4 -type f -perm -111
  ```

  然后运行对应的可执行文件。

- **Q: CMake 、GCC或者Ninja配置失败？**
  A: 请确认 CMake 版本与编译器可用：

  ```
  cmake --version
  g++ --version
  ninja --version
  ```

---

<a id="versioning"></a>

## 版本管理 | Versioning

PeriSci 遵循 **面向科研与工程软件的语义化版本管理策略**。

- 版本号格式为 `vMAJOR.MINOR.PATCH`
- 每一个版本 Tag 代表一个 **可长期复现、可被引用的稳定状态**
- 强烈建议在论文、仿真数据集与 AI 训练流程中引用具体版本 Tag

详细的版本管理原则与规范请参阅：

- [VERSIONING.md](VERSIONING.md)
- [CHANGELOG.md](CHANGELOG.md)

---

PeriSci follows a **SemVer-inspired versioning policy adapted for
scientific computing and CAE software**.

- Version tags follow the format `vMAJOR.MINOR.PATCH`
- Each tag represents a **long-term reproducible and citable state**
- Users are strongly encouraged to reference version tags in publications,
  simulation datasets, and AI training workflows

For detailed rules and conventions, please refer to:

- [VERSIONING.md](VERSIONING.md)
- [CHANGELOG.md](CHANGELOG.md)

---

<a id="contributing"></a>

## 参与贡献 | Contributing

我们欢迎来自社区的各种形式的贡献，包括但不限于：

- 数值方法与物理模型的实现
- 教学算例与工程基准问题
- 文档、教程与示例改进
- 测试、CI 与工程化增强

基本贡献流程如下：

1. Fork 本仓库
2. 新建功能分支（如 `feat/xxx`）
3. 提交代码并保证本地测试通过
4. 创建 Pull Request 并说明修改内容与动机

更详细的内容，如开发环境配置、代码格式规范（如 `.clang-format`、`.editorconfig`）以及其他贡献约定，请参阅：[CONTRIBUTING.md](CONTRIBUTING.md)

For more detailed information, such as development environment setup, code formatting rules (e.g. `.clang-format`, `.editorconfig`), and other contribution guidelines, please refer to: [CONTRIBUTING.md](CONTRIBUTING.md)

---

We welcome community contributions in various forms, including but not limited to:

- Implementation of numerical methods and physical models
- Educational examples and engineering benchmarks
- Improvements to documentation, tutorials, and examples
- Testing, CI, and engineering enhancements

The basic contribution workflow is:

1. Fork this repository
2. Create a feature branch (e.g. `feat/xxx`)
3. Commit your changes and ensure tests pass locally
4. Submit a Pull Request with a clear description of your changes

For more details, please refer to:  
[CONTRIBUTING.md](CONTRIBUTING.md)

---

<a id="license"></a>

## 开源协议 | License

本项目采用 **MulanPSL-2.0（木兰宽松许可证 v2）** 开源发布。
This project is released under the **MulanPSL-2.0 License**.

详见 | See: LICENSE

---

<a id="project-status"></a>

## 项目状态 | Project Status

PeriSci 当前处于 **早期开发阶段（v0.x）**。

- 软件架构与接口仍在持续演进中
- 数值方法与功能模块将逐步完善
- 但我们承诺：**每一个发布的版本 Tag 都是可复现、可解释、可被信任的**

在 v1.0.0 之前，API 与配置规范可能发生变化，相关破坏性变更将被清晰记录。

---

PeriSci is currently in an **early development stage (v0.x)**.

- The software architecture and interfaces are under active development
- Numerical methods and features will be progressively extended
- Nevertheless, we commit that **each released version tag is reproducible,
  interpretable, and trustworthy**

Before reaching v1.0.0, APIs and configuration schemas may evolve.
All breaking changes will be explicitly documented.

---

<a id="contact-community"></a>

## 联系与交流 | Contact & Community

我们欢迎关于以下方面的交流与合作：

- 学术研究与方法讨论
- 工程应用与算例验证
- 开源社区共建与长期合作

请通过以下方式与我们联系：

- 问题反馈与功能建议：请使用 Gitee / GitHub Issues
- 代码贡献与讨论：通过 Pull Request 与 Review
- 学术与合作交流：请通过仓库主页提供的联系方式联系维护者

---

We welcome communication and collaboration on:

- Academic research and methodological discussions
- Engineering applications and benchmark validation
- Open-source community building and long-term collaboration

You may contact us via:

- Bug reports and feature requests: Gitee / GitHub Issues
- Code contributions and discussions: Pull Requests and Reviews
- Academic and collaboration inquiries: via the contact information
  provided on the repository homepage

---

<a id="citation-notice"></a>

## 学术引用说明 | Citation Notice

若在论文、报告或数据集中引用 PeriSci，请以 `CITATION.cff` 为唯一权威引用来源。

For academic publications, reports, or datasets, please use `CITATION.cff` as the single authoritative citation source for PeriSci
