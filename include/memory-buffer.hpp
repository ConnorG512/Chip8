#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>

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

  struct AddressRange
  {
    std::int16_t start{0};
    std::int16_t end{0};
  };

  enum class AddressOffset : std::uint8_t
  {
    SystemReserve,
    Characters,
    Application,
  };

  auto store_value_in_buffer(MemoryStore store) -> void;

  void load_file_to_buffer(const std::filesystem::path &path, AddressOffset offset);

private:
  static constexpr auto max_memory_buffer_size{4096};
  std::array<std::byte, max_memory_buffer_size> buf_{};
};
} // namespace Chip8
