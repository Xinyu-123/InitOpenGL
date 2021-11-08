#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{
public:
	// Constructors / Destructors
	Camera();
	Camera(Resolution _screenResolution);
	virtual ~Camera();

	// Getters
	glm::mat4 GetProjection() { return m_projection; }
	glm::mat4 GetView() { return m_view; }
	glm::vec3 GetPosition() { return m_position; }
private:
	// Members
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::vec3 m_position;
};

#endif

