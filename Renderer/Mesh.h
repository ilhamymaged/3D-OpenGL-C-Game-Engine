#pragma once
#include <iostream>
#include <vector>
#include <Shader.h>
#include <Texture.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;
    std::shared_ptr<Texture> diffuseTexture;

public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        std::shared_ptr<Texture> texture);

    ~Mesh();

    void render();
    void renderInstanced(size_t size);
    void setTexture(std::shared_ptr<Texture> texture) {
        diffuseTexture = texture;
    }

    // Add these for accessing VAO (needed for instancing)
    GLuint getVAO() const { return VAO; }
    size_t getIndexCount() const { return indices.size(); }

    // Static factory methods - update signatures to accept optional texture
    static std::shared_ptr<Mesh> generateBlock(std::shared_ptr<Texture> texture = nullptr);
    static std::shared_ptr<Mesh> generatePlane(std::shared_ptr<Texture> texture = nullptr);
    static std::shared_ptr<Mesh> generateQuad(std::shared_ptr<Texture> texture = nullptr);
};