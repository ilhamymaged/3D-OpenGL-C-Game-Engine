#pragma once
#include "Layer.h"

class TimeLayer : public Layer {
public:
    TimeLayer();

    void onUpdate(float deltaTime) override;

    float getDeltaTime() const { return deltaTime; }

private:
    float lastFrame;
    float deltaTime;
}; 