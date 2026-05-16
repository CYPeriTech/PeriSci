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

#include <perisci/core/mesh.hpp>

#include <cstddef>
#include <stdexcept>

namespace perisci::core
{

  int StructuredQuadMesh::node_id(const int i, const int j) const
  {
    return j * (cells_per_axis + 1) + i;
  }

  int StructuredQuadMesh::center_node_id() const
  {
    const int middle_index = cells_per_axis / 2;
    return node_id(middle_index, middle_index);
  }

  StructuredQuadMesh make_structured_quad_mesh(const StructuredQuadMeshConfig& config)
  {
    // The first FEM examples use a deliberately simple 2D structured mesh.
    // This keeps topology explicit before later examples introduce richer mesh types.
    if (config.dimension != 2)
    {
      throw std::runtime_error("StructuredQuadMesh currently supports only dimension = 2.");
    }
    if (config.cells_per_axis < 2)
    {
      throw std::runtime_error("cells_per_axis must be at least 2.");
    }
    if (config.domain.x_max <= config.domain.x_min || config.domain.y_max <= config.domain.y_min)
    {
      throw std::runtime_error("Invalid rectangular domain bounds.");
    }

    StructuredQuadMesh mesh;
    mesh.dimension = config.dimension;
    mesh.cells_per_axis = config.cells_per_axis;
    mesh.domain = config.domain;

    const int cells_per_axis = config.cells_per_axis;
    const double cell_width = (config.domain.x_max - config.domain.x_min) / cells_per_axis;
    const double cell_height = (config.domain.y_max - config.domain.y_min) / cells_per_axis;

    // Node numbering is row-major: node_id(i, j) = j * (n + 1) + i.
    // Boundary flags are stored here so boundary conditions can stay reusable.
    mesh.nodes.reserve(static_cast<std::size_t>(cells_per_axis + 1) *
                       static_cast<std::size_t>(cells_per_axis + 1));
    for (int j = 0; j <= cells_per_axis; ++j)
    {
      for (int i = 0; i <= cells_per_axis; ++i)
      {
        MeshNode2D node;
        node.x = config.domain.x_min + i * cell_width;
        node.y = config.domain.y_min + j * cell_height;
        node.is_boundary = (i == 0 || i == cells_per_axis || j == 0 || j == cells_per_axis);
        mesh.nodes.push_back(node);
      }
    }

    // Quad cells reuse the Q1 local node ordering expected by FEM assembly.
    mesh.cells.reserve(static_cast<std::size_t>(cells_per_axis) *
                       static_cast<std::size_t>(cells_per_axis));
    for (int j = 0; j < cells_per_axis; ++j)
    {
      for (int i = 0; i < cells_per_axis; ++i)
      {
        const int lower_left = mesh.node_id(i, j);
        Quad4Cell cell;
        cell.node_ids = {lower_left, mesh.node_id(i + 1, j), mesh.node_id(i + 1, j + 1),
                         mesh.node_id(i, j + 1)};
        mesh.cells.push_back(cell);
      }
    }

    return mesh;
  }

} // namespace perisci::core
