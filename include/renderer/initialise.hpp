#pragma once

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <concepts>
#include <cstdint>
#include <expected>
#include <span>

namespace Chip8
{

template <typename T = SDL_GLAttr>
  requires std::same_as<T, SDL_GLAttr>
struct GLProperties
{
  T attribute{};
  std::int32_t val{};
};

template <typename T> GLProperties(T, std::uint32_t) -> GLProperties<T>;

inline auto initialize_renderer(std::span<const GLProperties<>> properties) noexcept
    -> std::expected<void, const char *>
{
  for (const auto prop : properties)
  {
    if (!SDL_GL_SetAttribute(prop.attribute, prop.val))
    {
      return std::unexpected(SDL_GetError());
    }
  }

  return {};
}
} // namespace Chip8
