#pragma once

#include "controls.hpp"

namespace Controls {

    void Input::update()
    {
      // Update keyboard
      empty = true;
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      for (int scancode = 0; scancode < SDL_NUM_SCANCODES; ++scancode) {
        keys_down[scancode] = state[scancode];
        if (state[scancode]) {
          empty = false;
        }
      }

      // Update mouse
      int prev_mouse_x_pos = mouse_x;
      Uint32 mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y); // can't pass floats here
      mouse_movement_dir = prev_mouse_x_pos < mouse_x ? 1 : prev_mouse_x_pos > mouse_x ? -1 : 0;
      mouse_left = (mouse_buttons & SDL_BUTTON_LMASK) != 0;
      mouse_middle = (mouse_buttons & SDL_BUTTON_MMASK) != 0;
      mouse_right = (mouse_buttons & SDL_BUTTON_RMASK) != 0;
    }
}