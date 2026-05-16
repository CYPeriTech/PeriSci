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

#include <perisci/api/config_schema.hpp>
#include <perisci/api/export_dataset.hpp>
#include <perisci/api/run_case.hpp>
#include <perisci/api/run_poisson_basic.hpp>
#include <perisci/api/types.hpp>
#include <string>

namespace perisci::api
{

  // Keep version/build-info symbols at facade level.
  std::string version_string();
  std::string build_info();

} // namespace perisci::api
