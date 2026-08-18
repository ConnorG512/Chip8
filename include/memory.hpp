#pragma once

#include "memory-buffer.hpp"
#include "screen-buffer.hpp"

namespace Chip8
{
struct Memory
{
  Chip8::ScrBuf scr_buf{};
  Chip8::MemBuf mem_buf{};
};
} // namespace Chip8
