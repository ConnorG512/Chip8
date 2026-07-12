#include "screen-buffer.hpp"

#include <cassert>

void Chip8::ScrBuf::flip_pixel(std::size_t index)
{
  assert(index >= 0);
  assert(index <= buf_.size());

  static constexpr auto flip_value {0xFFFFFFFF};
  buf_.at(index) ^= flip_value;
}


void Chip8::ScrBuf::clear_screen() noexcept
{
  for(auto &pixel : buf_)
  {
    pixel = 0x00000000;
  }
}
