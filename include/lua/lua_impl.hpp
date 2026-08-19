#pragma once

#include "lua/lua.hpp"

#include <algorithm>
#include <cassert>
#include <lua.h>
#include <lua.hpp>
#include <luaconf.h>
#include <lualib.h>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

namespace Lua::Impl
{
inline constexpr auto top_of_stack{-1};

template <LuaType T> [[nodiscard]] auto get_val(lua_State *lua) -> T
  pre(lua != nullptr)
{
  assert(lua != nullptr && "Lua must not be nullptr!");

  if constexpr (LuaInt<T> || LuaFloat<T>)
  {
    const auto final_val{lua_tonumber(lua, top_of_stack)};
    if constexpr(std::is_unsigned_v<T>)
    {
      static constexpr auto minimum_unsigned_value{0};
      assert(final_val >= minimum_unsigned_value && "Value must be at least 0 for unsigned integer!");
      return final_val;
    }
    return final_val;
  }
  else if constexpr (std::same_as<T, std::string>)
  {
    return static_cast<T>(lua_tostring(lua, top_of_stack));
  }
  else if constexpr (std::same_as<T, bool>)
  {
    return static_cast<T>(lua_toboolean(lua, top_of_stack));
  }
}
} // namespace Lua::Impl



template <Lua::LuaType T> auto Lua::Engine::get(const std::string &key_strings) -> T
{
  auto string_path = key_strings | std::views::split('.') | std::ranges::to<std::vector<std::string>>();

  static constexpr auto global_variable_index{0};
  if (lua_getglobal(lua_.get(), string_path.at(global_variable_index).c_str()) != LUA_TTABLE)
  {
    const auto found_val{Impl::get_val<T>(lua_.get())};
    lua_pop(lua_.get(), 1);
    return found_val;
  }

  static constexpr auto first_entry{1};
  const auto found_lua_val =
      std::ranges::find_if(string_path | std::views::drop(first_entry),
                           [this](const std::string &str) -> auto
                           {
                             const auto table_result{lua_istable(lua_.get(), Impl::top_of_stack)};

                             static constexpr auto not_found{0};
                             if (table_result == not_found)
                             {
                               return true;
                             }

                             lua_getfield(lua_.get(), Impl::top_of_stack, str.c_str());
                             lua_replace(lua_.get(), -2);
                             return !lua_istable(lua_.get(), Impl::top_of_stack);
                           });

  if (found_lua_val == string_path.end())
  {
    lua_pop(lua_.get(), 1);
    throw std::runtime_error("Unable to find valid lua data!");
  }

  const auto found_val{Impl::get_val<T>(lua_.get())};
  lua_pop(lua_.get(), 1);
  return found_val;
}
