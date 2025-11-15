#pragma once
#include <glm.hpp>

class MouseInput {
public:
    struct MouseState {
        glm::vec2 position{ 0.0f };
        glm::vec2 delta{ 0.0f };
        glm::vec2 scroll{ 0.0f };
        bool leftButton = false;
        bool rightButton = false;
        bool middleButton = false;
        bool firstMouse = true;
    };

    void update(glm::vec2 newPos, glm::vec2 scrollDelta);
    void setButton(int button, bool pressed);

    const MouseState& getState() const { return state; }
    glm::vec2 getPosition() const { return state.position; }
    glm::vec2 getDelta() const { return state.delta; }
    bool isButtonPressed(int button) const;

private:
    MouseState state;
    glm::vec2 lastPosition{ 0.0f };
};