#pragma once

#include "decode-types.hpp"

namespace Chip8
{
class Device;
}

namespace Chip8
{
void execute(DecodeTypes::List decode_list, Device &device);
}
