# 发布检查记录 | Release Checklists

## 目录说明 | Purpose of This Directory 

本目录用于存放 **PeriSci 各版本在打 tag 之前所使用的发布检查清单（sanity checklist）**。

这些 checklist 记录的是：
- 某一版本在发布当时，被认为已经满足的工程与治理条件
- 用于确认该版本是否可以被视为“可运行、可复现、可追溯”的稳定状态

它们不是功能说明文档，也不构成对未来能力的承诺。

This directory stores **release sanity checklists used before tagging each PeriSci version**.

These checklists record:
- The engineering and governance conditions considered satisfied at the time of release
- Confirmation that a given version was regarded as runnable, reproducible, and traceable

They are not feature descriptions and do not constitute commitments to future capabilities.

---

## Checklist 的使用时机 | When Checklists Are Used

每一份 checklist：
- **仅在对应版本打 tag 之前使用**
- 用于维护者的最终自检，而非自动化测试结果
- 反映的是“当时的判断”，而非后续版本的要求

发布完成后，checklist 将作为历史记录保留，不会随代码演进而回溯修改。

Each checklist:
- Is used **only before tagging the corresponding version**
- Serves as a final manual sanity check for maintainers, not as an automated test report
- Reflects the judgment at that point in time, not requirements for later versions

After release, checklists are preserved as historical records and are not retroactively updated.

---

## Checklist 与其他文档的关系 | Relation to Other Documentation

清单：

- checklist 不替代测试（tests）或持续集成（CI）
- checklist 不等同于 release notes
- checklist 不描述功能细节或数值正确性

它们与以下文档体系协同工作：
- `ARCHITECTURE.md`：定义架构边界
- `CONTRIBUTING.md` / `CODING_GUIDE.md`：定义开发与贡献规范
- `docs/specs/`：定义阶段性与结构性约束

Checklists:
- Do not replace tests or continuous integration (CI)
- Are not release notes
- Do not describe functional details or numerical correctness

They work in coordination with:
- `ARCHITECTURE.md` for architectural boundaries
- `CONTRIBUTING.md` / `CODING_GUIDE.md` for development and contribution rules
- `docs/specs/` for phase-specific and structural constraints

---

## 关于版本演进的说明 | Notes on Version Evolution

随着 PeriSci 的演进：
- checklist 的内容可能逐步增加或细化
- 但每一份 checklist 都仅对其对应版本负责

未来版本不应被要求满足早期 checklist 中未出现的条件。

As PeriSci evolves:
- Checklist content may expand or become more detailed
- Each checklist applies only to its corresponding version

Future versions should not be required to satisfy conditions that were not present in earlier checklists.

---

## 结语 | Closing Notes

这些 checklist 的目的，是为 PeriSci 的发布过程留下 **可审计、可理解的工程足迹**。

它们关注的不是“做了多少功能”，而是“在当时，这个版本是否站得住”。

The purpose of these checklists is to leave **auditable and understandable engineering traces** of PeriSci releases.

They focus not on how many features were implemented, but on whether a version was considered sound and defensible at the time.