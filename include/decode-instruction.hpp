#pragma once

#include "decode-types.hpp"
#include "instruction-packet.hpp"

namespace Chip8
{

[[nodiscard]] auto decode_instruction(InstructionPacket packet)
    -> DecodeTypes::List;
}
