#pragma once

#include <SDL2/SDL.h>

struct Clock {
  float delta() {
    last = now;
    now = SDL_GetPerformanceCounter();
    return (now - last) / (float)SDL_GetPerformanceFrequency();
  }


private:
  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
};
