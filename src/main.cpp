#include "application.hpp"
#include "renderer/initialise.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>

auto main() -> int
{
  SDL_Init(SDL_INIT_VIDEO);

  static constexpr auto render_init_attr = std::to_array<Chip8::GLProperties<SDL_GLAttr>>({
      {.attribute = SDL_GL_CONTEXT_MAJOR_VERSION, .val = 3}, {.attribute = SDL_GL_CONTEXT_MINOR_VERSION, .val = 3},
      {.attribute = SDL_GL_CONTEXT_PROFILE_MASK, .val = SDL_GL_CONTEXT_PROFILE_CORE}});
  
  const auto render_init_res = Chip8::initialize_renderer(render_init_attr);
  if(!render_init_res.has_value())
  {
    std::cerr << render_init_res.error() << '\n';
    return EXIT_FAILURE;
  }

  try
  {
    Chip8::Application app{};

    const auto app_res{app.run()};

    using ExitCode = Chip8::Application::ExitCode;
    if (app_res.value() == ExitCode::Quit)
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
