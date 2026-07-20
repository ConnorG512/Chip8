#pragma once 

#include "memory-buffer.hpp"
#include "register.hpp"
#include "screen-buffer.hpp"

namespace Chip8 {
  class Device {
    private:
      static constexpr auto gp_register_size{16};

    public:
      Chip8::ScrBuf screen_buffer{};
      Chip8::MemBuf mem_buf_{};
      
      // Registers: 
      Chip8::Register<std::uint8_t> reg_0_{};
      Chip8::Register<std::uint8_t> reg_1_{};
      Chip8::Register<std::uint8_t> reg_2_{};
      Chip8::Register<std::uint8_t> reg_3_{};
      Chip8::Register<std::uint8_t> reg_4_{};
      Chip8::Register<std::uint8_t> reg_5_{};
      Chip8::Register<std::uint8_t> reg_6_{};
      Chip8::Register<std::uint8_t> reg_7_{};
      Chip8::Register<std::uint8_t> reg_8_{};
      Chip8::Register<std::uint8_t> reg_9_{};
      Chip8::Register<std::uint8_t> reg_A_{};
      Chip8::Register<std::uint8_t> reg_B_{};
      Chip8::Register<std::uint8_t> reg_C_{};
      Chip8::Register<std::uint8_t> reg_D_{};
      Chip8::Register<std::uint8_t> reg_E_{};
      Chip8::Register<std::uint8_t> reg_F_{};
      Chip8::Register<std::uint16_t> index_register_{};
      Chip8::Register<std::uint16_t> program_counter_{};
      Chip8::Register<std::uint8_t> stack_pointer_{};
  };
}
