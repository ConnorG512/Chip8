#pragma once

#include <cstdint>

namespace Chip8
{
class Timer
{
public:
  Timer(const std::int8_t current) noexcept;
  Timer() = default;

  std::int8_t reset_timer() noexcept;

  [[nodiscard]] std::int8_t get_current() const noexcept;
  std::int8_t set_current(const std::int8_t val) noexcept;

  enum class State
  {
    Zero,
    Non_Zero,
  };
  [[nodiscard]] State dec() noexcept;

private:
  std::int8_t max_{60};
  std::int8_t current_{max_};
};
} // namespace Chip8
