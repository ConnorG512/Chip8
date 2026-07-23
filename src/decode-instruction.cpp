#include "decode-instruction.hpp"
#include "decode-types.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
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

[[nodiscard]] auto get_three_byte_val(std::array<std::byte, 2> instruction) -> std::uint16_t
{
  std::uint16_t number{};
  std::memcpy(&number, instruction.data(), sizeof(instruction));
  number = std::byteswap(number);

  static constexpr auto three_nibble_mask{0x0FFF};
  return number & three_nibble_mask;
}

enum class Instructions : std::uint8_t
{
  System = 0,
  JumpAddress = 0x1,
  SkipNextInstructionEqual = 0x3,
  SkipNextInstructionNotEqual = 0x4,
  SkipNextInstructionEqualRegister = 0x5,
  SetValueToRegister = 0x6,
  AddValueToRegister = 0x7,
  RegisterToRegisterArith = 0x8,
};

} // namespace

auto Chip8::decode_instruction(std::array<std::byte, 2> instruction) -> DecodeTypes::List
{
  const auto first_byte{instruction.at(std::to_underlying(Position::First))};
  const auto last_byte{instruction.at(std::to_underlying(Position::Last))};

  const auto instruction_found{get_instruction(first_byte)};
  switch (static_cast<Instructions>(instruction_found))
  {
    default:
      {
        throw std::runtime_error(std::format("Cannot decode given instruction! Value: {}.", instruction_found));
      }
    case Instructions::System:
      {
        constexpr static std::byte clear_display_byte{0xE0};
        constexpr static std::byte return_from_subroutine_byte{0xEE};

        if (last_byte == clear_display_byte)
        {
          return DecodeTypes::ClearDisplay{};
        }

        if (last_byte == return_from_subroutine_byte)
        {
          return DecodeTypes::ReturnFromSubroutine{};
        }

        [[fallthrough]];
      }
    case Instructions::JumpAddress:
      {
        return DecodeTypes::JumpAddress{
            .value = get_three_byte_val(instruction),
        };
      }
    case Instructions::SkipNextInstructionEqual:
      {
        return DecodeTypes::SkipNextInstructionEqual{
            .value = std::to_integer<std::uint16_t>(last_byte),
            .register_id = get_nibble(first_byte, Position::Last),
        };
      }
    case Instructions::SkipNextInstructionNotEqual:
      {
        return DecodeTypes::SkipNextInstructionNotEqual{
            .value = std::to_integer<std::uint16_t>(last_byte),
            .register_id = get_nibble(first_byte, Position::Last),
        };
      }
    case Instructions::SkipNextInstructionEqualRegister:
      {
        return DecodeTypes::SkipNextInstructionEqualRegister{
            .register_id_1 = get_nibble(first_byte, Position::Last),
            .register_id_2 = get_nibble(last_byte, Position::First),
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
    case Instructions::RegisterToRegisterArith:
      {
        return DecodeTypes::RegisterToRegisterArith{
            .first_register = get_nibble(first_byte, Position::Last),
            .second_register = get_nibble(last_byte, Position::First),
            .arith_instruction = static_cast<ALUInstructions>(get_nibble(last_byte, Position::Last)),
        };
      }
  }
}
