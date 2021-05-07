#pragma once

#include <SDL_stdinc.h>
#include "vector.h"
#include "utility.h"

enum EColor : Uint32{
	COL_BLACK = 0xFF000000,
	COL_WHITE = 0xFFFFFFFF,
	COL_RED = 0xFFFF0000,
	COL_GREEN = 0xFF00FF00,
	COL_BLUE = 0xFF0000FF,
	COL_YELLOW = 0xFFFFFF00,
	COL_MAGENTA = 0xFFFF00FF,
	COL_CYAN = 0xFF00FFFF
};

class Color{
public:
	float R, G, B;

	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f){
		R = r;
		G = g;
		B = b;
	}

	Color(Uint32 c){
		R = static_cast<Uint8>(c >> 16) / 255.0f;
		G = static_cast<Uint8>(c >> 8) / 255.0f;
		B = static_cast<Uint8>(c) / 255.0f;
	}

	Color(const Vec3& v){
		R = v.X;
		G = v.Y;
		B = v.Z;
	}

	Color(const Vec4& v){
		R = v.X;
		G = v.Y;
		B = v.Z;
	}

	Uint32 ToUint32() const;
	Color Lerp(const Color& other, float lerpFactor) const;
	const Color& Clamp();
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator*(float f) const;
	Color operator/(const Color& other) const;
	Color operator/(float f) const;
	void operator+=(const Color& other);
	void operator-=(const Color& other);
	void operator*=(const Color& other);
	void operator*=(float f);
	void operator/=(const Color& other);
	void operator/=(float f);
};