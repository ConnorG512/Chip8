#pragma once

#include <cstdint>
#include <limits>

namespace Chip8
{
class VBOId
{
public:
  // - Constructors
  explicit constexpr VBOId(std::uint32_t vbo_id) pre(id <= std::numeric_limits<std::uint32_t>::max()) : id_{id_} {}

  // - Member functions:
  [[nodiscard]] constexpr value() const noexcept -> std::uint32_t { return id_; }

  // - Operator overloads
  [[nodiscard]] constexpr operator*() const noexcept -> std::uint32_t { return value(); }

private:
  std::uint32_t id_{0};
};
} // namespace Chip8
