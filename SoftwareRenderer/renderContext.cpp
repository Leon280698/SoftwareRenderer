#include "renderContext.h"

void RenderContext::DrawPixel(int x, int y, const Color& c){
	static_cast<Uint32*>(frameBuffer->pixels)[x + y * frameBuffer->w] = c.ToUint32();
}

void RenderContext::DrawLine(int x1, int y1, int x2, int y2, const Color& c){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int xStep = 1;
	int yStep = 1;

	if(dx < 0){
		dx = -dx;
		xStep = -xStep;
	}

	if(dy < 0){
		dy = -dy;
		yStep = -yStep;
	}

	dx <<= 1;
	dy <<= 1;

	if(dx >= dy){
		int err = dx >> 1;

		while(x1 != x2){
			DrawPixel(x1, y1, c);
			err -= dy;

			if(err < 0){
				err += dx;
				y1 += yStep;
			}

			x1 += xStep;
		}
	}else{
		int err = dy >> 1;

		while(y1 != y2){
			DrawPixel(x1, y1, c);
			err -= dx;

			if(err < 0){
				err += dy;
				x1 += xStep;
			}

			y1 += yStep;
		}
	}

	DrawPixel(x2, y2, c);
}

void RenderContext::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, ShaderType shaderType,
								 const LightInfo* lightInfo, const SDL_Surface* texture){
	shaders[shaderType]->setLightInfo(lightInfo);

	if(shaderType == SHADER_TEXTURED)
		static_cast<Shader_Textured*>(shaders[shaderType])->setTexture(texture);

	if(v1.IsInsideViewingFrustum() && v2.IsInsideViewingFrustum() && v3.IsInsideViewingFrustum()){
		FillTriangle(v1, v2, v3, shaderType);

		return;
	}

	std::vector<Vertex> vertices(3);
	std::vector<Vertex> auxillaryList;

	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	auxillaryList.reserve(4);

	if(ClipPolygonAxis(vertices, auxillaryList, 0) && ClipPolygonAxis(vertices, auxillaryList, 1) && ClipPolygonAxis(vertices, auxillaryList, 2)){
		const Vertex& initialVertex = vertices[0];

		for(int i = 1; i < vertices.size() - 1; i++){
			FillTriangle(initialVertex, vertices[i], vertices[i + 1], shaderType);
		}
	}
}

void RenderContext::FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, ShaderType shaderType){
	Vertex& minY = v1.Transform(screenSpaceTransform).PerspectiveDivide();
	Vertex& midY = v2.Transform(screenSpaceTransform).PerspectiveDivide();
	Vertex& maxY = v3.Transform(screenSpaceTransform).PerspectiveDivide();

	if(TriangleOrientation(minY, midY, maxY))	//backface culling
		return;

	if(minY.getPosition().Y > midY.getPosition().Y){	//sort vertices by their Y-position
		Vertex temp = minY;
		minY = midY;
		midY = temp;
	}

	if(midY.getPosition().Y > maxY.getPosition().Y){
		Vertex temp = midY;
		midY = maxY;
		maxY = temp;
	}

	if(minY.getPosition().Y > midY.getPosition().Y){
		Vertex temp = minY;
		minY = midY;
		midY = temp;
	}

	ScanTriangle(minY, midY, maxY, shaderType);
}

void RenderContext::ScanTriangle(const Vertex& minY, const Vertex& midY, const Vertex& maxY, ShaderType shaderType){
	Edge topToBottom(minY, maxY);
	Edge topToMiddle(minY, midY);
	Edge middleToBottom(midY, maxY);

	if(TriangleOrientation(minY, midY, maxY)){
		shaders[shaderType]->ScanEdges(topToBottom, topToMiddle,
									   topToMiddle.getYStart(), topToMiddle.getYEnd());
		shaders[shaderType]->ScanEdges(topToBottom, middleToBottom,
									   middleToBottom.getYStart(), middleToBottom.getYEnd());
	}else{
		shaders[shaderType]->ScanEdges(topToMiddle, topToBottom,
									   topToMiddle.getYStart(), topToMiddle.getYEnd());
		shaders[shaderType]->ScanEdges(middleToBottom, topToBottom,
									   middleToBottom.getYStart(), middleToBottom.getYEnd());
	}
}

bool RenderContext::ClipPolygonAxis(std::vector<Vertex>& vertices, std::vector<Vertex>& auxillaryList, int componentIndex){
	ClipPolygonComponent(vertices, componentIndex, 1.0f, auxillaryList);
	vertices.clear();

	if(auxillaryList.empty())
		return false;

	ClipPolygonComponent(auxillaryList, componentIndex, -1.0f, vertices);
	auxillaryList.clear();

	return !vertices.empty();
}

void RenderContext::ClipPolygonComponent(std::vector<Vertex>& vertices, int componentIndex, float componentFactor, std::vector<Vertex>& result){
	Vertex previousVertex = vertices[vertices.size() - 1];
	float previousComponent = previousVertex.getPosition(componentIndex) * componentFactor;
	bool previousInside = previousComponent <= previousVertex.getPosition().W;

	for(int i = 0; i < vertices.size(); i++){
		Vertex currentVertex = vertices[i];
		float currentComponent = currentVertex.getPosition(componentIndex) * componentFactor;
		bool currentInside = currentComponent <= currentVertex.getPosition().W;

		if(currentInside ^ previousInside){
			float lerpAmount = (previousVertex.getPosition().W - previousComponent) /
				((previousVertex.getPosition().W - previousComponent) - (currentVertex.getPosition().W - currentComponent));

			result.push_back(previousVertex.Lerp(currentVertex, lerpAmount));
		}

		if(currentInside)
			result.push_back(currentVertex);

		previousVertex = currentVertex;
		previousComponent = currentComponent;
		previousInside = currentInside;
	}
}

void RenderContext::Clear(Uint32 c){
	SDL_FillRect(frameBuffer, nullptr, c);
}

void RenderContext::ClearZBuffer(){
	std::fill(zBuffer.begin(), zBuffer.end(), 1.0f);
}

bool RenderContext::TriangleOrientation(const Vertex& v1, const Vertex& v2, const Vertex& v3) const{
	Vec4 p1 = v1.getPosition();
	Vec4 p2 = v2.getPosition();
	Vec4 p3 = v3.getPosition();

	return p1.X * p2.Y - p2.X * p1.Y +
		   p2.X * p3.Y - p3.X * p2.Y +
		   p3.X * p1.Y - p1.X * p3.Y >= 0.0f;
}

int RenderContext::getWidth() const{
	return width;
}

int RenderContext::getHeight() const{
	return height;
}