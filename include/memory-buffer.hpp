#pragma once

#include "instruction-packet.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <string>

namespace Chip8
{

class MemBuf
{
public:
  // - Types
  static constexpr auto max_memory_buffer_size{4096};

  struct MemoryStore
  {
    std::int16_t index{};
    std::int8_t value{};
  };
  
  enum class AddressSection : std::uint8_t
  {
    SystemReserve,
    Characters,
    Application,
  };
  
  enum class LoadAppErr : std::uint8_t
  {
    EMPTY_APP_NAME,
    INVALID_PATH,
  };
  
  // - Member functions
  [[nodiscard]] auto get_value_at(std::uint16_t index) const -> std::uint8_t;

  auto store_value_in_buffer(MemoryStore store) -> void;

  [[nodiscard]] auto load_app_into_buffer(const std::string &app_name) -> std::expected<void, LoadAppErr>;

  [[nodiscard]] auto fetch_instruction(std::size_t offset) -> InstructionPacket;
  
  [[nodiscard]] auto fetch_sprite_data(std::size_t offset, std::uint8_t buffer_len)
      -> std::span<const std::byte>;

private:
  std::array<std::byte, max_memory_buffer_size> buf_{};
};
} // namespace Chip8
