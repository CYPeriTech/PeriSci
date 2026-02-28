#include <perisci/api/api.hpp>
#include <perisci/core/version.hpp>

namespace perisci::api
{

  std::string version_string()
  {
    // 让依赖链真实存在：api 调用 core
    return perisci::core::version_string();
  }

  std::string build_info()
  {
    // v0.2.0 只做占位：未来可以加入编译器、构建类型、git hash 等
    return "PeriSci (api) v" + version_string();
  }

} // namespace perisci::api
