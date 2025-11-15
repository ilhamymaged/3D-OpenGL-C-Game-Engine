#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Layer.h>
#include <vector>
#include <functional>

class RendererLayer : public Layer {
public:
    RendererLayer();
    ~RendererLayer() = default;

    void onAttach() override;
    void onUpdate(float deltaTime) override;
    void onRender() override;
    void onDetach() override;

    void submit(const std::function<void()>& renderFunc);

private:
    std::vector<std::function<void()>> renderQueue;
};
