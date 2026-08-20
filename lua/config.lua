-- Chip8 config: 

-- Uses SDL3's Scancodes:
-- https://wiki.libsdl.org/SDL3/SDL_Scancode
local Scancode = {
  KEY_A = 4,
  KEY_B = 5,
  KEY_C = 6,
  KEY_D = 7,
  KEY_E = 8,
  KEY_F = 9,
  KEY_G = 10,
  KEY_H = 11,
  KEY_I = 12,
  KEY_J = 13,
  KEY_K = 14,
  KEY_L = 15,
  KEY_M = 16,
  KEY_N = 17,
  KEY_O = 18,
  KEY_P = 19,
  KEY_Q = 20,
  KEY_R = 21,
  KEY_S = 22,
  KEY_T = 23,
  KEY_U = 24,
  KEY_V = 25,
  KEY_W = 26,
  KEY_X = 27,
  KEY_Y = 28,
  KEY_Z = 29,

  KEY_1 = 30,
  KEY_2 = 31,
  KEY_3 = 32,
  KEY_4 = 33,
  KEY_5 = 34,
  KEY_6 = 35,
  KEY_7 = 36,
  KEY_8 = 37,
  KEY_9 = 38,
  KEY_0 = 39,

  KEY_RETURN = 40,
  KEY_ESCAPE = 41,
  KEY_BACKSPACE = 42,
  KEY_TAB = 43,
  KEY_SPACE = 44,
};

config = {
  -- Base resolution of a Chip8 interpreter is 64 x 32. 
  -- Adjust to comfortable window scale.
  window_scale = 18;

  -- Application refresh rate, measured in ms.
  -- Example: 16 for ~60fps.
  refresh_rate = 16;

  app_name = "test-1-basic-loop";
  
  keybinds = {
    key_esc = Scancode.KEY_ESCAPE;
    key_0 = Scancode.KEY_1;
    key_1 = Scancode.KEY_2;
    key_2 = Scancode.KEY_3;
    key_3 = Scancode.KEY_4;
    key_4 = Scancode.KEY_Q;
    key_5 = Scancode.KEY_W;
    key_6 = Scancode.KEY_E;
    key_7 = Scancode.KEY_R;
    key_8 = Scancode.KEY_A;
    key_9 = Scancode.KEY_S;
    key_a = Scancode.KEY_D;
    key_b = Scancode.KEY_F;
    key_c = Scancode.KEY_Z;
    key_d = Scancode.KEY_X;
    key_e = Scancode.KEY_C;
    key_f = Scancode.KEY_V;
  };
}

