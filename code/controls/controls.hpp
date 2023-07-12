#pragma once

#include <array>
#include <SDL2/SDL.h>

namespace Controls {

  struct Input {
    void update();

    std::array<int, SDL_Scancode::SDL_NUM_SCANCODES> keys_down{};
    bool mouse_left, mouse_middle, mouse_right;
    int mouse_x, mouse_y;
    int mouse_movement_dir; // R = 1, L = -1
    bool empty = true;
  };
}