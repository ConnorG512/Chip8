#pragma once

#include "decode-types.hpp"

#include <array>
#include <cstddef>
#include <variant>

namespace Chip8
{
[[nodiscard]] auto decode_instruction(std::array<std::byte, 2> instruction) noexcept
    -> std::variant<std::monostate, DecodeTypes::RegisterToRegister, DecodeTypes::ValueToRegister>;
}
