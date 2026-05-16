/*
 * Copyright (c) 2026-present Fei Han
 * PeriSci is licensed under Mulan PSL v2.
 *
 * You can use this software according to the terms and conditions of
 * the Mulan PSL v2.
 *
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *     http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 */

#pragma once

#include <perisci/core/linear_algebra.hpp>
#include <perisci/core/mesh.hpp>

#include <vector>

namespace perisci::core
{

  // Assembly collects local discrete contributions into global algebraic systems.
  // It is intentionally broader than classical local FEM assembly, so future
  // PeriFEM near-field contributions can grow here without creating a parallel module too early.
  struct ScalarLaplaceSystem
  {
    DenseMatrix matrix;
    std::vector<double> rhs;
  };

  ScalarLaplaceSystem make_scalar_laplace_system(int num_dofs);

  // Q1 is the bilinear quadrilateral element; scalar means one unknown per node.
  ScalarLaplaceSystem assemble_q1_scalar_laplace_system(const StructuredQuadMesh& mesh,
                                                        double source_value);

} // namespace perisci::core
