#pragma once

#include <array>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../controls/controls.hpp"
#include "../camera/camera.hpp"
#include "../collision/collision.hpp"

namespace Render {
  std::vector<unsigned int> boxes_VAO();

  class Box {
  public:
    Box() : texture_id{0} {}

    void draw(const Camera &camera, const glm::vec3 &world_position);

  public:
    unsigned int texture_id;
  };
}
