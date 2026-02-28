# 算例资产 CI 审查清单（CI Gate Specification）

本文件定义 Case 资产的自动化质量门禁规则。

CI 的目标：

- 防止资产结构退化
- 防止验证规则回退
- 防止 input / expected 语义混淆
- 保证算例可执行、可验证、可维护

本清单为强制规则。

---

## 1. 适用范围

本 CI 门禁适用于：

- cases/ 下的所有 case-XX 目录
- 新增算例资产
- 修改 input.json / expected.json / README.md 的提交

不适用于：

- notes.md 的内容修改（除非删除文件）

---

## 2. 结构完整性检查（Structure Gates）

CI 必须检查：

### 2.1 必需文件存在

每个 case 目录必须包含：

- input.json
- expected.json
- README.md
- notes.md

缺失任一文件 → CI 失败。

---

### 2.2 JSON 合法性

- input.json 必须为合法 JSON
- expected.json 必须为合法 JSON

JSON 解析失败 → CI 失败。

---

## 3. input.json 合规检查（Input Gates）

### 3.1 Schema 合规

- input.json 必须通过 config-schema 校验

校验失败 → CI 失败。

---

### 3.2 禁止非 schema 字段

- 不允许引入未定义字段（以 schema 为准）

违规 → CI 失败。

---

## 4. expected.json 结构检查（Expected Structure Gates）

### 4.1 必须包含基本区块

expected.json 必须包含：

- invariants（数组）
- metrics（数组）
- artifacts（数组）

缺失 → CI 失败。

---

### 4.2 每条规则必须包含字段

每个规则项必须包含：

- id
- ref.readme_tag
- severity
- source
- assert

缺失任一字段 → CI 失败。

---

### 4.3 id 唯一性

- 所有 id 必须唯一
- 不得重复

重复 → CI 失败。

---

## 5. README ↔ expected 一致性检查（Tag Consistency Gates）

### 5.1 标签存在性

- expected.json 中的 ref.readme_item 必须在 README.md 中存在对应编号
- README 中的 M1.x / M2.x / M3.x 不得缺失对应 expected 项

不一致 → CI 失败。

---

### 5.2 标签类别正确性

- M1.x 只能对应 invariants
- M2.x 只能对应 metrics
- M3.x 只能对应 artifacts

违规 → CI 失败。

---

## 6. 执行门禁（Execution Gates）

CI 必须执行：

```
perisci-run --config input.json
perisci-export
```

必须满足：

- run_case 成功退出
- export 成功生成 dataset
- expected 验证通过

任一失败 → CI 失败。

---

## 7. 禁止事项（Prohibited Changes）

以下行为将被视为高风险变更：

### 7.1 修改 input 但未更新 expected

- 若 input.json 改变
- 且 expected.json 未更新
- 且验证失败

→ CI 失败。

---

### 7.2 删除不变量或降低严重级别

- 删除 invariants
- 将 severity 从 error 降级为 warning

→ 需明确说明理由，否则 CI 可阻止合并（策略可配置）。

---

### 7.3 在 notes 中定义规范

- notes.md 中不得重新定义 schema 或验证规则

（此条为人工审查项）

---

## 8. 自检与 CI 的关系

- cases/README.md 中的“自检清单”是人工流程。
- 本文件定义自动化强制规则。
- CI 规则优先级高于自检建议。

---

## 9. 资产门禁目标

一个合格的算例资产必须：

- 结构完整
- 输入合法
- 执行成功
- 判定稳定
- 标签一致
- 不发生语义混淆

CI 门禁的作用是：

> 防止能力退化  
> 防止验证标准漂移  
> 保证资产长期稳定

---

## 10. 后续可扩展项（未来增强）

未来可加入：

- input_hash 与 expected 绑定检查
- 自动对比 baseline 差异
- 自动生成回归报告
- 资产成熟度等级判定

当前版本不强制。
