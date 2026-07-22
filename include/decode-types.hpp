#pragma once

#include <cstdint>

enum class ALUInstructions : std::uint8_t
{
  Ld = 0x0,
  Or = 0x1,
  And = 0x2,
  Xor = 0x3,
  Add = 0x4,
  Sub = 0x5,
  Shr = 0x6,
  SubN = 0x7,
  Shl = 0xE,
};

namespace Chip8::DecodeTypes
{
struct RegisterToRegister
{
  std::uint8_t first_register {0};
  std::uint8_t second_register {0};
  ALUInstructions arith_instruction{0x0};
};

struct SetValueToRegister { 
  std::uint16_t value{0};
  std::uint8_t register_id {0};
};

struct AddValueToRegister 
{
  std::uint16_t value{0};
  std::uint8_t register_id {0};
};

} // namespace Chip8::DecodeTypes
