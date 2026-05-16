# ex-03-poisson-basic

本示例是 PeriSci 示例序列中的第一个真实数值教学示例，用最基础的有限元方法求解二维 Poisson 问题。

它属于 `examples/` 层，目标是教学、探索和后续 case asset 孵化；它当前不是稳定 case，也不使用 `run_case(config)` 作为入口。

## 1. 教学目标

本示例展示一个轻量但完整的 FEM 求解闭环：

- 用显式 C++ 配置对象声明问题；
- 建立规则二维四边形网格；
- 构造 Q1 标量有限元自由度；
- 装配全局刚度矩阵和右端项；
- 施加齐次 Dirichlet 边界条件；
- 用共轭梯度法求解对称正定线性系统；
- 输出基本运行指标。

术语说明：`Q1` 表示二维四边形单元上的一次双线性有限元；`标量` 表示未知量 `u(x, y)` 每个节点只有一个自由度。对于本示例，`Q1 标量` 就是“每个四边形单元使用 4 个双线性形函数，每个节点求一个标量未知量”。

求解问题为：

```text
-Delta u = 1      in [0, 1] x [0, 1]
u = 0             on the boundary
```

## 2. 入口原则

本示例遵循 v0.3.x+ 的入口原则：

```text
examples -> teaching-oriented API -> reusable core capabilities
cases    -> run_case(config)       -> reusable core capabilities
```

因此：

- `examples/ex-03-poisson-basic` 只 include `perisci/api/api.hpp`；
- example 不直接 include 或调用 `perisci/core/*`；
- example 不调用 `run_case(config)`；
- `api::run_poisson_basic(config)` 是教学型 API 入口；
- `core/` 只沉淀可复用数值能力，不出现 `core/poisson_basic.*`。

## 3. 三梁体现

本示例以轻量方式体现三梁结构：

```text
Config Beam  ->  PoissonBasicConfig
Run Beam     ->  api::run_poisson_basic(config)
Export Beam  ->  本示例默认不导出 dataset
```

`ex-03` 的教学重点是基础 FEM 求解闭环，因此默认不调用 `export_dataset`。
导出边界已由 `ex-02-dataset-export` 专门展示。未来当 Poisson 示例升级为 case asset 时，应通过 `cases/` 中的固定配置和 `api::run_case(config)` 进入执行，再通过 `export_dataset` 固化结果。

## 4. 四核体现

`api::run_poisson_basic(config)` 用教学阶段组织 FEM 流程，并通过 API 调用 core 中的通用能力：

```text
Discrete Objects    core::make_structured_quad_mesh
Local Interactions  core::assemble_q1_scalar_laplace_system
Accumulation        core::assemble_q1_scalar_laplace_system
State Advancement   core::conjugate_gradient
```

这与 PeriSci 的分层职责一致：

- `examples/`：展示问题、配置和结果，服务教学；
- `api/`：提供教学型入口，组织求解阶段，并隔离 core；
- `core/`：承载可复用数值能力，例如网格、装配、边界处理和线性求解；
- `cases/`：未来沉淀稳定算例资产。

## 5. 文件说明

```text
examples/ex-03-poisson-basic/poisson_basic.cpp
```

示例主程序。它构造 `PoissonBasicConfig`，调用 `perisci::api::run_poisson_basic`，并打印结果。

```text
api/include/perisci/api/run_poisson_basic.hpp
api/src/run_poisson_basic.cpp
```

教学型 API 入口。它不冻结 case schema，也不替代 `run_case(config)`；它负责把 Poisson 教学问题组织成清楚的 FEM 阶段。

```text
core/include/perisci/core/mesh.hpp
core/src/mesh.cpp
```

可复用网格能力：包含最小通用 `Mesh` 结构，并生成规则二维四边形网格。

```text
core/include/perisci/core/assembly.hpp
core/src/assembly.cpp
```

可复用装配能力：装配离散系统贡献。当前用于 Q1 标量 Laplace 系统，未来可承载 PeriFEM 近场贡献等统一装配能力。

```text
core/include/perisci/core/boundary.hpp
core/src/boundary.cpp
```

可复用边界条件能力：当前提供齐次 Dirichlet 边界条件的消行消列处理。

```text
core/include/perisci/core/linear_algebra.hpp
core/src/linear_algebra.cpp
```

可复用线性代数能力：稠密矩阵、向量范数和残差计算。

```text
core/include/perisci/core/solver.hpp
core/src/solver.cpp
```

可复用求解器能力：当前提供共轭梯度法，并保留 legacy `solve` 最小入口。

## 6. 构建

从仓库根目录执行：

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_poisson_basic -j
```

如果使用其他 CMake 生成器：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_poisson_basic
```

## 7. 运行

Linux/macOS:

```bash
./build/bin/perisci-poisson-basic
```

Windows PowerShell:

```powershell
.\build\bin\perisci-poisson-basic.exe
```

预期输出包括：

- API version；
- 问题名称、维度、网格规模和源项；
- 单元数和自由度数；
- CG 迭代次数；
- 最终残差范数；
- 中心节点解值；
- 三梁和 core 复用能力说明。

## 8. 与后续示例的关系

本示例只讲解基础 FEM 闭环，暂不讲误差范数、网格收敛、弹性力学和动力学。

当前规划的 FEM 教学主线为：

```text
ex-03-poisson-basic      标量静态 FEM 闭环
ex-04-poisson-error      误差与验证
ex-05-poisson-refinement 网格加密与收敛
ex-06-elasticity-basic   2D 线弹性静力，CG
ex-07-dynamics-basic     2D 显式动力学，中心差分
```

其中 `ex-03`、`ex-04` 和 `ex-05` 应复用同一批 core 能力，而不是在 core 中分别形成 `poisson_basic`、`poisson_error`、`poisson_refinement` 这样的示例同名实现。

## 9. 与 cases 的关系

本示例未来可以孵化出一个小型 Poisson case asset，但当前还不是 case。

如果未来升级为 case，应在 `cases/` 中补充：

- 固定输入；
- 期望指标；
- provenance；
- 回归门槛；
- 可复现说明。

届时 case 的数值执行入口应是 `api::run_case(config)`，而不是本示例使用的教学型 API 入口。
