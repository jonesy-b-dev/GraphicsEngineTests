#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 1) in vec3 aTextCoord;

//out vec2 TextCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
//	TextCoord = vec2(aTextCoord.x, aTextCoord.y);
}