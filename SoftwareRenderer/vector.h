#pragma once

#include <cmath>

class Vec2{
public:
	float X, Y;

	Vec2(float x = 0.0f, float y = 0.0f){
		X = x;
		Y = y;
	}

	float Length() const;
	float LengthSq() const;
	Vec2 Normalize() const;
	float Dot(const Vec2& other) const;
	Vec2 Lerp(const Vec2& other, float lerpFactor) const;
	Vec2 operator+(const Vec2& other) const;
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator*(float f) const;
	Vec2 operator/(float f) const;
	void operator+=(const Vec2& other);
	void operator-=(const Vec2& other);
	void operator*=(float f);
	void operator/=(float f);
};

class Vec3{
public:
	float X, Y, Z;

	Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f){
		X = x;
		Y = y;
		Z = z;
	}

	float Length() const;
	float LengthSq() const;
	Vec3 Normalize() const;
	float Dot(const Vec3& other) const;
	Vec3 Cross(const Vec3& other) const;
	Vec3 Lerp(const Vec3& other, float lerpFactor) const;
	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(float f) const;
	Vec3 operator/(float f) const;
	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);
	void operator*=(float f);
	void operator/=(float f);
};

class Vec4{
public:
	float X, Y, Z, W;

	Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f){
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Vec4(const Vec3& v){
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = 0.0f;
	}

	float Length() const;
	float LengthSq() const;
	Vec4 Normalize() const;
	float Dot(const Vec4& other) const;
	Vec4 Cross(const Vec4& other) const;
	Vec4 Lerp(const Vec4& other, float lerpFactor) const;
	Vec4 operator+(const Vec4& other) const;
	Vec4 operator-(const Vec4& other) const;
	Vec4 operator*(float f) const;
	Vec4 operator/(float f) const;
	void operator+=(const Vec4& other);
	void operator-=(const Vec4& other);
	void operator*=(float f);
	void operator/=(float f);
};

typedef Vec3 Rotator;