#pragma once

#include <perisci/api/types.hpp>
#include <string>


namespace perisci::api
{

  /**
   * C Beam: ONLY authoritative output boundary.
   * Performs filesystem writes under output_dir/dataset.
   */
  ExportReport export_dataset(const RunResults& results,
                              const ConfigJson& config_json,
                              const std::string& output_dir);

} // namespace perisci::api
