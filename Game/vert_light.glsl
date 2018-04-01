#version 440 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 cameraView;

void main()
{
	gl_Position = cameraView * transform * vec4(aPos, 1.0);
}