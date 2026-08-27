#include "application.hpp"
#include "event/handler.hpp"
#include "decode-instruction.hpp"
#include "event/type.hpp"
#include "execute-instructions.hpp"
#include <SDL3/SDL_events.h>

namespace Chip8
{
auto Application::run() -> std::optional<ExitCode>
{
  const auto screen_refresh_rate{lua_.get<std::uint32_t>("config.refresh_rate")};

  const auto mem_load_res{memory_.mem_buf.load_app_into_buffer(lua_.get<std::string>("config.app_name"))};
  if (!mem_load_res.has_value())
  {
    return ExitCode::Quit;
  }

  renderer_.clear_renderer();

  bool done{false};
  while (!done)
  {
    SDL_Event event {};
    while(SDL_PollEvent(&event))
    {
      const auto current_event = get_event_type(EventType(static_cast<SDL_EventType>(event.type)));
      if(current_event.has_value())
      {
        if(current_event.value() == SDL_EVENT_KEY_DOWN)
        {
          done = true;
        }
      }
    }

    // Application Loop start:
    auto fetched_instruction{Chip8::decode_instruction(
        {memory_.mem_buf.fetch_instruction(pc_.get_current_increment())})};

    pc_.increment_program();

    Chip8::execute(fetched_instruction, cpu_, memory_, pc_, renderer_);

    renderer_.present();
    // Application Loop end:

    SDL_Delay(screen_refresh_rate);
  }

  return ExitCode::Quit;
}
} // namespace Chip8
