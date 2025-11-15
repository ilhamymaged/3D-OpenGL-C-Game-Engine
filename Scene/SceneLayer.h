#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <RendererLayer.h>
#include <InputLayer.h>
#include <Layer.h>
#include <Shader.h>

class SceneLayer : public Layer
{
public:
	SceneLayer(RendererLayer* renderer, InputLayer* inputLayer);
	~SceneLayer() override = default;
	void onAttach() override;
	void onDetach() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;

private:
	RendererLayer* renderLayer;
	InputLayer* inputLayer;
	GLuint VAO, VBO, EBO;
	Shader* shader;
	glm::vec3 offset;
};