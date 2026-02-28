add_library(perisci_core STATIC
  src/core_stub.cpp
  src/mesh_stub.cpp
  src/material_stub.cpp
  src/solver_stub.cpp
)

target_compile_features(perisci_core PUBLIC cxx_std_17)

target_include_directories(perisci_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(perisci_core PROPERTIES OUTPUT_NAME "perisci_core")
