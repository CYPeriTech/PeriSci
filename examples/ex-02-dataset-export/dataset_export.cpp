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

#include <iostream>
#include <perisci/api/api.hpp>
#include <string>

namespace
{

  constexpr char native_path_separator()
  {
#if defined(_WIN32)
    return '\\';
#else
    return '/';
#endif
  }

  std::string normalize_path(std::string path)
  {
    for (char& ch : path)
    {
      if (ch == '/' || ch == '\\')
      {
        ch = native_path_separator();
      }
    }
    return path;
  }

  std::string join_path(const std::string& left, const std::string& right)
  {
    const std::string normalized_left = normalize_path(left);
    const std::string normalized_right = normalize_path(right);

    if (normalized_left.empty())
      return normalized_right;

    const char last = normalized_left.back();
    if (last == '/' || last == '\\')
      return normalized_left + normalized_right;

    return normalized_left + native_path_separator() + normalized_right;
  }

} // namespace

int main(int argc, char** argv)
{
  const std::string output_dir =
      normalize_path(argc > 1 ? std::string(argv[1])
                              : join_path(join_path("build", "examples"), "ex-02-dataset-export"));

  const perisci::api::ConfigJson config_json = R"(
{
  "meta": {
    "schema_version": "1.0.0",
    "config_id": "example-dataset-export"
  },
  "problem": {
    "name": "dataset-export",
    "kind": "teaching-example"
  },
  "solver": {
    "type": "stub",
    "max_steps": 1
  },
  "output": {
    "write_dataset": true
  }
})";

  std::cout << "PeriSci dataset export example\n";
  std::cout << "API version: " << perisci::api::version_string() << "\n";
  std::cout << "Schema version: " << perisci::api::schema_version() << "\n";
  std::cout << "Output directory: " << output_dir << "\n\n";

  std::cout << "Step 1: run_case(config_json)\n";
  const auto results = perisci::api::run_case(config_json);

  std::cout << "Run status: " << perisci::api::to_string(results.status) << "\n";
  std::cout << "Run message: " << results.message << "\n";

  if (!results.notes.empty())
  {
    std::cout << "Run notes:\n";
    for (const auto& note : results.notes)
    {
      std::cout << "- " << note << "\n";
    }
  }

  if (results.status == perisci::api::Status::failed)
  {
    std::cout << "\nStep 2 skipped: run_case failed, no dataset exported.\n";
    return 1;
  }

  std::cout << "\nStep 2: export_dataset(results, config_json, output_dir)\n";
  const auto report = perisci::api::export_dataset(results, config_json, output_dir);

  std::cout << "Export ok: " << (report.ok ? "true" : "false") << "\n";
  std::cout << "Export message: " << report.message << "\n";
  const std::string dataset_root = normalize_path(report.dataset_root);
  std::cout << "Dataset root: " << dataset_root << "\n";

  if (report.ok)
  {
    std::cout << "\nGenerated dataset files include:\n";
    std::cout << "- " << join_path(dataset_root, "manifest.json") << "\n";
    std::cout << "- " << join_path(join_path(dataset_root, "config"), "config.json") << "\n";
    std::cout << "- " << join_path(join_path(dataset_root, "version"), "dataset_version.txt")
              << "\n";
    std::cout << "- " << join_path(join_path(dataset_root, "version"), "export_tool_version.txt")
              << "\n";
  }

  return report.ok ? 0 : 1;
}
