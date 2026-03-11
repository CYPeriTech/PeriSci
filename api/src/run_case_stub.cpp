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

#include <perisci/api/run_case.hpp>

namespace perisci::api
{

  RunResults run_case(const ConfigJson&)
  {
    // v0.2.x stub:
    // - MUST be pure (no filesystem side effects).
    // - MUST return explicit status (no implicit inference).
    RunResults out;
    out.status = Status::success;
    out.message = "perisci::api::run_case is a v0.2.x stub (no execution pipeline yet).";
    out.notes.push_back("Invariant: run_case MUST NOT write any files.");
    return out;
  }

} // namespace perisci::api
