#pragma once

#include "chip8-spec.hpp"

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <utility>

namespace Chip8
{
struct Dimensions
{
  std::uint32_t width{};
  std::uint32_t height{};
};


class WindowWH
{
public:
  explicit constexpr WindowWH(Dimensions window_dim) noexcept : width_{window_dim.width}, height_{window_dim.height}
  {
    for (auto dim : {window_dim.width, window_dim.height})
    {
      assert(std::cmp_greater_equal(dim, Spec::minimum_window_size));
    }
  }

  [[nodiscard]] constexpr auto value() const -> Dimensions { return {.width = width_, .height = height_}; };
  constexpr auto operator=(Dimensions value) -> WindowWH &
  {
    for (auto dim : {value.width, value.height})
    {
      assert(std::cmp_greater_equal(dim, Spec::minimum_window_size));
    }
    width_ = value.width;
    height_ = value.height;
    return *this;
  }

private:
  std::uint32_t width_{};
  std::uint32_t height_{};
};
} // namespace Chip8
