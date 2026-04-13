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

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

// -----------------------------
// Small helpers
// -----------------------------
namespace
{

  std::string read_all_text(const fs::path& p)
  {
    std::ifstream ifs(p, std::ios::in | std::ios::binary);
    if (!ifs)
    {
      throw std::runtime_error("cannot open file for reading: " + p.string());
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  void write_all_text(const fs::path& p, const std::string& s)
  {
    std::ofstream ofs(p, std::ios::out | std::ios::binary);
    if (!ofs)
    {
      throw std::runtime_error("cannot open file for writing: " + p.string());
    }
    ofs << s;
  }

  bool contains(const std::string& s, const std::string& needle)
  {
    return s.find(needle) != std::string::npos;
  }

  std::string trim(const std::string& s)
  {
    const char* ws = " \t\r\n";
    const auto begin = s.find_first_not_of(ws);
    if (begin == std::string::npos)
      return {};
    const auto end = s.find_last_not_of(ws);
    return s.substr(begin, end - begin + 1);
  }

  std::string json_unescape(const std::string& s)
  {
    std::string out;
    out.reserve(s.size());

    for (std::size_t i = 0; i < s.size(); ++i)
    {
      char c = s[i];
      if (c == '\\' && i + 1 < s.size())
      {
        const char n = s[i + 1];
        switch (n)
        {
        case '\\':
          out.push_back('\\');
          ++i;
          break;
        case '"':
          out.push_back('"');
          ++i;
          break;
        case '/':
          out.push_back('/');
          ++i;
          break;
        case 'b':
          out.push_back('\b');
          ++i;
          break;
        case 'f':
          out.push_back('\f');
          ++i;
          break;
        case 'n':
          out.push_back('\n');
          ++i;
          break;
        case 'r':
          out.push_back('\r');
          ++i;
          break;
        case 't':
          out.push_back('\t');
          ++i;
          break;
        default:
          out.push_back(c);
          break;
        }
      }
      else
      {
        out.push_back(c);
      }
    }

    return out;
  }

} // namespace

/**
 * Extremely small JSON string extractor for flat/simple cases.
 * Assumes `"key": "value"` shape somewhere in the text.
 * Returns empty string if not found.
 */
static std::string extract_json_string_field(const std::string& json, const std::string& key)
{
  const std::string needle = "\"" + key + "\"";
  const auto key_pos = json.find(needle);
  if (key_pos == std::string::npos)
    return {};

  const auto colon_pos = json.find(':', key_pos + needle.size());
  if (colon_pos == std::string::npos)
    return {};

  const auto first_quote = json.find('"', colon_pos + 1);
  if (first_quote == std::string::npos)
    return {};

  const auto second_quote = json.find('"', first_quote + 1);
  if (second_quote == std::string::npos)
    return {};

  const std::string value = json.substr(first_quote + 1, second_quote - first_quote - 1);
  return json_unescape(value);
}

static std::string get_env_or_empty(const char* key)
{
  const char* v = std::getenv(key);
  if (!v)
    return {};
  return std::string(v);
}

static std::string require_env_exe(const char* key)
{
  std::string v = get_env_or_empty(key);
  if (v.empty())
  {
    std::cerr << "[case-00] missing required environment variable: " << key << "\n";
    std::cerr << "Hint: tests/CMakeLists.txt should set "
                 "PERISCI_RUN/PERISCI_EXPORT/PERISCI_VALIDATE via $<TARGET_FILE:...>\n";
    std::exit(3);
  }
  return v;
}

/**
 * Walk upward from current_path() until repository root is found.
 * Criterion: cases/case-00-minimal/input.json exists.
 */
static fs::path find_repo_root()
{
  fs::path p = fs::current_path();

  for (;;)
  {
    const fs::path input = p / "cases" / "case-00-minimal" / "input.json";
    const fs::path expected = p / "cases" / "case-00-minimal" / "expected.json";
    if (fs::exists(input) && fs::exists(expected))
    {
      return p;
    }

    if (!p.has_parent_path() || p.parent_path() == p)
      break;
    p = p.parent_path();
  }

  return {};
}

/**
 * Cross-platform command runner aligned with tests/test_cli_boundaries.cpp.
 * Uses temp files for stdin/stdout/stderr.
 */
static std::pair<int, std::string> run_capture(const std::vector<std::string>& args,
                                               const fs::path& workdir,
                                               const std::string* stdin_text)
{
  const fs::path in_file = workdir / "__stdin.txt";
  const fs::path out_file = workdir / "__stdout.txt";

  if (stdin_text)
    write_all_text(in_file, *stdin_text);

  std::ostringstream cmd;
#ifdef _WIN32
  cmd << "cmd /c \"";
  for (std::size_t i = 0; i < args.size(); ++i)
  {
    if (i)
      cmd << " ";
    cmd << args[i];
  }
  if (stdin_text)
    cmd << " < \"" << in_file.string() << "\"";
  cmd << " > \"" << out_file.string() << "\" 2>&1";
  cmd << "\"";
#else
  cmd << "cd \"" << workdir.string() << "\" && ";
  for (std::size_t i = 0; i < args.size(); ++i)
  {
    if (i)
      cmd << " ";
    cmd << args[i];
  }
  if (stdin_text)
    cmd << " < \"" << in_file.filename().string() << "\"";
  cmd << " > \"" << out_file.filename().string() << "\" 2>&1";
#endif

  const int rc = std::system(cmd.str().c_str());

  std::string out;
  if (fs::exists(out_file))
    out = read_all_text(out_file);

  std::error_code ec;
  fs::remove(in_file, ec);
  fs::remove(out_file, ec);

  return {rc, out};
}

// -----------------------------
// Test: case-00 regression gate
// -----------------------------
int main()
{
  try
  {
    const std::string perisci_run = require_env_exe("PERISCI_RUN");
    const std::string perisci_export = require_env_exe("PERISCI_EXPORT");
    const std::string perisci_validate = require_env_exe("PERISCI_VALIDATE");

    const fs::path repo_root = find_repo_root();
    if (repo_root.empty())
    {
      std::cerr << "[case-00] could not locate repository root containing "
                   "cases/case-00-minimal/{input.json,expected.json}\n";
      std::cerr << "Current working directory: " << fs::current_path().string() << "\n";
      return 2;
    }

    const fs::path case_dir = repo_root / "cases" / "case-00-minimal";
    const fs::path input_path = case_dir / "input.json";
    const fs::path expected_path = case_dir / "expected.json";

    if (!fs::exists(input_path))
    {
      std::cerr << "[case-00] missing input file: " << input_path.string() << "\n";
      return 2;
    }
    if (!fs::exists(expected_path))
    {
      std::cerr << "[case-00] missing expected file: " << expected_path.string() << "\n";
      return 2;
    }

    const std::string config_json = read_all_text(input_path);
    const std::string expected_json = read_all_text(expected_path);
    const std::string status_must_not_be =
        extract_json_string_field(expected_json, "status_must_not_be");

    const fs::path out_dir =
        fs::temp_directory_path() / ("perisci_case_00_export_" + std::to_string(std::rand()));
    fs::remove_all(out_dir);
    fs::create_directories(out_dir);

    // -----------------------------
    // Step 1: run_case (CLI)
    // -----------------------------
    {
      std::vector<std::string> cmd = {"\"" + fs::path(perisci_run).string() + "\"",
                                      "--config",
                                      "-"};

      auto [rc, out] = run_capture(cmd, out_dir, &config_json);

      if (rc != 0)
      {
        std::cerr << "[case-00] perisci-run failed (rc=" << rc << ")\n";
        std::cerr << out << "\n";
        return 1;
      }

      if (!contains(out, "{") || !contains(out, "}"))
      {
        std::cerr << "[case-00] perisci-run output not JSON-like.\n";
        std::cerr << out << "\n";
        return 1;
      }

      if (!status_must_not_be.empty())
      {
        const std::string status = extract_json_string_field(out, "status");
        if (!status.empty() && status == status_must_not_be)
        {
          std::cerr << "[case-00] run result violates expected rule: status_must_not_be="
                    << status_must_not_be << "\n";
          std::cerr << out << "\n";
          return 1;
        }

        const std::string forbidden_fragment = "\"status\":\"" + status_must_not_be + "\"";
        if (contains(out, forbidden_fragment))
        {
          std::cerr << "[case-00] run result violates expected rule: status_must_not_be="
                    << status_must_not_be << "\n";
          std::cerr << out << "\n";
          return 1;
        }
      }

      write_all_text(out_dir / "run_bundle.json", out);
    }

    // -----------------------------
    // Step 2: export_dataset (CLI)
    // -----------------------------
    fs::path dataset_root;
    {
      const std::string bundle = read_all_text(out_dir / "run_bundle.json");

      std::vector<std::string> cmd = {"\"" + fs::path(perisci_export).string() + "\"",
                                      "--bundle",
                                      "-",
                                      "--out",
                                      "\"" + out_dir.string() + "\""};

      auto [rc, out] = run_capture(cmd, out_dir, &bundle);

      if (rc != 0)
      {
        std::cerr << "[case-00] perisci-export failed (rc=" << rc << ")\n";
        std::cerr << out << "\n";
        return 1;
      }

      if (!contains(out, "{") || !contains(out, "\"ok\":"))
      {
        std::cerr << "[case-00] perisci-export output not recognized as JSON report.\n";
        std::cerr << out << "\n";
        return 1;
      }
      if (contains(out, "\"ok\":false"))
      {
        std::cerr << "[case-00] perisci-export reported ok=false.\n";
        std::cerr << out << "\n";
        return 1;
      }

      write_all_text(out_dir / "export_report.json", out);

      const std::string dataset_root_str = trim(extract_json_string_field(out, "dataset_root"));
      if (dataset_root_str.empty())
      {
        std::cerr << "[case-00] perisci-export did not report dataset_root.\n";
        std::cerr << out << "\n";
        return 1;
      }

      dataset_root = fs::path(dataset_root_str);
      if (!fs::exists(dataset_root))
      {
        std::cerr << "[case-00] reported dataset_root does not exist:\n";
        std::cerr << "  " << dataset_root.string() << "\n";
        std::cerr << out << "\n";
        return 1;
      }
    }

    // -----------------------------
    // Step 3: validate (CLI)
    // -----------------------------
    {
      const fs::path manifest = dataset_root / "manifest.json";
      if (!fs::exists(manifest))
      {
        std::cerr << "[case-00] expected manifest file not found:\n";
        std::cerr << "  " << manifest.string() << "\n";
        std::cerr << "dataset_root reported by export: " << dataset_root.string() << "\n";
        return 1;
      }

      std::vector<std::string> cmd = {"\"" + fs::path(perisci_validate).string() + "\"",
                                      "\"" + manifest.string() + "\""};

      auto [rc, out] = run_capture(cmd, out_dir, nullptr);

      if (rc != 0)
      {
        std::cerr << "[case-00] perisci-validate failed (rc=" << rc << ")\n";
        std::cerr << "Manifest: " << manifest.string() << "\n";
        std::cerr << out << "\n";
        return 1;
      }

      if (!contains(out, "\"ok\":true"))
      {
        std::cerr << "[case-00] perisci-validate did not report ok=true.\n";
        std::cerr << out << "\n";
        return 1;
      }
    }

    std::error_code ec;
    fs::remove_all(out_dir, ec);

    std::cout << "[case-00] regression gate PASSED\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "[case-00] unexpected exception: " << e.what() << "\n";
    return 2;
  }
}
