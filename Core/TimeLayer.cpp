#include "TimeLayer.h"
#include <GLFW/glfw3.h>

TimeLayer::TimeLayer() : lastFrame(0.0f), deltaTime(0.0f) {}

void TimeLayer::onUpdate(float) {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
