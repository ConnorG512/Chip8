#pragma once

#include "renderer/opengl.hpp"
#include <utility>

namespace Chip8
{
template <std::size_t num_id> [[nodiscard]] auto gen_buffers() -> std::array<Id, num_id>
{
  static constexpr auto minimum_id_to_generate{1};
  static_assert(num_id >= minimum_id_to_generate, "number of ID's to generate must be at least 1!");

  std::array<Id, num_id> vbo_arr{};
  glGenBuffers(num_id, vbo_arr.data());

  return vbo_arr;
}

template <BufferMode buffer_mode, DrawMode draw_mode> void buffer_data(std::span<const Vertex> verticies) noexcept
{
  static constexpr auto vertex_size{sizeof(Vertex)};
  const auto vertex_buffer_len{static_cast<GLsizeiptr>(verticies.size() * vertex_size)};

  glBufferData(std::to_underlying(buffer_mode), vertex_buffer_len, verticies.data(), std::to_underlying(draw_mode));
}

template <ShaderType type>
[[nodiscard]]
auto create_shader() noexcept -> Id
{
  const auto result{glCreateShader(std::to_underlying(type))};
  return Id{result};
}
} // namespace Chip8
