#pragma once
#include <array>
#include <string>
#include <glm/glm.hpp>
#include "../controls/controls.hpp"
#include "../camera/camera.hpp"
#include "../collision/collision.hpp"

int boxes_VAO();

class Box {
public:
  Box(const unsigned int VAO, const unsigned int shader_id)
      : VAO{VAO}, shader_id{shader_id}
  {
  }

  void draw(const glm::vec3 &position_world, const Camera &camera);

 public:
  float rotation_speed = .0f;

public:
  unsigned int VAO; // um mesmo VAO pode ser compartilhado por vários Cubos análogos
  unsigned int shader_id;
  unsigned int texture_id;
  Collision::AABB collider;
};
