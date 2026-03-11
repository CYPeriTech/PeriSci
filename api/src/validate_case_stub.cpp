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

#include <sstream>

namespace perisci::api
{

  namespace
  {

    void add_issue(ValidationReport& r,
                   ValidationIssue::Severity sev,
                   std::string code,
                   std::string message,
                   std::string path)
    {
      ValidationIssue issue;
      issue.severity = sev;
      issue.code = std::move(code);
      issue.message = std::move(message);
      issue.path = std::move(path);
      r.issues.push_back(std::move(issue));

      switch (sev)
      {
      case ValidationIssue::Severity::kError:
        r.error_count++;
        break;
      case ValidationIssue::Severity::kWarning:
        r.warning_count++;
        break;
      case ValidationIssue::Severity::kInfo:
        r.info_count++;
        break;
      }
    }

    // Extremely tiny "contains" checks for stub gate.
    // Replace with real JSON parsing later.
    bool contains_key_like(const std::string& s, const char* key)
    {
      // Looks for `"key"` substring.
      std::string needle = "\"";
      needle += key;
      needle += "\"";
      return s.find(needle) != std::string::npos;
    }

  } // namespace

  ValidationReport validate_case_from_json_text(const std::string& dataset_manifest_json_text)
  {
    ValidationReport report;

    if (dataset_manifest_json_text.empty())
    {
      add_issue(report,
                ValidationIssue::Severity::kError,
                "EMPTY_INPUT",
                "Input JSON text is empty.",
                "");
      report.ok = false;
      return report;
    }

    // ---- Minimal structural gates (stub) ----
    // Expect these top-level-ish keys to exist in a dataset manifest.
    // Adjust according to your dataset-spec once wired in.
    const bool has_manifest = contains_key_like(dataset_manifest_json_text, "manifest");
    const bool has_provenance = contains_key_like(dataset_manifest_json_text, "provenance");
    const bool has_status = contains_key_like(dataset_manifest_json_text, "status");

    if (!has_manifest)
    {
      add_issue(report,
                ValidationIssue::Severity::kError,
                "MANIFEST_MISSING",
                "Dataset manifest must contain top-level key \"manifest\".",
                "/manifest");
    }
    if (!has_provenance)
    {
      add_issue(report,
                ValidationIssue::Severity::kError,
                "PROVENANCE_MISSING",
                "Dataset manifest must contain top-level key \"provenance\".",
                "/provenance");
    }
    if (!has_status)
    {
      add_issue(report,
                ValidationIssue::Severity::kError,
                "STATUS_MISSING",
                "Dataset manifest must contain key \"status\" (either in manifest or provenance "
                "depending on spec).",
                "/status");
    }

    // Optional: some warnings for common expected fields.
    if (!contains_key_like(dataset_manifest_json_text, "schema_version"))
    {
      add_issue(report,
                ValidationIssue::Severity::kWarning,
                "SCHEMA_VERSION_MISSING",
                "Recommended field \"schema_version\" not found (spec-dependent).",
                "/schema_version");
    }
    if (!contains_key_like(dataset_manifest_json_text, "dataset_version"))
    {
      add_issue(report,
                ValidationIssue::Severity::kWarning,
                "DATASET_VERSION_MISSING",
                "Recommended field \"dataset_version\" not found (spec-dependent).",
                "/dataset_version");
    }

    report.ok = (report.error_count == 0);
    return report;
  }

  std::string to_json_text(const ValidationReport& report)
  {
    std::ostringstream os;
    os << "{";
    os << "\"ok\":" << (report.ok ? "true" : "false") << ",";
    os << "\"error_count\":" << report.error_count << ",";
    os << "\"warning_count\":" << report.warning_count << ",";
    os << "\"info_count\":" << report.info_count << ",";
    os << "\"issues\":[";
    for (std::size_t i = 0; i < report.issues.size(); ++i)
    {
      const auto& it = report.issues[i];
      os << "{";
      os << "\"severity\":" << static_cast<int>(it.severity) << ",";
      os << "\"code\":\"" << it.code << "\",";
      os << "\"message\":\"" << it.message << "\",";
      os << "\"path\":\"" << it.path << "\"";
      os << "}";
      if (i + 1 < report.issues.size())
        os << ",";
    }
    os << "]";
    os << "}";
    return os.str();
  }

} // namespace perisci::api
