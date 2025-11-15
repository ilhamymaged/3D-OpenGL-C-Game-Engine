#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <mat4x4.hpp> 
#include <ext/matrix_transform.hpp> 
#include <ext/matrix_clip_space.hpp> 

class Shader {
public:
	Shader(const std::string& name);
	~Shader();

	void use();
	void setMat4(const glm::mat4& value,const std::string& name);
	void setVec3(glm::vec3& value, const std::string& name);
	void setArrayVec3(std::vector<glm::vec3>& value, const std::string& name);
	void setArrayMat4(std::vector<glm::mat4>& value, const std::string& name);
	void setBool(bool value,const std::string& name);
	void setInt(int value, const std::string& name);
	void setFloat(float value, const std::string& name);

private:
	GLuint id;

private:
	std::string readConfigFile(const std::string& filename);

};