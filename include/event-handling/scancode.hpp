#pragma once

#include <SDL3/SDL_scancode.h>
#include <concepts>
#include <cstdint>
#include <expected>

namespace Chip8
{
inline constexpr auto max_scancode_size{512};

class Scancode
{
  public:
    template <typename T>
      requires std::same_as<T, SDL_Scancode>
    explicit constexpr Scancode(T scan_code) pre(scan_code <= max_scancode_size) : scan_code_{scan_code}
    {
    }

    template <typename T>
      requires std::same_as<T, std::uint16_t>
    explicit constexpr Scancode(T scan_code) pre(scan_code <= max_scancode_size)
        : scan_code_{static_cast<SDL_Scancode>(scan_code_)}
    {
    }

    enum class RemapErr : std::uint8_t
    {
      InvalidScancode,
    };
    [[nodiscard]] constexpr auto remap(SDL_Scancode new_scancode) -> std::expected<void, RemapErr>
    {
      if (new_scancode >= max_scancode_size)
      {
        return std::unexpected(RemapErr::InvalidScancode);
      }

      scan_code_ = new_scancode;
    }

    [[nodiscard]] constexpr auto val() const -> SDL_Scancode { return scan_code_; }

private:
  SDL_Scancode scan_code_{SDL_SCANCODE_UNKNOWN};
};
} // namespace Chip8
