#pragma once

#include "chip8-spec.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace Chip8
{
class ScrBuf
{
public:
  void flip_pixel(std::size_t index);
  void clear_screen() noexcept;

private:
  std::array<std::uint32_t, static_cast<std::size_t>(Spec::screen_width) * Spec::screen_height> buf_{};
};
} // namespace Chip8
