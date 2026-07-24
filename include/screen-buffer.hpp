#pragma once

#include "chip8-spec.hpp"

#include <SDL3/SDL_render.h>
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

namespace Chip8
{
class ScrBuf
{
public:
  void flip_pixels(std::span<const std::uint16_t> offsets);
  void clear_buffer() noexcept;

  [[nodiscard]] auto create_new_screen_buffer(std::pair<std::uint8_t, std::uint8_t> pos_xy, std::uint8_t draw_num)
      -> std::span<const std::byte>;

private:
  static constexpr auto buffer_size{static_cast<std::size_t>(Spec::screen_width) * Spec::screen_height};
  std::array<std::uint32_t, buffer_size> buf_{};
};
} // namespace Chip8
