#pragma once

#include <perisci/api/config_schema.hpp>
#include <perisci/api/export_dataset.hpp>
#include <perisci/api/run_case.hpp>
#include <perisci/api/types.hpp>
#include <string>

namespace perisci::api
{

  // Keep version/build-info symbols at facade level.
  std::string version_string();
  std::string build_info();

} // namespace perisci::api
