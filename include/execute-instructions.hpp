#pragma once

#include "decode-types.hpp"

#include <variant>

namespace Chip8
{
class AppRenderer;
class Cpu;
class Memory;
class ProgramCounter;
} // namespace Chip8

namespace Chip8
{
void execute(DecodeTypes::List decode_list, Cpu &cpu, Memory &memory, ProgramCounter &pc, AppRenderer &renderer)
    pre(decode_list.index() != std::variant_npos);
}
