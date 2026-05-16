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

add_library(perisci_core STATIC
  src/assembly.cpp
  src/boundary.cpp
  src/core_stub.cpp
  src/linear_algebra.cpp
  src/mesh.cpp
  src/material_stub.cpp
  src/solver.cpp
)

target_compile_features(perisci_core PUBLIC cxx_std_17)

target_include_directories(perisci_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(perisci_core PROPERTIES OUTPUT_NAME "perisci_core")
