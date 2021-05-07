#pragma once

#include "vector.h"
#include "utility.h"

class Matrix{
public:
	const Matrix& Identity();
	const Matrix& Translation(const Vec4& v);
	const Matrix& Rotation(const Rotator& r);
	const Matrix& Scale(const Vec4& v);
	const Matrix& Perspective(float fov, float aspecRatio, float zNear, float zFar);
	const Matrix& ScreenSpaceTransform(int width, int heigth);
	Vec4 Transform(const Vec4& v) const;
	Vec3 Transform(const Vec3& v) const;
	Matrix operator*(const Matrix& other) const;

private:
	float m[4][4];
};