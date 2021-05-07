#pragma once

#include "display.h"
#include "matrix.h"

class Camera{
public:
	Camera(const Display& display, float fov = 80.0f) : display(display){
		viewProjection = Matrix().Perspective(fov, display.getAspectRatio(), 0.1f, 1000.0f);
		this->fov = fov;
	}

	void Update(float deltaTime);
	Matrix getViewProjection() const;

private:
	const Display& display;
	Matrix viewProjection;
	Vec3 forwards, up, right;
	Vec4 position;
	Rotator rotation;
	float fov;
};