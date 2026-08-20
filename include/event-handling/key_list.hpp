#pragma once 

#include "scancode.hpp"

#include <SDL3/SDL_scancode.h>

namespace Chip8 {
  struct KeyList {
    Scancode key_esc{Scancode(SDL_SCANCODE_ESCAPE)};
    Scancode key_0{Scancode(SDL_SCANCODE_1)};
    Scancode key_1{Scancode(SDL_SCANCODE_2)};
    Scancode key_2{Scancode(SDL_SCANCODE_3)};
    Scancode key_3{Scancode(SDL_SCANCODE_4)};
    Scancode key_4{Scancode(SDL_SCANCODE_Q)};
    Scancode key_5{Scancode(SDL_SCANCODE_W)};
    Scancode key_6{Scancode(SDL_SCANCODE_E)};
    Scancode key_7{Scancode(SDL_SCANCODE_R)};
    Scancode key_8{Scancode(SDL_SCANCODE_A)};
    Scancode key_9{Scancode(SDL_SCANCODE_S)};
    Scancode key_a{Scancode(SDL_SCANCODE_D)};
    Scancode key_b{Scancode(SDL_SCANCODE_F)};
    Scancode key_c{Scancode(SDL_SCANCODE_Z)};
    Scancode key_d{Scancode(SDL_SCANCODE_X)};
    Scancode key_e{Scancode(SDL_SCANCODE_C)};
    Scancode key_f{Scancode(SDL_SCANCODE_V)};
  };
}
