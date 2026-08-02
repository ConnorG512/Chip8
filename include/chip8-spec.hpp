#pragma once

#include <cstddef>
#include <cstdint>

namespace Chip8::Spec
{
inline constexpr std::uint8_t screen_width{64};
inline constexpr std::uint8_t screen_height{32};

inline constexpr std::uint8_t max_pixel_row_len{8};

struct MemoryPortions
{
  std::size_t start{0};
  std::size_t end{0};
};

static constexpr MemoryPortions system_reserve{
    .start = 0x000,
    .end = 0x1FF,
};

static constexpr MemoryPortions character_reserve{
    .start = 0x050,
    .end = 0x0A0,
};

static constexpr MemoryPortions application_reserve{
    .start = 0x200,
    .end = 0xFFF,
};
} // namespace Chip8::Spec
