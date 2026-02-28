#pragma once

#include <string>
#include <vector>

namespace perisci::api
{

  // v0.2.x: authoritative input carrier is JSON text.
  // Canonicalization/hashing rules are enforced by governance tooling, not here.
  using ConfigJson = std::string;

  enum class Status
  {
    success,
    partial,
    failed
  };

  inline std::string to_string(Status s)
  {
    switch (s)
    {
    case Status::success:
      return "success";
    case Status::partial:
      return "partial";
    case Status::failed:
      return "failed";
    }
    return "failed";
  }

  /**
   * In-memory results produced by B-beam run_case.
   * MUST NOT imply any dataset filesystem semantics.
   */
  struct RunResults
  {
    Status status = Status::failed;
    std::string message;

    // Non-normative notes (debugging/hints). Not used for governance.
    std::vector<std::string> notes;
  };

  struct ExportReport
  {
    bool ok = false;
    std::string dataset_root; // path to ".../dataset"
    std::string message;
  };

} // namespace perisci::api
