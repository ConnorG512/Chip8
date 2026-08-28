#pragma once

#include <SDL3/SDL_render.h>
#include <cstddef>
#include <memory>
#include <span>

class SDL_Renderer;

namespace Chip8
{
class Texture
{
public:
  // - Constructor
  Texture(SDL_Renderer &renderer, SDL_TextureAccess texture_access, std::pair<int, int> dimensions_wh);
  
  // - Memeber functions
  auto update_texture(std::span<const std::byte> buffer) -> SDL_Texture&;

private:
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_{nullptr, &SDL_DestroyTexture};
};
} // namespace Chip8
