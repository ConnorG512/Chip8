#pragma once 

#include <concepts>

namespace Chip8 {
  template <typename T>
  concept BoundsT = std::integral<T> || std::floating_point<T>;
  
  template <BoundsT T>
  struct Bounds {
    T lower {};
    T upper {};
  };
  
  template <BoundsT T>
  [[nodiscard]] constexpr auto within_bounds(Bounds<T> bounds, BoundsT auto value) noexcept -> bool
    pre(bounds.lower < bounds.upper)
    pre(bounds.upper > bounds.lower)
  {
    const bool is_within_lower_bounds {value >= bounds.lower};
    const bool is_within_upper_bounds {value <= bounds.upper};

    return (is_within_lower_bounds && is_within_upper_bounds);
  }
}
