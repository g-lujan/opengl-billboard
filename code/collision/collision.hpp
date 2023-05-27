#pragma once

#include "glm/glm.hpp"

namespace Collision {

  struct AABB {
    glm::vec3 max;
    glm::vec3 min;
  };

  bool AABBtoAABB(const AABB &first, const AABB &second);
} // namespace Collision
