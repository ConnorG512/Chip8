#include "lua/lua.hpp"

#include <cassert>
#include <lauxlib.h>
#include <lualib.h>
#include <memory>

namespace
{
[[nodiscard]] auto create_engine() -> std::unique_ptr<lua_State, decltype(&lua_close)>
  post(result : result != nullptr)
{
  auto *state{luaL_newstate()};
  if (state == nullptr) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to create Lua State!"));
  }

  luaL_openlibs(state);

  return {state, &lua_close};
}
} // namespace

Lua::Engine::Engine() : lua_{create_engine()} {}

Lua::Engine::Engine(const std::filesystem::path &path_to_config)
  : lua_{create_engine()}
{
  execute_file(path_to_config.c_str());
}

void Lua::Engine::execute_file(const std::string &file_name) noexcept
{
  assert(!file_name.empty() && "Lua file to execute must have a name!");
  luaL_dofile(lua_.get(), file_name.c_str());
}
