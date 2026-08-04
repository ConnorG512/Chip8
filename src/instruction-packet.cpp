#include "instruction-packet.hpp"

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace
{
constexpr auto single_nibble_shift{4};

[[nodiscard]] auto get_first_nibble(std::byte byte) noexcept -> std::uint8_t
{
  static constexpr std::byte first_nibble_bitmask{0xF0};

  return std::to_integer<std::uint8_t>((byte & first_nibble_bitmask) >> single_nibble_shift);
}

[[nodiscard]] auto get_second_nibble(std::byte byte) noexcept -> std::uint8_t
{
  static constexpr std::byte second_nibble_bitmask{0x0F};

  return std::to_integer<std::uint8_t>(byte & second_nibble_bitmask);
}
} // namespace

auto Chip8::InstructionPacket::arr() const noexcept -> std::array<std::byte, 2> { return {first_byte_, second_byte_}; }

auto Chip8::InstructionPacket::nibble(PositionProperties properties) const noexcept -> std::uint8_t
{
  const bool is_first_nibble{properties.nibble == Position::First};

  switch (properties.byte)
  {
    case Position::First:
      {
        return (is_first_nibble) ? get_first_nibble(first_byte_) : get_second_nibble(first_byte_);
      }
    case Position::Second:
      {
        return (is_first_nibble) ? get_first_nibble(second_byte_) : get_second_nibble(second_byte_);
      }
  }
}

Chip8::InstructionPacket::InstructionPacket(std::array<std::byte, 2> bytes) noexcept
    : first_byte_{bytes.at(0)}, second_byte_{bytes.at(1)}
{
}

auto Chip8::InstructionPacket::three_byte_val() const noexcept -> std::uint16_t
{
  std::uint16_t number_result{};

  static constexpr auto instruction_length{2};
  std::array<std::byte, instruction_length> full_instruction{first_byte_, second_byte_};

  std::memcpy(&number_result, full_instruction.data(), sizeof(full_instruction));
  number_result = std::byteswap(number_result);

  static constexpr auto three_nibble_mask{0x0FFF};
  return number_result & three_nibble_mask;
}

[[nodiscard]] auto Chip8::InstructionPacket::get_instruction() const noexcept -> std::uint8_t
{
  return std::to_integer<std::uint8_t>(first_byte_) >> single_nibble_shift;
}

[[nodiscard]] auto Chip8::InstructionPacket::val(Position byte_pos) const noexcept -> std::uint8_t
{
  return std::to_integer<std::uint8_t>((byte_pos == Position::First) ? first_byte_ : second_byte_);
}
