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

#include <cassert>
#include <perisci/api/config_schema.hpp>
#include <string>

namespace
{

  bool looks_like_semver(const std::string& s)
  {
    int dots = 0;
    for (char c : s)
      if (c == '.')
        dots++;
    return dots >= 2;
  }

} // namespace

int main()
{
  const auto v = perisci::api::schema_version();
  assert(!v.empty());
  assert(looks_like_semver(v));
  // schema_json_text may be empty in v0.2 stub.
  return 0;
}
