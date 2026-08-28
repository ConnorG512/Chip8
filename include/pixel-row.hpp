#pragma once

#include "chip8-spec.hpp"

#include <array>
#include <cassert>
#include <concepts>

namespace Chip8
{
class PixelRow
{
public:
  // - Alias
  using PixelBuffer = std::array<std::byte, Chip8::Spec::max_pixel_row_len>;

  // - Constructors
  PixelRow() = default;

  template <typename T>
    requires std::same_as<T, PixelBuffer>
  explicit constexpr PixelRow(T buffer);

  // - Member functions
  [[nodiscard]] constexpr auto value() const -> PixelBuffer;
  
  [[nodiscard]] static constexpr auto new_filled() noexcept -> PixelRow;
  
  // - Operator overloads
  [[nodiscard]] constexpr auto operator=(PixelBuffer value) -> PixelRow &;

private:
  PixelBuffer buf_{};
};
} // namespace Chip8

#include "pixel-row-impl.hpp"
