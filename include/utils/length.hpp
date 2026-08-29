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
  // - Constructors
  Length() = default;
  explicit constexpr Length(std::unsigned_integral auto length) pre(length <= std::numeric_limits<T>::max())
      : length_{length} {};

  explicit constexpr Length(std::signed_integral auto length) pre(length >= 0) : length_{static_cast<T>(length)} {}

  // - Member functions
  [[nodiscard]] constexpr auto value() const noexcept -> T { return static_cast<T>(this->length_); }

  // - Operator overloads
  [[nodiscard]] constexpr auto operator==(Length length) const noexcept -> bool
  {
    return (this->length_ == length.length_);
  }

  [[nodiscard]] constexpr auto operator==(T length) const noexcept -> bool pre(length >= 0)
  {
    return (this->length_ == static_cast<T>(length));
  }

  [[nodiscard]] constexpr auto operator=(Length new_len) noexcept -> Length &
  {
    this->length_ = new_len.length_;
    return *this;
  }

  [[nodiscard]] constexpr auto operator=(T new_len) noexcept -> Length &
  {
    this->length_ = new_len;
    return *this;
  }

private:
  T length_{0};
};

// CTAD
template <std::signed_integral S> Length(S) -> Length<std::make_unsigned<S>>;
} // namespace Chip8
