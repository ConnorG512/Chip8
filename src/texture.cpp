#include "texture.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>

Chip8::Texture::Texture(SDL_Renderer &renderer, SDL_TextureAccess texture_access, std::pair<int, int> dimensions_wh)
    : texture_{SDL_CreateTexture(&renderer, SDL_PIXELFORMAT_RGBA8888, texture_access, dimensions_wh.first,
                                 dimensions_wh.second),
               &SDL_DestroyTexture}
{
}

auto Chip8::Texture::update_texture(std::span<const std::byte> buffer) -> SDL_Texture&
{
  void *pixel_buffer{};
  std::int32_t pixel_row{};

  if (SDL_LockTexture(texture_.get(), nullptr, &pixel_buffer, &pixel_row))
  {
    std::memcpy(pixel_buffer, buffer.data(), buffer.size_bytes());
    SDL_UnlockTexture(texture_.get());
    
    assert(texture_ != nullptr);
    return *texture_;
  }

  throw std::runtime_error(std::format("Failed to lock SDL Texture! Error {}", SDL_GetError()));
}
