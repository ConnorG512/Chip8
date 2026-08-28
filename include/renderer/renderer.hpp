#pragma once

#include "renderer/vbo-id.hpp"
#include "renderer/vertex.hpp"

#include <array>
#include <cstddef>
#include <span>

namespace Chip8
{
template <std::size_t id_to_generate> [[nodiscard]] auto gen_buffers() -> std::array<VBOId, id_to_generate>
{
  static constexpr auto minimum_id_to_generate{1};
  static_assert(id_to_generate >= minimum_id_to_generate, "number of ID's to generate must be at least 1!");

  std::array<VBOId, id_to_generate> vbo_arr{};
  glGenBuffers(id_to_generate, vbo_arr.data());

  return vbo_arr;
}

void bind_buffer(std::span<const VBOId> vbo_id_span) noexcept -> void pre(!vbo_id_span.empty());

auto buffer_data(std::span<const Vertex> verticies) noexcept -> void 
  pre(!verticies.empty())
{
  static constexpr auto vertex_size{sizeof(Vertex)};
  const auto vertex_buffer_len{verticies.size()};

  glBufferData(GL_ARRAY_BUFFER, vertex_size * vertex_buffer_len, verticies.data(), GL_STATIC_DRAW);
}

} // namespace Chip8
