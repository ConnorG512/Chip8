#pragma once

#include <lua.hpp>
#include <memory>

namespace Chip8
{
class LuaInstance
{
public:
  LuaInstance();

  auto read_config(const char *var_name) -> double;

private:
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
};
} // namespace Chip8
