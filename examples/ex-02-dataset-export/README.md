# ex-02-dataset-export

本目录展示 PeriSci 如何把一次运行的内存态结果导出为 `dataset/`。

它属于 **examples（示例层）**，用于教学和探索，不是稳定算例资产（case asset）。

---

## 教学目标

本示例展示：

- 如何构造一份包含 `"write_dataset": true` 的教学配置
- 如何调用 `perisci::api::run_case` 得到内存态 `RunResults`
- 如何调用 `perisci::api::export_dataset`
- 如何观察生成的 `dataset/` 目录和关键文件

在当前 v0.3.x+ 阶段，`run_case` 和 `export_dataset` 仍保留 v0.2.x 平台最小执行/导出边界，主要用于 cases 体系的统一入口与资产化契约演示；真实数值教学路径从后续教学型 API 示例（如 `ex-03-poisson-basic`）开始。因此本示例只展示执行边界与导出边界的连接方式，不展示真实物理结果。

---

## 文件说明

### `CMakeLists.txt`

定义示例 target：

```text
perisci_dataset_export
```

构建后输出可执行文件：

```text
perisci-dataset-export
```

### `dataset_export.cpp`

示例主程序。它在代码中构造一份教学用 JSON 配置，然后执行：

```text
run_case -> export_dataset -> dataset/
```

默认输出位置为：

```text
build/examples/ex-02-dataset-export/dataset
```

也可以在运行时传入自定义输出目录。

---

## 构建方式

从仓库根目录执行：

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_dataset_export -j
```

如果使用其他 CMake 生成器，也可以执行：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target perisci_dataset_export
```

---

## 运行方式

使用顶层 CMake 的默认输出布局时：

```bash
./build/bin/perisci-dataset-export
```

Windows PowerShell 中通常为：

```powershell
.\build\bin\perisci-dataset-export.exe
```

如需指定输出目录：

```powershell
.\build\bin\perisci-dataset-export.exe .\build\examples\my-dataset-export
```

预期输出会包含：

- API version
- Schema version
- Run status
- Export ok
- Dataset root
- 生成的关键 dataset 文件路径

---

## 与 ex-01 的区别

`ex-01-config-basics` 只展示：

```text
ConfigJson -> run_case -> RunResults
```

本示例进一步展示：

```text
RunResults -> export_dataset -> dataset/
```

这说明并非所有示例都需要落盘。只有当教学目标涉及 dataset 生成、结果资产化或导出边界时，示例才需要调用 `export_dataset`。

---

## 与 cases 的区别

本示例会生成 `dataset/`，但它仍不是 case asset。

它不会包含：

- `expected.json`
- CI 回归门禁规则
- 算例资产冻结声明

如果未来某个 dataset 具备稳定的物理意义、数值行为和验证标准，应迁移或复制到 `cases/`，再作为正式 case asset 维护。
