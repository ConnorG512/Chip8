#include "app-window.hpp"
#include "window-wh.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <expected>
#include <format>
#include <memory>
#include <stdexcept>

namespace
{
using AppWindow = Chip8::AppWindow;
[[nodiscard]] auto create_sdl_window(AppWindow::WindowTitle title, Chip8::WindowWH win_wh)
    -> std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>
{
  const auto [width, height] = win_wh.value();

  auto *created_window{SDL_CreateWindow(title.name, static_cast<std::int32_t>(width), static_cast<std::int32_t>(height),
                                        SDL_WINDOW_OPENGL)};
  return {created_window, &SDL_DestroyWindow};
}
} // namespace

Chip8::AppWindow::AppWindow(WindowTitle title, WindowWH win_wh) : window_{create_sdl_window(title, win_wh)}
{
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

[[nodiscard]] auto Chip8::AppWindow::get_window_dimensions()
    -> std::expected<std::pair<std::uint32_t, std::uint32_t>, std::string>
{
  static_assert(sizeof(int) == sizeof(std::uint32_t), "Int should be the same size as std::uint32_t (32bit)");

  std::int32_t window_x{};
  std::int32_t window_y{};

  if (!SDL_GetWindowSize(window_.get(), &window_x, &window_y))
  {
    return std::unexpected(std::format("Failed SDL_GetWindowSize! Error: {}", SDL_GetError()));
  }

  return std::pair{window_x, window_y};
}
