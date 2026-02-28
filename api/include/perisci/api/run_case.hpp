#pragma once

#include <perisci/api/types.hpp>

namespace perisci::api
{

  /**
   * B Beam: PURE execution boundary.
   * MUST NOT write dataset/ or perform filesystem side effects.
   * Returns in-memory results only.
   */
  RunResults run_case(const ConfigJson& config_json);

} // namespace perisci::api
