#pragma once

#include <glm/glm.hpp>

#include "player.hpp"
#include "../clock/clock.hpp"

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

Player::Player(glm::vec3 position) : position(position), billboard(Resources::SHADERS["billboard"]), animations(initialize_animations())
{
  billboard.texture_id = Resources::texture("assets/textures/player.jpg");
  animations.change_to("idle");
}

void Player::draw(Camera &camera)
{
  Animation::Frame& current_frame = animations.get_current_frame();
  billboard.draw(position, camera, current_frame.sheet_idx);
  animations.step();
}

void Player::tick(Controls::Configurations &config, Controls::Input &input, float angle)
{
  const float displacement = speed * CLOCK.delta();

  if (input.empty) {
    animations.change_to("idle");
  }

  for (int i = 0; i < input.keys_down.size(); i++) {
    if (input.keys_down[i]) {
      std::string action = config.player_movement[(SDL_Scancode)i](this, angle, displacement);
      animations.change_to(action);
    }
  }
  update_collider();
}

void Player::update_collider()
{
  // posicoes meio chutadas, para testar
  collider.min = position;
  collider.max = {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f};
}
