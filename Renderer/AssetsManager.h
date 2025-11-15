#pragma once

#include <vector>
#include <string>
#include <map>
#include <Mesh.h>
#include <Texture.h>
#include <tiny_obj_loader.h>
#include <Model.h>
#include <filesystem>
#include <Shader.h>

class AssetManager
{
public:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
    std::unordered_map<std::string, std::shared_ptr<Mesh>> primitives; 

private:
    const std::string TEXTURE_PATH = "../../../assets/Textures/";
    const std::string MODEL_PATH = "../../../assets/Models/";

public:
    // Load texture from assets folder by name
    std::shared_ptr<Texture> loadTexture(const std::string& name) {
        if (textures.find(name) != textures.end()) {
            return textures[name];  // Already loaded
        }

        std::string path = TEXTURE_PATH + name;
        auto texture = std::make_shared<Texture>(path);
        textures[name] = texture;
        return texture;
    }

    std::shared_ptr<Shader> loadShader(const std::string& name) {
        if (shaders.find(name) != shaders.end()) {
            return shaders[name];  // Already loaded
        }

        auto shader = std::make_shared<Shader>(name);
        shaders[name] = shader;
        return shader;
    }


    // Load texture from absolute path (for ImGui file picker)
    std::shared_ptr<Texture> loadTextureAbsPath(const std::string& absolutePath) {
        // Use filename as key
        std::filesystem::path p(absolutePath);
        std::string key = p.filename().string();

        if (textures.find(key) != textures.end()) {
            return textures[key];
        }

        auto texture = std::make_shared<Texture>(absolutePath);
        textures[key] = texture;
        return texture;
    }

    std::shared_ptr<Model> loadModel(const std::string& name) {
        if (models.find(name) != models.end()) {
            return models[name];
        }

        std::string objPath = MODEL_PATH + name + "/" + name + ".obj";
        auto model = std::make_shared<Model>(name);

        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = MODEL_PATH + name + "/";
        reader_config.triangulate = true;
        reader_config.vertex_color = false;

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(objPath, reader_config)) {
            if (!reader.Error().empty())
                std::cerr << "TinyObjReader error: " << reader.Error() << std::endl;
            return nullptr;  // Return nullptr instead of exit
        }

        if (!reader.Warning().empty()) {
            std::cout << "TinyObjReader warning: " << reader.Warning() << std::endl;
        }

        auto attrib = reader.GetAttrib();
        auto shapes = reader.GetShapes();
        auto materials = reader.GetMaterials();

        // Cache loaded textures to avoid duplicate loading
        std::unordered_map<std::string, std::shared_ptr<Texture>> materialTextures;

        for (size_t s = 0; s < shapes.size(); s++) {
            // Group vertices by material ID to create separate meshes
            std::unordered_map<int, std::vector<Vertex>> matVertices;
            std::unordered_map<int, std::vector<GLuint>> matIndices;

            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Get material ID for THIS face (not just first face)
                int matID = shapes[s].mesh.material_ids[f];

                for (size_t v = 0; v < fv; v++) {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    Vertex vertex;

                    vertex.position = glm::vec3(
                        attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                        attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                        attrib.vertices[3 * size_t(idx.vertex_index) + 2]
                    );

                    if (idx.normal_index >= 0) {
                        vertex.normal = glm::vec3(
                            attrib.normals[3 * size_t(idx.normal_index) + 0],
                            attrib.normals[3 * size_t(idx.normal_index) + 1],
                            attrib.normals[3 * size_t(idx.normal_index) + 2]
                        );
                    }
                    else {
                        vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (idx.texcoord_index >= 0) {
                        vertex.texCoords = glm::vec2(
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 0],
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]
                        );
                    }
                    else {
                        vertex.texCoords = glm::vec2(0.0f, 0.0f);
                    }

                    matVertices[matID].push_back(vertex);
                    matIndices[matID].push_back(static_cast<GLuint>(matVertices[matID].size() - 1));
                }

                index_offset += fv;
            }

            // Create one mesh per material
            for (auto& pair : matVertices) {
                int matID = pair.first;
                auto& vertices = pair.second;
                auto& indices = matIndices[matID];

                // Load texture for this material
                std::shared_ptr<Texture> meshTexture = nullptr;
                if (matID >= 0 && matID < materials.size() &&
                    !materials[matID].diffuse_texname.empty()) {

                    std::string texName = materials[matID].diffuse_texname;

                    // Check if already loaded in this model
                    if (materialTextures.find(texName) != materialTextures.end()) {
                        meshTexture = materialTextures[texName];
                    }
                    else {
                        // Load new texture
                        std::string texPath = MODEL_PATH + name + "/" + texName;
                        try {
                            meshTexture = std::make_shared<Texture>(texPath);
                            materialTextures[texName] = meshTexture;

                            // Also store in global texture cache with filename key
                            std::filesystem::path p(texName);
                            textures[p.filename().string()] = meshTexture;
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Failed to load texture: " << texPath
                                << " - " << e.what() << std::endl;
                        }
                    }
                }

                auto mesh = std::make_shared<Mesh>(vertices, indices, meshTexture);
                model->addMesh(mesh);
            }
        }

        models[name] = model;
        return model;
    }

    void initPrimitives() {
        primitives["Block"] = Mesh::generateBlock();
        primitives["Plane"] = Mesh::generatePlane();
    }
};