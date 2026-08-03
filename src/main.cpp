#include "app-renderer.hpp"
#include "app-window.hpp"
#include "chip8-spec.hpp"
#include "decode-instruction.hpp"
#include "device.hpp"
#include "execute-instructions.hpp"
#include "lua/lua.hpp"
#include "memory-buffer.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

auto main() -> int
{
  SDL_Init(SDL_INIT_VIDEO);

  try
  {
    Lua::Engine lua{};
    lua.execute_file("config.lua");

    const auto window_scale{lua.get<std::int32_t>("window_scale")};

    Chip8::AppWindow window{
        "Chip8",
        {.width = Chip8::Spec::screen_width * window_scale, .height = Chip8::Spec::screen_height * window_scale}};

    Chip8::AppRenderer renderer{window.window_ref(), window.get_window_dimensions().value()};

    Chip8::Device device{Chip8::Spec::application_reserve.start};

    const auto result = device.mem_buf_.load_app_into_buffer(lua.get<std::string>("app_name"));
    if (!result.has_value())
    {
      std::cerr << "Failed to load file!\n";
      return EXIT_FAILURE;
    }

    bool done{false};
    while (!done)
    {
      SDL_Event event{};
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_EVENT_QUIT)
        {
          done = true;
        }
      }
      // Application Loop start:

      renderer.clear_renderer();

      auto fetched_instruction{Chip8::decode_instruction(
          device.mem_buf_.fetch_instruction(device.program_counter_.get_current_increment()))};

      device.program_counter_.increment_program();

      Chip8::execute(fetched_instruction, device, renderer);

      renderer.present();
      // Application Loop end:

      static constexpr auto sixty_fps{16};
      SDL_Delay(sixty_fps);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception Caught! Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Unknown Exception Caught!" << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
