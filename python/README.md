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

Python 层只通过 **权威 CLI 边界** 调用系统。

---

## CLI 边界（权威执行入口）

Python 层只调用以下三个 CLI：

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

- 验证 canonical cases
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
| `dataset.py` | dataset 相关工具与辅助函数 |
| `cli.py` | Python 侧 CLI 封装 |
| `__main__.py` | 支持 `python -m perisci` 入口 |
| `__init__.py` | Python 包初始化 |

示例调用：
```python
from perisci import run
```

或命令行：
```
python -m perisci
```
