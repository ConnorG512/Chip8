#pragma once

#include "chip8-spec.hpp"
#include "register.hpp"

#include <array>
#include <cstdint>

namespace Chip8
{
struct Cpu
{
  std::array<Chip8::Register<std::uint8_t>, Spec::register_count> registers{};
  Chip8::Register<std::uint16_t> index_register{};
  Chip8::Register<std::uint8_t> stack_pointer{};
};
} // namespace Chip8
