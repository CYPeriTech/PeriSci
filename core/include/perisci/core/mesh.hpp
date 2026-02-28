#pragma once

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

} // namespace perisci::core
