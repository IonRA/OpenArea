#version 440 core

out vec4 FragColor;

in vec4 color;
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material
{
    sampler2D diff;
	sampler2D spec;
    float shin;
}; 

struct Light 
{
    vec3 pos;
    vec3 amb;
    vec3 diff;
    vec3 spec;
};

uniform Material material;
uniform Light light; 
uniform vec3 viewPos;

void main()
{
    vec3 ambient = light.amb * texture(material.diff, texCoord).rgb;

	vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diff * diff * texture(material.diff, texCoord).rgb;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shin);
    vec3 specular =  light.spec * spec * texture(material.spec, texCoord).rgb;
            
    vec3 result = (ambient + diffuse + specular);// * vec3(texture(ourTexture, texCoord));

	FragColor = vec4(result, 1.0);
}