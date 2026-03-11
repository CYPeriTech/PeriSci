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

namespace perisci::core
{

  // v0.2.0：最小“可引用、可链接”的稳定符号集合
  inline constexpr int kVersionMajor = 0;
  inline constexpr int kVersionMinor = 2;
  inline constexpr int kVersionPatch = 0;

  // 返回 "0.2.0" 这样的字符串（实现放在 .cpp，确保有可链接符号）
  std::string version_string();

} // namespace perisci::core
