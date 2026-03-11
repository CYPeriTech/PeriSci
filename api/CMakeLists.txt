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

add_library(perisci_api STATIC
  src/api_stub.cpp
  src/config_schema_stub.cpp
  src/run_case_stub.cpp
  src/export_dataset_stub.cpp
  src/validate_case_stub.cpp
  src/run_report_stub.cpp
)

target_compile_features(perisci_api PUBLIC cxx_std_17)

target_include_directories(perisci_api
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(perisci_api
  PUBLIC
    perisci_core
)

set_target_properties(perisci_api PROPERTIES OUTPUT_NAME "perisci_api")
