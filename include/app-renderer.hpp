#pragma once 

#include <memory>
#include <SDL3/SDL_render.h>

namespace Chip8 {
  class AppRenderer {
    public: 
      AppRenderer(SDL_Window& current_window);
      
      void clear_renderer() noexcept;
      void present() noexcept;

    private:
      std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{SDL_CreateRenderer(nullptr, nullptr),
                                                                          &SDL_DestroyRenderer};
  };
}
