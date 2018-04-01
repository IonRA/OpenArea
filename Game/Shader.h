#pragma once

#include <vector>
#include "Transformation.h"
#include "Camera.h"

class Shader
{
	unsigned int shaderProgram;
	std::vector<int> shaders;
	std::vector<unsigned int> uniforms; 
	
public:
	std::string ReadFile(const char*);
	Shader(const char * , const char *);
	virtual ~Shader();
	void useProgram() { glUseProgram(shaderProgram); }
	void actualize(const Transformation &, const Camera&);
	void setLightPos(glm::vec3);
	void setLightColor(glm::vec3);
	void setViewPos(glm::vec3);
};