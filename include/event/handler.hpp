#pragma once

#include "event/type.hpp"
#include "event/scancode.hpp"

#include <SDL3/SDL_events.h>
#include <optional>

namespace Chip8
{
  [[nodiscard]] auto get_event_type(EventType event) noexcept -> std::optional<EventType>;
  [[nodiscard]] auto get_scancode() noexcept -> std::optional<Scancode>;
} // namespace Chip8::Event
