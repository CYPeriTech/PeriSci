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

# tests: build/link + contract gates (v0.2.x)

# Ensure CTest is enabled from top-level:
# - Top-level should call: enable_testing()
# - Or: include(CTest)
# This file only registers tests.

# ------------------------------------------------------------
# (1) Legacy build/link smoke test
#     Introduced in v0.1.5.
#     Ensures library builds and links correctly.
add_executable(perisci_test_build
  test_build.cpp
)

target_compile_features(perisci_test_build PRIVATE cxx_std_17)
target_link_libraries(perisci_test_build PRIVATE perisci_api)
add_test(NAME perisci.build_and_link COMMAND perisci_test_build)
set_tests_properties(perisci.build_and_link PROPERTIES TIMEOUT 10)

# ------------------------------------------------------------
# (2.1) v0.2.x: A/B/C contract gates should be independent executables
add_executable(perisci_test_schema_validation
  test_schema_validation.cpp
)
target_compile_features(perisci_test_schema_validation PRIVATE cxx_std_17)
target_link_libraries(perisci_test_schema_validation PRIVATE perisci_api)
add_test(NAME perisci.schema_validation COMMAND perisci_test_schema_validation)
set_tests_properties(perisci.schema_validation PROPERTIES TIMEOUT 10)


add_executable(perisci_test_run_case_smoke
  test_run_case_smoke.cpp
)
target_compile_features(perisci_test_run_case_smoke PRIVATE cxx_std_17)
target_link_libraries(perisci_test_run_case_smoke PRIVATE perisci_api)
add_test(NAME perisci.run_case_smoke COMMAND perisci_test_run_case_smoke)
set_tests_properties(perisci.run_case_smoke PROPERTIES TIMEOUT 30)


add_executable(perisci_test_dataset_manifest
  test_dataset_manifest.cpp
)
target_compile_features(perisci_test_dataset_manifest PRIVATE cxx_std_17)
target_link_libraries(perisci_test_dataset_manifest PRIVATE perisci_api)
add_test(NAME perisci.dataset_manifest COMMAND perisci_test_dataset_manifest)
set_tests_properties(perisci.dataset_manifest PROPERTIES TIMEOUT 30)

# ------------------------------------------------------------
# (2.2) v0.2.x: case-00 regression gate (run -> export -> validate)
add_executable(perisci_test_case_00_regression
  test_case_00_regression.cpp
)
target_compile_features(perisci_test_case_00_regression PRIVATE cxx_std_17)

add_test(NAME perisci.case_00_regression COMMAND perisci_test_case_00_regression)

# 让测试稳定拿到 CLI 可执行文件所在目录（跨生成器/跨Debug/Release）
set_tests_properties(perisci.case_00_regression PROPERTIES
  ENVIRONMENT
    "PERISCI_RUN=$<TARGET_FILE:perisci-run>;PERISCI_EXPORT=$<TARGET_FILE:perisci-export>;PERISCI_VALIDATE=$<TARGET_FILE:perisci-validate>"
)

# 确保 CLI targets 都先构建（add_test 不保证构建顺序）
add_dependencies(perisci_test_case_00_regression perisci-run perisci-export perisci-validate)

set_tests_properties(perisci.case_00_regression PROPERTIES TIMEOUT 60)


# ------------------------------------------------------------
# (2.3) v0.2.x: CLI boundary gate
#     perisci-run must NOT create dataset/ (no filesystem side effects)
#     perisci-export is the ONLY entry allowed to write dataset under --out
add_executable(perisci_test_cli_boundaries
  test_cli_boundaries.cpp
)
target_compile_features(perisci_test_cli_boundaries PRIVATE cxx_std_17)
add_test(NAME perisci.cli_boundaries COMMAND perisci_test_cli_boundaries)

# 让 CTest 直接把 target 的真实路径传给测试（跨生成器/跨Debug/Release稳定）
# Pass real executable paths across generators/configs (Debug/Release)
set_tests_properties(perisci.cli_boundaries PROPERTIES
  ENVIRONMENT
    "PERISCI_RUN=$<TARGET_FILE:perisci-run>;PERISCI_EXPORT=$<TARGET_FILE:perisci-export>"
)

# 可选：确保先构建 CLI targets（多数生成器下 add_test 不保证构建顺序）
# Ensure CLI targets are built before running this test
add_dependencies(perisci_test_cli_boundaries perisci-run perisci-export)
set_tests_properties(perisci.cli_boundaries PROPERTIES TIMEOUT 30)
