#pragma once

#include <string>

namespace perisci::api {

// v0.1.5：对外最小 API（示例/测试只 include 这一层）
std::string version_string();

// 可选：一个小的自检函数，后续可扩展为打印 build/provenance 信息
std::string build_info();

}  // namespace perisci::api
