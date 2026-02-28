#pragma once

#include <string>

namespace perisci::api
{

  /**
   * A Beam: config_schema authoritative entry.
   * v0.2.x minimal: expose schema version and optional schema JSON text.
   */
  std::string schema_version();
  std::string schema_json_text(); // may be empty in stub

} // namespace perisci::api
