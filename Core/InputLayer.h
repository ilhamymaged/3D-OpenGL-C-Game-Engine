#pragma once
#include <Layer.h>
#include <MouseInputs.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class WindowLayer; // forward declaration

class InputLayer : public Layer {
public:
    InputLayer(WindowLayer* windowLayer);

    void onUpdate(float deltaTime) override;
    bool isKeyPressed(int key) const;

	inline const MouseInput& getMouse() const { return mouse; }

private:
    WindowLayer* window;
    std::unordered_map<int, bool> keyState;

    MouseInput mouse;

    static void mouseCallback(GLFWwindow* win, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* win, double xoffset, double yoffset);
    static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
};
