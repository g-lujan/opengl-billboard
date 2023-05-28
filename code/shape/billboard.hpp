#pragma once
#include "../controls/controls.hpp"
#include <array>
#include <glm/glm.hpp>
#include <string>
#include "../camera/camera.hpp"

std::vector<unsigned int> billboards_VAOS();

class Billboard {
public:
  Billboard(std::vector<unsigned int> &VAOS, const unsigned int shader_id) : VAOS{VAOS}, shader_id{shader_id} {}

  void draw(const glm::vec3 &position_world, const Camera &camera, int frame);

public:
  std::vector<unsigned int> VAOS;
  unsigned int shader_id;
  unsigned int texture_id;
};
