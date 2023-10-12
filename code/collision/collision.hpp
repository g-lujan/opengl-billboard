#pragma once

#include "glm/glm.hpp"

namespace Collision {

  struct AABB {
    glm::vec3 min;
    glm::vec3 max;
  };

  bool AABBtoAABB(const AABB &first, const AABB &second);
}