#pragma once

#include <glm.hpp>
#include <Mesh.h>

struct Transform 
{
    glm::vec3 position{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scale{ 1.0f };
};

struct Renderable
{
	std::shared_ptr<Mesh> mesh;
};




