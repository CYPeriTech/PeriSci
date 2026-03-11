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

#include <perisci/api/api.hpp>
#include <perisci/core/version.hpp>

namespace perisci::api
{

  std::string version_string()
  {
    // 让依赖链真实存在：api 调用 core
    return perisci::core::version_string();
  }

  std::string build_info()
  {
    // v0.2.0 只做占位：未来可以加入编译器、构建类型、git hash 等
    return "PeriSci (api) v" + version_string();
  }

} // namespace perisci::api
