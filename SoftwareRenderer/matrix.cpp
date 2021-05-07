#include "matrix.h"

const Matrix& Matrix::Identity(){
	m[0][0] = 1;	m[1][0] = 0;	m[2][0] = 0;	m[3][0] = 0;
	m[0][1] = 0;	m[1][1] = 1;	m[2][1] = 0;	m[3][1] = 0;
	m[0][2] = 0;	m[1][2] = 0;	m[2][2] = 1;	m[3][2] = 0;
	m[0][3] = 0;	m[1][3] = 0;	m[2][3] = 0;	m[3][3] = 1;

	return *this;
}

const Matrix& Matrix::Translation(const Vec4& v){
	m[0][0] = 1;	m[1][0] = 0;	m[2][0] = 0;	m[3][0] = v.X;
	m[0][1] = 0;	m[1][1] = 1;	m[2][1] = 0;	m[3][1] = v.Y;
	m[0][2] = 0;	m[1][2] = 0;	m[2][2] = 1;	m[3][2] = v.Z;
	m[0][3] = 0;	m[1][3] = 0;	m[2][3] = 0;	m[3][3] = 1;

	return *this;
}

const Matrix& Matrix::Rotation(const Rotator& r){
	Matrix rotY, rotZ;	//this = rotX

	m[0][0] = 1;	m[1][0] = 0;			m[2][0] = 0;			m[3][0] = 0;
	m[0][1] = 0;	m[1][1] = cos(r.X);		m[2][1] = sin(r.X);		m[3][1] = 0;
	m[0][2] = 0;	m[1][2] = -sin(r.X);	m[2][2] = cos(r.X);		m[3][2] = 0;
	m[0][3] = 0;	m[1][3] = 0;			m[2][3] = 0;			m[3][3] = 1;

	rotY.m[0][0] = cos(r.Y);	rotY.m[1][0] = 0;	rotY.m[2][0] = sin(r.Y);	rotY.m[3][0] = 0;
	rotY.m[0][1] = 0;			rotY.m[1][1] = 1;	rotY.m[2][1] = 0;			rotY.m[3][1] = 0;
	rotY.m[0][2] = -sin(r.Y);	rotY.m[1][2] = 0;	rotY.m[2][2] = cos(r.Y);	rotY.m[3][2] = 0;
	rotY.m[0][3] = 0;			rotY.m[1][3] = 0;	rotY.m[2][3] = 0;			rotY.m[3][3] = 1;

	rotZ.m[0][0] = cos(r.Z);	rotZ.m[1][0] = -sin(r.Z);	rotZ.m[2][0] = 0;	rotZ.m[3][0] = 0;
	rotZ.m[0][1] = sin(r.Z);	rotZ.m[1][1] = cos(r.Z);	rotZ.m[2][1] = 0;	rotZ.m[3][1] = 0;
	rotZ.m[0][2] = 0;			rotZ.m[1][2] = 0;			rotZ.m[2][2] = 1;	rotZ.m[3][2] = 0;
	rotZ.m[0][3] = 0;			rotZ.m[1][3] = 0;			rotZ.m[2][3] = 0;	rotZ.m[3][3] = 1;

	*this = *this * rotY * rotZ;

	return *this;
}

const Matrix& Matrix::Scale(const Vec4& v){
	m[0][0] = v.X;	m[1][0] = 0;	m[2][0] = 0;	m[3][0] = 0;
	m[0][1] = 0;	m[1][1] = v.Y;	m[2][1] = 0;	m[3][1] = 0;
	m[0][2] = 0;	m[1][2] = 0;	m[2][2] = v.Z;	m[3][2] = 0;
	m[0][3] = 0;	m[1][3] = 0;	m[2][3] = 0;	m[3][3] = 1;

	return *this;
}

const Matrix& Matrix::Perspective(float fov, float aspectRatio, float zNear, float zFar){
	float tanHalfFov = tan(util::to_radians(fov / 2));
	float zRange = zFar - zNear;

	m[0][0] = 1.0f / tanHalfFov;	m[1][0] = 0;								m[2][0] = 0;						m[3][0] = 0;
	m[0][1] = 0;					m[1][1] = 1.0f / tanHalfFov * aspectRatio;	m[2][1] = 0;						m[3][1] = 0;
	m[0][2] = 0;					m[1][2] = 0;								m[2][2] = -(zNear + zFar) / zRange;	m[3][2] = -2.0f * zNear * zFar / zRange;
	m[0][3] = 0;					m[1][3] = 0;								m[2][3] = -1;						m[3][3] = 0;

	return *this;
}

const Matrix& Matrix::ScreenSpaceTransform(int width, int height){
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	m[0][0] = halfWidth;	m[1][0] = 0;			m[2][0] = 0;	m[3][0] = halfWidth - 0.5f;
	m[0][1] = 0;			m[1][1] = -halfHeight;	m[2][1] = 0;	m[3][1] = halfHeight - 0.5f;
	m[0][2] = 0;			m[1][2] = 0;			m[2][2] = 1;	m[3][2] = 0;
	m[0][3] = 0;			m[1][3] = 0;			m[2][3] = 0;	m[3][3] = 1;

	return *this;
}

Vec4 Matrix::Transform(const Vec4& v) const{
	return Vec4(m[0][0] * v.X + m[1][0] * v.Y + m[2][0] * v.Z + m[3][0] * v.W,
				m[0][1] * v.X + m[1][1] * v.Y + m[2][1] * v.Z + m[3][1] * v.W,
				m[0][2] * v.X + m[1][2] * v.Y + m[2][2] * v.Z + m[3][2] * v.W,
				m[0][3] * v.X + m[1][3] * v.Y + m[2][3] * v.Z + m[3][3] * v.W);
}

Vec3 Matrix::Transform(const Vec3& v) const{
	return Vec3(m[0][0] * v.X + m[1][0] * v.Y + m[2][0] * v.Z,
				m[0][1] * v.X + m[1][1] * v.Y + m[2][1] * v.Z,
				m[0][2] * v.X + m[1][2] * v.Y + m[2][2] * v.Z);
}

Matrix Matrix::operator*(const Matrix& other) const{
	Matrix result;

	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			result.m[i][j] = m[0][j] * other.m[i][0] +
							 m[1][j] * other.m[i][1] +
							 m[2][j] * other.m[i][2] +
							 m[3][j] * other.m[i][3];
		}
	}

	return result;
}