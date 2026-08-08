#pragma once

#include "chip8-spec.hpp"

#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>

namespace Chip8
{
namespace Impl
{
inline constexpr std::byte white{0xFF};
inline constexpr std::byte black{0x00};

[[nodiscard]] constexpr auto is_black_or_white(std::byte pixel) { return (pixel == white || pixel == black); }
} // namespace Impl

class PixelRow
{
public:
  using PixelBuffer = std::array<std::byte, Chip8::Spec::max_pixel_row_len>;

  PixelRow() = default;

  template <typename T>
    requires std::same_as<T, PixelBuffer>
  explicit constexpr PixelRow(T buffer) : buf_{buffer}
  {
    for (auto pixel : buffer)
    {
      assert(Impl::is_black_or_white(pixel));
    }
  }

  [[nodiscard]] constexpr auto value() const -> PixelBuffer { return buf_; }

  constexpr auto operator=(PixelBuffer value) -> PixelRow &
  {
    for (auto pixel : value)
    {
      assert(Impl::is_black_or_white(pixel));
    }

    buf_ = value;
    return *this;
  }

  static constexpr auto new_filled() noexcept -> PixelRow
  {
    auto filled_buffer = []() consteval -> auto
    {
      std::array<std::byte, Spec::max_pixel_row_len> buffer{};
      static constexpr std::byte white_pixel{0xFF};
      buffer.fill(white_pixel);
      return buffer;
    };
    return PixelRow(filled_buffer());
  }

private:
  PixelBuffer buf_{};
};
} // namespace Chip8
