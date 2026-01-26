add_library(perisci_core STATIC
  src/core_stub.cpp
)

target_compile_features(perisci_core PUBLIC cxx_std_17)

target_include_directories(perisci_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# 可选：给 IDE 更清晰的分组
set_target_properties(perisci_core PROPERTIES OUTPUT_NAME "perisci_core")
