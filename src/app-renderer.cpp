#include "app-renderer.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cassert>
#include <format>
#include <stdexcept>

Chip8::AppRenderer::AppRenderer(SDL_Window &current_window, std::pair<std::uint32_t, std::uint32_t> window_dimensions)
    : renderer_{SDL_CreateRenderer(&current_window, nullptr), &SDL_DestroyRenderer}
{
  if (renderer_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to create SDL_Renderer! Error: {}", SDL_GetError()));
  }
  SDL_SetRenderLogicalPresentation(renderer_.get(), static_cast<int>(window_dimensions.first),
                                   static_cast<int>(window_dimensions.second), SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

void Chip8::AppRenderer::clear_renderer() noexcept { SDL_RenderClear(renderer_.get()); }

void Chip8::AppRenderer::present() noexcept { SDL_RenderPresent(renderer_.get()); }

void Chip8::AppRenderer::prepare_fullscreen_texture(std::span<const std::byte> buffer)
{
  auto &new_texture {screen_texture.update_texture(buffer)};

  if (!SDL_RenderTexture(renderer_.get(), &new_texture, nullptr, nullptr))
  {
    throw std::runtime_error(std::format("Failed to render fullscreen texture! Error: {}", SDL_GetError()));
  }
}

[[nodiscard]] auto Chip8::AppRenderer::get_sdl_renderer() const noexcept -> SDL_Renderer & { return *renderer_; }
