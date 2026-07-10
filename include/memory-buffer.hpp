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
  auto store_value_in_buffer(MemoryStore store) -> void;

private:
  static constexpr auto max_memory_buffer_size{4096};
  std::array<std::byte, max_memory_buffer_size> buf_{};
};
} // namespace Chip8
