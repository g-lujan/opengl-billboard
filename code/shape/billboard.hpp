#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../camera/camera.hpp"

std::vector<unsigned int> billboards_VAOS();

class Billboard {
public:
  Billboard(const unsigned int shader_id) : shader_id{shader_id} {}

  void draw(const glm::vec3 &position_world, const Camera &camera, int frame);

public:
  unsigned int shader_id;
  unsigned int texture_id;
};
