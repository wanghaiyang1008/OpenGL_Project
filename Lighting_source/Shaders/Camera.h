#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 Worldup;
	float Pitch;
	float Yaw;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;
	float Zoom= 45.0f;;
	float MouseSensitivity=0.002f;

	glm::mat4 GetViewMatrix();

	void updateCameraVectors();
	void ProcessMouseMovement(float xoffset, float yoffset);
	void updateCameraPosition();
	void ProcessMouseScroll(float yoffset);
};

