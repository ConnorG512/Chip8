#include "lua-instance.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <expected>
#include <filesystem>
#include <format>
#include <lauxlib.h>
#include <lua.h>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace
{
enum class SupportedTypes : std::uint8_t
{
  Number = 3,
  String = 4,
};
constexpr auto supported_types_arr = std::to_array<std::int32_t>({
    std::to_underlying(SupportedTypes::Number),
    std::to_underlying(SupportedTypes::String),
});

[[nodiscard]] auto load_lua_configuration_file() -> std::expected<std::filesystem::path, std::string_view>
{
  const auto *custom_config_dir{std::getenv("CHIP8_LUA_CONFIG_DIR")};
  if (custom_config_dir == nullptr)
  {
    return std::unexpected("\"CHIP8-LUA-CONFIG_DIR\" is nullptr!");
  }

  return std::filesystem::path{custom_config_dir} / "config.lua";
}

[[nodiscard]] auto is_supported_type(std::int32_t lua_type_recieved) noexcept -> bool
{
  const auto result{std::ranges::contains(supported_types_arr, lua_type_recieved)};
  assert(result == true);

  return result;
}

[[nodiscard]] auto get_found_type(std::int32_t lua_type_recieved) -> std::int32_t
{
  const auto *const found_lua_type =
      std::ranges::find_if(supported_types_arr, [lua_type_recieved](const auto valid_lua_type) -> auto
                           { return lua_type_recieved == valid_lua_type; });
  if (found_lua_type == supported_types_arr.end())
  {
    const char *err_message{"Valid Lua type not found."};
    assert(false && err_message);
    throw std::runtime_error(err_message);
  }

  return *found_lua_type;
}
} // namespace

Chip8::LuaInstance::LuaInstance() : lua_{luaL_newstate(), &lua_close}
{
  if (lua_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error("Failed to create a Lua instance!");
  }

  luaL_openlibs(lua_.get());

  if (const auto lres = luaL_dofile(lua_.get(), load_lua_configuration_file().value_or("config.lua").c_str());
      static_cast<int>(lres) != LUA_OK) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to read Lua config file! Error: {}", lres));
  }
}

auto Chip8::LuaInstance::read_config(const char *var_name) -> std::variant<std::string, double>
{
  assert(var_name != nullptr);

  const auto global_val{lua_getglobal(lua_.get(), var_name)};

  if (!is_supported_type(global_val))
  {
    throw std::runtime_error("Unsupported lua type provided for config.");
  }

  const auto found_type{get_found_type(global_val)};

  static constexpr auto lua_stack_top{1};
  switch (found_type)
  {
    case std::to_underlying(SupportedTypes::Number):
      {
        const double val{lua_tonumber(lua_.get(), -lua_stack_top)};
        lua_pop(lua_.get(), lua_stack_top);
        return val;
      }
    case std::to_underlying(SupportedTypes::String):
      {
        std::string val{lua_tostring(lua_.get(), -lua_stack_top)};
        lua_pop(lua_.get(), lua_stack_top);
        return val;
      }
    default:
      {
        throw std::runtime_error("Checking for unsupported Lua type!");
      }
  }
}
