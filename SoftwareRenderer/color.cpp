#include "color.h"

Uint32 Color::ToUint32() const{
	return static_cast<Uint8>(R * 255.0f) << 16 |
		   static_cast<Uint8>(G * 255.0f) << 8 |
		   static_cast<Uint8>(B * 255.0f);
}

Color Color::Lerp(const Color& other, float lerpFactor) const{
	return *this + (other - *this) * lerpFactor;
}

const Color& Color::Clamp(){
	R = util::clamp(R);
	G = util::clamp(G);
	B = util::clamp(B);

	return *this;
}

Color Color::operator+(const Color& other) const{
	return Color(R + other.R, G + other.G, B + other.B);
}

Color Color::operator-(const Color& other) const{
	return Color(R - other.R, G - other.G, B - other.B);
}

Color Color::operator*(const Color& other) const{
	return Color(R * other.R, G * other.G, B * other.B);
}

Color Color::operator*(float f) const{
	return Color(R * f, G * f, B * f);
}

Color Color::operator/(const Color& other) const{
	return Color(R / other.R, G / other.G, B / other.B);
}

Color Color::operator/(float f) const{
	return Color(R / f, G / f, B / f);
}

void Color::operator+=(const Color& other){
	R += other.R;
	G += other.G;
	B += other.B;
}

void Color::operator-=(const Color& other){
	R -= other.R;
	G -= other.G;
	B -= other.B;
}

void Color::operator*=(const Color& other){
	R *= other.R;
	G *= other.G;
	B *= other.B;
}

void Color::operator*=(float f){
	R *= f;
	G *= f;
	B *= f;
}

void Color::operator/=(const Color& other){
	R /= other.R;
	G /= other.G;
	B /= other.B;
}

void Color::operator/=(float f){
	R /= f;
	G /= f;
	B /= f;
}