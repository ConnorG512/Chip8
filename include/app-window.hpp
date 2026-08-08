#pragma once

#include "window-wh.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <cstdint>
#include <expected>
#include <memory>
#include <string>
#include <utility>

namespace Chip8
{
class AppWindow
{
public:
  struct WindowTitle
  {
    const char *name{nullptr};

    explicit WindowTitle(const char *title) : name{title}
    {
      assert(title != nullptr && "Window title should not be nullptr!");
    }
  };

  AppWindow(WindowTitle title, WindowWH win_wh);

  [[nodiscard]] auto window_ref() -> SDL_Window &;
  [[nodiscard]] auto get_window_dimensions() noexcept
      -> std::expected<std::pair<std::uint32_t, std::uint32_t>, std::string>;

private:
  static constexpr std::pair<std::int32_t, std::int32_t> xy_{1280, 720};
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{
      SDL_CreateWindow("Chip8", xy_.first, xy_.second, SDL_WINDOW_OPENGL), &SDL_DestroyWindow};
};
} // namespace Chip8
