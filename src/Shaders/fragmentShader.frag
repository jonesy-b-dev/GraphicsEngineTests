#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TextCoord;
uniform vec3 objectColor;
uniform vec3 lightColor;

// texture sampler
//uniform sampler2D texture1;

float ambientStrength = 0.1;

void main()
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
