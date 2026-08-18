#pragma once

#include "app-renderer.hpp"
#include "app-window.hpp"
#include "chip8-spec.hpp"
#include "cpu.hpp"
#include "lua/lua.hpp"
#include "program-counter.hpp"
#include "memory.hpp"
#include "window-wh.hpp"

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
  AppWindow window_{Chip8::AppWindow::WindowTitle("Chip8"),
                    Chip8::WindowWH(Dimensions<std::uint32_t>{
                        .width = Spec::screen_width * lua_.get<std::uint32_t>("config.window_scale"),
                        .height = Spec::screen_height * lua_.get<std::uint32_t>("config.window_scale")})};
  AppRenderer renderer_{window_.window_ref(), window_.get_window_dimensions().value()};
  Memory memory_{};
  Cpu cpu_{};
  ProgramCounter pc_{Spec::application_reserve.start};
};
} // namespace Chip8
