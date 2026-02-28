# 维护记录（Maintenance Notes）

> 本文件为维护层内部记录。
> 不属于权威规范，不参与 config_hash，不参与回归判定。
> 不作为教程入口。
> 不得复用 README 的标签前缀体系。
> 不得讨论格式或协议选择。

---

## 维护层标签体系说明（Frozen Maintenance Tag Set）

维护层采用独立标签前缀体系，与 README 标签体系完全分离。

| 标签    | 英文                 | 含义           |
| ------- | -------------------- | -------------- |
| [FAIL]  | Failure Log          | 回归失败记录   |
| [THR]   | Threshold Rationale  | 阈值与指标决策 |
| [NUM]   | Numerical Stability  | 数值稳定性问题 |
| [ENV]   | Environment Notes    | 平台与环境差异 |
| [PIT]   | Known Pitfalls       | 已知问题与坑   |
| [PLAN]  | Planned Improvements | 后续改进计划   |
| [LIMIT] | Model Limits         | 模型与能力限制 |

标签前缀具有长期稳定性，不得改变语义。

---

## [FAIL] 回归失败记录（Failure Log）

### [FAIL-1]

- 日期：
- 提交版本：
- 失败现象：
- 影响指标（如 M2.1）：
- 初步判断：
- 最终原因：
- 处理方式：
- 是否需要修改 expected：
- 是否涉及 input 变化：

> 用于记录真实回归失败与分析过程。

---

## [THR] 阈值与指标决策（Threshold Rationale）

### [THR-1]

- 指标编号（如 M2.1）：
- 原阈值：
- 新阈值：
- 调整原因：
- 是否影响历史 baseline：
- 关联 commit：

> 用于记录为什么阈值为当前数值。
> 不允许在此重新定义指标语义。

---

## [NUM] 数值稳定性问题（Numerical Stability）

### [NUM-1]

- 触发条件：
- 网格规模：
- 参数范围：
- 误差表现：
- 是否可复现：
- 结论：

> 用于记录浮点误差、收敛异常、震荡等问题。

---

## [ENV] 平台与环境记录（Environment Notes）

### [ENV-1]

- 操作系统：
- 编译器版本：
- 编译选项：
- 硬件信息（可选）：
- 是否影响指标：
- 说明：

> 本节仅用于解释平台差异。
> 不作为规范字段。

---

## [PIT] 已知问题与坑（Known Pitfalls）

- {{示例：网格过粗时误差可能非单调}}
- {{示例：特定编译优化下结果波动}}

> 用于提醒维护者和贡献者。

---

## [PLAN] 后续改进计划（Planned Improvements）

### [PLAN-1]

- 改进目标：
- 预期影响：
- 是否涉及 input：
- 是否涉及 expected：
- 优先级：

示例：

- [ ] 增加收敛阶验证
- [ ] 引入更严格的不变量
- [ ] 优化 baseline 生成逻辑

---

## [LIMIT] 模型与能力限制（Model Limits）

### [LIMIT-1]

- 当前物理假设：
- 不适用范围：
- 已知误差来源：
- 尚未支持功能：

> 用于说明当前能力边界。
> 不用于重新定义规范。

---

## 使用原则（Maintenance Governance Rules）

1. 本文件允许频繁修改。
2. 不得写入权威规范条款。
3. 不得使用 README 标签前缀（如 M1.x / P1 / E1 等）。
4. 不得作为 API 或 schema 设计依据。
5. 所有记录应以“事实与分析”为主，避免情绪性描述。

---

## 维护层定位总结

input.json   → 定义问题  
expected.json → 定义验证标准  
README.md     → 对外说明  
notes.md      → 记录演进过程  

notes 是历史与推理记录，不是规范来源。
