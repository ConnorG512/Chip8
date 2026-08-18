#include "application.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <cstdlib>
#include <exception>
#include <iostream>

auto main() -> int
{
  SDL_Init(SDL_INIT_VIDEO);

  try
  {
    Chip8::Application app{};

    const auto app_res {app.run()};
    if(app_res.value() == Chip8::Application::ExitCode::Quit)
    {
      return EXIT_SUCCESS;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception Caught! Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Unknown Exception!\n";
    return EXIT_FAILURE;
  }
}
