# ex-01-config-basics

本目录是 PeriSci 的第一个正式教学示例，用于展示 C++ 代码如何组织并提交一份基础配置。

它属于 **examples（示例层）**，用于教学和探索，不是算例资产（case asset）。

---

## 教学目标

本示例展示：

- 如何在 C++ 示例程序中构造 `ConfigJson`
- 如何读取当前 `schema_version`
- 如何调用 `perisci::api::run_case`
- 如何观察 `RunResults` 中的 `status`、`message` 和 `notes`

在当前 v0.3.x+ 阶段，`run_case` 仍保留 v0.2.x 平台最小执行边界，主要服务 cases 体系的统一入口；真实数值教学路径从后续教学型 API 示例（如 `ex-03-poisson-basic`）开始。因此本示例不展示真实物理求解，也不承诺数值正确性。

---

## 文件说明

### `CMakeLists.txt`

定义示例 target：

```text
perisci_config_basics
```

构建后输出可执行文件：

```text
perisci-config-basics
```

### `config_basics.cpp`

示例主程序。它在代码中构造一份教学用 JSON 配置，包含：

- `meta`
- `problem`
- `solver`
- `output`

然后调用 PeriSci API 并打印运行结果。

---

## 构建方式

从仓库根目录执行：

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_config_basics -j
```

如果使用其他 CMake 生成器，也可以执行：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_config_basics
```

---

## 运行方式

使用顶层 CMake 的默认输出布局时：

```bash
./build/bin/perisci-config-basics
```

Windows PowerShell 中通常为：

```powershell
.\build\bin\perisci-config-basics.exe
```

预期输出会包含：

- API version
- Schema version
- Input config JSON
- Run status
- Run message
- Notes

---

## 与 cases 的区别

本示例用于理解配置结构和 API 调用方式。它不会包含：

- `expected.json`
- CI 回归门禁规则
- 算例资产冻结声明

如果未来某个配置具备稳定的物理意义、数值行为和验证标准，应迁移或复制到 `cases/`，再作为正式 case asset 维护。
