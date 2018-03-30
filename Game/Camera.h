#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera
{
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	float pitch = 0.0f;
	float yaw = -90.0f;

public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	void chPerspective(float fov, float aspect, float zNear, float zFar)
	{
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	void rotate(float xoffset, float yoffset)
	{
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(front);
	}

	glm::vec3 inline getPos() const
	{
		return  pos;
	}

	glm::vec3 inline getForward() const
	{
		return  forward;
	}

	void moveForward()
	{
		this->pos += 0.05f * forward;
	}

	void moveBack()
	{
		this->pos -= 0.2f * forward;
	}

	void moveLeft()
	{
		this->pos -= glm::normalize(glm::cross(forward, up)) * 0.2f;
	}

	void moveRight()
	{
		this->pos += glm::normalize(glm::cross(forward, up)) * 0.2f;
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	virtual ~Camera() {}
	
};