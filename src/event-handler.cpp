#include "event-handler.hpp"

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <algorithm>
#include <array>
#include <cassert>
#include <expected>
#include <iostream>
#include <span>
#include <string_view>

namespace
{
[[nodiscard]] auto get_sdl_keyboard() noexcept -> std::expected<std::span<const bool>, std::string_view>
{
  std::int32_t keyboard_state_len{};
  const bool *keyboard_state{SDL_GetKeyboardState(&keyboard_state_len)};

  static constexpr auto minimum_keyboard_state_size{1};
  const bool is_valid_len{keyboard_state_len >= minimum_keyboard_state_size};
  const bool is_nullptr{keyboard_state == nullptr};
  if (!is_valid_len || is_nullptr) [[unlikely]]
  {
    return std::unexpected("SDL keyboard state is either nullptr or of an invalid len.");
  }

  std::span<const bool> keyboard_state_span(keyboard_state, static_cast<std::size_t>(keyboard_state_len));
  return keyboard_state_span;
}
} // namespace

auto Chip8::Event::poll() noexcept -> std::optional<List>
{
  static constexpr auto searched_keymaps = std::to_array({SDL_EVENT_QUIT, SDL_EVENT_KEY_DOWN});

  SDL_Event current_event{};

  while (SDL_PollEvent(&current_event))
  {
    const auto *found_event = std::ranges::find(searched_keymaps, current_event.type);
    if (found_event != searched_keymaps.end())
    {
      return static_cast<List>(*found_event);
    }
  }
  return std::nullopt;
}

auto Chip8::Event::get_keypress() noexcept -> std::optional<ScanCode>
{
  if (const auto result = get_sdl_keyboard(); result.has_value())
  {
    std::span<const bool> keypress_arr{result.value()};
    static constexpr auto checked_scancodes = std::to_array<std::int32_t>({SDL_SCANCODE_ESCAPE});

    for (auto scancode : checked_scancodes)
    {
      if (keypress_arr.at(scancode))
      {
        return static_cast<ScanCode>(scancode);
      }
    }
  }
  else
  {
    std::cout << result.error() << '\n';
  }
  return std::nullopt;
}
