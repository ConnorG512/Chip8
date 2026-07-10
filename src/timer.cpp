#include "timer.hpp"

#include <cassert>

Chip8::Timer::Timer(const std::int8_t current) noexcept
  : current_ {current} {
    assert(current < max_);
    assert(current >= 0);
  }

std::int8_t Chip8::Timer::reset_timer() noexcept
{
  current_ = max_;
  return current_;
}

std::int8_t Chip8::Timer::get_current() const noexcept { return current_; }

std::int8_t Chip8::Timer::set_current(const std::int8_t val) noexcept
{
  assert(val < max_);
  assert(val >= 0);

  current_ = val;
  return current_;
}

Chip8::Timer::State Chip8::Timer::dec() noexcept
{
  /*
    Timer will decrement and stay at 0 if hit.
  */

  current_ -= 1;
  if (current_ <= 0)
  {
    current_ = 0;
    return State::Zero;
  }
  else
    return State::Non_Zero;
}
