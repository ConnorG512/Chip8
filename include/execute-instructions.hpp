#pragma once

#include "decode-types.hpp"

namespace Chip8
{
class Device;
class Texture;
class AppRenderer;
} // namespace Chip8

namespace Chip8
{
void execute(DecodeTypes::List decode_list, Device &device, AppRenderer &renderer);
}
