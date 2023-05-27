#pragma once

#include <GL/glew.h>
#include <string>

namespace Shader {
  unsigned int compile(const std::string &vertexPath, const std::string &fragmentPath);
}
