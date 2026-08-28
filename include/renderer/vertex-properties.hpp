#pragma once

#include <concepts>

namespace Chip8
{
template <typename T = float>
  requires std::same_as<T, float>
struct VertexProperties
{
  T vx = {0.0F};
  T vy = {0.0F};
  T vz = {0.0F};
};

template <typename T> VertexProperties(T, T, T) -> VertexProperties<float>;
} // namespace Chip8
