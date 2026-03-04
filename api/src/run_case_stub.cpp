#include <perisci/api/run_case.hpp>

namespace perisci::api
{

  RunResults run_case(const ConfigJson&)
  {
    // v0.2.x stub:
    // - MUST be pure (no filesystem side effects).
    // - MUST return explicit status (no implicit inference).
    RunResults out;
    out.status = Status::success;
    out.message = "perisci::api::run_case is a v0.2.x stub (no execution pipeline yet).";
    out.notes.push_back("Invariant: run_case MUST NOT write any files.");
    return out;
  }

} // namespace perisci::api
