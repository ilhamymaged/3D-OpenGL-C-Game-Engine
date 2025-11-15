#pragma once
#include "Layer.h"
#include "InputLayer.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class CameraLayer : public Layer {
public:
    CameraLayer(InputLayer* input, glm::vec3 position = { 0.0f, 0.0f, 0.0f });

    void onUpdate(float deltaTime) override;

    glm::mat4 getViewMatrix() const;
    float getFOV() const { return fov; }

private:
    InputLayer* input;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float yaw;
    float pitch;
    float speed;
    float fov;

    void updateCameraVectors();
};
