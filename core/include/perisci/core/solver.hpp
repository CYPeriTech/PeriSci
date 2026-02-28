#pragma once

#include <perisci/core/material.hpp>
#include <perisci/core/mesh.hpp>
#include <string>

namespace perisci::core
{

  /**
   * v0.2.x Frozen: Minimal solver interface.
   * This is a stable boundary for later numerical implementations.
   */

  struct SolverInput
  {
    Mesh mesh;
    Material material;

    // Informative only. Example: "static", "quasi_static".
    std::string intent;
  };

  struct SolverOutput
  {
    // Aligned with governance vocabulary (not necessarily dataset status).
    // Allowed: "success" | "partial" | "failed"
    std::string status;
    std::string message;
  };

  SolverOutput solve(const SolverInput& in);

} // namespace perisci::core
