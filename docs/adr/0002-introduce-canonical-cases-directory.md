
# ADR-0002: Introduce Canonical `cases/` Directory for Reproducible Simulation Assets

- 状态（Status）：已接受  
- 日期（Date）：2026-03-06  
- 相关版本（Related Version）：v0.2.0
- 基准版本（Baseline Version）：v0.1.5
- 关联议题（Related Issues / PRs）：N/A

---

## 背景与上下文 | Context 

**描述：**

在 PeriSci v0.1.5 的基础架构中，仓库已经包含以下关键目录：

- `core/`：PeriFEM 数值内核  
- `api/`：稳定对外契约层  
- `python/` 与 `apps/`：运行时入口  
- `examples/`：教学示例与能力演示  
- `tests/`：回归测试  

然而，在早期结构中，**标准算例（canonical simulation cases）并没有一个独立、稳定的存放位置**。  
一些示例既承担教学演示作用，也承担实验配置角色，这导致：

- 教学示例与标准算例之间的角色边界不清晰  
- 难以明确哪些实验配置应被长期稳定保存  
- 回归测试缺乏统一的输入来源  
- AI 数据生成流程缺乏稳定、可追溯的算例资产基础  

因此，需要在仓库结构中引入一个专门用于存放 **标准算例资产（canonical case assets）** 的目录。

**Description:**

In the v0.1.5 baseline architecture of PeriSci, the repository already included
several core directories:

- `core/`: PeriFEM numerical kernel  
- `api/`: stable external contract layer  
- `python/` and `apps/`: runtime entry layers  
- `examples/`: teaching demonstrations and capability showcases  
- `tests/`: regression testing  

However, the early structure did not provide a dedicated location for
**canonical simulation cases**.

Some examples simultaneously served as teaching demonstrations and experimental
configurations, which led to several issues:

- Unclear boundary between teaching examples and canonical cases  
- Difficulty identifying which experiment configurations should be preserved long-term  
- Lack of a unified input source for regression tests  
- No stable, traceable foundation for AI dataset generation workflows  

To address this, a dedicated directory for **canonical case assets** is introduced.

---

## 问题陈述 | Problem Statement 

**陈述：**

PeriSci 需要一个清晰的机制来区分以下三类实验对象：

1. **教学与探索示例（examples）**  
   用于学习、演示和快速实验  

2. **标准算例（canonical cases）**  
   用于长期保存、复现实验和生成数据  

3. **回归验证（tests）**  
   用于确保系统演进不会破坏既有行为  

如果这些角色混合在同一目录中，将导致：

- 示例不断变化，无法作为稳定回归输入  
- 实验配置难以复现  
- 数据资产缺乏明确来源  

因此需要在架构层面明确：

```
examples → cases → tests
```
这一实验体系结构。

**Statement:**

PeriSci requires a clear mechanism to distinguish three types of experimental
artifacts:

1. **Teaching and exploratory examples (`examples/`)**  
   Used for learning, demonstrations, and quick experimentation  

2. **Canonical cases (`cases/`)**  
   Used for long-term preservation, reproducible experiments, and dataset generation  

3. **Regression validation (`tests/`)**  
   Used to ensure that system evolution does not break established behavior  

If these roles remain mixed within a single directory, it leads to:

- Examples evolving too frequently to serve as stable regression inputs  
- Experiment configurations becoming difficult to reproduce  
- Dataset assets lacking a clear origin  

Therefore, the architecture needs to explicitly introduce the structure:

```
examples → cases → tests
```
---

## 备选方案 | Considered Options  

### 方案 A | Option A 

**描述：**

继续将所有算例放在 `examples/` 中，通过命名或子目录区分。

**优点：**

- 结构简单  
- 不需要新增目录  

**风险：**

- 示例与标准算例角色混淆  
- 回归测试输入来源不稳定  
- 难以建立长期稳定的实验资产体系  

**Description:**

Keep all cases under `examples/` and distinguish canonical cases using naming
conventions or subdirectories.

Advantages:

- Simpler directory structure  
- No need to introduce a new directory  

Risks:

- Role confusion between teaching examples and canonical cases  
- Unstable input sources for regression tests  
- Difficulty establishing a stable experiment asset system  

