#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>

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
  [[nodiscard]] auto load_app_into_buffer(const std::string &app_name) -> std::expected<void, LoadAppErr>;
  [[nodiscard]] auto fetch_instruction(AddressSection addr_section, std::size_t offset) -> std::array<std::byte, 2>;
  

  static constexpr auto max_memory_buffer_size{4096};

private:
  std::array<std::byte, max_memory_buffer_size> buf_{};
};
} // namespace Chip8
