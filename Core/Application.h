#pragma once
#define GLFW_INCLUDE_NONE
#include <vector>
#include <string>
#include <Layer.h>

class WindowLayer;
class TimeLayer;
class InputLayer;
class RendererLayer;
class SceneLayer;
class CameraLayer;

class Application {
public:
    Application(const std::string& title, int width, int height);
    ~Application();

    void run();
    void pushLayer(Layer* layer); 

private:
    std::vector<Layer*> layers;

    WindowLayer* windowLayer;
    TimeLayer* timeLayer;
    InputLayer* inputLayer;
	RendererLayer* rendererLayer;
	SceneLayer* sceneLayer;
	CameraLayer* cameraLayer;
};
