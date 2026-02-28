// apps/perisci_export_main.cpp
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <perisci/api/export_dataset.hpp>
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

  // Base64 decode to recover exact config_json
  int b64_index(char c)
  {
    if ('A' <= c && c <= 'Z')
      return c - 'A';
    if ('a' <= c && c <= 'z')
      return c - 'a' + 26;
    if ('0' <= c && c <= '9')
      return c - '0' + 52;
    if (c == '+')
      return 62;
    if (c == '/')
      return 63;
    return -1;
  }

  std::string b64_decode(const std::string& in)
  {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++)
      T[static_cast<unsigned char>(
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i])] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in)
    {
      if (c == '=')
        break;
      int d = T[c];
      if (d == -1)
        continue;
      val = (val << 6) + d;
      valb += 6;
      if (valb >= 0)
      {
        out.push_back(char((val >> valb) & 0xFF));
        valb -= 8;
      }
    }
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
        o += ch;
        break;
      }
    }
    return o;
  }

  // Extremely small "parser" for our own bundle output.
  // It expects fields: "config_b64":"...", "status":"...", "message":"..."
  // Notes are optional; we do not need them for export_dataset.
  std::string extract_json_string_field(const std::string& json, const std::string& key)
  {
    const std::string pattern = "\"" + key + "\"";
    auto pos = json.find(pattern);
    if (pos == std::string::npos)
      throw std::runtime_error("Missing key: " + key);
    pos = json.find(':', pos);
    if (pos == std::string::npos)
      throw std::runtime_error("Malformed JSON near key: " + key);
    // find first quote
    pos = json.find('"', pos);
    if (pos == std::string::npos)
      throw std::runtime_error("Malformed JSON string for key: " + key);
    ++pos;
    std::string out;
    for (; pos < json.size(); ++pos)
    {
      char c = json[pos];
      if (c == '"')
        break;
      if (c == '\\')
      {
        if (pos + 1 >= json.size())
          break;
        char n = json[++pos];
        switch (n)
        {
        case '"':
          out.push_back('"');
          break;
        case '\\':
          out.push_back('\\');
          break;
        case 'n':
          out.push_back('\n');
          break;
        case 'r':
          out.push_back('\r');
          break;
        case 't':
          out.push_back('\t');
          break;
        default:
          out.push_back(n);
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

  perisci::api::Status parse_status(const std::string& s)
  {
    if (s == "success")
      return perisci::api::Status::success;
    if (s == "partial")
      return perisci::api::Status::partial;
    return perisci::api::Status::failed;
  }

  void print_help()
  {
    std::cout
        << "perisci-export (v0.2.x)\n"
        << "Usage:\n"
        << "  perisci-export --bundle <path> --out <output_dir>\n"
        << "  perisci-export --bundle -      --out <output_dir>   (read bundle JSON from stdin)\n"
        << "Notes:\n"
        << "  Writes dataset under <output_dir>/dataset via perisci::api::export_dataset.\n";
  }

} // namespace

int main(int argc, char** argv)
{
  try
  {
    std::string bundle_arg;
    std::string out_dir;

    for (int i = 1; i < argc; ++i)
    {
      std::string a = argv[i];
      if (a == "--help" || a == "-h")
      {
        print_help();
        return 0;
      }
      if (a == "--bundle" && i + 1 < argc)
      {
        bundle_arg = argv[++i];
        continue;
      }
      if (a == "--out" && i + 1 < argc)
      {
        out_dir = argv[++i];
        continue;
      }
      std::cerr << "Unknown arg: " << a << "\n";
      print_help();
      return 2;
    }

    if (bundle_arg.empty() || out_dir.empty())
    {
      std::cerr << "Missing --bundle or --out\n";
      print_help();
      return 2;
    }

    std::string bundle_json = (bundle_arg == "-") ? read_all_stdin() : read_file(bundle_arg);

    std::string config_b64 = extract_json_string_field(bundle_json, "config_b64");
    std::string status_str = extract_json_string_field(bundle_json, "status");
    std::string message_str = extract_json_string_field(bundle_json, "message");

    perisci::api::RunResults rr;
    rr.status = parse_status(status_str);
    rr.message = message_str;

    std::string config_json = b64_decode(config_b64);

    perisci::api::ExportReport report = perisci::api::export_dataset(rr, config_json, out_dir);

    std::cout << "{"
              << "\"ok\":" << (report.ok ? "true" : "false") << ","
              << "\"dataset_root\":\"" << json_escape(report.dataset_root) << "\","
              << "\"message\":\"" << json_escape(report.message) << "\""
              << "}\n";

    return report.ok ? 0 : 3;
  }
  catch (const std::exception& e)
  {
    std::cerr << "perisci-export error: " << e.what() << "\n";
    return 1;
  }
}
