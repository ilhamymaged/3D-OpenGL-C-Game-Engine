#pragma once
#include <Layer.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class WindowLayer; // forward declaration

class InputLayer : public Layer {
public:
    InputLayer(WindowLayer* windowLayer);

    void onUpdate(float deltaTime) override;

    bool isKeyPressed(int key) const;

private:
    WindowLayer* window;
    std::unordered_map<int, bool> keyState;
};
