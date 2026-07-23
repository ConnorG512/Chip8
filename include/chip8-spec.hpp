#pragma once

#include <cstddef>

namespace Chip8::Spec
{
inline constexpr auto screen_width{64};
inline constexpr auto screen_height{32};

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
