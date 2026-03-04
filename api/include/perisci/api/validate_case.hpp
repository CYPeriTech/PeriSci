#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace perisci::api
{

  /**
   * Validation report for validate-beam.
   * This is intentionally minimal in v0.2.x.
   *
   * Contract intent:
   * - validate is a pure function w.r.t. filesystem (no writes).
   * - it evaluates whether a run result / dataset manifest meets expected structure & gates.
   *
   * NOTE: In v0.2.x we allow "stub" behavior; semantics can be strengthened later.
   */
  struct ValidationIssue
  {
    enum class Severity
    {
      kInfo = 0,
      kWarning = 1,
      kError = 2
    };

    Severity severity{Severity::kError};
    std::string code;    // stable-ish short code, e.g. "MANIFEST_MISSING_FIELD"
    std::string message; // human-readable
    std::string path;    // JSON pointer-ish path, e.g. "/manifest/status"
  };

  struct ValidationReport
  {
    bool ok{false};
    std::vector<ValidationIssue> issues;

    std::size_t error_count{0};
    std::size_t warning_count{0};
    std::size_t info_count{0};
  };

  /**
   * Validate a dataset manifest represented as a JSON text.
   *
   * Why JSON text?
   * - apps/ and python/ can pass raw JSON without coupling to internal C++ manifest types.
   * - This keeps validate-beam API stable while other parts evolve.
   */
  ValidationReport validate_case_from_json_text(const std::string& dataset_manifest_json_text);

  /**
   * Helper: serialize report as JSON text (for CLI output).
   * Stub implementation produces a minimal JSON representation.
   */
  std::string to_json_text(const ValidationReport& report);

} // namespace perisci::api
