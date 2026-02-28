# apps/CMakeLists.txt
add_executable(perisci-run
  perisci_run_main.cpp
)

add_executable(perisci-export
  perisci_export_main.cpp
)

target_compile_features(perisci-run PUBLIC cxx_std_17)
target_compile_features(perisci-export PUBLIC cxx_std_17)

target_link_libraries(perisci-run PRIVATE perisci_api)
target_link_libraries(perisci-export PRIVATE perisci_api)

# Put executables in a predictable location for tests
set_target_properties(perisci-run PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(perisci-export PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
