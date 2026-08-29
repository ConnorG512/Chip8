#pragma once 

#include "utils/length.hpp"

#include <cstdint>

namespace Chip8 {
  struct WindowLengths
  {
    Length<std::uint32_t> width{};
    Length<std::uint32_t> height{};
  };
}
