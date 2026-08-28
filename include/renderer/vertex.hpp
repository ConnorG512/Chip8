#pragma once

#include "vertex-properties.hpp"
#include "utility"

#include <cstdint>
#include <stdexcept>

namespace Chip8
{
inline constexpr auto minimum_vertex_range{-1.0F};
inline constexpr auto max_vertex_range{1.0F};

class Vertex
{
public:
  // - Types
  enum class VertexCoord : std::uint8_t
  {
    X,
    Y,
    Z,
  };

  // - Constructors
  explicit constexpr Vertex(VertexProperties<float> vertex)
      pre(within_bounds({.lower = minimum_vertex_range, .upper = maximum_vertex_range}, vertex.vx))
      pre(within_bounds({.lower = minimum_vertex_range, .upper = maximum_vertex_range}, vertex.vy))
      pre(within_bounds({.lower = minimum_vertex_range, .upper = maximum_vertex_range}, vertex.vz))
      : vx{vertex.vx}, vy{vertex.vy}, vz{vertex.vz} {};

  // - Member functions:
  [[nodiscard]] constexpr auto value(VertexCoord coord) const -> float
  {
    switch (coord)
    {
      case VertexCoord::X:
        return vx_;
      case VertexCoord::Y:
        return vy_;
      case VertexCoord::Z:
        return vz_;
      default:
        throw std::runtime_error("Invalid Vertex Coord passed!");
    }
  }

  [[nodiscard]] constexpr auto value() const -> VertexProperties<float>
  {
    return VertexProperties{.vx = vx_, .vy = vy_, .vz = vz_};
  }

private:
  float vx_{0.0F};
  float vy_{0.0F};
  float vz_{0.0F};
};
} // namespace Chip8
