//
// Created by Xiaohe Cheng on 5/7/2018.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    UPWARD,
    DOWNWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         =  180.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angle
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float cameraSpeed = MovementSpeed * deltaTime;
        if (direction == UPWARD)
            Position += Up * cameraSpeed;
        if (direction == DOWNWARD)
            Position -= Up * cameraSpeed;
        if (direction == LEFT)
            Position -= Right * cameraSpeed;
        if (direction == RIGHT)
            Position += Right * cameraSpeed;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true){
        // Set Euler Angle
        Yaw += xoffset * MouseSensitivity;
        Pitch += yoffset * MouseSensitivity;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch){
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseSroll(float yoffset){
        Zoom -= yoffset;
        if (Zoom > 60.0f) Zoom = 60.0f;
        if (Zoom < 2.0f) Zoom = 2.0f;
    }

private:
    void updateCameraVectors()
    {
        Front.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
        Front.y = sin(glm::radians(Pitch));
        Front.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        Front = glm::normalize(Front); // Avoid rounding error
        // Recalculate Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};


#endif //CAMERA_H
