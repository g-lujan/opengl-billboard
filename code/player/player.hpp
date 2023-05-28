#pragma once

#include <glm/glm.hpp>

#include "../camera/camera.hpp"
#include "../controls/controls.hpp"
#include "../controls/configurations.hpp"
#include "../resources/resources.hpp"
#include "../shape/billboard.hpp"
#include "../shape/box.hpp"
#include "../collision/collision.hpp"

struct Player {
  Player(glm::vec3 position) : position(position), billboard(Resources::VAOS["billboard"], Resources::SHADERS["billboard"])
  {
    billboard.texture_id = Resources::texture("assets/textures/player.jpg");
  }

  glm::vec3 position;
  float speed = 2.0f;
  Billboard billboard;
  Collision::AABB collider;
  int curr_frame = 0;

  void draw(Camera &camera)
  {
    billboard.draw(position, camera, curr_frame);
    
    // um POC para mostrar como animar com OpenGL
    // ainda preciso pensar como controlar corretamente
    // os frames com acoes
    curr_frame = (curr_frame + 1)%6;
  }

  void tick(Controls::Configurations &config, Controls::Input &input, float angle, float delta)
  {
    const float displacement = speed * delta;
    for (int i = 0; i < input.keys_down.size(); i++) {
      if (input.keys_down[i] && config.player_movement.contains((SDL_Scancode)i)) {
        config.player_movement[(SDL_Scancode)i](this, angle, displacement);
      }
    }
    update_collider();
  }

  void update_collider() {
    // posicoes meio chutadas, s� para testar
    collider.min = position;
    collider.max = {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f};
  }
};
