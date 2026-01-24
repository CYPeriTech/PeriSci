# ADR-0001: Windows 构建工具链与生成器选择（Ninja 单配置）| Windows Build Toolchain and Generator Selection (Ninja Single-Config)

- **状态 / Status**：Accepted
- **日期 / Date**：2026-01-24
- **版本范围 / Version Scope**：v0.1.x
- **影响范围 / Impact**：构建系统 / 开发者体验 / CI *(Build system / Developer experience / CI)*

------

## 背景 | Context

PeriSci v0.1.x 处于骨架阶段，当前目标是：

- 建立**最小但真实可运行**的工程闭环（core → api → examples → tests）
- 降低新贡献者与使用者的**环境与心智负担**
- 确保构建、运行、测试流程在 Windows 平台上**可复现、可诊断**

PeriSci v0.1.x is in its scaffold phase. The current goals are:

- Establish a **minimal yet real, runnable** engineering loop (core → api → examples → tests)
- Reduce the **environmental and cognitive load** for new contributors and users
- Ensure that build, run, and test workflows on Windows are **reproducible and diagnosable**

在 Windows 平台上，CMake 默认生成器通常为 Visual Studio（多配置），其特点包括：

- 同一 build 目录下同时包含 Debug / Release 等配置
- 构建与测试命令需要显式指定配置（`--config Debug` / `ctest -C Debug`）
- 可执行文件路径包含配置子目录（如 `bin/Debug/`）

On Windows, CMake's default generator is typically Visual Studio (multi-config), which has the following characteristics:

- A single build directory contains multiple configurations (Debug / Release, etc.)
- Build and test commands must explicitly specify the configuration (`--config Debug` / `ctest -C Debug`)
- Executable paths include configuration subdirectories (e.g., `bin/Debug/`)

在 v0.1.x 阶段，这种复杂度对“最小闭环”和教学/示例并不友好，因此需要对**构建生成器与工具链**作出明确选择。

At the v0.1.x stage, this level of complexity is not friendly to the "minimal loop" goal or to teaching/examples. Therefore, a clear decision on the **build generator and toolchain** is required.

------

## 决策| Decision

在 Windows 平台上，PeriSci v0.1.x **推荐并默认支持**以下构建组合：

- **生成器**：Ninja（single-config）
- **编译器**：GCC / G++（MinGW-w64）或等价的 C++17 兼容编译器
- **构建系统**：CMake ≥ 3.16

On Windows, PeriSci v0.1.x **recommends and defaults to** the following build setup:

- **Generator**: Ninja (single-config)
- **Compiler**: GCC / G++ (MinGW-w64) or an equivalent C++17-compatible compiler
- **Build system**: CMake ≥ 3.16

推荐的标准构建命令为：

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

该组合在 v0.1.x 阶段被视为**参考实现（reference workflow）**，并用于：

- 本地开发
- 教学示例
- CI 默认配置

This setup is considered the **reference workflow** for v0.1.x and is used for:

- Local development
- Teaching examples
- Default CI configuration

------

## 决策理由 | Rationale

### 1. 降低工程心智负担 | Reduced Cognitive Load

Ninja 单配置模型具备以下优势：

- 一个 build 目录对应一个配置（Debug 或 Release）
- 不需要在 `cmake --build` 或 `ctest` 中额外指定配置参数
- 可执行文件路径稳定（如 `build/bin/perisci-hello`）

The Ninja single-config model provides:

- One build directory per configuration (Debug or Release)
- No need to specify configuration flags in `cmake --build` or `ctest`
- Stable executable paths (e.g., `build/bin/perisci-hello`)

这与 v0.1.x 阶段“**先让系统站起来**”的目标高度一致。

This aligns well with the v0.1.x goal of **"getting the system up and running first."**

### 2. 提升可复现性与教学友好度 | Improved Reproducibility and Teaching Friendliness

