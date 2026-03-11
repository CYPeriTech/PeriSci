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
#include <filesystem>
#include <perisci/api/run_case.hpp>
#include <string>

namespace fs = std::filesystem;

static std::size_t count_files_recursively(const fs::path& p)
{
  std::size_t n = 0;
  for (auto it = fs::recursive_directory_iterator(p); it != fs::recursive_directory_iterator();
       ++it)
  {
    if (it->is_regular_file())
      n++;
  }
  return n;
}

int main()
{
  // Prepare an empty temp directory as CWD sandbox.
  const fs::path tmp = fs::temp_directory_path() / "perisci_test_run_case_tmp";
  fs::remove_all(tmp);
  fs::create_directories(tmp);

  const auto old_cwd = fs::current_path();
  fs::current_path(tmp);

  const std::size_t before = count_files_recursively(tmp);

  // Minimal JSON string (authoritative carrier, not parsed in stub).
  const std::string config = R"({"schema_version":"1.0.0","case_id":"smoke"})";

  const auto r = perisci::api::run_case(config);

  // Status must be explicit.
  const auto s = perisci::api::to_string(r.status);
  assert(s == "success" || s == "partial" || s == "failed");

  const std::size_t after = count_files_recursively(tmp);

  // B-beam red line: run_case MUST NOT write files.
  assert(before == after);

  fs::current_path(old_cwd);
  fs::remove_all(tmp);
  return 0;
}
