#pragma once
#include "../controls/controls.hpp"
#include <array>
#include <glm/glm.hpp>
#include <string>
#include "../camera/camera.hpp"

int billboards_VAO();

class Billboard {
public:
  Billboard(const unsigned int VAO, const unsigned int shader_id) : VAO{VAO}, shader_id{shader_id} {}

  void draw(const glm::vec3 &position_world, const Camera &camera);

public:
  unsigned int VAO;
  unsigned int shader_id;
  unsigned int texture_id;
};
