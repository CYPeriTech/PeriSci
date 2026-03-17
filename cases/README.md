# 算例资产概述 | Case Assets Overview

本目录用于存放 PeriSci 的算例资产（Case Assets）。

一个完整的算例资产由以下文件构成：

- `input.json` —— 问题定义
- `expected.json` —— 验证判据
- `README.md` —— 对外说明
- `notes.md` —— 维护记录（对内）

---

## 0. 当前仓库中的最小算例资产

当前仓库已包含一个最小算例资产，用于平台闭环门禁：

```
cases/case-00-minimal
```

该算例资产的定位是：

- **平台闭环 smoke gate**
- 不追求物理正确性与数值精度
- 主要用于验证 `run_case → export_dataset → validate_case` 最小闭环是否可用，并验证基于配置契约的执行链路已经贯通

因此，在 v0.2.x 阶段，`case-00-minimal` 的 `expected.json` 可以保持为“结构/状态类门禁”（例如 status 不得失败），并逐步演进为更强的结构校验与可观测性字段校验。

---

## 1. input 与 expected 的职责划分

### 1.1 input.json —— 问题定义层

`input.json` 定义：

- 要求解的物理/数学问题
- 数值离散与求解配置
- 执行所需的全部权威参数

特性：

- 必须符合 config_schema 规范
- 参与 canonical 表示与 config_hash 计算
- 修改 input 等价于改变“问题定义”

> v0.2.x 阶段为了支持平台 smoke gate（如 `case-00-minimal`），允许最小配置仅包含 `meta` 分区。  
> `meta` 用于标识与追踪（如 `schema_version`、`config_id`），不得影响数值行为。  
> 当未来引入严格 schema 校验时，必须确保该最小输入仍然合法（详见 config-schema 的 v0.2.x 最小配置条款）。

---

### 1.2 expected.json —— 验证判据层

`expected.json` 定义：

- 运行结果是否“通过”的判据
- 数值指标阈值
- 不变量约束
- 结构完整性检查

特性：

- 不参与 config_hash
- 不影响执行流程
- 仅用于回归验证

修改 expected 等价于改变“通过标准”。

> expected 的校验对象可以逐步扩展：
>
> - v0.2.x：以“结构/状态/必备字段存在性”为主（平台 smoke gate）
> - v0.3.x+：逐步加入数值阈值、不变量、收敛行为等（能力基准）

---

## 2. README.md —— 对外说明层

README 是算例的说明书。

它应包含：

- 问题背景与数学定义
- 输入关键字段说明
- 运行步骤
- 回归判据摘要
- 结果解释
- 适用范围与局限性

README 内容应保持稳定、结构化、可长期引用。

---

## 3. notes.md —— 维护记录层

`notes.md` 用于记录：

- 回归失败分析
- 阈值调整原因
- 数值稳定性问题
- 平台差异
- 可疑点与坑
- 后续改进计划
- 模型限制说明

特性：

- 不属于权威规范
- 不参与 hash 或验证逻辑
- 可频繁修改
- 不作为教程入口

重要原则：

- notes 永远不讨论格式选择
- notes 不重新定义规范
- notes 只记录过程性信息

---

## 4. 执行关系

标准流程：

```text
input.json
   │
   ▼
run_case
   │
   ▼
results (bundle)
   │
   ▼
export_dataset
   │
   ▼
dataset
   │
   ▼
validate_case  ◀── expected.json
```

说明：

- **input.json**：权威输入配置，定义问题与执行所需的合法参数
- **run_case**：执行计算，产出 `results` / `bundle`（内存态）
- **export_dataset**：唯一允许落盘的边界，将运行结果固化为 `dataset`（资产态）
- **validate_case**：校验程序入口，可对 `results`、`dataset` 或其 manifest 进行结构检查、状态检查和回归判定
- **expected.json**：只定义“通过标准”，不参与执行，仅参与校验判定

需要特别区分的是：

- **三梁执行结构**对应的是：
  - 配置梁（Config Beam / `config_schema`）
  - 执行梁（Run Beam / `run_case`）
  - 输出梁（Export Beam / `export_dataset`）
- **validate_case** 不属于三梁本身，而属于回归验证与实验门禁机制
- **expected.json** 也不属于执行结构，而是验证判据配置

因此，可以更准确地理解为：

- `input.json` 定义问题
- `run_case` 执行问题
- `export_dataset` 固化结果
- `validate_case + expected.json` 共同判定该结果是否通过回归门禁

---

## 5. 时间维度上的关系（版本演进）

### 初始创建 case 时：

- 先写 input
- 跑一次
- 再写 expected（根据实际结果设阈值）

顺序是：

```
input → 执行 → 观察 → 写 expected
```

不是反过来。

---

### 后续演进时：

#### 情况 A：算法改进

- input 不变
- 结果更精确
- expected 阈值可能变得更严格

这说明能力增强。

---

#### 情况 B：问题定义变化

- input 改了
- expected 必须重新生成

这是“新问题”，不是“算法改进”。

---

## 6. 治理区分

修改 input = 改变问题定义  
修改 expected = 改变通过标准  
修改 notes = 更新维护记录

三者语义不同，应在评审中区分。

---

## 7. 设计原则总结

- input 描述系统行为
- expected 约束系统行为
- README 解释系统行为
- notes 记录演进过程

四者构成：

> 可重复数值实验 + 可判定计算结果 + 可维护历史

**注：Case资产创建标准流程，详见：CASE_WORKFLOW.md**
