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
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace
{

  std::string read_all(const fs::path& p)
  {
    std::ifstream ifs(p, std::ios::binary);
    if (!ifs)
    {
      throw std::runtime_error("cannot open file for reading: " + p.string());
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  void write_all(const fs::path& p, const std::string& s)
  {
    std::ofstream ofs(p, std::ios::binary);
    if (!ofs)
    {
      throw std::runtime_error("cannot open file for writing: " + p.string());
    }
    ofs << s;
  }

  int run_cmd(const std::vector<std::string>& args,
              const fs::path& workdir,
              const std::string* stdin_text,
              std::string* stdout_text)
  {
    // Minimal cross-platform-ish approach:
    // Use temporary files to pass stdin/stdout to the CLI (still OK for tests; the red line is
    // about *run_case/CLI behavior*, not about test harness using files).
    fs::path in_file = workdir / "__stdin.txt";
    fs::path out_file = workdir / "__stdout.txt";

    if (stdin_text)
      write_all(in_file, *stdin_text);

    // Build command string.
    std::ostringstream cmd;
#ifdef _WIN32
    // Windows: use cmd /c and redirect
    cmd << "cmd /c \"";
    for (size_t i = 0; i < args.size(); ++i)
    {
      if (i)
        cmd << " ";
      cmd << args[i];
    }
    if (stdin_text)
      cmd << " < " << in_file.string();
    cmd << " > " << out_file.string();
    cmd << "\"";
#else
    cmd << "cd " << workdir.string() << " && ";
    for (size_t i = 0; i < args.size(); ++i)
    {
      if (i)
        cmd << " ";
      cmd << args[i];
    }
    if (stdin_text)
      cmd << " < " << in_file.filename().string();
    cmd << " > " << out_file.filename().string();
#endif

    int code = std::system(cmd.str().c_str());
    if (stdout_text && fs::exists(out_file))
      *stdout_text = read_all(out_file);
    return code;
  }

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
      int rc = run_cmd(cmd, tmp, &config_json, &bundle);
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
      std::string report;
      int rc = run_cmd(cmd, tmp, &bundle, &report);
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
