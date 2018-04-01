#include <GL\glew.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Shader.h"
#include <glm\gtc\type_ptr.hpp>


Shader::Shader(const char * vh, const char * fh)
{
	shaders.push_back(glCreateShader(GL_VERTEX_SHADER));
	std::string file = ReadFile(vh);
	const char * f =file.c_str();
	
	glShaderSource(shaders[0], 1, &f, NULL);
	glCompileShader(shaders[0]);

	int success;
	char infoLog[512];
	glGetShaderiv(shaders[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaders[0], 512, NULL, infoLog);
		throw infoLog;
	}

	file = ReadFile(fh);
	f = file.c_str();
	shaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));
	glShaderSource(shaders[1], 1, &f, NULL);
	glCompileShader(shaders[1]);

	glGetShaderiv(shaders[1], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glDeleteShader(shaders[0]);
		glGetShaderInfoLog(shaders[1], 512, NULL, infoLog);
		throw infoLog;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaders[0]);
	glAttachShader(shaderProgram, shaders[1]);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glDetachShader(shaderProgram, shaders[0]);
		glDetachShader(shaderProgram, shaders[1]);
		glDeleteProgram(shaderProgram);
		glDeleteShader(shaders[0]);
		glDeleteShader(shaders[1]);
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		throw infoLog;
	}
	uniforms.push_back(glGetUniformLocation(shaderProgram, "transform"));
	uniforms.push_back(glGetUniformLocation(shaderProgram, "cameraView"));
	uniforms.push_back(glGetUniformLocation(shaderProgram, "lightColor"));
	uniforms.push_back(glGetUniformLocation(shaderProgram, "lightPos"));
	uniforms.push_back(glGetUniformLocation(shaderProgram, "normalMatrix"));
	uniforms.push_back(glGetUniformLocation(shaderProgram, "viewPos"));
}

std::string Shader::ReadFile(const char* file)
{
	std::ifstream t(file);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string fileContent = buffer.str();
	return fileContent;
}

void Shader::actualize(const Transformation &t, const Camera &c)
{
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(t.getModel())));
	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, glm::value_ptr(t.getModel()));
	glUniformMatrix4fv(uniforms[1], 1, GL_FALSE, glm::value_ptr(c.GetViewProjection()));
	glUniformMatrix3fv(uniforms[4], 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void Shader::setLightColor(glm::vec3 c)
{
	glUniform3fv(uniforms[2], 1, &c[0]);
}

void Shader::setLightPos(glm::vec3 p)
{
	glUniform3fv(uniforms[3], 1, &p[0]);
}

void Shader::setViewPos(glm::vec3 p)
{
	glUniform3fv(uniforms[5], 1, &p[0]);
}

Shader::~Shader()
{
	glUseProgram(0);

	for (auto i : shaders)
		glDetachShader(shaderProgram, i);
	
	glDeleteProgram(shaderProgram);

	for (auto i : shaders)
		glDeleteShader(i);
}