#include "renderer/renderer.hpp"

#include <glad/glad.h>

namespace Chip8
{
void bind_buffer(std::span<const Id> vbo_id_span) noexcept -> void
{
  for (const auto gl_id : vbo_id_span)
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_id.value());
  }
}

auto buffer_data(std::span<const Vertex> verticies) noexcept -> void
{
  static constexpr auto single_vertex_size{sizeof(Vertex)};
  const auto vertex_buffer_len{verticies.size()};

  const auto buffer_width{static_cast<GLsizeiptr>(single_vertex_size * vertex_buffer_len)};

  glBufferData(GL_ARRAY_BUFFER, buffer_width, verticies.data(), GL_STATIC_DRAW);
}

void shader_source(Id shader, std::span<const char *> shader_code)
{
  glShaderSource(shader.value(), shader_code.size(), shader_code.data(), nullptr);
}

void compile_shader(Id shader) { glCompileShader(shader.value()); }

auto create_program() noexcept -> Id { return Id(glCreateProgram()); }

void attach_shader(Id shader_program, Id shader) { glAttachShader(shader_program.value(), shader.value()); }

void link_program(Id shader_program) { glLinkProgram(shader_program.value()); }
} // namespace Chip8
