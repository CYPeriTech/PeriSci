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

#include <perisci/core/boundary.hpp>

#include <cstddef>

namespace perisci::core
{

  void apply_homogeneous_dirichlet_boundary(ScalarLaplaceSystem& system,
                                            const StructuredQuadMesh& mesh)
  {
    // Symmetric row/column elimination preserves the SPD character of the system,
    // which is why the teaching example can use conjugate gradient.
    for (int node_id = 0; node_id < static_cast<int>(mesh.nodes.size()); ++node_id)
    {
      if (!mesh.nodes[static_cast<std::size_t>(node_id)].is_boundary)
      {
        continue;
      }

      for (int col = 0; col < system.matrix.size(); ++col)
      {
        system.matrix(node_id, col) = 0.0;
      }
      for (int row = 0; row < system.matrix.size(); ++row)
      {
        system.matrix(row, node_id) = 0.0;
      }

      system.matrix(node_id, node_id) = 1.0;
      system.rhs[static_cast<std::size_t>(node_id)] = 0.0;
    }
  }

} // namespace perisci::core
