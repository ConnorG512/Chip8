#pragma once

#include "renderer/id.hpp"
#include "renderer/vertex.hpp"

#include <array>
#include <cstddef>
#include <glad/glad.h>
#include <span>
#include <utility>

namespace Chip8
{

// - Types
enum class ShaderType : std::uint16_t
{
  Vertex = GL_VERTEX_SHADER,
  Geometry = GL_GEOMETRY_SHADER,
  Fragment = GL_FRAGMENT_SHADER,
};

enum class DrawMode : std::uint16_t
{
  Static = GL_STATIC_DRAW,
  Dynamic = GL_DYNAMIC_DRAW,
  Stream = GL_STREAM_DRAW,
};

enum class BufferMode : std::uint16_t
{
  ArrayBuffer = GL_ARRAY_BUFFER,
  ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
};

// - Functions

template <std::size_t num_id> [[nodiscard]] auto gen_buffers() -> std::array<Id, num_id>;

template <BufferMode buffer_mode, DrawMode draw_mode>
void bind_buffer(std::span<const Id> vbo_id_span) noexcept pre(!vbo_id_span.empty());

void buffer_data(std::span<const Vertex> verticies) noexcept pre(!verticies.empty());

template <ShaderType type>
[[nodiscard]]
auto create_shader() noexcept -> Id;

void shader_source(Id shader, std::span<const char *> shader_code) pre(!shader_code.empty());

void compile_shader(Id shader);

[[nodiscard]] auto create_program() noexcept -> Id;

void attach_shader(Id shader_program, Id shader);

void link_program(Id shader_program);
} // namespace Chip8

#include "opengl-impl.hpp"
