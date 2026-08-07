#include "app-window.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <format>
#include <stdexcept>

namespace
{
constexpr auto minimum_window_size{1};
constexpr const char *const window_size_assert_message{
    "Window size in both X and Y dimensions must at least be the value of 1!"};
} // namespace

Chip8::AppWindow::AppWindow(WindowTitle title, Dimensions dim_xy)
    : window_{SDL_CreateWindow(title.name, dim_xy.width, dim_xy.height, SDL_WINDOW_OPENGL), &SDL_DestroyWindow}
{
  for (auto dim : {dim_xy.width, dim_xy.height})
  {
    assert(dim >= minimum_window_size && window_size_assert_message);
  }

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

  std::int32_t window_x{};
  std::int32_t window_y{};

  if (!SDL_GetWindowSize(window_.get(), &window_x, &window_y))
  {
    return std::unexpected(std::format("Failed SDL_GetWindowSize! Error: {}", SDL_GetError()));
  }

  return std::pair{window_x, window_y};
}
