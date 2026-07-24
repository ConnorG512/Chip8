#include "app-renderer.hpp"
#include "app-window.hpp"
#include "chip8-spec.hpp"
#include "decode-instruction.hpp"
#include "device.hpp"
#include "execute-instructions.hpp"
#include "lua-instance.hpp"
#include "memory-buffer.hpp"
#include "texture.hpp"

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
    Chip8::LuaInstance lua_instance{};

    const std::int32_t window_scale{
        static_cast<std::int32_t>(std::get<double>(lua_instance.read_config("window_scale")))};

    Chip8::AppWindow window{
        "Chip8",
        {.width = Chip8::Spec::screen_width * window_scale, .height = Chip8::Spec::screen_height * window_scale}};

    Chip8::AppRenderer renderer{window.window_ref(), window.get_window_dimensions().value()};
    Chip8::MemBuf mem_buf{};

    Chip8::Device device{Chip8::Spec::application_reserve.start};

    const auto result = mem_buf.load_app_into_buffer(std::get<std::string>(lua_instance.read_config("app_name")))
                            .or_else(
                                [&](const Chip8::MemBuf::LoadAppErr &err) -> auto
                                {
                                  std::cerr << "Failed to load app from Lua string. Error: "
                                            << static_cast<std::uint32_t>(std::to_underlying(err)) << '\n';
                                  return mem_buf.load_app_into_buffer("test-1");
                                });
    if (!result.has_value())
    {
      std::cerr << "Failed to load default app, Aborting.\n";
      return EXIT_FAILURE;
    }

    Chip8::Texture screen_texture{renderer.get_sdl_renderer(),
                                  SDL_TEXTUREACCESS_STREAMING,
                                  {Chip8::Spec::screen_width, Chip8::Spec::screen_height}};

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
      
      auto fetched_instruction{
          Chip8::decode_instruction(mem_buf.fetch_instruction(device.program_counter_.get_current_increment()))};

      Chip8::execute(fetched_instruction, device, renderer);
      
      device.program_counter_.increment_program();

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
