# ADR-0000: <简要标题 | Short Title>

- 状态（Status）：提议中 / 已接受 / 已拒绝 / 已废弃  
- 日期（Date）：YYYY-MM-DD  
- 相关版本（Related Version）：vX.Y.Z（如适用）  
- 关联议题（Related Issues / PRs）：#xxx（如有）

---

## 背景与上下文 | Context 
**描述：**

简要描述做出该架构决策的背景，包括但不限于：

- 当前系统所处的发展阶段  
- 现有架构或实现中存在的问题或限制  
- 触发本次决策的直接原因  

**Description:**

Briefly describe the context in which this architectural decision is made,
including but not limited to:

- The current stage of the system  
- Limitations or issues in the existing architecture or implementation  
- The immediate motivation for this decision  

---

## 问题陈述 | Problem Statement 
**陈述：**

清晰、具体地陈述需要解决的**架构级问题**。  
请避免描述具体实现细节，而应聚焦于“为什么这是一个架构问题”。

**Statement:**

Clearly and concretely state the **architecture-level problem** to be solved.  
Avoid implementation details; focus on why this is an architectural concern.

---

## 备选方案 | Considered Options  
### 方案 A | Option A 
**描述：**

- 简要描述该方案  
- 说明其优点与潜在风险  

**Description:**

- Brief description of the option  
- Advantages and potential risks  

---

### 方案 B | Option B   
**描述：**

- 简要描述该方案  
- 说明其优点与潜在风险  

**Description:**

- Brief description of the option  
- Advantages and potential risks  

---

> 可根据需要增加或减少方案数量。  
> Include more or fewer options as necessary.

---

## 决策 | Decision  
**解释：**

明确说明最终选择的方案，并解释：

- 为什么选择该方案  
- 为什么拒绝其他方案  

**Explanation:**

Clearly state the chosen option and explain:

- Why this option was selected  
- Why other options were rejected  

---

## 对架构边界的影响 | Impact on Architectural Boundaries
**澄清：**

请明确说明本决策是否影响 `ARCHITECTURE.md` 第 4 节定义的
**不可轻易改动的设计边界（Hard Design Boundaries）**：

- [ ] 不影响任何硬边界  
- [ ] 影响以下硬边界（请列出 Boundary 编号并说明）  

如有影响，必须说明对应的版本策略（例如 MAJOR 版本变更）。

**Clarification:**

Explicitly state whether this decision affects any
**Hard Design Boundaries** defined in Section 4 of `ARCHITECTURE.md`:

- [ ] Does not affect any hard boundary  
- [ ] Affects the following hard boundaries (list Boundary IDs and explain)  

If affected, the corresponding versioning implications (e.g., MAJOR bump)
must be stated.

---

## 影响与后果 | Consequences
**说明：**

描述该决策带来的直接与间接影响，包括但不限于：

- 对现有用户的影响  
- 对配置、数据、API 的影响  
- 对维护成本与长期演进的影响  

**Implications:**

Describe the direct and indirect consequences of this decision,
including but not limited to:

- Impact on existing users  
- Impact on configuration, data, and APIs  
- Impact on maintenance cost and long-term evolution  

---

## 迁移与兼容策略（如适用）| Migration and Compatibility (If Applicable)
**剖析：**

如该决策引入破坏性变更，请说明：

- 是否提供迁移路径  
- 是否存在过渡期或兼容层  

**Analysis:**

If this decision introduces breaking changes, describe:

- Whether a migration path is provided  
- Whether a transition period or compatibility layer exists  

---

## 备注 | Notes
**说明：**

补充任何有助于未来理解本决策的背景信息，
例如当时的技术条件、资源限制或未解决的问题。

**Explanation:**

Add any additional context that may help future readers understand
this decision, such as technical constraints, resource limitations,
or open questions at the time.
