#pragma once

#include "window/lengths.hpp"
#include "window/title.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <expected>
#include <memory>
#include <string>

namespace Chip8
{

class Window
{
public:
  Window(Title title, WindowLengths lengths);

  [[nodiscard]] auto window_ref() -> SDL_Window &pre(window_);

  [[nodiscard]] auto get_window_dimensions() -> std::expected<WindowLengths, std::string>;

private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
  WindowLengths lengths;
};
} // namespace Chip8
