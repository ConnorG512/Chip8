#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace Chip8
{
class InstructionPacket
{
public:
  explicit InstructionPacket(std::array<std::byte, 2> bytes) noexcept;

  enum class Position : std::uint8_t
  {
    First,
    Second,
  };
  struct PositionProperties
  {
    Position byte{};
    Position nibble{};
  };
  [[nodiscard]] auto nibble(PositionProperties properties) const noexcept -> std::uint8_t;

  [[nodiscard]] auto three_byte_val() const noexcept -> std::uint16_t;
  [[nodiscard]] auto get_instruction() const noexcept -> std::uint8_t;
  [[nodiscard]] auto val(Position byte_pos) const noexcept -> std::uint8_t;

private:
  std::byte first_byte_{};
  std::byte second_byte_{};
};
} // namespace Chip8