- 构建与运行命令简短、确定性强
- README 与 examples 中的命令可以直接复制执行
- 减少因多配置生成器导致的路径/参数差异
- Build and run commands are short and deterministic
- Commands in README and examples can be copied and executed directly
- Reduces path and parameter differences caused by multi-config generators

### 3. 与 CI 和跨平台实践一致 | Alignment with CI and Cross-Platform Practices

- Ninja 是跨平台事实标准（Windows / Linux / macOS）
- 与 CMake 集成成熟，行为稳定
- 便于在 CI 中并行构建与测试
- Ninja is a de facto cross-platform standard (Windows / Linux / macOS)
- Mature integration with CMake and stable behavior
- Well-suited for parallel builds and tests in CI

### 4. 避免过早引入不必要复杂性 | Avoiding Premature Complexity

Visual Studio 多配置生成器在以下场景更具优势：

- 频繁在 Debug / Release 间切换
- 深度依赖 IDE 工作流

Visual Studio's multi-config generators are more suitable when:

- Frequent switching between Debug and Release is required
- There is deep reliance on IDE-centric workflows

这些并非 v0.1.x 的核心诉求，因此选择将其复杂性**推迟到后续阶段**。

These are not core requirements for v0.1.x, so the associated complexity is **intentionally deferred to later stages**.

------

## 备选方案 | Alternatives Considered

### A. Visual Studio（多配置生成器）| (Multi-Config Generator)

- **优点**：IDE 体验好，可在同一 build 目录中切换配置
- **缺点**：
  - 构建/测试命令更复杂（需 `--config` / `-C`）
  - 示例与文档更难保持“一行可跑”
- **Pros**: Strong IDE experience; multiple configurations in one build directory
- **Cons**:
  - More complex build/test commands (`--config` / `-C` required)
  - Harder to keep examples and documentation "one-command runnable"

结论：

> 在 v0.1.x 阶段不作为推荐默认，但仍然是**受支持的可选方案**。

Conclusion:

> Not the recommended default for v0.1.x, but still a **supported alternative**.

### B. Unix Makefiles

- **优点**：单配置
- **缺点**：
  - 在 Windows 上依赖额外环境（MSYS2 / MinGW make）
  - 工具链组合复杂，可复现性较差
- **Pros**: Single-config
- **Cons**:
  - Requires additional environments on Windows (MSYS2 / MinGW make)
  - Complex toolchain combinations and weaker reproducibility

结论：

> 不作为推荐方案。

Conclusion:

> Not recommended.

------

## 影响与后果 | Consequences

### 正面影响 | Positive Effects

- 构建、运行、测试流程显著简化
- README 与 examples 可作为“可执行文档”
- 降低新用户与贡献者的上手门槛
- Build, run, and test workflows are significantly simplified
- README and examples function as "executable documentation"
- Lower onboarding barrier for new users and contributors

### 约束与注意事项 | Constraints and Notes

- 使用 Visual Studio / Ninja Multi-Config 的用户需要自行指定配置参数
- 文档需明确区分 single-config 与 multi-config 的命令差异
- Users of Visual Studio / Ninja Multi-Config must specify configurations explicitly
- Documentation must clearly distinguish between single-config and multi-config commands

------

## 后续演进 | Future Considerations

- v0.2.x 及以后阶段，可能在 CI 中同时验证：
  - Ninja（single-config）
  - Visual Studio（multi-config）
- 若 Python 绑定或安装/打包需求增加，可能需要重新审视生成器选择，但该 ADR 不构成对未来阶段的约束。
- In v0.2.x and later, CI may validate both:
  - Ninja (single-config)
  - Visual Studio (multi-config)
- If Python bindings or packaging requirements grow, generator choices may be revisited, but this ADR does not constrain future stages.

------

## 参考 | References

- CMake 官方文档：Single-Config vs Multi-Config Generators
- Ninja 官方文档
- PeriSci v0.1.x 架构与质量门禁设计文档
- CMake Documentation: Single-Config vs Multi-Config Generators
- Ninja Documentation
- PeriSci v0.1.x Architecture and Quality Gate Design Documents