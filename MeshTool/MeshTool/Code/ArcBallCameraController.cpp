#include "ArcBallCameraController.h"
#include <glm/gtx/rotate_vector.hpp>

ArcBallCameraController::ArcBallCameraController(const std::shared_ptr<Camera> &_camera, const glm::vec3 &_center, float _distance)
	:camera(_camera),
	center(_center),
	distance(_distance)
{
}

void ArcBallCameraController::update(const glm::vec2 &_mouseDelta, float _scrollDelta, bool _translateCenter)
{
	const float SCROLL_DELTA_MULT = -0.0005f;
	const float MOUSE_DELTA_MULT = 0.01f;
	distance += _scrollDelta * SCROLL_DELTA_MULT * distance;
	distance = glm::max(0.0f, distance);

	if (_translateCenter)
	{
		center -= camera->getRightDirection() * _mouseDelta.x * MOUSE_DELTA_MULT * 0.1f;
		center += camera->getUpDirection() * _mouseDelta.y * MOUSE_DELTA_MULT * 0.1f;
	}
	else
	{
		camera->rotate(glm::vec3(_mouseDelta.y * MOUSE_DELTA_MULT, _mouseDelta.x * MOUSE_DELTA_MULT, 0.0f));
	}

	camera->setPosition(center - camera->getForwardDirection() * distance);
	camera->lookAt(center);
}

void ArcBallCameraController::centerCamera()
{
	center = glm::vec3(0.0f);
	update(glm::vec2(0.0f), 0.0f, false);
}
