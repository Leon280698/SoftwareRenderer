#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_image.h>
#include "renderContext.h"

class Mesh{
public:
	Mesh(const std::string& fileName, ShaderType shaderType, const std::string& textureFile = ""){
		Uint32 startTime = SDL_GetTicks();

		this->shaderType = shaderType;

		if(textureFile != "")
			texture = IMG_Load(textureFile.c_str());

		if(LoadMeshPLY(fileName))
			std::cout << "Mesh '" << fileName << "' loaded in " << (SDL_GetTicks() - startTime) / 1000.0f <<
						 " seconds! " << vertices.size() << " verts  " << triangles.size() / 3 << " tris" << std::endl;
		else
			std::cerr << "ERROR: Could not load file '" << fileName << "'!" << std::endl;
	}

	void Draw(RenderContext& target, const Matrix& viewProjection, const LightInfo* lightInfo) const;
	Vec4 getPosition() const;
	void setPosition(const Vec4& v);
	Rotator getRotation() const;
	void setRotation(const Rotator& r);

private:
	std::vector<Vertex> vertices;
	std::vector<int> triangles;
	const SDL_Surface* texture;
	Vec4 position;
	Rotator rotation;
	ShaderType shaderType;

	bool LoadMeshPLY(const std::string& fileName);
};