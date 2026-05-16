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

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace perisci::core
{

  /**
   * v0.2.x Frozen: Minimal mesh interface (shape only).
   * No promise on element topology/format in v0.2.x.
   */
  struct Mesh
  {
    std::size_t dimension = 0; // e.g. 2 or 3
    std::size_t num_nodes = 0;

    // Flattened node coordinates: [x0,y0,z0, x1,y1,z1, ...]
    // For 2D meshes, z MAY be omitted (implementation-defined in v0.2.x),
    // but dimension and num_nodes MUST still be consistent with consumer logic.
    std::vector<double> nodes_xyz;

    // Informative only; does not participate in governance.
    std::string description;
  };

  struct RectangularDomain
  {
    double x_min = 0.0;
    double x_max = 1.0;
    double y_min = 0.0;
    double y_max = 1.0;
  };

  struct StructuredQuadMeshConfig
  {
    int dimension = 2;
    int cells_per_axis = 8;
    RectangularDomain domain;
  };

  struct MeshNode2D
  {
    double x = 0.0;
    double y = 0.0;
    bool is_boundary = false;
  };

  struct Quad4Cell
  {
    // Q1 node ordering: lower-left, lower-right, upper-right, upper-left.
    std::array<int, 4> node_ids{};
  };

  struct StructuredQuadMesh
  {
    int dimension = 2;
    int cells_per_axis = 0;
    RectangularDomain domain;
    std::vector<MeshNode2D> nodes;
    std::vector<Quad4Cell> cells;

    int node_id(int i, int j) const;
    int center_node_id() const;
  };

  StructuredQuadMesh make_structured_quad_mesh(const StructuredQuadMeshConfig& config);

} // namespace perisci::core
