#pragma once

class Layer {
public:
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}
};
