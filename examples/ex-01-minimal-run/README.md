# ex-01-minimal-run（v0.2.x）

本目录演示 PeriSci 的 **最小执行示例**。

该示例仅用于展示如何向 `perisci-run` 传递一个最小 JSON 配置并完成执行。

本示例属于 **examples（示例层）**，不是算例资产（case asset）。

---

## 文件说明

### input.json

权威配置 JSON。

在本示例中，该文件内容刻意保持为：

{}

目的仅是演示最小执行流程，而不是描述具体物理问题或数值模型。

该 JSON 会被直接传递给：

perisci-run

作为执行输入。

---

## 与 /cases/ 目录的关系

正式的 **算例资产（case assets）** 位于：

/cases/

例如：

cases/case-00-minimal

算例资产目录通常包含：

input.json
expected.json
README.md
notes.md

这些算例用于：

- 回归测试
- CI 门禁
- 算例资产管理

而本目录中的示例 **不会参与回归测试**。

---

## 本示例的用途

该示例主要用于快速验证以下功能是否正常：

- CLI 执行流程
- JSON 输入管道
- Python wrapper 调用
- 基本执行链路

该示例 **不保证任何物理正确性或数值结果**。

其目的仅是帮助开发者快速测试平台运行流程。
