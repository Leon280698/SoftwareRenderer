#include "light.h"

//DirectionalLight;

Vec3 DirectionalLight::getDirection() const{
	return direction;
}

void DirectionalLight::setDirection(const Vec3& v){
	direction = v;
}

float DirectionalLight::getBrightness() const{
	return brightness;
}

void DirectionalLight::setBrightness(float f){
	brightness = f;
}

Color DirectionalLight::getColor() const{
	return color;
}

void DirectionalLight::setColor(const Color& c){
	color = c;
}

//PointLight

Vec4 PointLight::getPosition() const{
	return position;
}

void PointLight::setPosition(const Vec4& v){
	position = v;
}

float PointLight::getRadius() const{
	return radius;
}

void PointLight::setRadius(float f){
	radius = f;
}

float PointLight::getBrightness() const{
	return brightness;
}

void PointLight::setBrightness(float f){
	brightness = f;
}

Color PointLight::getColor() const{
	return color;
}

void PointLight::setColor(const Color& c){
	color = c;
}