# 更新日志 | Changelog

本文件遵循 Keep a Changelog 规范，并与项目的 Semantic Versioning 版本策略保持一致。
This file follows the Keep a Changelog format and adheres to Semantic Versioning.

本文件记录项目中所有 **对用户、物理模型或数值方法有影响的重要变更**。
This file records all **significant changes that affect users, physical models, or numerical methods**.

更新日志遵循以下原则：
- 语义化版本管理
- 面向科学计算的可复现性
- 对物理模型与数值方法变化保持透明

The changelog follows these principles:
- Semantic versioning
- Reproducibility for scientific computing
- Transparency regarding changes to physical models and numerical methods

---

## [v0.1.5] - 2026-01-26

### Added | 新增

- 初始仓库结构
- 贡献规范与版本管理文档
- 最小构建系统与 CI 流水线
- 第一个可运行示例（`examples/hello`）

### Changed | 变更

- 

### Fixed | 修复

- 

---

## [v0.2.0] - 2026-03-XX

本版本为“契约冻结与治理体系确立版本”。  
本次更新不以数值能力扩展为目标，而以三梁执行契约、数据集资产规范与版本红线体系冻结为核心。

---

### Added | 新增

#### 三梁执行契约正式确立

- A 梁：`config_schema` 权威输入契约结构冻结
- B 梁：`run_case(config)` 纯执行接口确立
- C 梁：`export_dataset(results)` 资产级输出接口确立
- 明确三梁职责边界与调用路径约束

#### 数据集规范（dataset-spec）冻结

- 冻结数据集顶层目录结构
- 冻结 `manifest.json` 唯一权威元数据入口结构
- 冻结 `provenance` 最小字段集合
- 冻结失败 / partial 运行强制记录规则
- 冻结 Canonical JSON 最低规范要求
- 冻结 L1–L4 合规验证层级模型
- 冻结 Version Red Line（C 梁主版本触发规则）

#### 版本分层治理体系确立

- 引入 Repository Version / Schema Version / Dataset Version 三层体系
- 明确三层职责不可替代规则
- 明确 Schema 主版本 → Dataset 主版本联动规则
- 明确 Repository Tag ≠ Dataset Freeze
- 建立版本引用最小要求（Git Tag + dataset_version）

#### 冻结语义与资产级定义确立

- 明确 Freeze 为数据集治理状态，而非文件系统操作
- 明确 Freeze 判定仅基于 canonical 元数据
- 明确资产级（Asset-Level）治理定位
- 明确 dataset_version 为资产结构与语义唯一判定标识

---

### Changed | 变更

- 将 examples 语义升级为资产导向结构，为未来 cases 资产体系演进做准备
- 明确禁止隐式语义、默认值绕过与结构复用
- 统一所有规范性条款为 MUST / SHALL 级表达
- 统一中英文对照版本

---

### Fixed | 修复

- 修正 Schema 与 Dataset 主版本触发边界的双向映射
- 修正 Freeze 在 VERSIONING 与 dataset-spec 中的层级桥接语
- 修复版本红线与溯源规则间的潜在语义不对称
- 消除 Repository Version 与 Dataset Version 的替代风险

---

### Governance Impact | 治理影响说明

- 本版本确立 C 梁为资产级输出边界
- 自 v0.2.0 起，任何数据集结构破坏性修改必须提升 `dataset_version` 主版本 (major version)
- 自 v0.2.0 起，版本引用不完整视为不可复现状态
- 自 v0.2.0 起，三梁契约进入冻结阶段

---

### Breaking Changes | 破坏性变更说明

本版本为规范级冻结版本。

若与 v0.1.x 期间产生的临时结构或隐式行为存在差异，应以 v0.2.0 的规范为准。
旧版本数据集如不符合本规范，不具备冻结资格。

---

## [v0.3.0] - YYYY-MM-DD

### Added | 新增
- 

### Changed | 变更
- 

### Fixed | 修复
- 

---

## [v0.4.0] - YYYY-MM-DD

### Added | 新增
- 

### Changed | 变更
- 

### Fixed | 修复
- 

---

## [v0.5.0] - YYYY-MM-DD

### Added | 新增
- 

### Changed | 变更
- 

### Fixed | 修复
- 

---

## [v1.0.0] - YYYY-MM-DD

### Added | 新增
- 

### Changed | 变更
- 

### Fixed | 修复
- 

---

## 说明 | Notes

- 仅记录 **对用户可见或对物理模型/数值方法有影响的变更**
- 纯内部重构可不记录
- 所有破坏性变更必须明确说明
- Only changes that are **visible to users or affect physical models or numerical methods** are recorded
- Pure internal refactoring may be omitted
- All breaking changes must be explicitly documented