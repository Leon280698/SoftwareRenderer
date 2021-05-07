#include "vector.h"

//vec2

float Vec2::Length() const{
	return sqrt(X * X + Y * Y);
}

float Vec2::LengthSq() const{
	return X * X + Y * Y;
}

Vec2 Vec2::Normalize() const{
	float length = Length();

	return Vec2(X / length, Y / length);
}

float Vec2::Dot(const Vec2& other) const{
	return X * other.X + Y * other.Y;
}

Vec2 Vec2::Lerp(const Vec2& other, float lerpFactor) const{
	return *this + (other - *this) * lerpFactor;
}

Vec2 Vec2::operator+(const Vec2& other) const{
	return Vec2(X + other.X, Y + other.Y);
}

Vec2 Vec2::operator-(const Vec2& other) const{
	return Vec2(X - other.X, Y - other.Y);
}

Vec2 Vec2::operator*(float f) const{
	return Vec2(X * f, Y * f);
}

Vec2 Vec2::operator/(float f) const{
	return Vec2(X / f, Y / f);
}

void Vec2::operator+=(const Vec2& other){
	X += other.X;
	Y += other.Y;
}

void Vec2::operator-=(const Vec2& other){
	X -= other.X;
	Y -= other.Y;
}

void Vec2::operator*=(float f){
	X *= f;
	Y *= f;
}

void Vec2::operator/=(float f){
	X /= f;
	Y /= f;
}

//vec3

float Vec3::Length() const{
	return sqrt(X * X + Y * Y + Z * Z);
}

float Vec3::LengthSq() const{
	return X * X + Y * Y + Z * Z;
}

Vec3 Vec3::Normalize() const{
	float length = Length();

	return Vec3(X / length, Y / length, Z / length);
}

float Vec3::Dot(const Vec3& other) const{
	return X * other.X + Y * other.Y + Z * other.Z;
}

Vec3 Vec3::Cross(const Vec3& other) const{
	return Vec3(Y * other.Z - Z * other.Y,
				Z * other.X - X * other.Z,
				X * other.Y - Y * other.X);
}

Vec3 Vec3::Lerp(const Vec3& other, float lerpFactor) const{
	return *this + (other - *this) * lerpFactor;
}

Vec3 Vec3::operator+(const Vec3& other) const{
	return Vec3(X + other.X, Y + other.Y, Z + other.Z);
}

Vec3 Vec3::operator-(const Vec3& other) const{
	return Vec3(X - other.X, Y - other.Y, Z - other.Z);
}

Vec3 Vec3::operator*(float f) const{
	return Vec3(X * f, Y * f, Z * f);
}

Vec3 Vec3::operator/(float f) const{
	return Vec3(X / f, Y / f, Z / f);
}

void Vec3::operator+=(const Vec3& other){
	X += other.X;
	Y += other.Y;
	Z += other.Z;
}

void Vec3::operator-=(const Vec3& other){
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
}

void Vec3::operator*=(float f){
	X *= f;
	Y *= f;
	Z *= f;
}

void Vec3::operator/=(float f){
	X /= f;
	Y /= f;
	Z /= f;
}

//vec4

float Vec4::Length() const{
	return sqrt(X * X + Y * Y + Z * Z);
}

float Vec4::LengthSq() const{
	return X * X + Y * Y + Z * Z;
}

Vec4 Vec4::Normalize() const{
	float length = Length();

	return Vec4(X / length, Y / length, Z / length);
}

float Vec4::Dot(const Vec4& other) const{
	return X * other.X + Y * other.Y + Z * other.Z;
}

Vec4 Vec4::Cross(const Vec4& other) const{
	return Vec4(Y * other.Z - Z * other.Y,
				Z * other.X - X * other.Z,
				X * other.Y - Y * other.X);
}

Vec4 Vec4::Lerp(const Vec4& other, float lerpFactor) const{
	return *this + (other - *this) * lerpFactor;
}

Vec4 Vec4::operator+(const Vec4& other) const{
	return Vec4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

Vec4 Vec4::operator-(const Vec4& other) const{
	return Vec4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

Vec4 Vec4::operator*(float f) const{
	return Vec4(X * f, Y * f, Z * f, W * f);
}

Vec4 Vec4::operator/(float f) const{
	return Vec4(X / f, Y / f, Z / f, W / f);
}

void Vec4::operator+=(const Vec4& other){
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	W += other.W;
}

void Vec4::operator-=(const Vec4& other){
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	W -= other.W;
}

void Vec4::operator*=(float f){
	X *= f;
	Y *= f;
	Z *= f;
	W *= f;
}

void Vec4::operator/=(float f){
	X /= f;
	Y /= f;
	Z /= f;
	W /= f;
}