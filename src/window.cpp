#include "window/window.hpp"

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
using Window = Chip8::Window;
using Title = Chip8::Title;
using WindowLengths = Chip8::WindowLengths;

[[nodiscard]] auto create_sdl_window(Title title, WindowLengths lengths)
    -> std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>
{
  const auto window_width{lengths.width.value()};
  const auto window_height{lengths.height.value()};

  auto *created_window{SDL_CreateWindow(title.value(), window_width, window_height, SDL_WINDOW_OPENGL)};
  return {created_window, &SDL_DestroyWindow};
}
} // namespace

namespace Chip8
{
Window::Window(Title title, WindowLengths lengths) : window_{create_sdl_window(title, lengths)}
{
  if (window_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to create SDL_Window! Error: {}", SDL_GetError()));
  }
}

auto Window::window_ref() -> SDL_Window & { return *window_; }

[[nodiscard]] auto Window::get_window_dimensions() -> std::expected<WindowLengths, std::string>
{
  static_assert(sizeof(int) == sizeof(std::uint32_t), "Int should be the same size as std::uint32_t (32bit)");

  std::int32_t window_x{};
  std::int32_t window_y{};

  if (!SDL_GetWindowSize(window_.get(), &window_x, &window_y))
  {
    return std::unexpected(std::format("Failed SDL_GetWindowSize! Error: {}", SDL_GetError()));
  }

  return WindowLengths{.width = Length(window_x),
                       .height = Length(window_y)};
}
} // namespace Chip8
