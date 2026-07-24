#include "app-window.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <format>
#include <stdexcept>

Chip8::AppWindow::AppWindow(const char *name, Dimensions dim_xy)
    : window_{SDL_CreateWindow(name, dim_xy.width, dim_xy.height, SDL_WINDOW_OPENGL), &SDL_DestroyWindow}
{
  assert(name != nullptr);
  assert(dim_xy.width > 0);
  assert(dim_xy.height > 0);

  if (window_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to create SDL_Window! Error: {}", SDL_GetError()));
  }
}

auto Chip8::AppWindow::window_ref() -> SDL_Window &
{
  assert(window_.get() != nullptr);
  return *window_;
}

[[nodiscard]] auto Chip8::AppWindow::get_window_dimensions() noexcept
    -> std::expected<std::pair<std::uint32_t, std::uint32_t>, std::string>
{
  static_assert(sizeof(int) == sizeof(std::uint32_t), "Int should be the same size as std::uint32_t (32bit)");

  int window_x{};
  int window_y{};

  if (!SDL_GetWindowSize(window_.get(), &window_x, &window_y))
  {
    return std::unexpected(std::format("Failed SDL_GetWindowSize! Error: {}", SDL_GetError()));
  }

  return std::pair{window_x, window_y};
}
