#pragma once

#include "matrix.h"
#include "color.h"

class Vertex{
public:
	Vertex(const Vec4& position = Vec4(), const Vec3& normal = Vec3(),
		   const Vec2& textureCoordinates = Vec2(), const Color& color = Color(),
		   const Vec4& worldPosition = Vec4()){
		this->position = position;
		this->normal = normal;
		this->textureCoordinates = textureCoordinates;
		this->color = color;
		this->worldPosition = worldPosition;
	}

	Vertex Transform(const Matrix& transform, const Matrix& normalTransform = Matrix().Identity()) const;
	Vertex Lerp(const Vertex& other, float lerpFactor) const;
	Vertex& PerspectiveDivide();
	bool IsInsideViewingFrustum() const;
	Vec4 getPosition() const;
	float getPosition(int index) const;
	void setPosition(const Vec4& v);
	Vec3 getNormal() const;
	void setNormal(const Vec3& v);
	Vec2 getTextureCoordinates() const;
	void setTextureCoordinates(const Vec2& v);
	Color getColor() const;
	void setColor(const Color& c);
	Vec4 getWorldPosition() const;

private:
	Vec4 position, worldPosition;
	Vec3 normal;
	Vec2 textureCoordinates;
	Color color;
};