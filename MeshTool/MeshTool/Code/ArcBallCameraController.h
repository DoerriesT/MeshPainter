#pragma once
#include "Camera.h"
#include <memory>

class ArcBallCameraController
{
public:
	explicit ArcBallCameraController(const std::shared_ptr<Camera> &_camera, const glm::vec3 &_center, float _distance);
	void update(const glm::vec2 &_mouseDelta, float _scrollDelta, bool _translateCenter);

private:
	std::shared_ptr<Camera> camera;
	glm::vec3 center;
	float distance;
};