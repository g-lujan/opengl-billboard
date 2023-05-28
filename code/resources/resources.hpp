#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <gl/glew.h>

namespace Resources {
  extern std::unordered_map<std::string, std::vector<unsigned int>> VAOS;
  extern std::unordered_map<std::string, unsigned int> SHADERS;

  GLuint texture(const std::string &texture_path, const bool alpha = true);
};
