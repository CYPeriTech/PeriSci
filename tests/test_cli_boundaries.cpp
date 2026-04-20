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

// tests/test_cli_boundaries.cpp
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "test_common_functions.hpp"

namespace fs = std::filesystem;

namespace
{

  bool exists_dataset_anywhere(const fs::path& root)
  {
    if (!fs::exists(root))
      return false;
    for (auto const& e : fs::recursive_directory_iterator(root))
    {
      if (!e.is_directory())
        continue;
      if (e.path().filename() == "dataset")
        return true;
    }
    return false;
  }

} // namespace

int main()
{
  try
  {
    fs::path tmp = fs::temp_directory_path() / "perisci_test_cli_boundaries";
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    // Minimal config JSON. If your schema requires fields, replace this file with a valid minimal
    // config.
    const std::string config_json = "{}\n";

    // 1) perisci-run must NOT create dataset/ anywhere in workdir
    std::string bundle;
    {
      std::vector<std::string> cmd = {
          (fs::path(std::getenv("PERISCI_RUN") ? std::getenv("PERISCI_RUN") : "perisci-run"))
              .string(),
          "--config",
          "-"};
      const auto [rc, out] = perisci::tests::run_capture(cmd, tmp, &config_json);
      bundle = out;
      if (rc != 0)
      {
        std::cerr << "perisci-run failed rc=" << rc << "\n";
        return 1;
      }
      if (exists_dataset_anywhere(tmp))
      {
        std::cerr << "Boundary violation: dataset/ created by perisci-run\n";
        return 2;
      }
    }

    // 2) perisci-export MUST create out/dataset
    fs::path out = tmp / "out";
    fs::create_directories(out);
    {
      std::vector<std::string> cmd = {
          (fs::path(std::getenv("PERISCI_EXPORT") ? std::getenv("PERISCI_EXPORT")
                                                  : "perisci-export"))
              .string(),
          "--bundle",
          "-",
          "--out",
          out.string()};
      const auto [rc, report] = perisci::tests::run_capture(cmd, tmp, &bundle);
      (void)report;
      if (rc != 0)
      {
        std::cerr << "perisci-export failed rc=" << rc << "\n";
        return 3;
      }
      if (!fs::exists(out / "dataset"))
      {
        std::cerr << "Expected out/dataset to exist after perisci-export\n";
        return 4;
      }
    }

    std::cout << "OK\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "test_cli_boundaries exception: " << e.what() << "\n";
    return 99;
  }
}
