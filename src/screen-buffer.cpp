#include "chip8-spec.hpp"
#include "screen-buffer.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <span>
#include <strings.h>

namespace
{
using ScrBuf = Chip8::ScrBuf;

[[nodiscard]] auto set_starting_pixel_position(ScrBuf::PixelPosition pos_xy) -> std::uint16_t
{
  const auto wrapped_x{pos_xy.x % Chip8::Spec::screen_width};
  const auto wrapped_y{pos_xy.y % Chip8::Spec::screen_height};

  return (wrapped_y * Chip8::Spec::screen_width) + wrapped_x;
}

auto convert_bits_to_byte_array(std::byte bits) -> std::array<std::byte, Chip8::Spec::max_pixel_row_len>
{
  std::array<std::byte, Chip8::Spec::max_pixel_row_len> pixel_values{};

  for (const auto &[index, pixel] : pixel_values | std::views::enumerate)
  {
    const auto current_bit{index};
    const bool is_on_bit{((bits >> (7 - current_bit)) & std::byte{0b1}) != std::byte{0}};

    if (is_on_bit)
    {
      static constexpr auto white_pixel{0xFF};
      pixel ^= std::byte{white_pixel};
    }
  }
  return pixel_values;
}

auto paint_pixels(std::span<std::uint32_t, Chip8::Spec::max_pixel_row_len> pixel_row,
                  std::span<const std::byte> pixel_values)
{
  assert(!pixel_row.empty() && !pixel_values.empty());

  for (const auto &&[scr_buf, pixel_val] : std::views::zip(pixel_row, pixel_values))
  {
    static constexpr auto on_pixel{0xFF};
    static constexpr auto flip_value{0xFFFFFFFF};

    if (pixel_val == std::byte{on_pixel})
    {
      scr_buf ^= flip_value;
    }
  }
}
} // namespace

void Chip8::ScrBuf::clear_buffer() noexcept
{
  static constexpr auto black_pixel{0x00000000};
  std::ranges::fill(buf_, black_pixel);
}

auto Chip8::ScrBuf::create_new_screen_buffer(PixelPosition pos_xy, std::span<const std::byte> sprite_data)
    -> std::span<const std::byte>
{
  const std::uint16_t starting_position{set_starting_pixel_position(pos_xy)};

  for (const auto [row_index, pixel] : sprite_data | std::views::enumerate)
  {
    const auto current_position{starting_position + (row_index * Chip8::Spec::screen_width)};
    const std::array<std::byte, Chip8::Spec::max_pixel_row_len> pixels_to_paint{convert_bits_to_byte_array(pixel)};
    paint_pixels(std::span{buf_}.subspan(current_position).first<Chip8::Spec::max_pixel_row_len>(), pixels_to_paint);
  }

  return std::as_bytes(std::span(buf_));
}
