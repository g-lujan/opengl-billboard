#pragma once

#include "camera.hpp"
#include "../clock/clock.hpp"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

// Default camera values
namespace Default {
  static constexpr float YAW = -90.0f;
  static constexpr float PITCH = 0.0f;
  static constexpr float SPEED = 2.5f;
  static constexpr float SENSITIVITY = 0.1f;
  static constexpr float ZOOM = 45.0f;
  static constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera() : Camera(glm::vec3(0.0f, 5.0f, 0.0f), Default::YAW, Default::PITCH) {}

// constructor with vectors
Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)), 
    speed_(Default::SPEED), 
    sensitivity_(Default::SENSITIVITY), 
    zoom_(Default::ZOOM),
    position_(position),
    yaw_(yaw),
    pitch_(pitch)
{
  update_camera_vectors();
}


// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)), 
    speed_(Default::SPEED), 
    sensitivity_(Default::SENSITIVITY), 
    zoom_(Default::ZOOM),
    position_(glm::vec3(posX, posY, posZ)),
    yaw_(yaw),
    pitch_(pitch)
{
  update_camera_vectors();
}

void Camera::rotate(int mouse_move_dir)
{
  float rotation_speed = 2.f;
  angular_position_ += mouse_move_dir * rotation_speed * CLOCK.delta();
}

void Camera::update(const glm::vec3 &center)
{
  position_.x = center.x + 5 * glm::cos(angular_position_);
  position_.z = center.z + 5 * glm::sin(angular_position_);
  view_matrix_ = glm::lookAt(position_, center, Default::WORLD_UP);
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::update_camera_vectors()
{
  // calculate the new Front vector
  glm::vec3 front{cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)), 
                  sin(glm::radians(pitch_)), 
                  sin(glm::radians(yaw_)) * cos(glm::radians(pitch_))
  };
  front_ = glm::normalize(front);

  // also re-calculate the Right and Up vector
  // normalize the vectors, because their length gets closer to 0 the more you
  // look up or down which results in slower movement.
  right_ = glm::normalize(glm::cross(front_, Default::WORLD_UP));
  up_ = glm::normalize(glm::cross(right_, front_));
}
