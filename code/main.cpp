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
#include "main.h"

int main(int argc, char *argv[])
{
  Window window;
  if (!window.active()) {
    return 1;
  }

  init_resources();

  Camera camera;
  SDL_Event event;
  Controls::Input input;
  Controls::Configurations controls_configs;
  
  Player player(glm::vec3(3.0f, 0.0f, 3.0f));

  Render::Box render_box;
  render_box.texture_id = Resources::texture("assets/textures/container.jpg", false);
  Collision::AABB collider_box{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)};

  Render::Box render_box2;
  render_box2.texture_id = Resources::texture("assets/textures/container.jpg", false);
  Collision::AABB collider_box2{glm::vec3(2.0f, 3.0f, 1.0f), glm::vec3(3.0f, 4.0f, 2.0f)};

  SDL_GL_SetSwapInterval(1);
  glEnable(GL_DEPTH_TEST);
  while (true) {
    CLOCK.update_delta();
    input.update();

    // player update (attempt before solving collisions)
    glm::vec3 prev_player_position = player.position;
    player.tick(controls_configs, input, camera.angular_position());
    
    // collisions
    if (Collision::AABBtoAABB(player.collider, collider_box)) {
      player.position = prev_player_position;
      player.update_collider();
    }

    // update camera
    if (input.mouse_right) {
        camera.rotate(input.mouse_movement_dir);
    }
    camera.update(player.position);
    
    // draw
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_box.draw(camera, collider_box.min);
    render_box2.draw(camera, collider_box2.min);
    player.draw(camera);
    SDL_GL_SwapWindow(window.sdl_window.get());

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      break;
    }
  }
  SDL_Quit();
  return 0;
}

void init_resources()
{
  Resources::VAOS["box"] = Render::boxes_VAO();
  Resources::VAOS["billboard"] = Render::billboards_VAOS();
  Resources::SHADERS["box"] = Shader::compile("shaders/box.vs", "shaders/box.fs");
  Resources::SHADERS["billboard"] = Shader::compile("shaders/billboard.vs", "shaders/box.fs");
}
