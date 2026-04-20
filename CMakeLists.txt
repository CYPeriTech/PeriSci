# Copyright (c) 2026-present Fei Han
# PeriSci is licensed under Mulan PSL v2.
#
# You can use this software according to the terms and conditions of
# the Mulan PSL v2.
#
# You may obtain a copy of Mulan PSL v2 at:
#
#     http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
#
# See the Mulan PSL v2 for more details.

cmake_minimum_required(VERSION 3.16)

project(PeriSci
  VERSION 0.2.0
  DESCRIPTION "PeriSci: PeriFEM Based Open-Source CAE Software for Science (v0.2.0)"
  LANGUAGES CXX
)

# --- Global defaults (v0.x.x scaffold) ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 常见输出布局：build/bin, build/lib
# 注意：多配置生成器（VS/Xcode）会在后面加配置子目录（Debug/Release）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


# 可选：让 IDE 里 target 分组更清晰
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 开关（v0.2.x：examples/tests 默认都打开，保证最小闭环 + 质量门禁 quality gate）
option(PERISCI_BUILD_EXAMPLES "Build examples" ON)
option(PERISCI_BUILD_TESTS "Build tests" ON)

# --- Subprojects ---
add_subdirectory(core)
add_subdirectory(api)
add_subdirectory(apps)

if(PERISCI_BUILD_EXAMPLES)
  # 直接在代码中定义需要跳过的示例目录列表
  # 格式：set(EXAMPLES_TO_SKIP "目录1" "目录2" ...)
  # 例如：set(EXAMPLES_TO_SKIP "examples/ex-01-minimal-run" "examples/ex-02-another")
  set(EXAMPLES_TO_SKIP "")
  
  # 批量添加所有示例目录
  file(GLOB EXAMPLE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "examples/ex-*")
  foreach(EXAMPLE_DIR ${EXAMPLE_DIRS})
    set(EXAMPLE_FULL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_DIR})
    
    # 检查是否为目录
    if(IS_DIRECTORY ${EXAMPLE_FULL_PATH})
      # 检查是否包含CMakeLists.txt文件
      if(EXISTS ${EXAMPLE_FULL_PATH}/CMakeLists.txt)
        # 检查是否在跳过列表中
        list(FIND EXAMPLES_TO_SKIP ${EXAMPLE_DIR} SKIP_INDEX)
        if(SKIP_INDEX EQUAL -1)
          add_subdirectory(${EXAMPLE_DIR})
          message(STATUS "Added example: ${EXAMPLE_DIR}")
        else()
          message(STATUS "Skipped example (in skip list): ${EXAMPLE_DIR}")
        endif()
      else()
        message(STATUS "Skipped example (no CMakeLists.txt): ${EXAMPLE_DIR}")
      endif()
    endif()
  endforeach() 
endif()

if(PERISCI_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
