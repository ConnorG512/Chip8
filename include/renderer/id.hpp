#pragma once

#include <cstdint>
#include <limits>

namespace Chip8
{
class Id
{
public:
  // - Constructors
  explicit constexpr Id(std::uint32_t gl_id) pre(id <= std::numeric_limits<std::uint32_t>::max()) : id_{gl_id} {}

  // - Member functions:
  [[nodiscard]] constexpr value() const noexcept -> std::uint32_t { return id_; }

private:
  std::uint32_t id_{0};
};
} // namespace Chip8
