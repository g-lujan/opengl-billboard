#include "resources.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stbi.hpp"
#include <SDL.h>

namespace Resources {
  std::unordered_map<std::string, std::vector<unsigned int>> VAOS;
  std::unordered_map<std::string, unsigned int> SHADERS;
}

GLuint Resources::texture(const std::string &texture_path, const bool alpha)
{
  GLuint texture_id;
  // texture
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
  if (data) {
    const GLint format = alpha ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    SDL_Log("Erro box");
  }
  stbi_image_free(data);
  return texture_id;
}