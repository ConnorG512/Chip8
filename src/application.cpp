#include "application.hpp"
#include "event-handler.hpp"
#include "decode-instruction.hpp"
#include "execute-instructions.hpp"

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
    if (const auto poll = Chip8::Event::poll(); poll.has_value())
    {
      using EventList = Chip8::Event::List;

      switch (poll.value())
      {
        case EventList::Quit:
          {
            done = true;
            break;
          }
        case EventList::Key_Down:
          {
            if (const auto pressed_key = Chip8::Event::get_keypress(); pressed_key.has_value())
            {
              using ScanCode = Chip8::Event::ScanCode;
              switch (pressed_key.value())
              {
                case ScanCode::Escape:
                  {
                    done = true;
                  }
              }
            }

            break;
          }
        default:
          {
            throw std::runtime_error("Invalid Event!");
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
