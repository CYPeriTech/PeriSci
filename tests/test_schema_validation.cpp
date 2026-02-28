#include <cassert>
#include <perisci/api/config_schema.hpp>
#include <string>

static bool looks_like_semver(const std::string& s)
{
  int dots = 0;
  for (char c : s)
    if (c == '.')
      dots++;
  return dots >= 2;
}

int main()
{
  const auto v = perisci::api::schema_version();
  assert(!v.empty());
  assert(looks_like_semver(v));
  // schema_json_text may be empty in v0.2 stub.
  return 0;
}
