#include "renderer/renderer.hpp"
#include "renderer/vbo-id.hpp"

#include <glad/glad.h>

namespace Chip8
{
void bind_buffer(std::span<const VBOId> vbo_id_span) noexcept -> void
{
  for (const auto vbo_id : vbo_id_span)
  {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id.value());
  }
}

auto buffer_data(std::span<const Vertex> verticies) noexcept -> void 
{
  static constexpr auto single_vertex_size{sizeof(Vertex)};
  const auto vertex_buffer_len{verticies.size()};

  const auto buffer_width {static_cast<GLsizeiptr>(single_vertex_size * vertex_buffer_len)};

  glBufferData(GL_ARRAY_BUFFER, buffer_width, verticies.data(), GL_STATIC_DRAW);
}
} // namespace Chip8
