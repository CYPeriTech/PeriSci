#pragma once

#include <string>
#include <vector>

namespace perisci::api
{

  /**
   * run_report is an observability structure produced by run_case.
   *
   * It contains execution statistics useful for:
   * - teaching
   * - debugging
   * - AI agents
   * - regression diagnostics
   *
   * NOTE:
   * - This is NOT a dataset artifact.
   * - It belongs to run-beam results (in-memory).
   */
  struct RunReport
  {
    std::size_t mesh_cells{0};
    std::size_t dof_count{0};

    std::size_t matrix_rows{0};
    std::size_t matrix_nnz{0};

    std::size_t solver_iterations{0};

    double residual_initial{0.0};
    double residual_final{0.0};

    std::vector<double> residual_curve;
  };

  /**
   * Serialize RunReport to JSON text.
   * Stub implementation for v0.2.x.
   */
  std::string run_report_to_json(const RunReport& r);

} // namespace perisci::api
