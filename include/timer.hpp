#pragma once

#include <cstdint>

namespace
{
constexpr auto maximum_timer_len{60};
}

namespace Chip8
{
class Timer
{
public:
  Timer(std::int8_t current) noexcept;
  Timer() = default;

  auto reset_timer() noexcept -> std::int8_t;

  [[nodiscard]] auto get_current() const noexcept -> std::int8_t;
  auto set_current(std::int8_t val) noexcept -> std::int8_t;

  enum class State : std::int8_t
  {
    Zero,
    Non_Zero,
  };
  [[nodiscard]] auto dec() noexcept -> State;

private:
  std::int8_t max_{maximum_timer_len};
  std::int8_t current_{max_};
};
} // namespace Chip8
