#include "vertices.hpp"
#include "billboard.hpp"
#include "../shaders/shader.hpp"
#include "../resources/resources.hpp"

#include <SDL.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
static const glm::vec2 board_size = glm::vec2(1.f, 1.f);

std::vector<unsigned int> billboards_VAOS()
{
  std::vector<unsigned int> VAO{0, 0, 0, 0, 0, 0};
  glGenVertexArrays(6, VAO.data());
  for (int i = 0; i < 6; i++) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO[i]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices::BILLBOARD[i]), Vertices::BILLBOARD[i].data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
  return VAO;
}

void Billboard::draw(const glm::vec3 &position_world, const Camera &camera, int frame)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindVertexArray(Resources::VAOS["billboard"][frame]);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glUseProgram(shader_id);

  glUniformMatrix4fv(glGetUniformLocation(shader_id, "projection"), 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(shader_id, "view"), 1, GL_FALSE, camera.view_matrix());
  glUniform2fv(glGetUniformLocation(shader_id, "board_size"), 1, &board_size[0]);
  glUniform3fv(glGetUniformLocation(shader_id, "board_center_worldspace"), 1, &position_world[0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisable(GL_BLEND);
}
