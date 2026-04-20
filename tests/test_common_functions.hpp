/*
 * Copyright (c) 2026-present Fei Han
 * PeriSci is licensed under Mulan PSL v2.
 *
 * You can use this software according to the terms and conditions of
 * the Mulan PSL v2.
 *
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *     http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 */

#pragma once

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace perisci::tests
{

std::string read_all_text(const std::filesystem::path& p);

void write_all_text(const std::filesystem::path& p, const std::string& s);

bool contains(const std::string& s, const std::string& needle);

std::pair<int, std::string> run_capture(const std::vector<std::string>& args,
                                        const std::filesystem::path& workdir,
                                        const std::string* stdin_text);

} // namespace perisci::tests
