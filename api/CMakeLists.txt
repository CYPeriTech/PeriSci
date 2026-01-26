add_library(perisci_api STATIC
  src/api_stub.cpp
)

target_compile_features(perisci_api PUBLIC cxx_std_17)

target_include_directories(perisci_api
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# 依赖方向：api -> core
target_link_libraries(perisci_api
  PUBLIC
    perisci_core
)

set_target_properties(perisci_api PROPERTIES OUTPUT_NAME "perisci_api")
