#pragma once

#include "vertex-properties.hpp"

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
      pre(vertex.vx >= minimum_vertex_range && vertex.vx <= maximum_vertex_range)
      pre(vertex.vy >= minimum_vertex_range && vertex.vy <= maximum_vertex_range)
      pre(vertex.vz >= minimum_vertex_range && vertex.vz <= maximum_vertex_range)
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
