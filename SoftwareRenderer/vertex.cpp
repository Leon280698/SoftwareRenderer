#include "vertex.h"

Vertex Vertex::Transform(const Matrix& transform, const Matrix& normalTransform) const{
	return Vertex(transform.Transform(position), normalTransform.Transform(normal), textureCoordinates, color, normalTransform.Transform(worldPosition));
}

Vertex Vertex::Lerp(const Vertex& other, float lerpFactor) const{
	return Vertex(position.Lerp(other.position, lerpFactor),
				  normal.Lerp(other.normal, lerpFactor),
				  textureCoordinates.Lerp(other.textureCoordinates,lerpFactor),
				  color.Lerp(other.color, lerpFactor),
				  worldPosition.Lerp(other.worldPosition, lerpFactor));
}

Vertex& Vertex::PerspectiveDivide(){
	position.X /= position.W;
	position.Y /= position.W;
	position.Z /= position.W;

	return *this;
}

bool Vertex::IsInsideViewingFrustum() const{
	float W = abs(position.W);

	return abs(position.X) <= W && abs(position.Y) <= W && abs(position.Z) <= W;
}

Vec4 Vertex::getPosition() const{
	return position;
}

float Vertex::getPosition(int index) const{
	switch(index){
		case 0:
			return position.X;
		case 1:
			return position.Y;
		case 2:
			return position.Z;
	}
}

void Vertex::setPosition(const Vec4& v){
	position = v;
	worldPosition = v;
}

Vec3 Vertex::getNormal() const{
	return normal;
}

void Vertex::setNormal(const Vec3& v){
	normal = v;
}

Vec2 Vertex::getTextureCoordinates() const{
	return textureCoordinates;
}

void Vertex::setTextureCoordinates(const Vec2& v){
	textureCoordinates = v;
}

Color Vertex::getColor() const{
	return color;
}

void Vertex::setColor(const Color& c){
	color = c;
}

Vec4 Vertex::getWorldPosition() const{
	return worldPosition;
}