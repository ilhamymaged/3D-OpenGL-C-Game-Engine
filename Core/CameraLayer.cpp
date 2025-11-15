#include "CameraLayer.h"
#include <GLFW/glfw3.h>

CameraLayer::CameraLayer(InputLayer* inputLayer, glm::vec3 pos)
    : input(inputLayer), position(pos), front(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f), yaw(-90.0f), pitch(0.0f),
    speed(5.0f), fov(45.0f)
{
    updateCameraVectors();
}

void CameraLayer::onUpdate(float deltaTime) {
    float velocity = speed * deltaTime;

    if (input->isKeyPressed(GLFW_KEY_W))
        position += front * velocity;
    if (input->isKeyPressed(GLFW_KEY_S))
        position -= front * velocity;
    if (input->isKeyPressed(GLFW_KEY_A))
        position -= right * velocity;
    if (input->isKeyPressed(GLFW_KEY_D))
        position += right * velocity;

    updateCameraVectors();
}

glm::mat4 CameraLayer::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void CameraLayer::updateCameraVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}
