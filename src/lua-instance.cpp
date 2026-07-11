#include "lua-instance.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

Chip8::LuaInstance::LuaInstance() : lua_{luaL_newstate(), &lua_close}
{
  if (lua_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error("Failed to create a Lua instance!");
  }

  luaL_openlibs(lua_.get());
  if (const auto lres = luaL_dofile(lua_.get(), "config.lua"); static_cast<int>(lres) != LUA_OK) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to read Lua config file! Error: {}", lres));
  }
}

auto Chip8::LuaInstance::read_config(const char *var_name) -> double
{
  assert(var_name != nullptr);
  const auto found_type{lua_getglobal(lua_.get(), var_name)};

  if (found_type != LUA_TNUMBER)
  {
    throw std::runtime_error("Unsupported lua type provided for config.");
  }

  const auto val{lua_tonumber(lua_.get(), -1)};
  lua_pop(lua_.get(), 1);

  return val;
}
