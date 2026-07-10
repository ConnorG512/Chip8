#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace Chip8
{

template <typename T>
concept RegisterType = std::is_same_v<T, std::uint8_t> || std::is_same_v<T, std::uint16_t>;

template <RegisterType T> class Register
{
public:
  auto assign_val(T val) noexcept -> void { held_value_ = val; }
  [[nodiscard]] auto get_data() const noexcept -> T { return held_value_; }
  auto reset() noexcept -> void { held_value_ = 0; };

private:
  T held_value_{0};
};
} // namespace Chip8
