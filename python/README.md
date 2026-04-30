# PeriSci Python Layer (v0.2.x)

本目录包含 **PeriSci 的 Python 工作流层（workflow layer）**。

它的职责不是实现数值计算本身，也不是定义新的物理语义或配置契约，而是为教学、研究脚本、自动化和 AI 数据生产提供一个更容易组织的外层入口。

在仓库整体分层中，`python/` 对应根 README 中的：

```text
python/  # Python 绑定与工作流层（教学、AI 数据生产、脚本接口）
```

---

## 1. 定位与边界 | Role and Boundaries

### Python 层是什么

- 教学与演示工作流层
- 研究脚本入口
- 自动化与批量组织层
- dataset 与算例运行的辅助编排层

### Python 层不是什么

- 不是数值内核
- 不是权威配置契约层
- 不是 regression 的权威归属层
- 不是 `examples/` 的镜像目录

### 当前 v0.2.x 的实现状态

当前 `v0.2.x` 中，Python 层是一个**基于 CLI 的过渡性包装层**。

也就是说，当前实际执行路径更接近：

```text
python -> apps -> api -> core
```

但这只是阶段性实现方式，不代表长期架构边界。

长期目标仍应与 `docs/ARCHITECTURE.md` 保持一致：

```text
python -> api -> core
```

### 边界提醒

- Python 层可以**编排** `run -> export -> validate`
- 但这不意味着 Python 层拥有 `cases + tests` 的 regression 权威
- Python 层可以**调用** `validate`
- 但 `validate_case` 仍然属于围绕 case asset 的验证与门禁机制，而不是 Python 自己发明的新层

---

## 2. 五分钟学习路径 | Five-Minute Path

如果你第一次接触 `python/`，推荐只做下面四件事。

### 第一步：先构建 C++ 可执行程序

在仓库根目录执行：

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

### 第二步：让 Python 找到本地包

仍然在仓库根目录执行：

```powershell
$env:PYTHONPATH = "$PWD\python"
```

### 第三步：运行最小闭环工作流

```powershell
python -m perisci run .\cases\case-00-minimal\input.json > .\build\bundle.json

python -m perisci export --bundle .\build\bundle.json --out .\build\py_cli_demo > .\build\export_report.json

python -m perisci validate .\build\py_cli_demo\dataset
```

### 第四步：看懂这三个产物

- `build/bundle.json`：`run` 的内存态结果包
- `build/py_cli_demo/dataset/`：`export` 生成的数据集目录
- 终端里的 validation JSON：`validate` 的结构检查结果

如果这四步你已经能顺下来，说明你已经理解了 Python 层最核心的教学目标：  
**它不是重新实现求解器，而是把已有入口组织成一个可教学、可脚本化的工作流。**

---

## 3. 为什么在 Python 层学习闭环 | Why Learn the Loop Here

PeriSci 里有四个相邻但不同的角色：

| 位置 | 主要职责 |
| --- | --- |
| `examples/` | 教 C++ API 边界与最小可运行示例 |
| `python/` | 教如何组织 `run / export / validate` 工作流 |
| `cases/` | 提供稳定、可复现的 canonical inputs |
| `tests/` | 使用 canonical cases 承担 regression 与 CI gate |

因此：

- 如果你想学 `run_case` / `export_dataset` 的 **C++ API 边界**，先看 `examples/`
- 如果你想学如何把三步串起来形成 **工作流**，看 `python/`
- 如果你想看**稳定输入**从哪里来，去 `cases/`
- 如果你想看**回归权威**落在哪里，去 `tests/`

这也是为什么 `python/README.md` 不应该写成一个新的 `example`，而应该写成一个**工作流教学文档**。

---

## 4. 为什么复用 `case-00-minimal` | Why Reuse `case-00-minimal`

当前 Python 教学文档复用：

```text
cases/case-00-minimal/input.json
```

这是刻意的，而不是偷懒。

原因有三点：

- `case-00-minimal` 已经是仓库里现成的 **最小 canonical case**
- Python 层这里要教的是**工作流组织**，不是再发明一份新的教学配置
- 复用 canonical case 可以避免在 `python/` 里再长出一份职责重叠的影子输入

所以在当前阶段，**Python 教程复用 `case-00-minimal` 是合理且推荐的**。

只有当未来 Python 层要讲的是另一类工作流主题，比如参数扫描、批量 case 组织、数据后处理时，才需要引入新的示范输入。

---

## 5. 三个步骤各自产生什么 | What Each Step Produces

Python 层最值得学会的，不只是“怎么执行命令”，而是：  
**每一步到底产出什么对象，它和三梁/验证机制的关系是什么。**

### 5.1 `run` 产生什么

`run` 对应执行梁（Run Beam）的 Python 包装，最终调用 `perisci-run`。

它产出的是一个 **bundle JSON / Python dict**，大致形状如下：

```json
{
  "config_b64": "...",
  "results": {
    "status": "success",
    "message": "...",
    "notes": ["..."]
  },
  "run_report": {}
}
```

理解重点：

- `run` 只返回**内存态运行结果**
- 它**不负责**生成 `dataset/`
- `config_b64` 用于把输入配置随 bundle 一起传递下去
- `run_report` 是观测信息位；在当前 `v0.2.x` 阶段可能为空，后续可逐步增强

### 5.2 `export` 产生什么

`export` 对应输出梁（Export Beam）的 Python 包装，最终调用 `perisci-export`。

它产出两类东西：

1. 一个 **export report**
2. 一个真正落盘的 `dataset/`

`export report` 大致形状如下：

```json
{
  "ok": true,
  "dataset_root": "D:/.../dataset",
  "message": "..."
}
```

理解重点：

