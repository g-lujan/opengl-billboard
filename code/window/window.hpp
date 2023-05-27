#pragma once
#include "SDL.h"
#include <memory>

struct Window {
  Window();
  bool active() { return sdl_window && gl_context; }

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
  std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)> gl_context;
};
