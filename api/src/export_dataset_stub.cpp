#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <perisci/api/export_dataset.hpp>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{

  // Minimal ISO8601 UTC time string (stub-level).
  std::string now_utc_iso8601()
  {
    using namespace std::chrono;
    const auto now = system_clock::now();
    const auto t = system_clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buf[32];
    std::snprintf(buf,
                  sizeof(buf),
                  "%04d-%02d-%02dT%02d:%02d:%02dZ",
                  tm.tm_year + 1900,
                  tm.tm_mon + 1,
                  tm.tm_mday,
                  tm.tm_hour,
                  tm.tm_min,
                  tm.tm_sec);
    return std::string(buf);
  }

  // Deterministic tiny hash for v0.2.x stub (NOT canonical JSON hash, NOT cryptographic).
  std::string fnv1a64_hex(const std::string& s)
  {
    std::uint64_t h = 1469598103934665603ull;
    for (unsigned char c : s)
    {
      h ^= static_cast<std::uint64_t>(c);
      h *= 1099511628211ull;
    }
    std::ostringstream oss;
    oss << std::hex;
    oss.width(16);
    oss.fill('0');
    oss << h;
    return oss.str();
  }

  void write_text(const fs::path& p, const std::string& s)
  {
    std::ofstream f(p, std::ios::binary);
    if (!f)
      throw std::runtime_error("cannot write file: " + p.string());
    f << s;
  }

} // namespace

namespace perisci::api
{

  ExportReport export_dataset(const RunResults& results,
                              const ConfigJson& config_json,
                              const std::string& output_dir)
  {
    ExportReport rep;
    const fs::path root = fs::path(output_dir) / "dataset";

    try
    {
      // Top-level structure (minimal).
      fs::create_directories(root / "results");
      fs::create_directories(root / "config");
      fs::create_directories(root / "code");
      fs::create_directories(root / "version");

      // Store config snapshot (authoritative carrier).
      write_text(root / "config" / "config.json", config_json);

      // Version files required by dataset-spec.
      const std::string dataset_version = "0.2.0"; // align with release line
      const std::string tool_version = "0.2.0";    // stub tool version

      write_text(root / "version" / "dataset_version.txt", dataset_version);
      write_text(root / "version" / "export_tool_version.txt", tool_version);

      // Minimal manifest.json (structure-only; v0.2 stub).
      // NOTE: in v0.2 we enforce boundary invariants and minimal fields,
      // while canonical JSON and full L1-L4 checks can be strengthened in validate_dataset.
      const std::string created_at = now_utc_iso8601();
      const std::string config_hash = fnv1a64_hex(config_json);

      std::ostringstream manifest;
      manifest << "{\n"
               << "  \"manifest\": {\n"
               << "    \"manifest_version\": \"0.2\",\n"
               << "    \"schema_version\": \"1.0.0\",\n"
               << "    \"dataset_id\": \"perisci_dataset_stub\",\n"
               << "    \"dataset_version\": \"" << dataset_version << "\",\n"
               << "    \"status\": \"" << to_string(results.status) << "\",\n"
               << "    \"provenance\": {\n"
               << "      \"generator\": {\n"
               << "        \"tool\": \"export_dataset\",\n"
               << "        \"tool_version\": \"" << tool_version << "\"\n"
               << "      },\n"
               << "      \"created_at\": \"" << created_at << "\",\n"
               << "      \"config_hash\": \"" << config_hash << "\",\n"
               << "      \"inputs\": {\n"
               << "        \"config_path\": \"config/config.json\",\n"
               << "        \"code_ref\": \"code/\"\n"
               << "      }\n"
               << "    },\n"
               << "    \"code\": {\n"
               << "      \"code_version\": \"unknown\",\n"
               << "      \"dirty\": true\n"
               << "    },\n"
               << "    \"results\": {\n"
               << "      \"path\": \"results/\",\n"
               << "      \"files\": []\n"
               << "    }\n"
               << "  }\n"
               << "}\n";

      write_text(root / "manifest.json", manifest.str());

      rep.ok = true;
      rep.dataset_root = root.string();
      rep.message = "export_dataset stub emitted minimal dataset structure.";
    }
    catch (const std::exception& e)
    {
      rep.ok = false;
      rep.message = std::string("export_dataset failed: ") + e.what();
    }

    return rep;
  }

} // namespace perisci::api
