#include "billboard.hpp"
#include "../shaders/shader.hpp"
#include "vertices.hpp"
#include <SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int billboards_VAO()
{
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices::BILLBOARD), Vertices::BILLBOARD.data(), GL_STATIC_DRAW);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  return VAO;
}

void Billboard::draw(const glm::vec3 &position_world, const Camera &camera)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUseProgram(shader_id);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
  glUniformMatrix4fv(glGetUniformLocation(shader_id, "projection"), 1, GL_FALSE, &projection[0][0]);

  glUniformMatrix4fv(glGetUniformLocation(shader_id, "view"), 1, GL_FALSE, &camera.view_matrix[0][0]);

  glm::vec2 board_size = glm::vec2(1.f, 1.f);
  glUniform2fv(glGetUniformLocation(shader_id, "board_size"), 1, &board_size[0]);
  glUniform3fv(glGetUniformLocation(shader_id, "board_center_worldspace"), 1, &position_world[0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisable(GL_BLEND);
}
