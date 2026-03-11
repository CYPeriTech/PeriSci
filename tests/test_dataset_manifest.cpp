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
#include <fstream>
#include <perisci/api/export_dataset.hpp>
#include <perisci/api/run_case.hpp>
#include <string>

namespace fs = std::filesystem;

static std::string read_all(const fs::path& p)
{
  std::ifstream f(p, std::ios::binary);
  std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
  return s;
}

static bool contains(const std::string& hay, const std::string& needle)
{
  return hay.find(needle) != std::string::npos;
}

int main()
{
  const fs::path out = fs::temp_directory_path() / "perisci_test_export_tmp";
  fs::remove_all(out);
  fs::create_directories(out);

  const std::string config = R"({"schema_version":"1.0.0","case_id":"export"})";

  // B-beam returns in-memory results (may be failed in stub; export still must record status).
  const auto results = perisci::api::run_case(config);

  const auto rep = perisci::api::export_dataset(results, config, out.string());
  assert(rep.ok);
  assert(!rep.dataset_root.empty());

  const fs::path root = fs::path(rep.dataset_root);
  assert(fs::exists(root));
  assert(fs::exists(root / "manifest.json"));
  assert(fs::exists(root / "results"));
  assert(fs::exists(root / "config"));
  assert(fs::exists(root / "code"));
  assert(fs::exists(root / "version"));
  assert(fs::exists(root / "version" / "dataset_version.txt"));
  assert(fs::exists(root / "version" / "export_tool_version.txt"));

  const std::string manifest = read_all(root / "manifest.json");
  assert(contains(manifest, "\"dataset_version\""));
  assert(contains(manifest, "\"provenance\""));
  assert(contains(manifest, "\"code\""));
  assert(contains(manifest, "\"results\""));

  fs::remove_all(out);
  return 0;
}
