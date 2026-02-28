#pragma once

#include <string>
#include <unordered_map>

namespace perisci::core
{

  /**
   * v0.2.x Frozen: Minimal material parameter container.
   * No constitutive semantics promised in v0.2.x.
   */
  struct Material
  {
    std::string name; // informative label, e.g. "linear_elastic"
    std::unordered_map<std::string, double> params;
  };

} // namespace perisci::core
