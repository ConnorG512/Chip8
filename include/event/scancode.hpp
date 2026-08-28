#pragma once

#include <SDL3/SDL_scancode.h>
#include <concepts>

namespace Chip8
{
template <typename T>
concept SDLScancodeType = std::same_as<T, SDL_Scancode>;

class Scancode
{
public:
  // - Constructors
  Scancode() = default;
  explicit constexpr Scancode(SDLScancodeType auto scancode) : scancode_{scancode} {}

  // - Member functions
  [[nodiscard]] constexpr auto same_as(Scancode scancode) const noexcept -> bool
  {
    return (this->scancode_ == scancode.scancode_);
  }

  [[nodiscard]] constexpr auto same_as(SDLScancodeType auto scancode) const noexcept -> bool
  {
    return (this->scancode_ == scancode);
  }

  constexpr auto remap(SDLScancodeType auto scancode) noexcept -> void { this->scancode_ = scancode; }

  // - Operator overloads
  [[nodiscard]] constexpr auto operator==(Scancode scancode) const noexcept -> bool { return same_as(scancode); }

  [[nodiscard]] constexpr auto operator==(SDLScancodeType auto scancode) const noexcept -> bool
  {
    return same_as(scancode);
  }

private:
  SDL_Scancode scancode_{SDL_SCANCODE_UNKNOWN};
};
} // namespace Chip8
