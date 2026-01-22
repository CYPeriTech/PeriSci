# PeriSci  
**An Open-source PeriFEM-based CAE Platform for Scientific Computing and Engineering Simulation**  
**开源近场有限元（PeriFEM）科学计算与工程仿真平台**

---

<a id="overview"></a>

## 项目简介 | Overview

**PeriSci** 是一款面向科学研究与工程分析的开源 CAE 软件，  
以 **近场有限元法（PeriFEM, Peridynamics-based Finite Element Method）** 为核心数值框架，  
用于模拟 **多物理场耦合及极端条件下结构变形与破坏行为**。

PeriSci 是近场有限元软件生态体系**PERISOFT**中的开源软件品牌，  
目标是构建一个 **可教学、可研究、可工程化、可被 AI 调用的物理可信仿真基座**。

---

**PeriSci** is an open-source CAE software platform designed for scientific research and engineering analysis.  
It is built upon the **PeriFEM (Peridynamics-based Finite Element Method)** framework,  
aiming to simulate **structural deformation and failure behavior under coupled multiphysics and extreme conditions**.

PeriSci is the open-source brand of the PeriFEM software ecosystem (**PERISOFT**).  
Its long-term vision is to provide a **physically trustworthy simulation backbone** that supports  
education, research, engineering applications, and AI-driven modeling.

---

<a id="toc"></a>

## 目录 | Table of Contents

- [核心理念 | Core Philosophy](#core-philosophy)
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

---

- **PeriFEM as the central numerical paradigm**
- **Physics-first instead of purely data-driven fitting**
- **System-level complexity hidden from end users**
- **Reproducibility and traceability by design**
- **Open interfaces for future AI–CAE integration**

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
├── core/          		 # PeriFEM 数值内核（算子、装配、材料/损伤、求解驱动等）
├── api/           		 # 稳定对外契约层：run_case / export_dataset / config入口
├── python/        		 # Python 绑定与工作流层（教学、AI数据生产、脚本接口）
├── apps/          		 # 可执行程序/CLI（工程入口、批处理、校验、工具）
├── examples/      		 # 教学与参考算例（最小示例、教程、benchmark）
├── tests/         		 # 单测/回归（保证核心与契约层不退化）
├── docs/          		 # 文档（含 specs/ 规范、架构说明、路线图）
├── README.md            # 项目对外门面（中英双语）
├── LICENSE              # 开源协议（法律文件）
├── CONTRIBUTING.md      # 参与贡献规则
├── CODE_OF_CONDUCT.md   # 行为准则
├── MAINTAINERS.md       # 项目治理与责任
├── VERSIONING.md        # 版本与承诺规则
├── CHANGELOG.md         # 版本变更历史
├── CMakeLists.txt		 # 跨平台编译和管理
└── .gitignore		 	 # 版本控制规避文件清单
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
cd PeriSci
```

### 2) 配置与编译 | Configure & Build (CMake)

建议使用 out-of-source 构建（保持仓库根目录干净）：

```bash
mkdir -p build
cmake -S . -B build
cmake --build build -j
```

### 3) 运行最小示例 | Run the Minimal Example

v0.1.0 提供一个最小示例用于验证“能编译、能运行、能产出结果文件”。

方式 A（推荐）：直接运行 build 目录生成的可执行文件（具体名称以实际为准）：

```
./build/examples/hello/hello_example
```

方式 B：进入示例目录运行（若你的构建脚本把可执行文件放在该目录）：

```
cd examples/hello
./hello_example
```

运行成功后，应该能看到终端输出，并在指定位置生成输出文件（例如 `output/hello.txt`）。

### 4) 运行测试 | Run Tests (Optional but Recommended)

如果已配置测试：

```
ctest --test-dir build
```

------

### 常见问题 | Common Issues

- **Q: 找不到可执行文件路径？**
   A: 不同 CMake 组织方式生成路径可能不同。你可以在 `build/` 下查找：

  ```
  find build -maxdepth 4 -type f -perm -111
  ```

  然后运行对应的可执行文件。

- **Q: CMake 配置失败？**
   A: 请确认 CMake 版本与编译器可用：

  ```
  cmake --version
  g++ --version
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

------

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

详细说明请参阅：[CONTRIBUTING.md](CONTRIBUTING.md)

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

------

<a id="license"></a>

## 开源协议 | License

本项目采用 **MulanPSL-2.0（木兰宽松许可证 v2）** 开源发布。
 This project is released under the **MulanPSL-2.0 License**.

详见 | See: LICENSE

------

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

------

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

All breaking changes will be explicitly documented.

------

<a id="citation-notice"></a>

## 学术引用说明 | Citation Notice

若在论文、报告或数据集中引用 PeriSci，请以 `CITATION.cff` 为唯一权威引用来源。

For academic publications, reports, or datasets, please use `CITATION.cff` as the single authoritative citation source for PeriSci

