#include "memory-buffer.hpp"

#include <cassert>

[[nodiscard]] auto Chip8::MemBuf::get_value_at(std::uint16_t index) const -> std::uint8_t
{
  assert(index <= max_memory_buffer_size);
  return static_cast<std::uint8_t>(buf_.at(index));
}

auto Chip8::MemBuf::store_value_in_buffer(AddressOffsets offset, MemoryStore store) -> void
{
  assert(store.index >= offset.start);
  assert(store.index <= offset.end);

  buf_.at(store.index) = static_cast<std::byte>(store.value);
}
