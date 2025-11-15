#include <MouseInputs.h>
#include <GLFW/glfw3.h>

void MouseInput::update(glm::vec2 newPos, glm::vec2 scrollDelta) {
    if (state.firstMouse) {
        lastPosition = newPos;
        state.firstMouse = false;
    }

    state.delta = newPos - lastPosition;
    state.position = newPos;
    state.scroll = scrollDelta;
    lastPosition = newPos;
}

void MouseInput::setButton(int button, bool pressed) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) state.leftButton = pressed;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) state.rightButton = pressed;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE) state.middleButton = pressed;
}

bool MouseInput::isButtonPressed(int button) const {
    if (button == GLFW_MOUSE_BUTTON_LEFT) return state.leftButton;
    if (button == GLFW_MOUSE_BUTTON_RIGHT) return state.rightButton;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) return state.middleButton;
    return false;
}