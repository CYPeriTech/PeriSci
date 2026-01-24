# tests: build/link smoke test (v0.1.5)
add_executable(perisci_test_build
  test_build.cpp
)

target_compile_features(perisci_test_build PUBLIC cxx_std_17)

target_link_libraries(perisci_test_build
  PRIVATE
    perisci_api
)

# 注册到 CTest：能运行即通过
add_test(NAME perisci.build_and_link COMMAND perisci_test_build)
