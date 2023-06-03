#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <glm/glm.hpp>

namespace Controls {

  struct Input {
    std::array<int, SDL_Scancode::SDL_NUM_SCANCODES> keys_down{};
    bool mouse_left, mouse_middle, mouse_right;
    int mouse_x, mouse_y;
    int mouse_movement_dir; // R = 1, L = -1

    void update()
    {
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      for (int scancode = 0; scancode < SDL_NUM_SCANCODES; ++scancode) {
        keys_down[scancode] = state[scancode];
      }
      int prev_mouse_x_pos = mouse_x;
      Uint32 mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y); // can't pass floats here
      mouse_movement_dir = prev_mouse_x_pos < mouse_x ? 1 : prev_mouse_x_pos > mouse_x ? -1 : 0;
      mouse_left = (mouse_buttons & SDL_BUTTON_LMASK) != 0;
      mouse_middle = (mouse_buttons & SDL_BUTTON_MMASK) != 0;
      mouse_right = (mouse_buttons & SDL_BUTTON_RMASK) != 0;
    }
  };
}