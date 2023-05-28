#include "shaders/shader.hpp"
#include "window/window.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <string>
#include <vector>
#include "shape/box.hpp"
#include "shape/billboard.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <filesystem>
#include "clock/clock.hpp"
#include "player/player.hpp"
#include "resources/resources.hpp"
#include "collision/collision.hpp"
#include "controls/configurations.hpp"

int main(int argc, char *argv[])
{
  Window window;
  if (!window.active()) {
    return 1;
  }

  Resources::VAOS["box"] = boxes_VAO();
  Resources::VAOS["billboard"] = billboards_VAOS();
  Resources::SHADERS["box"] =  Shader::compile("shaders/box.vs", "shaders/box.fs");
  Resources::SHADERS["billboard"] =  Shader::compile("shaders/billboard.vs", "shaders/box.fs");

  Camera camera;
  Controls::Input input;
  Controls::Configurations controls_configs;
  Player player(glm::vec3(3.0f, 0.0f, 3.0f));
  Clock clock;
  
  Box box;
  box.texture_id = Resources::texture("assets/textures/container.jpg", false);
  Box box2;
  box2.texture_id = Resources::texture("assets/textures/container.jpg", false);
  SDL_Event event;

  SDL_GL_SetSwapInterval(1);
  glEnable(GL_DEPTH_TEST);
  while (1) {
    float delta = clock.delta();
    input.update();
    glm::vec3 prev_player_position = player.position;
    player.tick(controls_configs, input, camera.angular_position, delta);
    if (Collision::AABBtoAABB(player.collider, box.collider)) {
      player.position = prev_player_position;
      player.update_collider();
    }
    if (input.mouse_right) {
        camera.rotate(input.mouse_movement_dir, delta);
    }
    camera.update(player.position);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    box.draw(glm::vec3(0.0f, 0.0f, 0.0f), camera);
    box2.draw(glm::vec3(2.0f, 3.0f, 1.0f), camera);
    player.draw(camera);
    SDL_GL_SwapWindow(window.sdl_window.get());
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      break;
    }
  }
  SDL_Quit();
  return 0;
}