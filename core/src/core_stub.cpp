#include <perisci/core/version.hpp>

namespace perisci::core {

std::string version_string() {
  return std::to_string(kVersionMajor) + "." +
         std::to_string(kVersionMinor) + "." +
         std::to_string(kVersionPatch);
}

}  // namespace perisci::core
