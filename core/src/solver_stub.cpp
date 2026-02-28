#include <perisci/core/solver.hpp>

namespace perisci::core
{

  SolverOutput solve(const SolverInput&)
  {
    // v0.2.x stub: provides a linkable symbol without promising physics.
    return SolverOutput{"failed",
                        "perisci::core::solve is a v0.2.x stub (no numerical implementation yet)."};
  }

} // namespace perisci::core
