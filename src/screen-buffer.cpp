#include "chip8-spec.hpp"
#include "screen-buffer.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

namespace
{
struct DrawPosition
{
  std::uint8_t starting_offset{0};
  std::uint8_t increments{0};
};

[[nodiscard]] auto calculate_offsets(DrawPosition draw_position) -> std::vector<std::uint16_t>
{
  assert(draw_position.increments > 0 && draw_position.starting_offset >= 0);

  static constexpr auto max_sprite_height{15};
  static constexpr std::array<std::uint16_t, max_sprite_height> pixel_offsets = [] consteval -> auto
  {
    std::array<std::uint16_t, max_sprite_height> offsets{};
    std::ranges::transform(offsets | std::views::enumerate, std::ranges::begin(offsets),
                           [](const auto index_offset_pair) -> auto
                           {
                             const auto [index, offset] = index_offset_pair;
                             return offset = Chip8::Spec::screen_width * index;
                           });
    return offsets;
  }();

  const auto max_increments{draw_position.increments};
  std::vector<std::uint16_t> increments(max_increments);
  std::ranges::transform(pixel_offsets | std::views::take(max_increments), std::ranges::begin(increments),
                         [starting_offset = draw_position.starting_offset](auto offset) -> auto
                         { return offset + starting_offset; });

  return increments;
}
} // namespace

void Chip8::ScrBuf::flip_pixels(std::span<const std::uint16_t> offsets)
{
  if (offsets.empty())
  {
    return;
  }

  static constexpr auto flip_value{0xFFFFFFFF};
  for (auto offset : offsets)
  {
    assert(offset >= 0);
    buf_.at(offset) ^= flip_value;
  }
}

void Chip8::ScrBuf::clear_buffer() noexcept
{
  static constexpr auto clear_value{0x00000000};
  std::ranges::fill(buf_, clear_value);
}

auto Chip8::ScrBuf::create_new_screen_buffer(std::pair<std::uint8_t, std::uint8_t> pos_xy, std::uint8_t draw_num)
    -> std::span<const std::byte>
{
  const std::uint8_t starting_point = (pos_xy.second * Chip8::Spec::screen_width) + pos_xy.first;
  const auto pixels_to_write{calculate_offsets({.starting_offset = starting_point, .increments = draw_num})};
  flip_pixels(pixels_to_write);

  return std::as_bytes(std::span(buf_));
}
