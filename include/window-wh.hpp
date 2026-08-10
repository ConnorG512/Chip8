#pragma once

#include "chip8-spec.hpp"

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>

namespace Chip8
{
template <typename T>
concept DimensionsT = std::same_as<T, std::uint32_t> || std::same_as<T, std::int32_t>;

template <DimensionsT T = std::uint32_t> struct Dimensions
{
  T width{};
  T height{};
};

class WindowWH
{
public:
  explicit constexpr WindowWH(Dimensions<std::uint32_t> window_dim) noexcept
      pre(window_dim.width >= Chip8::Spec::screen_width)
      pre(window_dim.height >= Chip8::Spec::screen_height)
      pre(window_dim.width <= std::numeric_limits<std::int32_t>::max())
      pre(window_dim.height <= std::numeric_limits<std::int32_t>::max())
      : width_{window_dim.width}, height_{window_dim.height} 
  {
  }

  [[nodiscard]] constexpr auto value() const -> Dimensions<std::int32_t>
  {
    return {.width = static_cast<std::int32_t>(width_), .height = static_cast<std::int32_t>(height_)};
  };

  constexpr auto operator=(Dimensions<std::uint32_t> value) -> WindowWH &
    pre(value.width >= Chip8::Spec::screen_width)
    pre(value.height >= Chip8::Spec::screen_height)
    pre(value.width <= std::numeric_limits<std::int32_t>::max())
    pre(value.height <= std::numeric_limits<std::int32_t>::max())
  {
    width_ = value.width;
    height_ = value.height;
    return *this;
  }

private:
  std::uint32_t width_{};
  std::uint32_t height_{};
};
} // namespace Chip8
