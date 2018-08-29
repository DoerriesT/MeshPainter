#include <glm\gtc\matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3 &_position, const glm::quat &_rotation)
	: position(_position), rotation(_rotation), startPosition(_position), startRotation(_rotation)
{
}

Camera::Camera(const glm::vec3 & _position, const glm::vec3 &_pitchYawRoll)
	: position(_position), rotation(_pitchYawRoll), startPosition(_position), startRotation(_pitchYawRoll)
{
}

void Camera::setRotation(const glm::quat &_rotation)
{
	rotation = _rotation;
	needToUpdateViewMatrix = true;
}

void Camera::setPosition(const glm::vec3 &_position)
{
	position = _position;
	needToUpdateViewMatrix = true;
}

void Camera::rotate(const glm::vec3 &_pitchYawRoll)
{
	glm::quat tmp = glm::quat(glm::vec3(_pitchYawRoll.x, 0.0, 0.0));
	glm::quat tmp1 = glm::quat(glm::angleAxis(_pitchYawRoll.y, glm::vec3(0.0, 1.0, 0.0)));
	rotation = glm::normalize(tmp * rotation * tmp1);

	needToUpdateViewMatrix = true;
}

void Camera::translate(const glm::vec3 &_translation)
{
	glm::vec3 forward(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
	glm::vec3 strafe(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);

	static const float speed = 1.12f;

	position += (_translation.z * forward + _translation.x * strafe) * speed;
	needToUpdateViewMatrix = true;
}

void Camera::lookAt(const glm::vec3 &_targetPosition)
{
	static const glm::vec3 UP(0.0, 1.0f, 0.0);

	viewMatrix = glm::lookAt(position, _targetPosition, UP);
	glm::quat rot = glm::quat_cast(viewMatrix);
	needToUpdateViewMatrix = false;
}

void Camera::setZoom(float _zoom)
{
	assert(zoom > 0.0f);
	zoom = _zoom;
	//SystemManager::getInstance().getSystem<RenderSystem>()->getWindow()->setFieldOfView(Window::DEFAULT_FOV / zoom);
}

const glm::mat4 &Camera::getViewMatrix()
{
	if (needToUpdateViewMatrix)
	{
		updateViewMatrix();
		needToUpdateViewMatrix = false;
	}
	return viewMatrix;
}

const glm::vec3 &Camera::getPosition() const
{
	return position;
}

const glm::quat &Camera::getRotation() const
{
	return rotation;
}

glm::vec3 Camera::getForwardDirection()
{
	return -glm::transpose(getViewMatrix())[2];
}

glm::vec3 Camera::getUpDirection()
{
	return glm::transpose(getViewMatrix())[1];
}

glm::vec3 Camera::getRightDirection()
{
	return glm::transpose(getViewMatrix())[0];
}

float Camera::getZoom() const
{
	return zoom;
}

void Camera::reset()
{
	position = startPosition;
	rotation = startRotation;
	needToUpdateViewMatrix = true;
}

void Camera::updateViewMatrix()
{
	glm::mat4 translate;
	viewMatrix = glm::mat4_cast(rotation) * glm::translate(translate, -position);
}