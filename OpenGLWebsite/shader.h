#pragma once
#include <string>

class Shader
{
public:
	// ID of the program
	unsigned int shaderID;

	// Constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmanePath);
	// use/activate shader
	void use();

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};