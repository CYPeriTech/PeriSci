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

#include <perisci/api/run_poisson_basic.hpp>

#include <perisci/core/assembly.hpp>
#include <perisci/core/boundary.hpp>
#include <perisci/core/linear_algebra.hpp>
#include <perisci/core/mesh.hpp>
#include <perisci/core/solver.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace
{

  perisci::core::StructuredQuadMeshConfig to_core_mesh_config(const perisci::api::PoissonBasicConfig& config)
  {
    // Keep config translation explicit so the example shows where API ends and core begins.
    perisci::core::StructuredQuadMeshConfig mesh_config;
    mesh_config.dimension = config.mesh.dimension;
    mesh_config.cells_per_axis = config.mesh.cells_per_axis;
    mesh_config.domain.x_min = config.mesh.x_min;
    mesh_config.domain.x_max = config.mesh.x_max;
    mesh_config.domain.y_min = config.mesh.y_min;
    mesh_config.domain.y_max = config.mesh.y_max;
    return mesh_config;
  }

  perisci::core::ConjugateGradientControl
  to_core_solver_control(const perisci::api::PoissonBasicConfig& config)
  {
    // Solver options are runtime data, not template parameters.
    perisci::core::ConjugateGradientControl control;
    control.max_iterations = config.solver.max_iterations;
    control.relative_tolerance = config.solver.relative_tolerance;
    return control;
  }

  class PoissonBasicTeachingRun
  {
  public:
    explicit PoissonBasicTeachingRun(perisci::api::PoissonBasicConfig config)
        : config_(std::move(config))
    {
    }

    perisci::api::PoissonBasicResults run()
    {
      // These stage names intentionally keep the deal.II-like teaching narrative.
      // Each stage calls reusable core capabilities instead of an example-named core solver.
      validate_config();
      make_grid();
      setup_system();
      assemble_system();
      apply_boundary_conditions();
      solve();
      return collect_results();
    }

  private:
    void validate_config() const
    {
      // This entry is intentionally small, but still rejects invalid teaching inputs
      // before they reach the reusable core capabilities.
      if (config_.name.empty())
      {
        throw std::runtime_error("PoissonBasicConfig.name must not be empty.");
      }
      if (!std::isfinite(config_.source_value))
      {
        throw std::runtime_error("source_value must be finite.");
      }
    }

    void make_grid()
    {
      // Discrete Objects:
      // Build a structured quadrilateral mesh through the core mesh capability.
      mesh_ = perisci::core::make_structured_quad_mesh(to_core_mesh_config(config_));
    }

    void setup_system()
    {
      // Discrete Objects:
      // Q1 means bilinear basis functions on quadrilateral cells; scalar means
      // one unknown degree of freedom is attached to each node.
      system_ = perisci::core::make_scalar_laplace_system(static_cast<int>(mesh_.nodes.size()));
      solution_.assign(mesh_.nodes.size(), 0.0);
    }

    void assemble_system()
    {
      // Local Interactions + Accumulation:
      // core::assemble_q1_scalar_laplace_system computes element contributions
      // and accumulates them into the global linear system.
      system_ = perisci::core::assemble_q1_scalar_laplace_system(mesh_, config_.source_value);
    }

    void apply_boundary_conditions()
    {
      // Homogeneous Dirichlet boundary condition:
      // u = 0 on the whole boundary. The symmetric elimination keeps the global
      // system suitable for the conjugate gradient method.
      perisci::core::apply_homogeneous_dirichlet_boundary(system_, mesh_);
    }

    void solve()
    {
      // State Advancement:
      // For this static FEM problem, state advancement means solving Ku = f.
      rhs_norm_ = perisci::core::norm(system_.rhs);
      const perisci::core::ConjugateGradientResult cg =
          perisci::core::conjugate_gradient(system_.matrix, system_.rhs, to_core_solver_control(config_));
      solution_ = cg.solution;
      cg_iterations_ = cg.iterations;
      residual_norm_ =
          perisci::core::norm(perisci::core::subtract(system_.matrix.multiply(solution_), system_.rhs));
    }

    perisci::api::PoissonBasicResults collect_results() const
    {
      perisci::api::PoissonBasicResults results;

      // Use the same relative residual criterion as CG so the API status reflects
      // the numerical stopping rule rather than a hard-coded absolute threshold.
      const double residual_limit =
          config_.solver.relative_tolerance * std::max(rhs_norm_, 1.0);

      results.status = residual_norm_ <= residual_limit ? perisci::api::Status::success
                                                        : perisci::api::Status::partial;
      results.message = "2D Q1 scalar Poisson FEM run completed.";
      results.metrics.dimension = mesh_.dimension;
      results.metrics.num_cells = static_cast<int>(mesh_.cells.size());
      results.metrics.num_dofs = static_cast<int>(mesh_.nodes.size());
      results.metrics.cg_iterations = cg_iterations_;
      results.metrics.rhs_norm = rhs_norm_;
      results.metrics.residual_norm = residual_norm_;
      results.metrics.center_value = solution_[static_cast<std::size_t>(mesh_.center_node_id())];
      results.notes.push_back("Config Beam: the example uses an explicit teaching config object.");
      results.notes.push_back("Run Beam: api::run_poisson_basic organizes the FEM workflow.");
      results.notes.push_back(
          "Core: mesh, assembly, boundary handling, and CG are reusable numerical capabilities.");
      results.notes.push_back(
          "Export Beam: dataset materialization is intentionally not invoked by default.");
      return results;
    }

    perisci::api::PoissonBasicConfig config_;
    perisci::core::StructuredQuadMesh mesh_;
    perisci::core::ScalarLaplaceSystem system_;
    std::vector<double> solution_;
    int cg_iterations_ = 0;
    double rhs_norm_ = 0.0;
    double residual_norm_ = 0.0;
  };

} // namespace

namespace perisci::api
{

  PoissonBasicResults run_poisson_basic(const PoissonBasicConfig& config)
  {
    return PoissonBasicTeachingRun(config).run();
  }

  RunResults to_run_results(const PoissonBasicResults& results)
  {
    // Compatibility adapter for callers that want to consume the generic RunResults shape.
    // It deliberately keeps detailed Poisson metrics in the teaching result type.
    RunResults run_results;
    run_results.status = results.status;
    run_results.message = results.message;
    run_results.notes = results.notes;
    return run_results;
  }

} // namespace perisci::api
