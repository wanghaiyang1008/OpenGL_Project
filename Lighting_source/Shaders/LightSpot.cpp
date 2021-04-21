#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	positon(_position),
	angles(_angles),
	color(_color)
{
	UpdateDirection();
}

LightSpot::LightSpot()
{
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);//每次初始化为Z轴
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateY(direction, angles.y);
	direction = glm::rotateX(direction, angles.x);
	direction = -1.0f * direction;
}
