#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 cameraView;
uniform mat3 normalMatrix;

out vec4 color;
out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

void main()
{
  normal = normalMatrix * aNormal;
  fragPos = vec3(transform * vec4(aPos, 1.0));
  gl_Position = cameraView * transform * vec4(aPos, 1.0);
  color = aColor;
  texCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}