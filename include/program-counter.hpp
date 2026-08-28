#pragma once

#include <cstddef>

namespace Chip8
{
class ProgramCounter
{
public:
  // - Constructors
  ProgramCounter(std::size_t initial_offset);

  // - Member functions
  void increment_program() noexcept;

  [[nodiscard]] auto get_current_increment() const noexcept -> std::size_t;

  void set_counter(std::size_t offset);

private:
  std::size_t current_count_{0};
};
} // namespace Chip8
