#pragma once

#include "chip8-spec.hpp"
#include "texture.hpp"
#include "window/lengths.hpp"

#include <SDL3/SDL_render.h>
#include <memory>

namespace Chip8
{
class AppRenderer
{
public:
  // - Constructors
  AppRenderer(SDL_Window &current_window, WindowLengths lengths);
  
  // - Member functions
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
