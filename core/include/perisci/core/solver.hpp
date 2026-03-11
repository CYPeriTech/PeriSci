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
