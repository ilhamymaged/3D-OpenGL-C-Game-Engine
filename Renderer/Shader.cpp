#include <Shader.h>

Shader::Shader(const std::string& name)
{
	std::string temp = "../../../shaders/" + name;
	std::string vertexShaderSourceStr = readConfigFile(temp + ".v");
	std::string fragmentShaderSourceStr = readConfigFile(temp + ".f");
	const char* vertexShaderSource = vertexShaderSourceStr.c_str();
	const char* fragmentShaderSource = fragmentShaderSourceStr.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED::\n" << name << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<  name << infoLog << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << name << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::cout << "DEBUG: Shader " << name << " compiled successfully. Program ID: " << id << std::endl;
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setMat4(const glm::mat4& value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

void Shader::setArrayMat4(std::vector<glm::mat4>& value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniformMatrix4fv(loc, value.size(), GL_FALSE, &value.at(0)[0][0]);
}

void Shader::setVec3(glm::vec3& value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniform3fv(loc, 1, &value[0]);
}

void Shader::setArrayVec3(std::vector<glm::vec3>& value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniform3fv(loc, value.size(), &value.at(0)[0]);
}

void Shader::setBool(bool value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniform1i(loc, value);
}

void Shader::setInt(int value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniform1i(loc, value);
}

void Shader::setFloat(float value, const std::string& name)
{
	unsigned int loc = glGetUniformLocation(id, name.c_str());
	if (loc == -1) std::cout << "There's nothing called " << name << std::endl;
	glUniform1f(loc, value);
}

std::string Shader::readConfigFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open shader file: " << filename << std::endl;
		return "";
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
