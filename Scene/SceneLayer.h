#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <RendererLayer.h>
#include <InputLayer.h>
#include <Layer.h>
#include <Shader.h>
#include <CameraLayer.h>
#include <WindowLayer.h>
#include <entt.hpp>  

class SceneLayer : public Layer
{
public:
	SceneLayer(RendererLayer* renderer, InputLayer* inputLayer, 
		CameraLayer* cameraLayer, WindowLayer* windowLayer);
	~SceneLayer() override = default;
	void onAttach() override;
	void onDetach() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;

private:
	entt::registry registry;

	RendererLayer* renderLayer;
	InputLayer* inputLayer;
	WindowLayer* windowLayer;
	CameraLayer* cameraLayer;
	Shader* shader;
};