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

#include <perisci/core/assembly.hpp>

#include <array>
#include <cmath>
#include <cstddef>

namespace
{

  std::array<double, 4> q1_shape_values(const double xi, const double eta)
  {
    // Q1 denotes the bilinear finite element on a quadrilateral reference cell.
    // These four basis functions live on [-1, 1] x [-1, 1].
    return {0.25 * (1.0 - xi) * (1.0 - eta),
            0.25 * (1.0 + xi) * (1.0 - eta),
            0.25 * (1.0 + xi) * (1.0 + eta),
            0.25 * (1.0 - xi) * (1.0 + eta)};
  }

  std::array<std::array<double, 2>, 4>
  q1_shape_gradients(const double xi, const double eta, const double cell_width, const double cell_height)
  {
    // The current mesh is axis-aligned, so the reference-to-physical gradient
    // map is diagonal and can be written directly.
    const double dxi_dx = 2.0 / cell_width;
    const double deta_dy = 2.0 / cell_height;

    const std::array<double, 4> d_shape_dxi{-0.25 * (1.0 - eta),
                                            0.25 * (1.0 - eta),
                                            0.25 * (1.0 + eta),
                                            -0.25 * (1.0 + eta)};
    const std::array<double, 4> d_shape_deta{-0.25 * (1.0 - xi),
                                             -0.25 * (1.0 + xi),
                                             0.25 * (1.0 + xi),
                                             0.25 * (1.0 - xi)};

    std::array<std::array<double, 2>, 4> gradients{};
    for (int i = 0; i < 4; ++i)
    {
      gradients[static_cast<std::size_t>(i)] = {
          d_shape_dxi[static_cast<std::size_t>(i)] * dxi_dx,
          d_shape_deta[static_cast<std::size_t>(i)] * deta_dy};
    }
    return gradients;
  }

} // namespace

namespace perisci::core
{

  ScalarLaplaceSystem make_scalar_laplace_system(const int num_dofs)
  {
    ScalarLaplaceSystem system;
    system.matrix = DenseMatrix(num_dofs);
    system.rhs.assign(static_cast<std::size_t>(num_dofs), 0.0);
    return system;
  }

  ScalarLaplaceSystem assemble_q1_scalar_laplace_system(const StructuredQuadMesh& mesh,
                                                        const double source_value)
  {
    ScalarLaplaceSystem system = make_scalar_laplace_system(static_cast<int>(mesh.nodes.size()));

    // Two-point Gauss quadrature integrates the Q1 Laplace stiffness exactly
    // on rectangular cells and is enough for the constant source term here.
    const double gauss_point = 1.0 / std::sqrt(3.0);
    const std::array<double, 2> quadrature_points{-gauss_point, gauss_point};

    for (const Quad4Cell& cell : mesh.cells)
    {
      double cell_matrix[4][4] = {};
      double cell_rhs[4] = {};

      const MeshNode2D& node_0 = mesh.nodes[static_cast<std::size_t>(cell.node_ids[0])];
      const MeshNode2D& node_1 = mesh.nodes[static_cast<std::size_t>(cell.node_ids[1])];
      const MeshNode2D& node_3 = mesh.nodes[static_cast<std::size_t>(cell.node_ids[3])];
      const double cell_width = node_1.x - node_0.x;
      const double cell_height = node_3.y - node_0.y;
      const double jacobian_determinant = cell_width * cell_height / 4.0;

      // Local Interactions:
      // Build the 4x4 element stiffness and 4-entry element load vector.
      for (const double xi : quadrature_points)
      {
        for (const double eta : quadrature_points)
        {
          const auto shape_values = q1_shape_values(xi, eta);
          const auto shape_gradients = q1_shape_gradients(xi, eta, cell_width, cell_height);

          for (int i = 0; i < 4; ++i)
          {
            for (int j = 0; j < 4; ++j)
            {
              cell_matrix[i][j] +=
                  (shape_gradients[i][0] * shape_gradients[j][0] +
                   shape_gradients[i][1] * shape_gradients[j][1]) *
                  jacobian_determinant;
            }
            cell_rhs[i] += shape_values[i] * source_value * jacobian_determinant;
          }
        }
      }

      // Accumulation:
      // Scatter local element contributions into the global dense system.
      for (int i = 0; i < 4; ++i)
      {
        const int global_i = cell.node_ids[static_cast<std::size_t>(i)];
        system.rhs[static_cast<std::size_t>(global_i)] += cell_rhs[i];
        for (int j = 0; j < 4; ++j)
        {
          const int global_j = cell.node_ids[static_cast<std::size_t>(j)];
          system.matrix(global_i, global_j) += cell_matrix[i][j];
        }
      }
    }

    return system;
  }

} // namespace perisci::core
