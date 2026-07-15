#include "app-renderer.hpp"
#include "app-window.hpp"
#include "chip8-spec.hpp"
#include "lua-instance.hpp"
#include "memory-buffer.hpp"
// #include "register.hpp"
// #include "screen-buffer.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

auto main() -> int
{
  SDL_Init(SDL_INIT_VIDEO);

  // Chip8::Register<std::uint8_t> Reg0{};
  // Chip8::Register<std::uint8_t> Reg1{};
  // Chip8::Register<std::uint8_t> Reg2{};
  // Chip8::Register<std::uint8_t> Reg3{};
  // Chip8::Register<std::uint8_t> Reg4{};
  // Chip8::Register<std::uint8_t> Reg5{};
  // Chip8::Register<std::uint8_t> Reg6{};
  // Chip8::Register<std::uint8_t> Reg7{};
  // Chip8::Register<std::uint8_t> Reg8{};
  // Chip8::Register<std::uint8_t> Reg9{};
  // Chip8::Register<std::uint8_t> RegA{};
  // Chip8::Register<std::uint8_t> RegB{};
  // Chip8::Register<std::uint8_t> RegC{};
  // Chip8::Register<std::uint8_t> RegD{};
  // Chip8::Register<std::uint8_t> RegE{};
  // Chip8::Register<std::uint8_t> RegF{};
  // Chip8::Register<std::uint16_t> RegI{};
  // Chip8::Register<std::uint16_t> RegPC{};

  try
  {
    Chip8::LuaInstance lua_instance{};

    const std::int32_t window_scale{
        static_cast<std::int32_t>(std::get<double>(lua_instance.read_config("window_scale")))};

    Chip8::AppWindow window{
        "Chip8",
        {.width = Chip8::Spec::screen_width * window_scale, .height = Chip8::Spec::screen_height * window_scale}};

    Chip8::AppRenderer renderer{window.window_ref()};
    Chip8::MemBuf mem_buf{};
    // Chip8::ScrBuf scr_buf{};

    const auto result =
        mem_buf.load_app_into_buffer(std::get<std::string>(lua_instance.read_config("app_name")))
            .or_else(
                [&](const Chip8::MemBuf::LoadAppErr &err) -> auto
                {
                  std::cerr << "Failed to load app from Lua string, Aborting. Error: " << static_cast<std::uint32_t>(std::to_underlying(err)) << '\n';
                  return mem_buf.load_app_into_buffer("test-1");
                });
    if (!result.has_value())
    {
      std::cerr << "Failed to load default app, Aborting.\n";
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
      renderer.present();

      // Application Loop end:
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
