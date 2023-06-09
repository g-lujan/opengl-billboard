#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shape/box.hpp"
#include "clock/clock.hpp"
#include "window/window.hpp"
#include "player/player.hpp"
#include "shaders/shader.hpp"
#include "shape/billboard.hpp"
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
  SDL_Event event;
  Controls::Input input;
  Controls::Configurations controls_configs;
  
  Player player(glm::vec3(3.0f, 0.0f, 3.0f));
  Box box;
  box.texture_id = Resources::texture("assets/textures/container.jpg", false);
  Box box2;
  box2.texture_id = Resources::texture("assets/textures/container.jpg", false);

  SDL_GL_SetSwapInterval(1);
  glEnable(GL_DEPTH_TEST);
  while (1) {
    CLOCK.update_delta();
    input.update();

    // player update (attemp before solving collisions)
    glm::vec3 prev_player_position = player.position;
    player.tick(controls_configs, input, camera.angular_position());
    
    // collisions
    if (Collision::AABBtoAABB(player.collider, box.collider)) {
      player.position = prev_player_position;
      player.update_collider();
    }

    // update camera
    if (input.mouse_right) {
        camera.rotate(input.mouse_movement_dir);
    }
    camera.update(player.position);
    
    // draw -- should the object draw itself?
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