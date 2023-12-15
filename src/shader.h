#pragma once
#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

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

    // Vec2
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;

    // Vec3
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

    // Vec4
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;

    // Mat2
    void setMat2(const std::string& name, const glm::mat2& mat) const;

    // Mat3
    void setMat3(const std::string& name, const glm::mat3& mat) const;

    // Mat4
    void setMat4(const std::string& name, const glm::mat4& mat) const;

};