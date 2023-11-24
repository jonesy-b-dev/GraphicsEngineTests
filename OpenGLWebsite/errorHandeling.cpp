#include "glad\glad.h"
#include <glfw3.h>
#include <iostream>
#include <stdio.h>


#include "errorHandeling.h"


void errorHandeling::checkShader(unsigned int shader)
{
	static int success;
	static char infoLog[512];

	//check if the shader compiled correctly and print any errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	//If the shader failed to compile print the error
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void errorHandeling::checkShaderProgram(unsigned int program)
{
	static int success;
	static char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}