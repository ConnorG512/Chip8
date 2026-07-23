#include "program-counter.hpp"
      
Chip8::ProgramCounter::ProgramCounter(std::size_t initial_offset)
  : current_count_{initial_offset} {} 

void Chip8::ProgramCounter::increment_program() noexcept
{
  constexpr static auto steps{2};
  current_count_ += steps;
}

[[nodiscard]] auto Chip8::ProgramCounter::get_current_increment() const noexcept -> std::size_t 
{
  return current_count_;
}
