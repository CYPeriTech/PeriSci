#include <iostream>
#include <perisci/api/api.hpp>
#include <string>

int main()
{
  // 目标：验证头文件可 include、符号可链接、可运行
  const std::string v = perisci::api::version_string();

  if (v.empty())
  {
    std::cerr << "PeriSci version_string() returned empty string.\n";
    return 1;
  }

  // 打印一下，方便 ctest -V 时查看
  std::cout << "PeriSci test_build OK. Version: " << v << "\n";
  return 0;
}
