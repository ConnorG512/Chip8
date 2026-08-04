#include "decode-instruction.hpp"
#include "decode-types.hpp"
#include "instruction-packet.hpp"

#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <print>

namespace
{
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
  LoadIntoIndexRegister = 0xA,
  DrawToScreen = 0xD,
};

} // namespace

auto Chip8::decode_instruction(InstructionPacket packet) -> DecodeTypes::List
{
  const auto instruction_found{packet.get_instruction()};
  switch (static_cast<Instructions>(instruction_found))
  {
    using Pos = InstructionPacket::Position;

    case Instructions::System:
      {
        constexpr static auto clear_display_byte{0xE0};
        constexpr static auto return_from_subroutine_byte{0xEE};

        if (packet.val(Pos::Second) == clear_display_byte)
        {
          return DecodeTypes::ClearDisplay{};
        }

        if (packet.val(Pos::Second) == return_from_subroutine_byte)
        {
          return DecodeTypes::ReturnFromSubroutine{};
        }

        break;
      }
    case Instructions::JumpAddress:
      {
        return DecodeTypes::JumpAddress{
            .value = packet.three_byte_val(),
        };
      }
    case Instructions::SkipNextInstructionEqual:
      {
        return DecodeTypes::SkipNextInstructionEqual{
            .value = packet.val(Pos::Second),
            .register_id = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
        };
      }
    case Instructions::SkipNextInstructionNotEqual:
      {
        return DecodeTypes::SkipNextInstructionNotEqual{
            .value = packet.val(Pos::Second),
            .register_id = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
        };
      }
    case Instructions::SkipNextInstructionEqualRegister:
      {
        return DecodeTypes::SkipNextInstructionEqualRegister{
            .register_id_1 = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
            .register_id_2 = packet.nibble({.byte = Pos::Second, .nibble = Pos::First}),
        };
      }
    case Instructions::SetValueToRegister:
      {
        return DecodeTypes::SetValueToRegister{
            .value = packet.val(Pos::Second),
            .register_id = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
        };
      }
    case Instructions::AddValueToRegister:
      {
        return DecodeTypes::AddValueToRegister{
            .value = packet.val(Pos::Second),
            .register_id = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
        };
      }
    case Instructions::RegisterToRegisterArith:
      {
        return DecodeTypes::RegisterToRegisterArith{
            .first_register = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
            .second_register = packet.nibble({.byte = Pos::Second, .nibble = Pos::First}),
            .arith_instruction = static_cast<ALUInstructions>(packet.val(Pos::Second)),
        };
      }
    case Instructions::LoadIntoIndexRegister:
      {
        return DecodeTypes::LoadIntoIndexRegister{
            .value = packet.three_byte_val(),
        };
      }
    case Instructions::DrawToScreen:
      {
        return DecodeTypes::DrawToScreen{
            .register_id_1 = packet.nibble({.byte = Pos::First, .nibble = Pos::Second}),
            .register_id_2 = packet.nibble({.byte = Pos::Second, .nibble = Pos::First}),
            .bytes_to_draw = packet.nibble({.byte = Pos::Second, .nibble = Pos::Second}),
        };
      }
    default:
      {
        std::uint16_t address{};
        std::memcpy(&address, packet.arr().data(), sizeof(packet.arr()));
        address = std::byteswap(address);

        std::println("Cannot decode given instruction! Value: 0x{:04X}.", address);
        break;
        // throw std::runtime_error(std::format("Cannot decode given instruction! Value: 0x{:04X}.\n", address));
      }
  }
}
