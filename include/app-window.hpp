#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <memory>

namespace Chip8
{
class AppWindow
{
public:
  AppWindow(const char *name, std::pair<std::int32_t, std::int32_t> dim_xy);
  
  auto window_ref() -> SDL_Window&;

private:
  static constexpr std::pair<std::int32_t, std::int32_t> xy_{1280, 720};
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{
      SDL_CreateWindow("Chip8", xy_.first, xy_.second, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE), &SDL_DestroyWindow};
};
} // namespace Chip8
