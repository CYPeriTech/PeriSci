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

// apps/perisci_run_main.cpp
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <perisci/api/run_case.hpp>
#include <perisci/api/types.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{

  std::string read_all_stdin()
  {
    std::ostringstream ss;
    ss << std::cin.rdbuf();
    return ss.str();
  }

  std::string read_file(const std::string& path)
  {
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs)
      throw std::runtime_error("Failed to open file: " + path);
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  // Minimal Base64 (URL-unsafe) for carrying config_json without JSON escaping headaches.
  // Good enough for v0.2 CLI bundle.
  static const char* kB64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  std::string b64_encode(const std::string& in)
  {
    std::string out;
    out.reserve(((in.size() + 2) / 3) * 4);
    int val = 0, valb = -6;
    for (unsigned char c : in)
    {
      val = (val << 8) + c;
      valb += 8;
      while (valb >= 0)
      {
        out.push_back(kB64[(val >> valb) & 0x3F]);
        valb -= 6;
      }
    }
    if (valb > -6)
      out.push_back(kB64[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
      out.push_back('=');
    return out;
  }

  std::string json_escape(const std::string& s)
  {
    std::string o;
    o.reserve(s.size() + 8);
    for (char ch : s)
    {
      switch (ch)
      {
      case '\\':
        o += "\\\\";
        break;
      case '"':
        o += "\\\"";
        break;
      case '\n':
        o += "\\n";
        break;
      case '\r':
        o += "\\r";
        break;
      case '\t':
        o += "\\t";
        break;
      default:
        if (static_cast<unsigned char>(ch) < 0x20)
        {
          // control char: emit as \u00XX
          static const char* hex = "0123456789ABCDEF";
          o += "\\u00";
          o += hex[(ch >> 4) & 0xF];
          o += hex[ch & 0xF];
        }
        else
        {
          o += ch;
        }
      }
    }
    return o;
  }

  void print_help()
  {
    std::cout
        << "perisci-run (v0.2.x)\n"
        << "Usage:\n"
        << "  perisci-run --config <path>\n"
        << "  perisci-run --config -   (read config JSON from stdin)\n"
        << "Output:\n"
        << "  Writes a JSON bundle to stdout: {config_b64, results{status,message,notes[]}}\n";
  }

} // namespace

int main(int argc, char** argv)
{
  try
  {
    std::string config_arg;

    for (int i = 1; i < argc; ++i)
    {
      std::string a = argv[i];
      if (a == "--help" || a == "-h")
      {
        print_help();
        return 0;
      }
      if (a == "--config" && i + 1 < argc)
      {
        config_arg = argv[++i];
        continue;
      }
      std::cerr << "Unknown arg: " << a << "\n";
      print_help();
      return 2;
    }

    if (config_arg.empty())
    {
      std::cerr << "Missing --config\n";
      print_help();
      return 2;
    }

    std::string config_json = (config_arg == "-") ? read_all_stdin() : read_file(config_arg);

    // B Beam: must be pure. (No filesystem writes here.)
    perisci::api::RunResults rr = perisci::api::run_case(config_json);

    // Bundle JSON to stdout.
    // Use base64 for config_json to avoid escaping & allow exact round-trip provenance.
    std::string config_b64 = b64_encode(config_json);

    std::cout << "{"
              << "\"config_b64\":\"" << json_escape(config_b64) << "\","
              << "\"results\":{"
              << "\"status\":\"" << perisci::api::to_string(rr.status) << "\","
              << "\"message\":\"" << json_escape(rr.message) << "\","
              << "\"notes\":[";
    for (size_t i = 0; i < rr.notes.size(); ++i)
    {
      if (i)
        std::cout << ",";
      std::cout << "\"" << json_escape(rr.notes[i]) << "\"";
    }
    std::cout << "]"
              << "}"
              << "}\n";

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "perisci-run error: " << e.what() << "\n";
    return 1;
  }
}
