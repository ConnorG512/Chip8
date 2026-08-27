#pragma once

#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace Chip8
{
template <std::unsigned_integral T = std::uint32_t> class Length
{
public:
  Length() = default;
  explicit constexpr Length(std::unsigned_integral auto length) pre(length <= std::numeric_limits<T>::max())
      : length_{length} {};

  explicit constexpr Length(std::signed_integral auto length) pre(length >= 0) : length_{static_cast<T>(length)} {}

  [[nodiscard]] constexpr auto value() const noexcept -> T { return static_cast<T>(this->length_); }

  [[nodiscard]] constexpr auto same_as(Length compared_len) const noexcept -> bool
  {
    return (this->length_ == compared_len.value());
  }

  [[nodiscard]] constexpr auto same_as(T length) const noexcept -> bool { return (this->length_ == length); }

  [[nodiscard]] constexpr auto operator==(Length length) const noexcept -> bool { return same_as(length); }

  [[nodiscard]] constexpr auto operator==(T length) const noexcept -> bool { return same_as(length); }

  [[nodiscard]] constexpr auto resize(std::unsigned_integral auto new_size) noexcept
      -> Length &pre(new_size <= std::numeric_limits<T>::max())
  {
    this->length_ = new_size;
    return *this;
  }

  [[nodiscard]] constexpr auto operator=(std::unsigned_integral auto new_size) noexcept -> Length &
  {
    return resize(new_size);
  }

private:
  T length_{0};
};

// CTAD
template <std::signed_integral S>
Length(S) -> Length<std::make_unsigned<S>>;
} // namespace Chip8
