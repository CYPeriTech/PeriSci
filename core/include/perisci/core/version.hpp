#pragma once

#include <string>

namespace perisci::core
{

  // v0.1.5：最小“可引用、可链接”的稳定符号集合
  inline constexpr int kVersionMajor = 0;
  inline constexpr int kVersionMinor = 1;
  inline constexpr int kVersionPatch = 5;

  // 返回 "0.1.5" 这样的字符串（实现放在 .cpp，确保有可链接符号）
  std::string version_string();

} // namespace perisci::core
