#include "window.hpp"
#include <GL/glew.h>

/*****************************************************************************/
/* STATIC CONSTANTS                                                          */
/*****************************************************************************/
static constexpr auto TITLE = "GAME";
static constexpr int X = SDL_WINDOWPOS_CENTERED, Y = SDL_WINDOWPOS_CENTERED, W = 800, H = 600;
static constexpr Uint32 FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

/*****************************************************************************/
/* STATIC FUNCTIONS                                                          */
/*****************************************************************************/

static void display_libs_info()
{
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  SDL_Log("We compiled against SDL version %u.%u.%u ...\n", compiled.major, compiled.minor, compiled.patch);
  SDL_Log("But we are linking against SDL version %u.%u.%u.\n", linked.major, linked.minor, linked.patch);
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
  fprintf(stdout, "OpenGL version (%s): \n", glGetString(GL_VERSION));
}

/*****************************************************************************/
/* PUBLIC FUNCTIONS                                                          */
/*****************************************************************************/

Window::Window() : sdl_window(nullptr, SDL_DestroyWindow), gl_context(nullptr, SDL_GL_DeleteContext)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Can't initialize SDL: %s\n", SDL_GetError());
    return;
  }

  sdl_window.reset(SDL_CreateWindow(TITLE, X, Y, W, H, FLAGS));
  gl_context.reset(SDL_GL_CreateContext(sdl_window.get()));
  if (gl_context == NULL) {
    SDL_Log("Can't create OpenGL context: %s\n", SDL_GetError());
    return;
  }

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
    return;
  }

  display_libs_info();

  /* Config viewport and clear color for a fresh start */
  glViewport(0, 0, W, H);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
