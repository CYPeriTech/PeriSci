# Case 资产创建与修改标准流程

(Standard Workflow for Creating and Evolving a Case Asset)

本文件定义 Case 资产的创建、修改与演进流程。

目标：

- 保证资产结构清晰
- 防止 input / expected 语义混淆
- 防止验证标准回退
- 保证资产可重复、可判定、可维护

本文件描述“如何做”，具体自动化规则见：CI_GATES.md。

---

## 一、资产构成

一个完整的 Case 资产包含：

- input.json —— 问题定义
- expected.json —— 验证标准
- README.md —— 对外说明
- notes.md —— 维护记录

四者职责必须清晰分离。

---

## 二、新建算例资产流程

### 第 1 步：复制模板

```
cp -r cases/_template cases/case-XX-name
```

修改：

- 目录名称
- README 中的 Case ID
- expected.json 中的 case_id

---

### 第 2 步：定义 input.json（问题定义）

填写：

- 物理/数学问题
- 几何
- 边界条件
- 材料参数
- 离散与求解器配置

原则：

- 必须符合 config-schema
- 不添加未定义字段
- 保持最小可执行结构

语义提醒：

> 修改 input = 修改问题定义

---

### 第 3 步：首次执行

运行：

```
perisci-run --config input.json > bundle.json
perisci-export --bundle bundle.json --out output_dir
```

确认：

- 运行成功
- dataset 正确生成
- manifest 合法

此阶段：

- expected.json 暂不填写具体阈值
- 仅验证流程正确

---

### 第 4 步：定义 expected.json（验证标准）

基于实际运行结果填写：

- M1.x 不变量（治理级约束）
- M2.x 数值指标（误差、范数等）
- M3.x 结构检查（dataset 完整性）

原则：

- 阈值基于稳定运行结果
- 不设定过严导致偶发失败
- 不得修改 input 以“迎合”阈值

语义提醒：

> 修改 expected = 修改通过标准

---

### 第 5 步：完善 README.md

填写：

- 问题定义（[P]）
- 输入关键字段（JSONPath）
- 运行方式
- 回归判据摘要（与 expected 编号对应）
- 局限性说明

要求：

- 使用标签协议
- 编号必须与 expected.json 一一对应
- 不重复 schema 规则

---

### 第 6 步：补充 notes.md

记录：

- 阈值选择原因
- 首次运行误差
- 数值稳定性问题
- 平台差异
- 后续改进计划

原则：

- 不定义规范
- 不讨论格式选择
- 允许频繁修改
- 记录事实与分析

---

### 第 7 步：提交前自检

确认：

- input.json 合法且最小
- expected.json 与 README 编号一致
- expected 不参与执行逻辑
- notes 未复用 README 标签
- 执行结果稳定可复现

自动化检查规则见：CI_GATES.md

---

## 三、修改已有算例的流程

修改算例时，必须区分变更类型。

---

### 情况 A：算法实现改进

- input 不变
- 结果更精确

允许：

- 调整 expected 阈值
- 更新 notes 记录

禁止：

- 降低严重级别掩盖问题

---

### 情况 B：问题定义变化

- input 改变
- 可能改变 config_hash

必须：

- 重新执行
- 重新定义 expected
- 更新 README
- 在 notes 中记录原因

---

### 情况 C：仅文档修改

- 修改 README 或 notes
- 不影响 input 与 expected

无需重新生成 baseline。

---

## 四、禁止行为

- 通过修改 input 来强行满足 expected
- 删除不变量以通过 CI
- 在 notes 中定义规范规则
- 修改 expected 却不说明原因

---

## 五、资产演进顺序

正确顺序：

```
定义问题 → 执行 → 观察 → 定义验证标准 → 文档化 → 记录维护信息
```

错误顺序：

```
先设阈值 → 再修改实现以迎合阈值
```

---

## 六、治理目标

一个成熟的 Case 资产应具备：

- 可重复执行
- 可稳定判定
- 可明确区分问题定义与验证标准
- 可长期维护
- 可追溯修改历史

最终目标：

> 可重复数值实验 + 可判定结果 + 可维护历史

---

## 七、与其他文档的关系

- 资产结构说明：见 README.md
- 自动化门禁规则：见 CI_GATES.md
- 输入规范定义：见 docs/specs/
- 设计原则：见 DESIGN_CONTRACT.md

本文件只定义流程。
