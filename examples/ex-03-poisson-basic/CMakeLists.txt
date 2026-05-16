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

add_executable(perisci_poisson_basic
  poisson_basic.cpp
)

target_compile_features(perisci_poisson_basic PUBLIC cxx_std_17)

target_link_libraries(perisci_poisson_basic
  PRIVATE
    perisci_api
)

set_target_properties(perisci_poisson_basic PROPERTIES OUTPUT_NAME "perisci-poisson-basic")
