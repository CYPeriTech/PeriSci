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

#include <string>
#include <unordered_map>

namespace perisci::core
{

  /**
   * v0.2.x Frozen: Minimal material parameter container.
   * No constitutive semantics promised in v0.2.x.
   */
  struct Material
  {
    std::string name; // informative label, e.g. "linear_elastic"
    std::unordered_map<std::string, double> params;
  };

} // namespace perisci::core
