#pragma once

#include <concepts>
#include <cstdint>
#include <lua.hpp>
#include <memory>
#include <string>

namespace Lua
{
template <typename T>
concept LuaInt = std::same_as<T, std::uint8_t> || std::same_as<T, std::uint16_t> || std::same_as<T, std::uint32_t> ||
                 std::same_as<T, std::uint64_t> || std::same_as<T, std::int8_t> || std::same_as<T, std::int16_t> ||
                 std::same_as<T, std::int32_t> || std::same_as<T, std::int64_t>;

template <typename T>
concept LuaFloat = std::same_as<T, float> || std::same_as<T, double>;

template <typename T>
concept LuaType = LuaInt<T> || LuaFloat<T> || std::same_as<T, bool> || std::same_as<T, std::string>;

enum class SupportedTypes : std::uint8_t
{
  Number = LUA_TNUMBER,
  String = LUA_TSTRING,
  Boolean = LUA_TBOOLEAN,
};

class Engine
{
public:
  Engine();

  template <LuaType T> [[nodiscard]] auto get(const std::string &key_strings) -> T;
  void execute_file(const std::string &file_name) noexcept;

private:
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
};
} // namespace Lua

#include "lua/lua_impl.hpp"
