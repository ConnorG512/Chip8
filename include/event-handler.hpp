#pragma once

#include <SDL3/SDL_events.h>
#include <cstdint>
#include <optional>

namespace Chip8::Event
{
enum class List : std::uint16_t
{
  Quit = SDL_EVENT_QUIT,
  Key_Down = SDL_EVENT_KEY_DOWN,
};
[[nodiscard]] auto poll() noexcept -> std::optional<List>;

enum class ScanCode : std::uint8_t
{
  Escape = SDL_SCANCODE_ESCAPE,
};
[[nodiscard]] auto get_keypress() -> std::optional<ScanCode>;
} // namespace Chip8::Event
