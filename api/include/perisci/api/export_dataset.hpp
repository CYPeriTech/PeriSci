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

namespace perisci::api
{

  /**
   * C Beam: ONLY authoritative output boundary.
   * Performs filesystem writes under output_dir/dataset.
   */
  ExportReport export_dataset(const RunResults& results,
                              const ConfigJson& config_json,
                              const std::string& output_dir);

} // namespace perisci::api
