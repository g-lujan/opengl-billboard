#pragma once

#include <array>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../controls/controls.hpp"
#include "../camera/camera.hpp"
#include "../collision/collision.hpp"

std::vector<unsigned int> boxes_VAO();

class Box {
public:
  Box() {}

  void draw(const glm::vec3 &position_world, const Camera &camera);

 public:
  float rotation_speed = .0f;

public:
  unsigned int texture_id;
  Collision::AABB collider;
};
