#include "InputLayer.h"
#include "WindowLayer.h"

InputLayer::InputLayer(WindowLayer* windowLayer)
    : window(windowLayer) {
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

bool InputLayer::isKeyPressed(int key) const {
    auto it = keyState.find(key);
    if (it != keyState.end())
        return it->second;
    return false;
}