- `export` 是**唯一合法的 dataset 固化入口**
- dataset 的生成职责仍然属于 `export_dataset` / `perisci-export`
- Python 只是负责把这一步组织进 workflow

### 5.3 `validate` 产生什么

`validate` 对应验证入口的 Python 包装，最终调用 `perisci-validate`。

它返回一个 **validation report**，大致形状如下：

```json
{
  "ok": true,
  "error_count": 0,
  "warning_count": 0,
  "info_count": 0,
  "issues": []
}
```

理解重点：

- `validate` 检查的是导出的 `dataset` / `manifest`
- 它可以被 Python 调用，但**不意味着 regression 职责转移到了 Python**
- regression 的权威组织仍然在 `cases + tests`

---

## 6. 最常用的两种调用方式 | Two Common Ways to Use It

### 6.1 方式一：作为命令行工作流包装层

适合：

- 直接在终端里跑工作流
- 写批处理脚本
- 快速串联 `run / export / validate`

先看帮助：

```powershell
python -m perisci --help
python -m perisci run --help
python -m perisci export --help
python -m perisci validate --help
```

#### `run`

```powershell
python -m perisci run <config.json>
python -m perisci run <case-dir>
python -m perisci run <case-name>
```

例如：

```powershell
python -m perisci run case-00-minimal
```

如果当前工作目录是仓库根目录，上面的写法会自动解析到：

```text
cases/case-00-minimal/input.json
```

#### `export`

```powershell
python -m perisci export --bundle .\build\bundle.json --out .\build\py_cli_demo
```

#### `validate`

```powershell
python -m perisci validate .\build\py_cli_demo\dataset
```

这里既可以传 `manifest.json`，也可以直接传 `dataset` 目录。

### 6.2 方式二：作为 Python 包调用

适合：

- 在 Python 脚本中组织工作流
- 在 Notebook / 交互式 Python 中试验接口
- 在自动化逻辑里组合多个 case

示例：

```python
from pathlib import Path
from perisci import run_case, export_dataset, validate_case

repo_root = Path.cwd()
config_path = repo_root / "cases" / "case-00-minimal" / "input.json"
config_json = config_path.read_text(encoding="utf-8")

bundle = run_case(config_json)
report = export_dataset(bundle, str(repo_root / "build" / "py_package_demo"))
validation = validate_case(report["dataset_root"])

print(bundle)
print(report)
print(validation)
```

说明：

- `run_case()` 接收的是**权威配置 JSON 文本**
- `export_dataset()` 接收 bundle，并把 dataset 导出到你指定的目录
- `validate_case()` 可以接收 `dataset_root` 或 `manifest.json` 路径

如果 Python 找不到 `perisci-run` / `perisci-export` / `perisci-validate`：

- 先确认你已经完成了 C++ 构建
- Python 会优先从 `PATH` 查找
- 如果 `PATH` 中没有，它还会尝试查找仓库下的 `build/bin/`

---

## 7. Python 包结构 | Package Layout

```text
python/
└─ perisci/
   ├─ __init__.py
   ├─ __main__.py
   ├─ cli.py
   ├─ run.py
   ├─ export.py
   └─ validate.py
```

| 模块 | 作用 |
| --- | --- |
| `run.py` | 对执行梁的薄包装 |
| `export.py` | 对输出梁的薄包装 |
| `validate.py` | 对验证入口的薄包装 |
| `cli.py` | `python -m perisci` 的命令行封装 |
| `__main__.py` | 模块入口 |
| `__init__.py` | 对外暴露 `run_case` / `export_dataset` / `validate_case` |

---

## 8. 和其他目录的关系 | Relationship to Other Layers

### 与 `examples/` 的关系

- `examples/` 教 C++ API 的正确使用方式
- `python/` 教如何组织更高层的工作流

尤其是：

```text
examples/ex-02-dataset-export
```

展示的是：

```text
run_case -> export_dataset -> dataset/
```

而 `python/` 展示的是：

```text
run -> export -> validate
```

两者互补，但不应互相复制。

### 与 `cases/` 的关系

- `cases/` 提供 canonical inputs
- Python 教程优先复用 canonical case，而不是在 `python/` 里复制一份新输入

### 与 `tests/` 的关系

- `tests/` 承担 regression gate
- Python 可以调用 `validate`
- 但 Python 文档的教学闭环不等于测试闭环的权威定义

---

## 9. 常见误解 | Common Misunderstandings

### 误解 1：Python 能调用 `validate`，所以 regression 属于 Python

不对。  
Python 只是一个**工作流调用层**；regression 的权威仍在 `cases + tests`。

### 误解 2：Python 导出了 dataset，所以 dataset 依赖 Python

不对。  
dataset 的固化边界仍然是 `export_dataset` / `perisci-export`；Python 只是把它组织起来。

### 误解 3：Python 层应该复制一套 `examples/`

不对。  
`examples/` 负责 C++ API 教学，`python/` 负责 workflow 教学，职责不同。

### 误解 4：既然能用 `case-00-minimal`，那 Python README 就只是测试说明

也不对。  
这里复用 `case-00-minimal`，是为了给工作流教学提供**现成、稳定、最小的 canonical input**，而不是把 Python README 变成测试文档。

---

## 10. 下一步看什么 | Where to Go Next

如果你已经理解了本 README，下一步建议按顺序看：

1. `examples/ex-01-config-basics`：理解配置与 `run_case`
2. `examples/ex-02-dataset-export`：理解 `export_dataset` 为什么是唯一落盘边界
3. `cases/case-00-minimal`：理解 canonical case 与最小闭环 gate
4. `docs/ARCHITECTURE.md`：理解 Python 层在整体架构中的位置

这样学下来，`python/` 就不会只是“会敲三条命令”，而会真正变成你理解 PeriSci 工作流分层的入口。
