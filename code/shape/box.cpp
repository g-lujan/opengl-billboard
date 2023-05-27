#include "box.hpp"
#include "../shaders/shader.hpp"
#include "vertices.hpp"
#include <SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int boxes_VAO()
{
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
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

void Box::draw(const glm::vec3 &position_world, const Camera &camera)
{
  // --- START TEST ---
  // posicoes meio chutadas, só para testar
  // e isso nem deveria ficar no draw
  // --- END TEST ---
  collider.min = position_world;
  collider.max = {position_world.x + 1.0f, position_world.y + 1.0f, position_world.z + 1.0f};
  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUseProgram(shader_id);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
  glUniformMatrix4fv(glGetUniformLocation(shader_id, "projection"), 1, GL_FALSE, &projection[0][0]);

  glUniformMatrix4fv(glGetUniformLocation(shader_id, "view"), 1, GL_FALSE, &camera.view_matrix[0][0]);

  glm::mat4 model = glm::translate(glm::mat4(1.0f), position_world);
  glUniformMatrix4fv(glGetUniformLocation(shader_id, "model"), 1, GL_FALSE, &model[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 36);
}
