#include "application.hpp"

#include <SDL3/SDL_init.h>
#include <exception>
#include <iostream>

auto main() -> int
{
  SDL_Init(SDL_INIT_VIDEO);

  try
  {
    Chip8::Application app{};

    const auto app_res {app.run()};

    using ExitCode = Chip8::Application::ExitCode;
    if(app_res.value() == ExitCode::Quit)
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
