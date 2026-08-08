#include "chip8-spec.hpp"
#include "pixel-row.hpp"
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

auto convert_bits_to_byte_array(std::byte bits) -> Chip8::PixelRow
{
  using PixelRow = Chip8::PixelRow;

  static constexpr std::byte full_row{0b1'1'1'1'1'1'1'1};
  if (bits == full_row)
  {
    return Chip8::PixelRow::new_filled();
  }

  static constexpr std::byte empty_row{0b0'0'0'0'0'0'0'0};
  if (bits == empty_row)
  {
    return PixelRow{};
  }

  std::array<std::byte, Chip8::Spec::max_pixel_row_len> pixel_values{};

  for (const auto &[index, pixel] : pixel_values | std::views::enumerate)
  {
    const auto current_bit{index};
    static constexpr std::byte single_bitmask{0b1};
    static constexpr std::byte zero{0x00};
    static constexpr auto most_significant_bit{7};
    const bool is_on_bit{((bits >> (most_significant_bit - current_bit)) & single_bitmask) != zero};

    if (is_on_bit)
    {
      static constexpr auto flip_val{0xFF};
      pixel ^= std::byte{flip_val};
    }
  }
  return PixelRow{pixel_values};
}

auto paint_pixels(std::span<std::uint32_t, Chip8::Spec::max_pixel_row_len> pixel_row,
                  std::span<const std::byte> pixel_values)
{
  assert(!pixel_row.empty() && !pixel_values.empty());

  for (const auto &&[scr_buf, pixel_val] : std::views::zip(pixel_row, pixel_values))
  {
    static constexpr std::byte white{0xFF};
    static constexpr auto flip_value{0xFFFFFFFF};

    if (pixel_val == white)
    {
      scr_buf ^= flip_value;
    }
  }
}
} // namespace

void Chip8::ScrBuf::clear_buffer() noexcept
{
  static constexpr auto black_pixel{0xFF};
  std::ranges::fill(buf_, black_pixel);
}

auto Chip8::ScrBuf::create_new_screen_buffer(PixelPosition pos_xy, std::span<const std::byte> sprite_data)
    -> std::span<const std::byte>
{
  const std::uint16_t starting_position{set_starting_pixel_position(pos_xy)};

  for (const auto [row_index, pixel] : sprite_data | std::views::enumerate)
  {
    const auto current_position{starting_position + (row_index * Chip8::Spec::screen_width)};
    const Chip8::PixelRow pixels_to_paint{convert_bits_to_byte_array(pixel)};
    paint_pixels(std::span{buf_}.subspan(current_position).first<Chip8::Spec::max_pixel_row_len>(),
                 pixels_to_paint.value());
  }

  return std::as_bytes(std::span(buf_));
}
