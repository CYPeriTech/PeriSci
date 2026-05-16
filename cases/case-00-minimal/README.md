# case-00-minimal（v0.2.x 平台基线 / v0.3.x+ smoke gate）

本目录是 PeriSci 的 **最小算例资产（case asset）**，用于验证平台的基本执行闭环：

- run：纯执行（不产生文件系统副作用）
- validate：结构与门禁检查
- export：唯一允许写入数据集资产的边界

该算例主要用于验证平台基础能力是否正常工作。

---

## 本算例的定位

- 目的：**平台执行管线的 smoke gate（基础门禁）**
- 物理正确性保证：**无**
- 数值正确性保证：**无**

本算例存在的主要意义是确保以下功能正常：

1. `perisci-run` 可以接受权威 JSON 配置并成功执行
2. `perisci-validate` 可以对结果结构进行基本检查
3. `perisci-export` 在未来可以生成合法的数据集结构

---

## 目录结构

本算例包含以下文件：

### `input.json`

权威输入 JSON。

注意：

- 输入 JSON 必须保持 **原始文本形式**
- 不允许自动填充默认值
- 不允许在 Python 层修改

---

### `expected.json`

回归门禁规则。

作为 v0.2.x 平台基线，并在 v0.3.x+ 中继续作为 smoke gate，本算例仅要求：

status 不得为 failed

即：

```json
{
  "status_must_not_be": "failed"
}
```
