#pragma once
#include <glad/glad.h>

#include <iostream>
#include <string>

#include <stb_image.h>

class Texture {
    GLuint textureID;
    std::string path;
public:
    Texture(const std::string& absolutePath);
    ~Texture();
    void bind();
    GLuint getID() const { return textureID; }
};