#include "memory-buffer.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <filesystem>
#include <format>
#include <fstream>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

namespace
{
auto get_offset(Chip8::MemBuf::AddressOffset offset) -> Chip8::MemBuf::AddressRange
{
  using MemBuf = Chip8::MemBuf;

  static constexpr MemBuf::AddressRange system_reserved = {.start = 0x000, .end = 0x1FF};
  static constexpr MemBuf::AddressRange characters = {.start = 0x050, .end = 0x0A0};
  static constexpr MemBuf::AddressRange application = {.start = 0x200, .end = 0xFFF};

  switch (offset)
  {
    case MemBuf::AddressOffset::SystemReserve:
      return system_reserved;
    case MemBuf::AddressOffset::Characters:
      return characters;
    case MemBuf::AddressOffset::Application:
      return application;
  };

  assert(false && "Invalid AddressOffset enum value hit.");
  std::unreachable();
}

auto load_binary_from_path(const std::filesystem::path &path) -> std::ifstream
{
  if (!std::filesystem::exists(path))
  {
    throw std::runtime_error(std::format("File path provided [{}] does not exist!", path.string()));
  }

  return std::ifstream{path, std::ios::binary};
}

auto get_file_len(std::ifstream &file) -> std::size_t
{
  assert(file.is_open());

  file.clear();
  file.seekg(0, std::ios::end);
  const auto file_size{file.tellg()};
  file.seekg(0, std::ios::beg);

  assert(file_size > 0);
  return static_cast<std::size_t>(file_size);
}

auto create_buffer(std::ifstream &file, std::size_t size) -> std::vector<std::byte>
{
  assert(file.is_open());
  assert(size > 0);

  if (size > static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max())) [[unlikely]]
  {
    throw std::runtime_error("File size too large to allocate to buffer!");
  }

  std::vector<std::byte> file_buffer(static_cast<std::streamsize>(size));

  // Using a std::vector of std::byte requires the use of reinterpret cast to cast to char*
  // Therfore disabled the linting for the line below.
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  file.read(reinterpret_cast<char *>(file_buffer.data()), static_cast<std::streamsize>(size));

  return file_buffer;
}

void copy_to_buffer(std::span<const std::byte> src_buffer, std::span<std::byte> dest_bufffer,
                    Chip8::MemBuf::AddressOffset buffer_offset) noexcept
{
  std::ranges::copy(src_buffer, std::ranges::begin(dest_bufffer.subspan(get_offset(buffer_offset).start)));
}
} // namespace

[[nodiscard]] auto Chip8::MemBuf::get_value_at(std::uint16_t index) const -> std::uint8_t
{
  assert(index <= max_memory_buffer_size - 1);
  return static_cast<std::uint8_t>(buf_.at(index));
}

auto Chip8::MemBuf::store_value_in_buffer(MemoryStore store) -> void
{
  buf_.at(store.index) = static_cast<std::byte>(store.value);
}

auto Chip8::MemBuf::load_app_into_buffer(const std::string &app_name) -> std::expected<void, LoadAppErr>
{
  if (app_name.empty())
  {
    return std::unexpected(LoadAppErr::EMPTY_APP_NAME);
  }

  const std::filesystem::path app_path{std::filesystem::path("ch8-apps") / std::format("{}{}", app_name, ".ch8")};
  if (!std::filesystem::exists(app_path))
  {
    return std::unexpected(LoadAppErr::INVALID_PATH);
  }
  
  const auto app_file_buffer = [](const std::filesystem::path &path) -> std::vector<std::byte> {
    auto app_file{load_binary_from_path(path)};
    const auto app_file_size{get_file_len(app_file)};
    return create_buffer(app_file, app_file_size);
  }(app_path);
  
  copy_to_buffer(app_file_buffer, buf_, AddressOffset::Application);
  return {};
}

auto Chip8::MemBuf::fetch_instruction(std::size_t index) -> std::array<std::byte, 2>
{
  assert(index >= 0);
  static constexpr auto final_valid_memory_offset{2};
  assert(index < buf_.size() - final_valid_memory_offset);

  static constexpr auto following_byte{1};
  const std::array<std::byte, 2> fetched_bytes{buf_.at(index), buf_.at(index + following_byte)};

  return fetched_bytes;
}
