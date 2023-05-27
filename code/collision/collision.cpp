#include "collision.hpp"

bool Collision::AABBtoAABB(const AABB &first, const AABB &second)
{
  // this is based on a left-handed system
  // clang-format off
    return first.max.x > second.min.x && 
           first.min.x < second.max.x && 
           first.max.y > second.min.y && 
           first.min.y < second.max.y &&
           first.max.z > second.min.z && 
           first.min.z < second.max.z;
  // clang-format on
}