#pragma once

namespace Chip8
{
class Title
{
public:
  Title() = default;
  constexpr Title(const char *title) pre(title != nullptr) : title_{title} {};

  [[nodiscard]] constexpr auto value() const -> const char*
  {
    return title_;
  }

private:
  const char *title_{"App"};
};
} // namespace Chip8
