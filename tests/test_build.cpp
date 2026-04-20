/*
 * Copyright (c) 2026-present Fei Han
 * PeriSci is licensed under Mulan PSL v2.
 *
 * You can use this software according to the terms and conditions of
 * the Mulan PSL v2.
 *
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *     http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 */

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
