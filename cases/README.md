# 算例资产概述 | Case Assets Overview

本目录用于存放 PeriSci 的算例资产（Case Assets）。

一个完整的算例资产由以下文件构成：

- `input.json` —— 问题定义
- `expected.json` —— 验证判据
- `README.md` —— 对外说明
- `notes.md` —— 维护记录（对内）

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

```
input.json  ──▶  run_case  ──▶  results
                                   │
                                   ▼
                             export_dataset
                                   │
                                   ▼
                                dataset
```

然后：

```
(results + dataset)  ──▶  expected.json 校验
```

expected 不参与执行，只参与验证。

>因此，可以认为：input 产生结果；expected 约束结果

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

------

### 后续演进时：

#### 情况 A：算法改进

- input 不变
- 结果更精确
- expected 阈值可能变得更严格

这说明能力增强。

------

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

> 可重复实验 + 可判定结果 + 可维护历史

**注：Case资产创建标准流程，详见：CASE_WORKFLOW.md**