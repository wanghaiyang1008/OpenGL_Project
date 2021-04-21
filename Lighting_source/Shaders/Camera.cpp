#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	Worldup = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Forward, Right));

}


Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	Worldup = worldup;
	Yaw = yaw;
	Pitch = pitch;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	//右手定则
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Right, Forward));

}


glm::mat4 Camera::GetViewMatrix() {
	glm::mat4 view;
	view = glm::lookAt(Position, Position + Forward, Worldup);
	return view;
}

void Camera::updateCameraVectors() {

	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	//右手定则
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch -= yoffset;
	bool constrainPitch = true;
	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::updateCameraPosition() {
	Position += Forward * speedZ *0.001f + Right * speedX * 0.001f + Up * speedY * 0.001f;
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}