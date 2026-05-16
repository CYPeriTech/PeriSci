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

#include <perisci/core/solver.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace perisci::core
{

  SolverOutput solve(const SolverInput&)
  {
    // Keep the legacy broad solve() symbol linkable, but do not route real examples
    // through it until a stable general solver contract exists.
    return SolverOutput{
        "failed",
        "perisci::core::solve is a legacy minimal entry; use concrete solver capabilities."};
  }

  ConjugateGradientResult conjugate_gradient(const DenseMatrix& matrix,
                                             const std::vector<double>& rhs,
                                             const ConjugateGradientControl& control)
  {
    if (matrix.size() != static_cast<int>(rhs.size()))
    {
      throw std::runtime_error("conjugate_gradient dimension mismatch.");
    }
    if (control.max_iterations < 0)
    {
      throw std::runtime_error("max_iterations must be non-negative.");
    }
    if (control.relative_tolerance <= 0.0)
    {
      throw std::runtime_error("relative_tolerance must be positive.");
    }

    std::vector<double> solution(rhs.size(), 0.0);
    std::vector<double> residual = rhs;
    std::vector<double> direction = residual;

    // With zero initial guess, the initial residual is rhs. The scaling by max(||b||, 1)
    // avoids making tiny right-hand sides require unrealistically tiny absolute residuals.
    const double rhs_norm = std::max(norm(rhs), 1.0);
    double residual_squared_old = dot(residual, residual);

    ConjugateGradientResult result;
    result.solution = solution;
    result.residual_norm = std::sqrt(residual_squared_old);

    if (result.residual_norm <= control.relative_tolerance * rhs_norm)
    {
      return result;
    }

    for (int iteration = 1; iteration <= control.max_iterations; ++iteration)
    {
      const std::vector<double> matrix_direction = matrix.multiply(direction);
      const double denominator = dot(direction, matrix_direction);
      const double denominator_scale = std::max(dot(direction, direction), 1.0);

      // A near-zero denominator means the CG recurrence can no longer make a
      // reliable update, so return the best state obtained so far.
      if (std::abs(denominator) <= std::numeric_limits<double>::epsilon() * denominator_scale)
      {
        return result;
      }

      // Standard CG update:
      // alpha = (r_k, r_k) / (p_k, A p_k), then x and r are advanced together.
      const double step_length = residual_squared_old / denominator;
      for (std::size_t i = 0; i < solution.size(); ++i)
      {
        solution[i] += step_length * direction[i];
        residual[i] -= step_length * matrix_direction[i];
      }

      const double residual_squared_new = dot(residual, residual);
      result.iterations = iteration;
      result.residual_norm = std::sqrt(residual_squared_new);
      result.solution = solution;

      if (result.residual_norm <= control.relative_tolerance * rhs_norm)
      {
        return result;
      }

      // beta updates the search direction while preserving A-conjugacy in exact arithmetic.
      const double direction_scale = residual_squared_new / residual_squared_old;
      for (std::size_t i = 0; i < direction.size(); ++i)
      {
        direction[i] = residual[i] + direction_scale * direction[i];
      }
      residual_squared_old = residual_squared_new;
    }

    return result;
  }

} // namespace perisci::core
