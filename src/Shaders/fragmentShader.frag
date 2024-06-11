#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

//in vec3 ourColor;
//in vec2 TextCoord;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

// texture sampler
//uniform sampler2D texture1;

float ambientStrength = 0.1;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
} 
