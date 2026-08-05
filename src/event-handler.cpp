#include "event-handler.hpp"

#include <algorithm>
#include <array>

auto Chip8::Event::poll() noexcept -> std::optional<List>
{
  static constexpr auto searched_keymaps = std::to_array({SDL_EVENT_QUIT, SDL_EVENT_KEY_DOWN});

  SDL_Event current_event{};

  while (SDL_PollEvent(&current_event))
  {
    const auto* found_event = std::ranges::find(searched_keymaps, current_event.type);
    if(found_event != searched_keymaps.end())
    {
      return static_cast<List>(*found_event);
    }
  }
  return std::nullopt;
}
