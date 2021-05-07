#include "edge.h"

void Edge::Step(){
	currentXPos += xStep;
	currentZ += zStep;
	currentDepth += depthStep;
	currentTexCoords += texCoordsStep;
	currentWorldPos += worldPosStep;
	currentNormal += normalStep;
	currentColor += colorStep;
}

int Edge::getYStart() const{
	return yStart;
}

int Edge::getYEnd() const{
	return yEnd;
}

int Edge::getCurrentXPos() const{
	return static_cast<int>(ceil(currentXPos));
}

float Edge::getCurrentZ() const{
	return currentZ;
}

float Edge::getCurrentDepth() const{
	return currentDepth;
}

Vec2 Edge::getCurrentTextureCoordinates() const{
	return currentTexCoords;
}

Vec3 Edge::getCurrentNormal() const{
	return currentNormal;
}

Vec4 Edge::getCurrentWorldPos() const{
	return currentWorldPos;
}

Color Edge::getCurrentColor() const{
	return currentColor;
}