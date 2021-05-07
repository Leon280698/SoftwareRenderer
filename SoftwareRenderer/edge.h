#pragma once

#include "vertex.h"

class Edge{
public:
	Edge(const Vertex& minY, const Vertex& maxY){
		Vec4& pos1 = minY.getPosition();
		Vec4& pos2 = maxY.getPosition();

		yStart = static_cast<int>(ceil(pos1.Y));
		yEnd = static_cast<int>(ceil(pos2.Y));

		float dy = pos2.Y - pos1.Y;

		float yPrestep = yStart - pos1.Y;
		xStep = (pos2.X - pos1.X) / dy;
		currentXPos = pos1.X + yPrestep * xStep;

		depthStep = (pos2.Z - pos1.Z) / dy;
		currentDepth = pos1.Z + yPrestep * depthStep;		//don't need to divide by W as this is done in Vertex::PerspectiveDivide

		zStep = (1.0f / pos2.W - 1.0f / pos1.W) / dy;
		currentZ = 1.0f / pos1.W + yPrestep * zStep;

		texCoordsStep = (maxY.getTextureCoordinates() / pos2.W - minY.getTextureCoordinates() / pos1.W) / dy;
		currentTexCoords = minY.getTextureCoordinates() / pos1.W + texCoordsStep * yPrestep;

		normalStep = (maxY.getNormal() - minY.getNormal()) / dy;
		currentNormal = minY.getNormal() + normalStep * yPrestep;

		worldPosStep = (maxY.getWorldPosition() / pos2.W - minY.getWorldPosition() / pos1.W) / dy;
		currentWorldPos = minY.getWorldPosition() / pos1.W + worldPosStep * yPrestep;

		colorStep = (maxY.getColor() - minY.getColor()) / dy;
		currentColor = minY.getColor() + colorStep * yPrestep;
	}

	void Step();
	int getYStart() const;
	int getYEnd() const;
	int getCurrentXPos() const;
	float getCurrentZ() const;
	float getCurrentDepth() const;
	Vec2 getCurrentTextureCoordinates() const;
	Vec3 getCurrentNormal() const;
	Vec4 getCurrentWorldPos() const;
	Color getCurrentColor() const;

private:
	int yStart, yEnd;
	float currentXPos, xStep;
	float currentZ, zStep;	//Z value for perspective
	float currentDepth, depthStep;	//Z value for occlusion
	Vec2 currentTexCoords, texCoordsStep;
	Vec3 currentNormal, normalStep;
	Vec4 currentWorldPos, worldPosStep;
	Color currentColor, colorStep;
};