#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#if defined(_WIN32)
#  include <cstdio>
#  define POPEN _popen
#  define PCLOSE _pclose
#else
#  include <cstdio>
#  include <sys/wait.h>
#  define POPEN popen
#  define PCLOSE pclose
#endif

namespace fs = std::filesystem;

// -----------------------------
// Small helpers
// -----------------------------
static std::string read_all_text(const fs::path& p)
{
  std::ifstream ifs(p, std::ios::in | std::ios::binary);
  std::ostringstream ss;
  ss << ifs.rdbuf();
  return ss.str();
}

static void write_all_text(const fs::path& p, const std::string& s)
{
  std::ofstream ofs(p, std::ios::out | std::ios::binary);
  ofs << s;
}

static bool contains(const std::string& s, const std::string& needle)
{
  return s.find(needle) != std::string::npos;
}

/**
 * Run a command and capture stdout. Optionally feed stdin.
 * Returns {exit_code, stdout_text}.
 *
 * Note:
 * - uses popen; stderr is redirected to stdout for debugging.
 */
static std::pair<int, std::string> run_capture(const std::string& cmd,
                                               const std::string& stdin_text = "")
{
  fs::path tmp_in;
  std::string final_cmd = cmd;

  if (!stdin_text.empty())
  {
    tmp_in =
        fs::temp_directory_path() / ("perisci_test_stdin_" + std::to_string(std::rand()) + ".txt");
    write_all_text(tmp_in, stdin_text);

#if defined(_WIN32)
    final_cmd = "type \"" + tmp_in.string() + "\" | " + cmd;
#else
    final_cmd = "cat \"" + tmp_in.string() + "\" | " + cmd;
#endif
  }

  // Redirect stderr to stdout
  final_cmd += " 2>&1";

  std::string out;
  FILE* pipe = POPEN(final_cmd.c_str(), "r");
  if (!pipe)
  {
    if (!tmp_in.empty())
      fs::remove(tmp_in);
    return {127, "popen failed"};
  }

  char buffer[4096];
  while (std::fgets(buffer, sizeof(buffer), pipe))
  {
    out += buffer;
  }

  int rc = PCLOSE(pipe);

#if !defined(_WIN32)
  if (WIFEXITED(rc))
    rc = WEXITSTATUS(rc);
#endif

  if (!tmp_in.empty())
    fs::remove(tmp_in);
  return {rc, out};
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
 * Find a JSON file under dir that likely contains a dataset manifest.
 * Heuristic: file extension .json and contains substring "\"manifest\"".
 *
 * (If later you freeze manifest path, replace this by direct path check.)
 */
static fs::path find_manifest_json(const fs::path& dir)
{
  if (!fs::exists(dir))
    return {};

  for (auto const& entry : fs::recursive_directory_iterator(dir))
  {
    if (!entry.is_regular_file())
      continue;
    auto p = entry.path();
    if (p.extension() != ".json")
      continue;

    std::string txt = read_all_text(p);
    if (contains(txt, "\"manifest\""))
    {
      return p;
    }
  }
  return {};
}

// -----------------------------
// Test: case-00 regression gate
// -----------------------------
int main()
{
  // Minimal v0.2.x config: only meta (schema frozen rule).
  const std::string config_json = R"json(
{
  "meta": {
    "schema_version": "1.0.0",
    "config_id": "case-00-minimal"
  }
}
)json";

  // Governance mode: CTest must provide the ONLY authoritative paths.
  const std::string perisci_run = require_env_exe("PERISCI_RUN");
  const std::string perisci_export = require_env_exe("PERISCI_EXPORT");
  const std::string perisci_validate = require_env_exe("PERISCI_VALIDATE");

  // Temp output directory for export
  const fs::path out_dir =
      fs::temp_directory_path() / ("perisci_case_00_export_" + std::to_string(std::rand()));
  fs::create_directories(out_dir);

  // -----------------------------
  // Step 1: run_case (CLI)
  // -----------------------------
  {
    const std::string cmd = "\"" + perisci_run + "\" --config -";
    auto [rc, out] = run_capture(cmd, config_json);

    if (rc != 0)
    {
      std::cerr << "[case-00] perisci-run failed (rc=" << rc << ")\n";
      std::cerr << out << "\n";
      return 1;
    }

    // Smoke: output should be JSON-ish.
    if (!contains(out, "{") || !contains(out, "}"))
    {
      std::cerr << "[case-00] perisci-run output not JSON-like.\n";
      std::cerr << out << "\n";
      return 1;
    }

    // Gate: must not be a failed run.
    // (Once you freeze the bundle schema, tighten to exact field check.)
    if (contains(out, "\"status\":\"failed\""))
    {
      std::cerr << "[case-00] perisci-run returned failed status.\n";
      std::cerr << out << "\n";
      return 1;
    }

    write_all_text(out_dir / "run_bundle.json", out);
  }

  // -----------------------------
  // Step 2: export_dataset (CLI)
  //   ONLY legal calling pattern per apps/perisci_export_main.cpp:
  //     perisci-export --bundle - --out <output_dir>
  // -----------------------------
  {
    const std::string bundle = read_all_text(out_dir / "run_bundle.json");

    const std::string cmd =
        "\"" + perisci_export + "\" --bundle - --out \"" + out_dir.string() + "\"";

    auto [rc, out] = run_capture(cmd, bundle);
    if (rc != 0)
    {
      std::cerr << "[case-00] perisci-export failed (rc=" << rc << ")\n";
      std::cerr << out << "\n";
      std::cerr << "Expected the ONLY supported usage: perisci-export --bundle - --out <dir>\n";
      return 1;
    }

    // Export prints a small JSON: {"ok":true/false,"dataset_root":"...","message":"..."}
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
  }

  // -----------------------------
  // Step 3: validate (CLI)
  // -----------------------------
  {
    // Locate a manifest-like json file produced by export.
    fs::path manifest = find_manifest_json(out_dir);
    if (manifest.empty())
    {
      std::cerr << "[case-00] could not locate a dataset manifest json under export output dir:\n";
      std::cerr << "  " << out_dir.string() << "\n";
      std::cerr
          << "Hint: ensure export_dataset writes a manifest json containing key \"manifest\".\n";
      return 1;
    }

    const std::string cmd = "\"" + perisci_validate + "\" \"" + manifest.string() + "\"";
    auto [rc, out] = run_capture(cmd);

    if (rc != 0)
    {
      std::cerr << "[case-00] perisci-validate failed (rc=" << rc << ")\n";
      std::cerr << "Manifest: " << manifest.string() << "\n";
      std::cerr << out << "\n";
      return 1;
    }

    // Expect ok=true in validation report (align with your validate/report style).
    if (!contains(out, "\"ok\":true"))
    {
      std::cerr << "[case-00] perisci-validate did not report ok=true.\n";
      std::cerr << out << "\n";
      return 1;
    }
  }

  // Cleanup (best effort)
  std::error_code ec;
  fs::remove_all(out_dir, ec);

  std::cout << "[case-00] regression gate PASSED\n";
  return 0;
}
