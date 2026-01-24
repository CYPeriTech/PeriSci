cmake_minimum_required(VERSION 3.16)

project(PeriSci
  VERSION 0.1.5
  DESCRIPTION "PeriSci: PeriFEM Based Open-Source CAE Software for Science (v0.1.5)"
  LANGUAGES CXX
)

# --- Global defaults (v0.1.5 scaffold) ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 常见输出布局：build/bin, build/lib
# 注意：多配置生成器（VS/Xcode）会在后面加配置子目录（Debug/Release）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# 可选：让 IDE 里 target 分组更清晰
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 开关（v0.1.5：examples/tests 默认都打开，保证最小闭环 + 质量门禁 quality gate）
option(PERISCI_BUILD_EXAMPLES "Build examples" ON)
option(PERISCI_BUILD_TESTS "Build tests" ON)

# --- Subprojects ---
add_subdirectory(core)
add_subdirectory(api)

if(PERISCI_BUILD_EXAMPLES)
  add_subdirectory(examples/hello)
endif()

if(PERISCI_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()