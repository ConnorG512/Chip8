#pragma once

#include "decode-types.hpp"

#include <array>
#include <cstddef>

namespace Chip8
{
[[nodiscard]] auto decode_instruction(std::array<std::byte, 2> instruction)
    -> DecodeTypes::List;
}
