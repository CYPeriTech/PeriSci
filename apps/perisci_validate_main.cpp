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

#include "perisci/api/validate_case.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace
{

  std::string read_all_text(const std::string& path)
  {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (!ifs)
    {
      return {};
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  void print_usage(const char* argv0)
  {
    std::cerr << "Usage:\n"
              << "  " << argv0 << " <dataset_manifest.json>\n\n"
              << "Exit codes:\n"
              << "  0  validation ok\n"
              << "  2  validation failed (errors)\n"
              << "  3  invalid arguments / cannot read file\n";
  }

} // namespace

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    print_usage(argv[0]);
    return 3;
  }

  const std::string path = argv[1];
  const std::string json_text = read_all_text(path);
  if (json_text.empty())
  {
    std::cerr << "ERROR: failed to read file or file is empty: " << path << "\n";
    return 3;
  }

  const auto report = perisci::api::validate_case_from_json_text(json_text);

  // Print JSON report to stdout to be machine-friendly.
  std::cout << perisci::api::to_json_text(report) << "\n";

  return report.ok ? 0 : 2;
}
