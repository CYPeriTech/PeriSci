# PeriSci Python Layer（v0.2.x）

本目录包含 **PeriSci 的 Python 工作流层（workflow layer）**。

Python 层的目标不是实现数值计算逻辑，也不是定义新的语义契约，而是提供：

- 教学与示例工作流
- 研究脚本入口
- AI / 自动化工具调用接口
- dataset 与算例运行辅助工具

Python 层始终处于 **runtime architecture 的最外层**：
```
python / apps → api → core
```

## v0.2.x 状态说明

当前 `v0.2.x` 的 Python 层实现是**基于 CLI 的临时适配/包装**，用于先建立最小可用的教学、研究与自动化工作流入口。

这意味着当前实现路径更接近：

```
python → apps → api → core
```

但这**不代表长期架构边界**。

长期目标仍应与 `docs/ARCHITECTURE.md` 保持一致：

```
python → api → core
```

也就是说，长期目标是 **`python → api`**，而不是 **`python → apps → api`**。

其中：

- `core/`：数值计算内核
- `api/`：稳定 C++ API 契约层
- `apps/`：CLI 执行入口
- `python/`：工作流与工具层

---

## 设计原则

Python 层是 **non-authoritative layer（非权威层）**。

因此必须遵守以下约束：

1. **不得引入新的语义**
2. **不得绕过 schema 验证**
3. **不得引入隐式默认值**
4. **不得绕过 CLI 边界直接操作核心逻辑**

当前 `v0.2.x` 中，Python 层通过 **CLI 适配层** 调用系统；这是过渡实现，不应被理解为长期正式边界。

---

## 当前 v0.2.x 的 CLI 适配实现（过渡态）

下述内容描述的是当前 `v0.2.x` 的实现方式，而不是长期架构承诺。

当前 Python 层主要调用以下三个 CLI：

### `perisci-run`

对应 **B 梁（run beam）**

职责：

- 纯执行
- 不产生 filesystem 副作用
- 返回结构化运行结果

---

### `perisci-export`

对应 **C 梁（export beam）**

职责：

- 唯一合法 dataset 写入点
- 在
```
output_dir/dataset
```
下生成 dataset 结构

---

### `perisci-validate`

对应 **validate beam**

职责：

- 验证 dataset manifest 或 dataset 目录
- 用于 CI / regression testing

---

## Python 包结构

Python 层以一个包形式提供：
```
python/perisci/
```
主要模块包括：

| 模块 | 作用 |
|-----|------|
| `run.py` | 封装运行工作流（调用 `perisci-run`） |
| `export.py` | dataset 导出工具（调用 `perisci-export`） |
| `validate.py` | 验证工具（调用 `perisci-validate`） |
| `cli.py` | Python 侧 CLI 封装 |
| `__main__.py` | 支持 `python -m perisci` 入口 |
| `__init__.py` | Python 包初始化 |

## 使用方式

当前 `v0.2.x` 的 Python 层本质上是对 `perisci-run`、`perisci-export`、`perisci-validate`
这三个 CLI 的 Python 包装，因此在使用前建议先完成 C++ 可执行程序构建。

推荐先在仓库根目录执行：

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

### 方式一：作为 Python 包调用

适用于：

- 在 Python 脚本中组织工作流
- 在交互式 Python / Notebook 中试验接口
- 在自动化脚本里组合 `run -> export -> validate`

如果你在**仓库根目录**下使用，需要先让 Python 能找到 `python/perisci/` 这个包目录：

```powershell
$env:PYTHONPATH = "$PWD\python"
```

然后启动 Python 解释器：

```powershell
python
```

再在 Python 提示符 `>>>` 中输入：

```python
from perisci import run_case, export_dataset, validate_case

config_json = r'{"schema_version":"1.0.0","case_id":"smoke"}'

bundle = run_case(config_json, perisci_run=r"D:\My_Work\Works\20260105_PeriSci\projects\perisci\build\bin\perisci-run.exe",)

report = export_dataset(bundle, r"D:\My_Work\Works\20260105_PeriSci\projects\perisci\build\py_package_demo", perisci_export=r"D:\My_Work\Works\20260105_PeriSci\projects\perisci\build\bin\perisci-export.exe",)

validation = validate_case(report["dataset_root"], perisci_validate=r"D:\My_Work\Works\20260105_PeriSci\projects\perisci\build\bin\perisci-validate.exe",)

print(bundle)
print(report)
print(validation)
```

说明：

- `from perisci import ...` 是 **Python 代码**，必须在 Python 解释器里执行，不能直接在 PowerShell 里输入。
- 上例显式传入了 `build/bin` 下的可执行文件路径，这样最清晰、最稳妥。
- 如果你已经把这些可执行文件所在目录加入了 `PATH`，则可以省略 `perisci_run=...`、`perisci_export=...`、`perisci_validate=...` 参数。

### 方式二：作为命令行调用

适用于：

- 直接在终端里运行工作流
- 编写批处理脚本
- 快速串联 `run / export / validate`

同样建议在**仓库根目录**下执行，并先设置：

```powershell
$env:PYTHONPATH = "$PWD\python"
```

你可以先查看帮助：

```powershell
python -m perisci --help
python -m perisci run --help
python -m perisci export --help
python -m perisci validate --help
```

一个完整的命令行示例如下：

```powershell
python -m perisci run .\cases\case-00-minimal\input.json > .\build\bundle.json

python -m perisci export --bundle .\build\bundle.json --out .\build\py_cli_demo > .\build\export_report.json

python -m perisci validate .\build\py_cli_demo\dataset\manifest.json
```

这三步分别表示：

1. `run`：读取 `input.json`，调用 `perisci-run`，把运行 bundle 输出到 `build/bundle.json`
2. `export`：读取 bundle，调用 `perisci-export`，把 dataset 导出到 `build/py_cli_demo/dataset`
3. `validate`：调用 `perisci-validate`，验证导出的 `manifest.json`

如果你当前就在 `python/` 目录下，也可以直接运行：

```powershell
python -m perisci --help
python -m perisci run ..\cases\case-00-minimal\input.json
```

但这种情况下，涉及 `cases/`、`build/` 的路径需要改成相对于 `python/` 目录的写法。
