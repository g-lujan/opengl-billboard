#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
  // camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;

  // euler Angles
  float Yaw;
  float Pitch;
  // camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  float angular_position = 0.0f;
  glm::mat4x4 view_matrix;

  // constructor with vectors
  Camera(glm::vec3 position = glm::vec3(0.0f, 3.0f, 5.0f), float yaw = YAW, float pitch = PITCH)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
  {
    Position = position;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }
  // constructor with scalar values
  Camera(float posX, float posY, float posZ, float yaw, float pitch)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
  {
    Position = glm::vec3(posX, posY, posZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }

  void rotate(int mouse_move_dir, float delta)
  { 
      float rotation_speed = 2.f;
      angular_position += mouse_move_dir * rotation_speed * delta;
  }

  void update(glm::vec3 &center) {
      Position.x = center.x + 5 * glm::cos(angular_position);
      Position.z = center.z + 5 * glm::sin(angular_position);
      view_matrix = glm::lookAt(Position, center, WorldUp);
  }

private:
  // calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors()
  {
    // calculate the new Front vector
    glm::vec3 front{
        cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)), 
        sin(glm::radians(Pitch)), 
        sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
    };
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you 
    // look up or down which results in slower movement.
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
  }
};