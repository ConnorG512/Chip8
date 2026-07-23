#include "device.hpp"

Chip8::Device::Device(std::size_t pc_start) noexcept
  : program_counter_{pc_start} {}
