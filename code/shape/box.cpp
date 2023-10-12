#include "box.hpp"
#include "../shaders/shader.hpp"
#include "vertices.hpp"
#include "../resources/resources.hpp"

#include <SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

std::vector<unsigned int> Render::boxes_VAO()
{
  unsigned int VBO;
  std::vector<unsigned int> VAO{0};
  glGenVertexArrays(1, VAO.data());
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices::CUBE), Vertices::CUBE.data(), GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return VAO;
}

void Render::Box::draw(const Camera &camera, const glm::vec3 &world_position)
{
  glBindVertexArray(Resources::VAOS["box"][0]);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUseProgram(Resources::SHADERS["box"]);

  glUniformMatrix4fv(glGetUniformLocation(Resources::SHADERS["box"], "projection"), 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(Resources::SHADERS["box"], "view"), 1, GL_FALSE, camera.view_matrix());
  glm::mat4 model = glm::translate(glm::mat4(1.0f), world_position);
  glUniformMatrix4fv(glGetUniformLocation(Resources::SHADERS["box"], "model"), 1, GL_FALSE, &model[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 36);
}
