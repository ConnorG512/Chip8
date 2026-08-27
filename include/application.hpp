#pragma once

#include "app-renderer.hpp"
#include "chip8-spec.hpp"
#include "cpu.hpp"
#include "event/key_list.hpp"
#include "lua/lua.hpp"
#include "memory.hpp"
#include "program-counter.hpp"
#include "window/window.hpp"

#include <SDL3/SDL_scancode.h>
#include <cstdint>
#include <optional>

namespace Chip8
{
class Application
{
public:
  enum class ExitCode : std::uint8_t
  {
    Quit,
  };
  [[nodiscard]] auto run() -> std::optional<ExitCode>;

private:
  Lua::Engine lua_{"config.lua"};
  KeyList key_list_{
      .key_esc = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_esc"))),
      .key_0 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_0"))),
      .key_1 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_1"))),
      .key_2 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_2"))),
      .key_3 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_3"))),
      .key_4 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_4"))),
      .key_5 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_5"))),
      .key_6 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_6"))),
      .key_7 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_7"))),
      .key_8 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_8"))),
      .key_9 = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_9"))),
      .key_a = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_a"))),
      .key_b = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_b"))),
      .key_c = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_c"))),
      .key_d = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_d"))),
      .key_e = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_e"))),
      .key_f = Scancode(static_cast<SDL_Scancode>(lua_.get<std::uint16_t>("config.keybinds.key_f"))),
  };
  // AppWindow window_{Title("Chip8"),
  //                   WindowSize(Dimensions<std::uint32_t>{
  //                       .width = Spec::screen_width * lua_.get<std::uint32_t>("config.window_scale"),
  //                       .height = Spec::screen_height * lua_.get<std::uint32_t>("config.window_scale")})};

  Window window_{Title("Chip8"),
                 WindowLengths{.width = Length(static_cast<std::uint32_t>(
                                   Spec::screen_width * lua_.get<std::uint32_t>("config.window_scale"))),
                               .height = Length(static_cast<std::uint32_t>(
                                   Spec::screen_height * lua_.get<std::uint32_t>("config.window_scale")))}};

  AppRenderer renderer_{window_.window_ref(), window_.get_window_dimensions().value()};
  Memory memory_{};
  Cpu cpu_{};
  ProgramCounter pc_{Spec::application_reserve.start};
};
} // namespace Chip8
