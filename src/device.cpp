#include "device.hpp"

#include <SDL3/SDL_render.h>

Chip8::Device::Device(std::size_t pc_start) noexcept
  : program_counter_{pc_start} {}
