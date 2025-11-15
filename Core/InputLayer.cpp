#include "InputLayer.h"
#include "WindowLayer.h"

static InputLayer* s_Instance = nullptr;

InputLayer::InputLayer(WindowLayer* windowLayer)
    : window(windowLayer) {
    s_Instance = this;

    // Set up mouse callbacks
    GLFWwindow* win = window->getWindow();
    glfwSetCursorPosCallback(win, mouseCallback);
    glfwSetScrollCallback(win, scrollCallback);
    glfwSetMouseButtonCallback(win, mouseButtonCallback);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

void InputLayer::onUpdate(float) {
    keyState.clear();
    GLFWwindow* win = window->getWindow();

    for (int key = 32; key <= 348; ++key) {
        keyState[key] = (glfwGetKey(win, key) == GLFW_PRESS);
    }

    if(isKeyPressed(GLFW_KEY_ESCAPE))
		window->close();

}

void InputLayer::mouseCallback(GLFWwindow* win, double xpos, double ypos) {
    if (s_Instance) {
        s_Instance->mouse.update(glm::vec2(xpos, ypos), glm::vec2(0.0f));
    }
}

void InputLayer::scrollCallback(GLFWwindow* win, double xoffset, double yoffset) {
    if (s_Instance) {
        glm::vec2 currentPos = s_Instance->mouse.getPosition();
        s_Instance->mouse.update(currentPos, glm::vec2(xoffset, yoffset));
    }
}

void InputLayer::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
    if (s_Instance) {
        s_Instance->mouse.setButton(button, action == GLFW_PRESS);
    }
}

bool InputLayer::isKeyPressed(int key) const {
    auto it = keyState.find(key);
    if (it != keyState.end())
        return it->second;
    return false;
}
