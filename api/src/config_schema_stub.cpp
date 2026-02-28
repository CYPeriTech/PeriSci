#include <perisci/api/config_schema.hpp>

namespace perisci::api
{

  std::string schema_version()
  {
    // v0.2.x stub value; later align with config-schema.md canonical version.
    return "1.0.0";
  }

  std::string schema_json_text()
  {
    // v0.2.x: schema text is optional; can be supplied later.
    return "";
  }

} // namespace perisci::api
