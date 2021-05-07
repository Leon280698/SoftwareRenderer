#pragma once

#include "shader.h"

#define NUM_SHADERS 3	//number of available shaders (shader.h -> ShaderTypes)
#define NUM_THREADS 4

class RenderContext{
public:
	RenderContext(SDL_Surface* frameBuffer){
		this->frameBuffer = frameBuffer;
		width = frameBuffer->w;
		height = frameBuffer->h;
		screenSpaceTransform = Matrix().ScreenSpaceTransform(width, height);
		zBuffer.resize(width * height);

		shaders[SHADER_DEFAULT] = new Shader(frameBuffer, &zBuffer);
		shaders[SHADER_VERTEXCOLORS] = new Shader_VertexColors(frameBuffer, &zBuffer);
		shaders[SHADER_TEXTURED] = new Shader_Textured(frameBuffer, &zBuffer);
	}

	~RenderContext(){
		for(int i = 0; i < NUM_SHADERS; i++)
			delete shaders[i];
	}

	void DrawPixel(int x, int y, const Color& c = Color());
	void DrawLine(int x1, int y1, int x2, int y2, const Color& c = Color());
	void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, ShaderType shaderType = SHADER_DEFAULT,
					  const LightInfo* lightInfo = nullptr, const SDL_Surface* texture = nullptr);
	void Clear(Uint32 c = COL_BLACK);
	void ClearZBuffer();
	int getWidth() const;
	int getHeight() const;

private:
	SDL_Surface* frameBuffer;
	Matrix screenSpaceTransform;
	std::vector<float> zBuffer;
	Shader* shaders[NUM_SHADERS];
	int width, height;

	void FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, ShaderType shaderType);
	void ScanTriangle(const Vertex& minY, const Vertex& midY, const Vertex& maxY, ShaderType shaderType);
	bool ClipPolygonAxis(std::vector<Vertex>& vertices, std::vector<Vertex>& auxillaryList, int componentIndex);
	void ClipPolygonComponent(std::vector<Vertex>& vertices, int componentIndex, float componentFactor, std::vector<Vertex>& result);
	bool TriangleOrientation(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
};