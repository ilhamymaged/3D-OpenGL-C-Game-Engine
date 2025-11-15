#include <Mesh.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
	std::shared_ptr<Texture> texture) : diffuseTexture(std::move(texture))
{
	this->vertices = vertices;
	this->indices = indices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::render()
{
	if (diffuseTexture) {  
		glActiveTexture(GL_TEXTURE0);
		diffuseTexture->bind();
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::renderInstanced(size_t size)
{
	if (diffuseTexture) {
		glActiveTexture(GL_TEXTURE0);
		diffuseTexture->bind();
	}
	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, size);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

std::shared_ptr<Mesh> Mesh::generateBlock(std::shared_ptr<Texture> texture)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// Cube vertices with normals per face
	vertices = {
		// Front (+Z)
		{{-0.5f,-0.5f, 0.5f},{0,0,1},{0,0}},
		{{ 0.5f,-0.5f, 0.5f},{0,0,1},{1,0}},
		{{ 0.5f, 0.5f, 0.5f},{0,0,1},{1,1}},
		{{-0.5f, 0.5f, 0.5f},{0,0,1},{0,1}},

		// Back (–Z)  **REVERSED**
		{{ 0.5f,-0.5f,-0.5f},{0,0,-1},{0,0}},
		{{-0.5f,-0.5f,-0.5f},{0,0,-1},{1,0}},
		{{-0.5f, 0.5f,-0.5f},{0,0,-1},{1,1}},
		{{ 0.5f, 0.5f,-0.5f},{0,0,-1},{0,1}},

		// Left (–X)
		{{-0.5f,-0.5f,-0.5f},{-1,0,0},{0,0}},
		{{-0.5f,-0.5f, 0.5f},{-1,0,0},{1,0}},
		{{-0.5f, 0.5f, 0.5f},{-1,0,0},{1,1}},
		{{-0.5f, 0.5f,-0.5f},{-1,0,0},{0,1}},

		// Right (+X)
		{{ 0.5f,-0.5f, 0.5f},{1,0,0},{0,0}},
		{{ 0.5f,-0.5f,-0.5f},{1,0,0},{1,0}},
		{{ 0.5f, 0.5f,-0.5f},{1,0,0},{1,1}},
		{{ 0.5f, 0.5f, 0.5f},{1,0,0},{0,1}},

		// Top (+Y)
		{{-0.5f, 0.5f, 0.5f},{0,1,0},{0,0}},
		{{ 0.5f, 0.5f, 0.5f},{0,1,0},{1,0}},
		{{ 0.5f, 0.5f,-0.5f},{0,1,0},{1,1}},
		{{-0.5f, 0.5f,-0.5f},{0,1,0},{0,1}},

		// Bottom (–Y) **REVERSED**
		{{-0.5f,-0.5f,-0.5f},{0,-1,0},{0,1}},
		{{ 0.5f,-0.5f,-0.5f},{0,-1,0},{1,1}},
		{{ 0.5f,-0.5f, 0.5f},{0,-1,0},{1,0}},
		{{-0.5f,-0.5f, 0.5f},{0,-1,0},{0,0}}
	};

	indices = {
	0,1,2, 2,3,0,
	4,5,6, 6,7,4,
	8,9,10, 10,11,8,
	12,13,14, 14,15,12,
	16,17,18, 18,19,16,
	20,21,22, 22,23,20
	};

	return std::make_shared<Mesh>(vertices, indices, texture);
}

std::shared_ptr<Mesh> Mesh::generatePlane(std::shared_ptr<Texture> texture)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// A simple 2x2 plane on the XZ plane (Y = 0)
	vertices = {
		// Position                 // Normal           // TexCoord
		{{-1.0f, 0.0f, -1.0f},      {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left
		{{ 1.0f, 0.0f, -1.0f},      {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-right
		{{ 1.0f, 0.0f,  1.0f},      {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Top-right
		{{-1.0f, 0.0f,  1.0f},      {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}  // Top-left
	};

	indices = {
		0, 1, 2,
		0, 2, 3
	};

	return std::make_shared<Mesh>(vertices, indices, texture);
}

std::shared_ptr<Mesh> Mesh::generateQuad(std::shared_ptr<Texture> texture)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	vertices = {
		// Position                 // Normal           // TexCoord
		{{-1.0f, -1.0f, 0.0f},      {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Bottom-left
		{{ 1.0f, -1.0f, 0.0f},      {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // Bottom-right
		{{ 1.0f, 1.0f,  0.0f},      {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // Top-right
		{{-1.0f, 1.0f,  0.0f},      {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}  // Top-left
	};

	indices = {
		0, 1, 2,
		0, 2, 3
	};

	return std::make_shared<Mesh>(vertices, indices, texture);
}
