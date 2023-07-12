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

struct Player {

  Player(glm::vec3 position);
  void draw(Camera &camera);
  void tick(Controls::Configurations &config, Controls::Input &input, float angle);
  void update_collider();


  glm::vec3 position;
  float speed = 2.0f;
  Billboard billboard;
  Collision::AABB collider;

  std::string current_animation;
  Animation::Animations animations;
  int curr_frame = 0;
};
