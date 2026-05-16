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

#include <perisci/api/types.hpp>
#include <string>
#include <vector>

namespace perisci::api
{

  // Teaching configuration for ex-03.
  // This is intentionally not a frozen case schema; cases use run_case(config).
  struct PoissonBasicMeshConfig
  {
    int dimension = 2;
    int cells_per_axis = 8;
    double x_min = 0.0;
    double x_max = 1.0;
    double y_min = 0.0;
    double y_max = 1.0;
  };

  struct PoissonBasicSolverConfig
  {
    int max_iterations = 500;
    double relative_tolerance = 1.0e-10;
  };

  struct PoissonBasicConfig
  {
    std::string name = "poisson-basic";
    PoissonBasicMeshConfig mesh;
    PoissonBasicSolverConfig solver;

    // Constant right-hand side in -Delta u = source_value.
    double source_value = 1.0;
  };

  // Small result bundle for teaching and console output.
  // Asset-grade result materialization remains the responsibility of export_dataset.
  struct PoissonBasicMetrics
  {
    int dimension = 0;
    int num_cells = 0;
    int num_dofs = 0;
    int cg_iterations = 0;
    double rhs_norm = 0.0;
    double residual_norm = 0.0;
    double center_value = 0.0;
  };

  struct PoissonBasicResults
  {
    Status status = Status::failed;
    std::string message;
    PoissonBasicMetrics metrics;
    std::vector<std::string> notes;
  };

  // Teaching API entry used by examples. It organizes the FEM workflow through API
  // while delegating numerical capabilities to core.
  PoissonBasicResults run_poisson_basic(const PoissonBasicConfig& config);

  RunResults to_run_results(const PoissonBasicResults& results);

} // namespace perisci::api
