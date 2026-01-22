# 理论与方法参考文献 | References on Theories and Methods 
本文档列出 PeriSci 所参考的**主要理论文献与专著**，  
用于帮助用户理解本项目所采用方法的**理论来源、学术脉络与技术定位**。

This document lists the **key academic papers and monographs**
referenced by PeriSci, aiming to help users understand the
**theoretical foundations, academic context, and technical positioning**
of the methods used in this project.

---

## 使用说明 | How to Use This Document
- 本文件仅作为**学习与理解的参考索引**  
- 列出的文献不等同于 PeriSci 的完整实现或逐条复现  
- 文献与代码模块的对应关系仅用于**概念性指引**

- This file serves as a **reference index for learning and understanding**  
- Listed works do not imply full or literal implementation in PeriSci  
- Mapping between literature and code modules is **conceptual**, not exact

---

## 近场有限元法 | Peridynamics-based Finite Element Method (PeriFEM)  
### 参考文献 | References
- F. Han, Z. Li, A Peridynamics-Based Finite Element Method (PeriFEM) for Quasi-Static Fracture Analysis, Acta Mechanica Solida Sinica 35 (2022) 446–460.
  
- Z. Li, F. Han, The peridynamics-based finite element method (PeriFEM) with adaptive continuous/discrete element implementation for fracture simulation, Engineering Analysis with Boundary Elements 146 (2023) 56-65.
  
- F. Han, Z. Li, J. Zhang, Z. Liu, C. Yao, W. Han, ABAQUS and ANSYS Implementations of the Peridynamics-Based Finite Element Method (PeriFEM) for Brittle Fractures, CMES - Computer Modeling in Engineering and Sciences 136(3) (2023) 2715-2740.

### 相关学术方向 | Related Academic Topics

- 近场动力学
- 有限元法  
- 基于单元离散的近场动力学数值求解技术  
- 损伤与断裂建模  

- Peridynamics  
- Finite element mehtod
- Numerical method of peridynamics based on Element-based discretization  
- Damage and fracture modeling 

### PeriSci 中的关联（概念性） | Association in PeriSci (Conceptual)

- 核心方法与目的：近场有限元法（PeriFEM）是基于近场动力学理论被用于建模和模拟固体的变形、损伤与断裂过程  
- 在PeriSci中的作用：当前阶段主要作为 PeriSci 的核心数值方法基础  
- 可能关联模块：`core/perifem/*`（示意性路径）

- Core methods and objectives: the PeriFEM is based on the peidynamic theory, and is used to model and simulate the deformation, damage and fracture processes of solids. 
- Role in PeriSci: At this stage, it serves as the fundamental numerical method for PeriSci.  
- Associated code modules: `core/perifem/*` (indicative)

---

## 近场动力学与经典连续介质力学的渐变耦合方法 | Morphing Coupling Method between Peridynamics and Classical Continuum Mechanics  
### 参考文献 | References

- G. Lubineau, Y. Azdoud, F. Han, C. Rey, A. Askari, A morphing strategy to couple non-local to local continuum mechanics, Journal of the Mechanics and Physics of Solids 60(6) (2012) 1088-1102.

- Y. Azdoud, F. Han, G. Lubineau, A Morphing framework to couple non-local and local anisotropic continua, International Journal of Solids and Structures 50(9) (2013) 1332-1341.

- Y. Azdoud, F. Han, G. Lubineau, The morphing method as a flexible tool for adaptive local/non-local simulation of static fracture, Computational Mechanics 54(3) (2014) 711-722.

- F. Han, G. Lubineau, Y. Azdoud, A. Askari, A morphing approach to couple state-based peridynamics with classical continuum mechanics, Computer Methods in Applied Mechanics and Engineering 301 (2016) 336-358.

- F. Han, S. Liu, G. Lubineau, A dynamic hybrid local/nonlocal continuum model for wave propagation, Computational Mechanics 67(1) (2021) 385-407.

- Y. Wang, F. Han, G. Lubineau, Strength-induced peridynamic modeling and simulation of fractures in brittle materials, Computer Methods in Applied Mechanics and Engineering 374 (2021) 113558.

- X. Ou, X. Yao, F. Han, An adaptive coupling modeling between peridynamics and classical continuum mechanics for dynamic crack propagation and crack branching, Engineering Fracture Mechanics 281 (2023) 109096.

- Z. Li, F. Han, Adaptive coupling of non-ordinary state-based peridynamics and classical continuum mechanics for fracture analysis, Computer Methods in Applied Mechanics and Engineering 420 (2024) 116691.

- Li, S. Liu, F. Han, Y. Mei, Y. Sun, F. Zhou, Adaptive Coupling of Peridynamic and Classical Continuum Mechanical Models Driven by Broken Bond/Strength Criteria for Structural Dynamic Failure, International Journal for Numerical Methods in Engineering 126(7) (2025) e70021


### 相关学术方向 | Related Academic Topics

- 多模型耦合方法 
- 自适应耦合技术
- 键型-/常规态型-/非常规态型-近场动力学
- 经典连续介质力学
- 局部/非局部力学理论
- 拟静态/动态断裂力学
- Multi-model coupling modeling
- Adaptive coupling technology
- Bond-based-/Ordinary State-based-/Non-ordinary State-based-Peridynamics 
- Classical Continuum Mechanics
- Local/Nonlocal Mechanics Theory
- Quasi-static/dynamic fracture mechanics

### PeriSci 中的关联（概念性） | Association in PeriSci (Conceptual)

- 待更新  
- to be updated

---

## 其他相关理论（预留）| Other Related Theories (Reserved)  
## Other Related Theories (Reserved)

- ### 参考文献 | References

  - Authors, Title, Journal, volume num.(issue num.) (year) page num.

  ### 相关学术方向 | Related Academic Topics

  - 待更新  
  - to be updated

  ### PeriSci 中的关联（概念性） | Association in PeriSci (Conceptual)

  - 待更新  
  - to be updated

---

## 免责声明 | Disclaimer
- 本文档列出的参考文献不构成对任何具体实现细节的承诺  
- PeriSci 的实现以 `ARCHITECTURE.md` 与代码为准  

- Listed references do not constitute commitments to specific implementations  
- The implementation of PeriSci is governed by `ARCHITECTURE.md` and the codebase