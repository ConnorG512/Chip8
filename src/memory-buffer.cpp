#include "memory-buffer.hpp"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>
#include <limits>
#include <ranges>
#include <stdexcept>
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
} // namespace

[[nodiscard]] auto Chip8::MemBuf::get_value_at(std::uint16_t index) const -> std::uint8_t
{
  assert(index <= max_memory_buffer_size);
  return static_cast<std::uint8_t>(buf_.at(index));
}

auto Chip8::MemBuf::store_value_in_buffer(MemoryStore store) -> void
{
  buf_.at(store.index) = static_cast<std::byte>(store.value);
}

void Chip8::MemBuf::load_file_to_buffer(const std::filesystem::path &path, AddressOffset offset)
{
  auto file{load_binary_from_path(path)};
  const auto file_size{get_file_len(file)};
  auto file_buffer{create_buffer(file, file_size)};

  const auto offsets{get_offset(offset)};

  std::ranges::copy(file_buffer | std::views::take(file_size),
                    std::ranges::begin(std::span{buf_}.subspan(offsets.start)));
}
