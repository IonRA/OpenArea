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
	void setLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	void setViewPos(glm::vec3);
	void setMaterial(float);
	void setT1(){
		glUniform1i(uniforms[9], 0);
	}
	void setT2(){
		glUniform1i(uniforms[10], 1);
	}
};