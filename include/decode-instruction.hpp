#pragma once

#include "decode-types.hpp"

#include <array>
#include <cstddef>
#include <variant>

namespace Chip8
{
[[nodiscard]] auto decode_instruction(std::array<std::byte, 2> instruction)
    -> std::variant<DecodeTypes::SkipNextInstructionEqual, DecodeTypes::SkipNextInstructionNotEqual,
                    DecodeTypes::RegisterToRegisterArith, DecodeTypes::AddValueToRegister,
                    DecodeTypes::SetValueToRegister, DecodeTypes::SkipNextInstructionEqualRegister>;
}
