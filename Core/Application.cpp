#include <Application.h>
#include <WindowLayer.h>
#include <TimeLayer.h>
#include <InputLayer.h>
#include <RendererLayer.h>
#include <CameraLayer.h>
#include <SceneLayer.h>

Application::Application(const std::string& title, int width, int height) 
{
    windowLayer = new WindowLayer(width, height, title);
    timeLayer = new TimeLayer();
    inputLayer = new InputLayer(windowLayer);
	rendererLayer = new RendererLayer();
	cameraLayer = new CameraLayer(inputLayer);
	sceneLayer = new SceneLayer(rendererLayer, inputLayer, cameraLayer, windowLayer); 

    pushLayer(timeLayer);
    pushLayer(windowLayer);
    pushLayer(inputLayer);
	pushLayer(cameraLayer);
	pushLayer(rendererLayer);
	pushLayer(sceneLayer);
}

Application::~Application()
{
    for (auto layer : layers) layer->onDetach();
    for (auto layer : layers) delete layer;
}

void Application::pushLayer(Layer* layer) 
{
    layer->onAttach();
    layers.push_back(layer);
}

void Application::run() 
{
    while (!windowLayer->shouldClose()) 
    {
        timeLayer->onUpdate(0.0f);
        float deltaTime = timeLayer->getDeltaTime();

        // Update all layers
        for (auto layer : layers) layer->onUpdate(deltaTime);
        for (auto layer : layers) layer->onRender();
    }
}
