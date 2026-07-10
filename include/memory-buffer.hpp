#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace Chip8
{

class MemBuf
{
public:
  [[nodiscard]] auto get_value_at(std::uint16_t index) const -> std::uint8_t;

  struct MemoryStore
  {
    std::int16_t index{};
    std::int8_t value{};
  };

  struct AddressOffsets
  {
    std::int16_t start{0};
    std::int16_t end{0};
  };
  static constexpr AddressOffsets system_reserved = {.start = 0x000, .end = 0x1FF};
  static constexpr AddressOffsets characters = {.start = 0x050, .end = 0x0A0};
  static constexpr AddressOffsets application = {.start = 0x200, .end = 0xFFF};

  auto store_value_in_buffer(AddressOffsets offset, MemoryStore store) -> void;

private:
  static constexpr auto max_memory_buffer_size{4096};
  std::array<std::byte, max_memory_buffer_size> buf_{};
};
} // namespace Chip8
