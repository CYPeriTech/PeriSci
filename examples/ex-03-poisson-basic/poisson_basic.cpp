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

#include <iomanip>
#include <iostream>
#include <perisci/api/api.hpp>
#include <string>

namespace
{

  perisci::api::PoissonBasicConfig make_config()
  {
    // Config Beam:
    // Keep the teaching problem explicit and close to the user's mental model.
    // The dimension is ordinary configuration data, not a C++ template parameter.
    perisci::api::PoissonBasicConfig config;
    config.name = "ex-03-poisson-basic";
    config.mesh.dimension = 2;
    config.mesh.cells_per_axis = 8;
    config.mesh.x_min = 0.0;
    config.mesh.x_max = 1.0;
    config.mesh.y_min = 0.0;
    config.mesh.y_max = 1.0;
    config.solver.max_iterations = 500;
    config.solver.relative_tolerance = 1.0e-10;
    config.source_value = 1.0;
    return config;
  }

  void print_config(const perisci::api::PoissonBasicConfig& config)
  {
    std::cout << "Problem config\n";
    std::cout << "  name: " << config.name << "\n";
    std::cout << "  dimension: " << config.mesh.dimension << "\n";
    std::cout << "  cells_per_axis: " << config.mesh.cells_per_axis << "\n";
    std::cout << "  domain: [" << config.mesh.x_min << ", " << config.mesh.x_max << "] x ["
              << config.mesh.y_min << ", " << config.mesh.y_max << "]\n";
    std::cout << "  source_value: " << config.source_value << "\n";
    std::cout << "  cg_max_iterations: " << config.solver.max_iterations << "\n";
    std::cout << "  cg_relative_tolerance: " << config.solver.relative_tolerance << "\n";
  }

  void print_results(const perisci::api::PoissonBasicResults& results)
  {
    std::cout << "\nRun results\n";
    std::cout << "  status: " << perisci::api::to_string(results.status) << "\n";
    std::cout << "  message: " << results.message << "\n";

    std::cout << "\nRun metrics\n";
    std::cout << "  dimension: " << results.metrics.dimension << "\n";
    std::cout << "  cells: " << results.metrics.num_cells << "\n";
    std::cout << "  dofs: " << results.metrics.num_dofs << "\n";
    std::cout << "  cg_iterations: " << results.metrics.cg_iterations << "\n";
    std::cout << "  rhs_norm: " << results.metrics.rhs_norm << "\n";
    std::cout << "  residual_norm: " << results.metrics.residual_norm << "\n";
    std::cout << "  center_value: " << results.metrics.center_value << "\n";

    if (!results.notes.empty())
    {
      std::cout << "\nNotes\n";
      for (const std::string& note : results.notes)
      {
        std::cout << "  - " << note << "\n";
      }
    }
  }

} // namespace

int main()
{
  const perisci::api::PoissonBasicConfig config = make_config();

  std::cout << "PeriSci Poisson basic example\n";
  std::cout << "API version: " << perisci::api::version_string() << "\n\n";

  print_config(config);

  // Run Beam:
  // The example enters the numerical computation through the API layer.
  // api::run_poisson_basic organizes the teaching workflow and calls reusable
  // core capabilities for mesh generation, assembly, boundary handling, and CG.
  const perisci::api::PoissonBasicResults results = perisci::api::run_poisson_basic(config);

  std::cout << std::scientific << std::setprecision(6);
  print_results(results);

  // Export Beam:
  // This basic teaching example does not materialize a dataset by default.
  // A future case asset should call api::export_dataset with fixed inputs and
  // provenance metadata, instead of letting the solver write governed files.
  return results.status == perisci::api::Status::failed ? 1 : 0;
}
