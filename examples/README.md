# 示例目录说明（examples）

本目录用于存放 PeriSci 的教学示例（Examples）。

示例的目标是：

- 展示功能
- 教学演示
- 探索能力
- 说明 API 使用方式
- 提供进阶学习路径

示例不是算例资产（Case Asset）。

---

## 0. 当前示例目录结构

当前仓库中的 examples 目录结构如下：

```
examples/
 ex-00-hello/
 ex-01-minimal-run/
```

说明：

- **ex-00-hello**：环境验证示例（Quickstart）
- **ex-01-minimal-run**：最小运行示例，用于展示 CLI 执行流程

未来示例将按编号逐步增加。

---

## 1. 示例与算例的区别

| 项目                 | examples   | cases          |
| -------------------- | ---------- | -------------- |
| 目的                 | 教学与展示 | 回归与基准验证 |
| 是否必须稳定         | 否         | 是             |
| 是否有 expected.json | 否         | 是             |
| 是否受 CI_GATES 强制 | 否         | 是             |
| 是否长期冻结         | 否         | 是             |

示例可以探索、演进、重构。  
算例资产必须稳定、可验证、可追溯。

---

## 1.1 与 cases/case-00-minimal 的关系

仓库中同时存在一个最小算例资产：

```
cases/case-00-minimal
```

它与 `examples/ex-01-minimal-run` 的职责不同：

| 项目                 | ex-01-minimal-run | case-00-minimal |
| -------------------- | ----------------- | --------------- |
| 位置                 | examples          | cases           |
| 用途                 | CLI 使用示例      | CI 回归门禁     |
| 是否稳定             | 可演进            | 必须稳定        |
| 是否含 expected.json | 否                | 是              |

因此：

- **examples 可以修改**
- **cases 必须保持稳定**

两者共同构成：

```
教学路径 + 回归验证
```

---

## 2. 命名规范

示例目录必须采用以下格式：

```
ex-XX-keyword
```

其中：

- `ex` 固定前缀
- `XX` 为两位数字排序编号（00, 01, 02, ...）
- `keyword` 为简洁英文关键词

示例：

```
ex-00-hello
ex-01-minimal-run
ex-02-config-basics
ex-03-poisson-basic
ex-04-poisson-refinement
ex-05-three-beam-intro
```

---

## 3. 排序规则

示例编号表示教学顺序，而非物理重要性。

推荐分级：

- 00：环境验证示例
- 01–09：基础入门示例
- 10–19：中级能力示例
- 20+：高级或专题示例

新增示例应：

- 保持编号连续
- 不轻易调整已有编号
- 避免频繁重排

---

## 4. 特殊示例：ex-00-hello

ex-00-hello 是环境验证示例（Quickstart Example）。

用途：

- 验证项目是否成功构建
- 验证 CLI 是否可运行
- 验证最小运行链路是否畅通

它不展示物理能力，不涉及数值收敛，不构成进阶教学内容。

建议所有新用户首先运行 ex-00-hello。

---

## 4.1 最小运行示例：ex-01-minimal-run

`ex-01-minimal-run` 用于展示 PeriSci CLI 的最小执行流程。

示例配置通常为：

```json
{
  "meta": {
    "schema_version": "1.0.0",
    "config_id": "example-minimal-run"
  }
}
```

最小运行方式：

```
cat examples/ex-01-minimal-run/input.json | perisci-run --config -
```

该命令会输出一个 JSON bundle。

随后可以进行数据导出：

```
cat bundle.json | perisci-export --bundle - --out output_dir
```

并进行验证：

```
perisci-validate output_dir/manifest.json
```

上述流程构成 PeriSci 的最小执行闭环：

```
run → export → validate
```

该示例的目的仅为展示执行流程，不保证任何物理正确性或数值结果。

---

## 5. 关键词选取原则

关键词应优先表达“教学重点”，而不是仅表达物理名称。

推荐优先级：

### 5.1 基础功能类

- minimal-run
- config-basics
- boundary-conditions
- solver-options
- dataset-export
- visualization

### 5.2 数值能力类

- poisson-basic
- poisson-refinement
- nonlinear-demo
- transient-demo
- convergence-study

### 5.3 物理问题类

- elasticity-beam
- diffusion-2d
- wave-1d
- coupled-physics

关键词应：

- 简洁
- 不使用空格
- 使用短横线分隔
- 不使用中文

---

## 6. 示例目录结构建议

每个示例目录建议包含：

- README.md（说明该示例的目的与使用方式）
- input.json（或示例配置文件）
- 可选脚本（运行或可视化）
- 可选结果文件（非权威）

示例不应包含：

- expected.json
- CI 强制规则
- 资产冻结声明

---

## 7. 示例的演进路径

推荐采用以下演进模式：

```
探索性示例
↓
稳定教学示例
↓
候选算例
↓
正式 Case Asset（迁移至 cases/）
```

当一个示例满足以下条件时，可以考虑升级为算例资产：

- 数值行为稳定
- 物理意义明确
- 结果可解释
- 可在 CI 中稳定运行
- 不依赖随机行为

升级流程：

1. 复制目录至 cases/
2. 添加 expected.json
3. 增加 CI 门禁
4. 编写完整 README
5. 添加 notes.md

---

## 8. 示例的维护原则

- 示例允许重构与改进
- 示例允许修改参数
- 示例不承诺数值稳定性
- 示例不参与长期基准验证

但应保证：

- 可以正常运行
- 能体现预期教学目标
- 不故意破坏基本功能

---

## 9. 示例与算例的协作关系

推荐结构：

```
examples/
ex-03-poisson-basic
ex-04-poisson-refinement

cases/
case-01-poisson
```

Poisson 示例用于教学：

- 展示问题定义
- 展示网格影响
- 展示 API 使用

Poisson 算例用于验证：

- 固定输入
- 固定 baseline
- 固定回归标准

两者职责不同，但可以共享概念背景。

---

## 10. 示例的治理定位

examples 是：

> 教学路径与能力展示层

cases 是：

> 能力验证与回归基准层

保持两层分离，是项目结构稳定的关键。

## 11. 示例结构级别（v0.3.x 引入）

除教学编号外，每个示例应标注其结构成熟度：

- demo：仅用于演示，不要求进入 run→export→validate 闭环
- closed-loop：可完整执行 run→export→validate
- pre-case：具备稳定输入与验证条件，可升级为 case

该标注用于指导示例向 case 的演进路径，不影响编号体系。
