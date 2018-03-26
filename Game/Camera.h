#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera
{
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;

public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	void rotate(glm::mat4 r)
	{
		forward = (glm::mat3)r * forward;
	}

	void moveForward()
	{
		this->pos += 0.05f * forward;
	}

	void moveBack()
	{
		this->pos -= 0.05f * forward;
	}

	void moveLeft()
	{
		this->pos -= glm::normalize(glm::cross(forward, up)) * 0.05f;
	}

	void moveRight()
	{
		this->pos += glm::normalize(glm::cross(forward, up)) * 0.05f;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	virtual ~Camera() {}
	
};