#pragma once

#include <vector>
#include "color.h"
#include "matrix.h"

class DirectionalLight{
public:
	DirectionalLight(const Vec3& direction, float brightness = 1.0f, const Color& color = Color()){
		this->direction = direction.Normalize();
		this->brightness = brightness;
		this->color = color;
	}

	Vec3 getDirection() const;
	void setDirection(const Vec3& v);
	float getBrightness() const;
	void setBrightness(float f);
	Color getColor() const;
	void setColor(const Color& c);

private:
	Vec3 direction;
	float brightness;
	Color color;
};

class PointLight{
public:
	PointLight(const Vec4& position, float radius, const Color& color = Color(), float brightness = 1.0f){
		this->position = position;
		this->radius = radius;
		this->color = color;
		this->brightness = brightness;
	}

	Vec4 getPosition() const;
	void setPosition(const Vec4& v);
	float getRadius() const;
	void setRadius(float f);
	float getBrightness() const;
	void setBrightness(float f);
	Color getColor() const;
	void setColor(const Color& c);

private:
	Vec4 position;
	float radius, brightness;
	Color color;
};

struct LightInfo{
	float brightness;
	Color color;
	std::vector<DirectionalLight*>* directionalLights;
	std::vector<PointLight*>* pointLights;
};