#pragma once

#include "pixel-row.hpp"

#include <concepts>
#include <cstddef>

namespace Chip8::Impl
{
inline constexpr std::byte white{0xFF};
inline constexpr std::byte black{0x00};

[[nodiscard]] constexpr auto is_black_or_white(std::byte pixel) { return (pixel == white || pixel == black); }
} // namespace Chip8::Impl

template <typename T>
  requires std::same_as<T, Chip8::PixelRow::PixelBuffer>
constexpr Chip8::PixelRow::PixelRow(T buffer) : buf_{buffer}
{
  for (auto pixel : buffer)
  {
    assert(Impl::is_black_or_white(pixel));
  }
}

constexpr auto Chip8::PixelRow::value() const -> PixelBuffer { return buf_; };

constexpr auto Chip8::PixelRow::operator=(PixelBuffer value) -> PixelRow &
{
  for (auto pixel : value)
  {
    assert(Impl::is_black_or_white(pixel));
  }

  buf_ = value;
  return *this;
}

constexpr auto Chip8::PixelRow::new_filled() noexcept -> PixelRow
{
  auto filled_buffer = []() consteval -> auto
  {
    std::array<std::byte, Spec::max_pixel_row_len> buffer{};
    buffer.fill(Impl::white);
    return buffer;
  };
  return PixelRow(filled_buffer());
}
