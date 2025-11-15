#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <Shader.h>
#include <Mesh.h>

class Model {
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::string name;

public:
    // Constructor
    Model(const std::string& name) : name(name) {}

    // Add mesh to the model
    void addMesh(std::shared_ptr<Mesh> mesh) {
        meshes.push_back(mesh);
    }

    // Render all meshes in the model
    void render() {
        for (auto& mesh : meshes) {
            mesh->render();
        }
    }

    void renderInstanced(size_t size)
    {
        for (auto& mesh : meshes) 
            mesh->renderInstanced(size);
    }


    // Get all meshes (const version)
    const std::vector<std::shared_ptr<Mesh>>& getMeshes() const {
        return meshes;
    }

    // Get all meshes (non-const version for modification)
    std::vector<std::shared_ptr<Mesh>>& getMeshes() {
        return meshes;
    }

    // Get model name
    const std::string& getName() const {
        return name;
    }

    // Get number of meshes
    size_t getMeshCount() const {
        return meshes.size();
    }

    // Check if model is empty
    bool isEmpty() const {
        return meshes.empty();
    }

    // Clear all meshes
    void clear() {
        meshes.clear();
    }
};