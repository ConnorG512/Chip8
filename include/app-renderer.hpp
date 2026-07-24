#pragma once

#include "chip8-spec.hpp"
#include "texture.hpp"
#include <SDL3/SDL_render.h>
#include <memory>

namespace Chip8
{
class AppRenderer
{
public:
  AppRenderer(SDL_Window &current_window, std::pair<std::uint32_t, std::uint32_t> window_dimensions);

  void clear_renderer() noexcept;
  void present() noexcept;

  void prepare_fullscreen_texture(std::span<const std::byte> buffer);

  [[nodiscard]] auto get_sdl_renderer() const noexcept -> SDL_Renderer &;

private:
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{SDL_CreateRenderer(nullptr, nullptr),
                                                                          &SDL_DestroyRenderer};
  Texture screen_texture{
      *renderer_, SDL_TEXTUREACCESS_STREAMING, {Chip8::Spec::screen_width, Chip8::Spec::screen_height}};
};
} // namespace Chip8
