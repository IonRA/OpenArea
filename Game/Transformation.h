#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transformation
{
	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;

public:
	Transformation(const glm::vec3& translate = glm::vec3(), const glm::vec3& rotate = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->translate = translate;
		this->rotate = rotate;
		this->scale = scale;
	}

	inline glm::vec3& getTranslate()
	{
		return translate;
	}

	inline glm::vec3& getRotate() 
	{
		return rotate;
	}

	inline glm::vec3& getScale() 
	{
		return scale;
	}

	inline glm::mat4 getModel() const
	{
		glm::mat4 transMat = glm::translate(translate);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotMat = glm::rotate(rotate.x, glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(rotate.y, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(rotate.z, glm::vec3(0.0, 0.0, 1.0));
		return transMat * rotMat * scaleMat;
	}

	virtual ~Transformation() {};
};

