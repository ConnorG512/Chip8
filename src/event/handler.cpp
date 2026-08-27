#include "event/handler.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <span>
#include <ranges>

namespace
{
[[nodiscard("Required for getting user input!")]] auto get_sdl_keyboard() noexcept -> std::span<const bool>
{
  std::int32_t keyboard_state_len{};
  const bool *keyboard_state{SDL_GetKeyboardState(&keyboard_state_len)};

  static constexpr auto minimum_keyboard_state_size{1};
  const bool is_valid_len{keyboard_state_len >= minimum_keyboard_state_size};
  const bool is_nullptr{keyboard_state == nullptr};
  if (!is_valid_len || is_nullptr) [[unlikely]]
  {
    return {};
  }

  std::span<const bool> keyboard_state_span(keyboard_state, static_cast<std::size_t>(keyboard_state_len));
  return keyboard_state_span;
}
} // namespace

namespace Chip8
{
[[nodiscard]] auto get_event_type(EventType currently_set_event) noexcept -> std::optional<EventType>
{
  static constexpr auto available_events =
      std::to_array<const EventType>({EventType(SDL_EVENT_KEY_DOWN), EventType(SDL_EVENT_GAMEPAD_BUTTON_DOWN),
                                      EventType(SDL_EVENT_GAMEPAD_ADDED), EventType(SDL_EVENT_GAMEPAD_REMOVED)});

  const auto *const result = std::ranges::find_if(
      available_events, [current_event = currently_set_event](const EventType available_event) -> bool
      { return (current_event == available_event); });

  if (result == available_events.end())
  {
    return std::nullopt;
  }

  return *result;
}

[[nodiscard]] auto get_scancode() noexcept -> std::optional<Scancode>
{
  const auto keys = get_sdl_keyboard();
  
  static constexpr bool pressed {true};
  const auto result = std::ranges::find(keys, pressed);
  if(result == keys.end())
  {
    return std::nullopt;
  }
  
  const auto key_index {std::ranges::distance(std::ranges::begin(keys), result)};
  return Scancode(static_cast<SDL_Scancode>(key_index));
}
} // namespace Chip8
