-- Chip8 config: 

config = {
  -- Base resolution of a Chip8 interpreter is 64 x 32. 
  -- Adjust to comfortable window scale.
  window_scale = 18;

  -- Application refresh rate, measured in ms.
  -- Example: 16 for ~60fps.
  refresh_rate = 16;

  app_name = "test-1-basic-loop";
  
  -- Uses SDL3's Scancodes:
  -- https://wiki.libsdl.org/SDL3/SDL_Scancode
  keybinds = {
    key_esc = 41;       -- ESC
    key_0 = 30;         -- 1
    key_1 = 31;         -- 2
    key_2 = 32;         -- 3
    key_3 = 33;         -- 4
    key_4 = 20;         -- Q
    key_5 = 26;         -- W
    key_6 = 8;          -- E
    key_7 = 21;         -- R
    key_8 = 4;          -- A 
    key_9 = 22;         -- S
    key_a = 7;          -- D
    key_b = 9;          -- F
    key_c = 29;         -- Z
    key_d = 27;         -- X
    key_e = 6;          -- C 
    key_f = 25;         -- V
  };
}