---

### 方案 B | Option B 

**描述：**

引入独立的 `cases/` 目录，用于存放 **标准算例资产**。

**优点：**

- 明确区分示例与标准算例  
- 为回归测试提供稳定输入  
- 为 AI 数据生产提供可靠来源  
- 提升实验可复现性  

**风险：**

- 需要定义 examples → cases 的演进流程  
- 仓库结构略微增加复杂度  

**Description:**

Introduce a dedicated `cases/` directory for storing **canonical case assets**.

Advantages:

- Clear separation between examples and canonical cases  
- Stable inputs for regression tests  
- Reliable source for AI dataset generation  
- Improved reproducibility of computational experiments  

Risks:

- Requires defining a promotion workflow from examples to cases  
- Slightly increases repository structure complexity  

---

## 决策 | Decision  

**解释：**

选择 **方案 B**。

在仓库中新增：
```
cases/
```
用于集中存放 **标准算例资产（canonical case assets）**。

同时明确实验体系结构：
```
examples → cases → tests
```
其中：

- `examples/`  
  用于教学、演示与探索  

- `cases/`  
  存放经过验证并冻结的标准算例  

- `tests/`  
  使用 `cases/` 作为回归输入  

**Explanation:**

**Option B** is adopted.

A new directory is introduced:
```
cases/
```
to store **canonical simulation case assets**.

The experiment structure is defined as:
```
examples → cases → tests
```
Where:

- `examples/` serve teaching and exploratory purposes  
- `cases/` store validated and stable canonical simulation cases  
- `tests/` use canonical cases as regression inputs  

---

## 对架构边界的影响 | Impact on Architectural Boundaries

**澄清：**

- [ ] 不影响任何硬边界  
- [x] 影响以下硬边界  

影响：

- **Boundary 5 — Reproducibility and Provenance**

通过引入 `cases/`，PeriSci 的实验可复现性结构被进一步强化。

同时，该目录被纳入长期稳定结构：
```
core → api → cases
```
**Clarification:**

- [ ] Does not affect any hard boundary  
- [x] Affects the following hard boundaries  

Affected boundary:

- **Boundary 5 — Reproducibility and Provenance**

The introduction of `cases/` strengthens the reproducibility structure of
PeriSci and incorporates it into the long-term stability structure:
```
core → api → cases
```
---

## 影响与后果 | Consequences

**说明：**

该决策带来的主要影响包括：

- 仓库新增 `cases/` 目录  
- 明确 examples → cases 的演进关系  
- 回归测试逐步使用 `cases/` 作为输入来源  
- AI 数据生成流程可直接基于标准算例  

同时：

- 示例不再被视为稳定实验资产  
- 标准算例成为可复现计算实验的核心基础  

**Implications:**

This decision introduces the following consequences:

- A new `cases/` directory is added to the repository  
- A clear evolution path from examples to cases is defined  
- Regression tests gradually use canonical cases as inputs  
- AI dataset generation can rely on stable case assets  

At the same time:

- Examples are no longer treated as stable experiment assets  
- Canonical cases become the core foundation of reproducible experiments  

---

## 迁移与兼容策略（如适用）| Migration and Compatibility (If Applicable)

**剖析：**

该变更不会破坏现有 API 或配置语义，因此：

- 不需要立即迁移现有代码  
- 现有 examples 可逐步被提升为 canonical cases  

**Analysis:**

This change does not break existing APIs or configuration semantics.

Therefore:

- No immediate migration is required  
- Existing examples may gradually be promoted into canonical cases  

---

## 备注 | Notes

**说明：**

该决策使 PeriSci 的实验体系更加清晰：
```
examples → cases → tests
```
并将 `cases/` 纳入系统长期稳定结构：
```
core → api → cases
```
这为未来的：

- 可复现实验  
- AI 数据生产  
- 长期回归验证  

提供了稳定基础。

**Explanation:**

This decision clarifies the experiment structure of PeriSci:
```
examples → cases → tests
```
and integrates `cases/` into the long-term stability structure:
```
core → api → cases
```
This provides a stable foundation for:

- reproducible experiments  
- AI dataset generation  
- long-term regression validation