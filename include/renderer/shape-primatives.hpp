#pragma once

#include "renderer/vertex.hpp"
#include <array>

namespace Chip8
{
inline constexpr std::array<Vertex, 3> triangle{
    Vertex({.vx = 0.5F, .vy = -0.5F, .vz = 0.0F}),
    Vertex({.vx = 0.5F, .vy = 0.5F, .vz = 0.0F}),
    Vertex({.vx = 0.0F, .vy = 0.5F, .vz = 0.0F}),
};
}
