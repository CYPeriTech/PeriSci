#pragma once

#include <string>

namespace perisci::core
{

  // v0.2.0：最小“可引用、可链接”的稳定符号集合
  inline constexpr int kVersionMajor = 0;
  inline constexpr int kVersionMinor = 2;
  inline constexpr int kVersionPatch = 0;

  // 返回 "0.2.0" 这样的字符串（实现放在 .cpp，确保有可链接符号）
  std::string version_string();

} // namespace perisci::core
