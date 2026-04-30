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
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 */

#include <iostream>
#include <perisci/api/api.hpp>

int main()
{
  const perisci::api::ConfigJson config_json = R"(
  {
    "meta": {
      "schema_version": "1.0.0",
      "config_id": "example-config-basics"
    },
    "problem":{
      "name": "config-basics",
      "kind": "teaching-example"
    },
    "solver": {
      "type": "stub",
      "max_steps": 1
    },
    "output": {
      "write_dataset": false
    }
  })";

  std::cout << "PeriSci config basics\n";
  std::cout << "API version: " << perisci::api::version_string() << "\n";
  std::cout << "Schema version: " << perisci::api::schema_version() << "\n\n";

  std::cout << "Input config JSON:\n";
  std::cout << config_json << "\n\n";

  const auto results = perisci::api::run_case(config_json);

  std::cout << "Run status: " << perisci::api::to_string(results.status) << "\n";
  std::cout << "Run message: " << results.message << "\n";

  if (!results.notes.empty())
  {
    std::cout << "Notes:\n";
    for (const auto& note : results.notes)
    {
      std::cout << "- " << note << "\n";
    }
  }

  return results.status == perisci::api::Status::failed ? 1 : 0;
}
