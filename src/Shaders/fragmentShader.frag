#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TextCoord;
uniform vec3 objectColor;
uniform vec3 lightColor;

// texture sampler
//uniform sampler2D texture1;

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}
