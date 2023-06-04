#pragma once

#include <glm/glm.hpp>

#include "../animation/animation.hpp"
#include "../camera/camera.hpp"
#include "../collision/collision.hpp"
#include "../controls/configurations.hpp"
#include "../controls/controls.hpp"
#include "../resources/resources.hpp"
#include "../shape/billboard.hpp"
#include "../shape/box.hpp"

static Animation::Animations initialize_animations()
{
  Animation::Animations player_animations;
  
  player_animations.add_frames("idle", {
    Animation::Frame{.duration = 1000, .time_running = 0, .sheet_idx = 0},
    Animation::Frame{.duration = 1000, .time_running = 0, .sheet_idx = 4},
    Animation::Frame{.duration = 1000, .time_running = 0, .sheet_idx = 2}
  });

  player_animations.add_frames("move", {
    Animation::Frame{.duration = 100, .time_running = 0, .sheet_idx = 0},
    Animation::Frame{.duration = 100, .time_running = 0, .sheet_idx = 3},
    Animation::Frame{.duration = 100, .time_running = 0, .sheet_idx = 1}
  });

  return player_animations;
}

struct Player {

  Player(glm::vec3 position) : position(position), billboard(Resources::SHADERS["billboard"]), animations(initialize_animations())
  {
    billboard.texture_id = Resources::texture("assets/textures/player.jpg");
    animations.change_to("idle");
  }

  glm::vec3 position;
  float speed = 2.0f;
  Billboard billboard;
  Collision::AABB collider;

  std::string current_animation;
  Animation::Animations animations;

  int curr_frame = 0;

  void draw(Camera &camera)
  {
    Animation::Frame& current_frame = animations.get_current_frame();
    billboard.draw(position, camera, current_frame.sheet_idx);
    animations.step();
  }

  void tick(Controls::Configurations &config, Controls::Input &input, float angle, float delta)
  {
    const float displacement = speed * delta;

    if (input.empty) {
      animations.change_to("idle");
    }

    for (int i = 0; i < input.keys_down.size(); i++) {
      if (input.keys_down[i] && config.player_movement.contains((SDL_Scancode)i)) {
        std::string action = config.player_movement[(SDL_Scancode)i](this, angle, displacement);
        animations.change_to(action);
      }
    }
    update_collider();
  }

  void update_collider()
  {
    // posicoes meio chutadas, para testar
    collider.min = position;
    collider.max = {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f};
  }
};
