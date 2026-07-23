#pragma once

#include <cstdint>
#include <variant>

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
struct ClearDisplay
{
};

struct ReturnFromSubroutine
{
};

struct JumpAddress {
  std::uint16_t value{0};
};

struct SkipNextInstructionEqual
{
  std::uint16_t value{0};
  std::uint8_t register_id{0};
};

struct SkipNextInstructionNotEqual
{
  std::uint16_t value{0};
  std::uint8_t register_id{0};
};

struct SkipNextInstructionEqualRegister
{
  std::uint8_t register_id_1{0};
  std::uint8_t register_id_2{0};
};

struct SetValueToRegister
{
  std::uint16_t value{0};
  std::uint8_t register_id{0};
};

struct AddValueToRegister
{
  std::uint16_t value{0};
  std::uint8_t register_id{0};
};

struct RegisterToRegisterArith
{
  std::uint8_t first_register{0};
  std::uint8_t second_register{0};
  ALUInstructions arith_instruction{0x0};
};

using List =
    std::variant<ClearDisplay, ReturnFromSubroutine, JumpAddress, SkipNextInstructionEqual, SkipNextInstructionNotEqual,
                 SkipNextInstructionEqualRegister, SetValueToRegister, AddValueToRegister, RegisterToRegisterArith>;

} // namespace Chip8::DecodeTypes
