#include <iostream>
#include <perisci/api/api.hpp>

int main() {
  std::cout << "Hello, PeriSci!\n";
  std::cout << "Version: " << perisci::api::version_string() << "\n";
  std::cout << "Build: " << perisci::api::build_info() << "\n";
  return 0;
}
