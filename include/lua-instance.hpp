#pragma once

#include <lua.hpp>
#include <memory>
#include <variant>

namespace Chip8
{
class LuaInstance
{
public:
  LuaInstance();

  auto read_config(const char *var_name) -> std::variant<std::string, double>;

private:
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
};
} // namespace Chip8
