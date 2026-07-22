#include "decode-instruction.hpp"
#include "decode-types.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <stdexcept>
#include <utility>

namespace
{
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

auto Chip8::decode_instruction(std::array<std::byte, 2> instruction)
    -> std::variant<DecodeTypes::RegisterToRegister, DecodeTypes::AddValueToRegister, DecodeTypes::SetValueToRegister>
{
  const auto first_byte{instruction.at(std::to_underlying(Position::First))};
  const auto last_byte{instruction.at(std::to_underlying(Position::Last))};

  const auto instruction_found{get_instruction(first_byte)};
  switch (static_cast<Instructions>(instruction_found))
  {
    default:
      {
        throw std::runtime_error(std::format("Unsupported Instruction hit! Value: {}.", instruction_found));
      }
    case Instructions::RegisterToRegisterArith:
      {
        return DecodeTypes::RegisterToRegister{
            .first_register = get_nibble(first_byte, Position::Last),
            .second_register = get_nibble(last_byte, Position::First),
            .arith_instruction = static_cast<ALUInstructions>(get_nibble(last_byte, Position::Last)),
        };
      }
    case Instructions::SetValueToRegister:
      {
        return DecodeTypes::SetValueToRegister{
            .value = get_nibble(first_byte),
            .register_id = get_nibble(first_byte, Position::Last),
        };
      }
    case Instructions::AddValueToRegister:
      {
        return DecodeTypes::AddValueToRegister{
            .value = std::to_integer<std::uint16_t>(last_byte),
            .register_id = get_nibble(first_byte, Position::Last),
        };
      }
  }
}
