#pragma once

#include <glm/glm.hpp>

class Camera {
public:
  Camera();
  Camera(glm::vec3 position, float yaw, float pitch);
  Camera(float posX, float posY, float posZ, float yaw, float pitch);

  void rotate(int mouse_move_dir, float delta);
  void update(const glm::vec3 &center);

  float angular_position() const { return angular_position_; }
  const float *const view_matrix() const { return &view_matrix_[0][0]; }

private:
  // camera Attributes
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;

  // euler Angles
  float yaw_;
  float pitch_;

  // camera options
  float speed_;
  float sensitivity_;
  float zoom_;

  float angular_position_ = 0.0f;
  glm::mat4x4 view_matrix_;

private:
  void update_camera_vectors();
};