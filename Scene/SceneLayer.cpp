#include <SceneLayer.h>

SceneLayer::SceneLayer(RendererLayer* renderer, InputLayer* inputLayer)
	:renderLayer{renderer}, inputLayer(inputLayer), VAO(0), VBO(0), EBO(0), shader(nullptr),
	offset{ 0.1f, 0.1f, 0.1f }
{}

void SceneLayer::onAttach()
{
	shader = new Shader("triangle");

	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint indices[] = 
	{
		0, 1, 2 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void SceneLayer::onDetach()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete shader;
}

void SceneLayer::onUpdate(float deltaTime)
{
	if (inputLayer->isKeyPressed(GLFW_KEY_D))
		offset.x += deltaTime;
	if (inputLayer->isKeyPressed(GLFW_KEY_A))
		offset.x -= deltaTime;
	if (inputLayer->isKeyPressed(GLFW_KEY_W))
		offset.y += deltaTime;
	if (inputLayer->isKeyPressed(GLFW_KEY_S))
		offset.y -= deltaTime;
}

void SceneLayer::onRender()
{
	renderLayer->submit([this]() {
		shader->use();
		shader->setVec3(offset, "offset");
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	});
}
	