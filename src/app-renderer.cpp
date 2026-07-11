#include "app-renderer.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <format>
#include <stdexcept>

Chip8::AppRenderer::AppRenderer(SDL_Window& current_window)
  : renderer_{SDL_CreateRenderer(&current_window, nullptr), &SDL_DestroyRenderer} 
{
  if (renderer_ == nullptr) [[unlikely]]
  {
    throw std::runtime_error(std::format("Failed to create SDL_Renderer! Error: {}", SDL_GetError()));
  }
}

void Chip8::AppRenderer::clear_renderer() noexcept
{
  SDL_RenderClear(renderer_.get());
}

void Chip8::AppRenderer::present() noexcept
{
  SDL_RenderPresent(renderer_.get());
}
