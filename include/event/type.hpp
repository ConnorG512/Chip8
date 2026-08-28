#pragma once

#include <SDL3/SDL_events.h>
#include <concepts>

namespace Chip8
{
template <typename T>
concept SDLEventType = std::same_as<T, SDL_EventType>;

class EventType
{
public:
  // Constructors
  explicit constexpr EventType(SDLEventType auto event_t) : event_type_{event_t} {}
  
  // Member functions
  [[nodiscard]] constexpr auto same_as(SDLEventType auto event) const noexcept -> bool
  {
    return (this->event_type_ == event);
  }

  [[nodiscard]] constexpr auto same_as(EventType event) const noexcept -> bool
  {
    return (this->event_type_ == event.event_type_);
  }
  
  // Operator overloads
  [[nodiscard]] constexpr auto operator==(SDLEventType auto event_type) const noexcept -> bool
  {
    return same_as(event_type);
  }

  [[nodiscard]] constexpr auto operator==(EventType event) const noexcept -> bool { return same_as(event); }

private:
  SDL_EventType event_type_{};
};
} // namespace Chip8
