#pragma once 

#include "memory-buffer.hpp"
#include "register.hpp"
#include "screen-buffer.hpp"
#include "program-counter.hpp"

#include <array>

namespace Chip8 {
  class Device {
    private:
      constexpr static auto regular_register_count{16};

    public:
      Device(std::size_t pc_start) noexcept;
      Device() = default;
      
      Chip8::ScrBuf screen_buffer{};
      Chip8::MemBuf mem_buf_{};
      
      std::array<Chip8::Register<std::uint8_t>, regular_register_count> registers_{};
      Chip8::Register<std::uint16_t> index_register_{};
      Chip8::ProgramCounter program_counter_{0};
      Chip8::Register<std::uint8_t> stack_pointer_{};
  };
}
