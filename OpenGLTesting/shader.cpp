#include "shader.h"

#include "glad\glad.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "errorHandeling.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << "\n" << e.code() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // 2. compile shaders
    
    // Vertex shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    // Attach shader source code to shader object
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    errorHandeling::checkShader(vertex);
    
    // Fragment Shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach shader source code to shader object
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    errorHandeling::checkShader(fragment);

    // shader Program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    errorHandeling::checkShaderProgram(shaderID);
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(shaderID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
