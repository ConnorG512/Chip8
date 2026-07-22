#include "decode-instruction.hpp"
#include "decode-types.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

namespace
{
void unimplemmented_opcode_message(const int16_t instruction_val)
{
  std::cout << "Unsupported instruction with value: [" << static_cast<std::uint32_t>(instruction_val)
            << "]. Returning value 0.\n";
}

[[nodiscard]] auto get_instruction(std::byte instruction_byte) -> std::uint8_t
{
  constexpr static auto one_nibble{4};
  return std::to_integer<std::uint8_t>(instruction_byte >> one_nibble);
}

enum class Position : std::uint8_t
{
  First = 0,
  Last = 1,
};

[[nodiscard]] auto get_nibble(std::byte register_byte, Position nibble_position = Position::First) -> std::uint8_t
{
  constexpr static std::byte first_nibble_mask{0xF0};
  constexpr static std::byte last_nibble_mask{0x0F};

  switch (nibble_position)
  {
    case Position::First:
      {
        return std::to_integer<std::uint8_t>(register_byte & first_nibble_mask);
      }
    case Position::Last:
      {
        return std::to_integer<std::uint8_t>(register_byte & last_nibble_mask);
      }
  }

  return std::to_integer<std::uint8_t>(register_byte & last_nibble_mask);
}

enum class Instructions : std::uint8_t
{
  SetValueToRegister = 6,
  AddValueToRegister = 7,
  RegisterToRegisterArith = 8,
};

} // namespace

auto Chip8::decode_instruction(std::array<std::byte, 2> instruction) noexcept
    -> std::variant<std::monostate, DecodeTypes::RegisterToRegister, DecodeTypes::ValueToRegister>
{
  const auto found_instruction{get_instruction(instruction.at(0))};

  switch (found_instruction)
  {
    default:
      {
        unimplemmented_opcode_message(found_instruction);
        return std::monostate();
      }
    case std::to_underlying(Instructions::RegisterToRegisterArith):
      {
        return DecodeTypes::RegisterToRegister{
            .first_register = get_nibble(instruction.at(std::to_underlying(Position::First)), Position::Last),
            .second_register = get_nibble(instruction.at(std::to_underlying(Position::Last)), Position::First),
            .arith_instruction = static_cast<ALUInstructions>(
                get_nibble(instruction.at(std::to_underlying(Position::Last)), Position::Last)),
        };
      }
    case std::to_underlying(Instructions::SetValueToRegister):
    case std::to_underlying(Instructions::AddValueToRegister):
      {
        return DecodeTypes::ValueToRegister {
          .value = std::to_integer<std::uint16_t>(instruction.at(std::to_underlying(Position::Last))),
          .register_id = get_nibble(instruction.at(std::to_underlying(Position::First)), Position::Last),
        };
      }
  }
}
