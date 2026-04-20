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

#include "test_common_functions.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>

namespace fs = std::filesystem;

namespace perisci::tests
{

std::string read_all_text(const fs::path& p)
{
  std::ifstream ifs(p, std::ios::in | std::ios::binary);
  if (!ifs)
  {
    throw std::runtime_error("cannot open file for reading: " + p.string());
  }

  std::ostringstream ss;
  ss << ifs.rdbuf();
  return ss.str();
}

void write_all_text(const fs::path& p, const std::string& s)
{
  std::ofstream ofs(p, std::ios::out | std::ios::binary);
  if (!ofs)
  {
    throw std::runtime_error("cannot open file for writing: " + p.string());
  }

  ofs << s;
}

bool contains(const std::string& s, const std::string& needle)
{
  return s.find(needle) != std::string::npos;
}

std::pair<int, std::string> run_capture(const std::vector<std::string>& args,
                                        const fs::path& workdir,
                                        const std::string* stdin_text)
{
  const fs::path in_file = workdir / "__stdin.txt";
  const fs::path out_file = workdir / "__stdout.txt";

  if (stdin_text)
    write_all_text(in_file, *stdin_text);

  std::ostringstream cmd;
#ifdef _WIN32
  cmd << "cmd /c \"";
  for (std::size_t i = 0; i < args.size(); ++i)
  {
    if (i)
      cmd << " ";
    cmd << args[i];
  }
  if (stdin_text)
    cmd << " < \"" << in_file.string() << "\"";
  cmd << " > \"" << out_file.string() << "\" 2>&1";
  cmd << "\"";
#else
  cmd << "cd \"" << workdir.string() << "\" && ";
  for (std::size_t i = 0; i < args.size(); ++i)
  {
    if (i)
      cmd << " ";
    cmd << args[i];
  }
  if (stdin_text)
    cmd << " < \"" << in_file.filename().string() << "\"";
  cmd << " > \"" << out_file.filename().string() << "\" 2>&1";
#endif

  const int rc = std::system(cmd.str().c_str());

  std::string out;
  if (fs::exists(out_file))
    out = read_all_text(out_file);

  std::error_code ec;
  fs::remove(in_file, ec);
  fs::remove(out_file, ec);

  return {rc, out};
}

} // namespace perisci::tests
