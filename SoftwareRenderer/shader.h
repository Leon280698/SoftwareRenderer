#pragma once

#include <vector>
#include <SDL.h>
#include "edge.h"
#include "light.h"

enum ShaderType{
	SHADER_DEFAULT,
	SHADER_VERTEXCOLORS,
	SHADER_TEXTURED
};

#define X_INTEROPLANT int xStart = left.getCurrentXPos(); int xEnd = right.getCurrentXPos();
#define Z_INTERPOLANT float zStart = left.getCurrentZ(); float zEnd = right.getCurrentZ();
#define DEPTH_INTERPOLANT float depthStart = left.getCurrentDepth(); float depthEnd = right.getCurrentDepth();
#define TEX_COORD_INTERPOLANT Vec2& textureCoordinatesStart = left.getCurrentTextureCoordinates(); Vec2& textureCoordinatesEnd = right.getCurrentTextureCoordinates();
#define NORMAL_INTERPOLANT Vec3& normalStart = left.getCurrentNormal(); Vec3& normalEnd = right.getCurrentNormal();
#define POS_INTERPOLANT Vec4& posStart = left.getCurrentWorldPos(); Vec4& posEnd = right.getCurrentWorldPos();
#define COLOR_INTERPOLANT Color& colorStart = left.getCurrentColor(); Color& colorEnd = right.getCurrentColor();
#define LIGHTING_COMPUTATION	Color lightColor = lightInfo->color * lightInfo->brightness;	\
								Vec3 normal = normalStart.Lerp(normalEnd, lerpFactor);	\
								for(int i = 0; i < lightInfo->directionalLights->size(); i++){	\
									DirectionalLight& light = *(*lightInfo->directionalLights)[i];	\
									lightColor += light.getColor() *	\
									util::clamp((normalStart.Lerp(normalEnd, lerpFactor)).Dot(	\
									light.getDirection()) * light.getBrightness());	\
								}	\
								Vec4 pos = posStart.Lerp(posEnd, lerpFactor) * z;	\
								for(int i = 0; i < lightInfo->pointLights->size(); i++){	\
									PointLight& light = *(*lightInfo->pointLights)[i];	\
									Vec4 diff = pos - light.getPosition();	\
									float dist = diff.Length();	\
									float radius = light.getRadius();	\
																		\
									if(dist <= radius)	\
										lightColor += light.getColor() * util::clamp(((diff.Normalize()).Dot(normal) * (1.0f - radius / dist)) * light.getBrightness());	\
								}

class Shader{
public:
	Shader(SDL_Surface* frameBuffer, std::vector<float>* zBuffer){
		this->frameBuffer = frameBuffer;
		this->zBuffer = zBuffer;
	}

	void ScanEdges(Edge& left, Edge& right, int yStart, int yEnd) const{
		for(int y = yStart; y < yEnd; y++){
			DrawScanLine(left, right, y);
			left.Step();
			right.Step();
		}
	}

	void setLightInfo(const LightInfo* lightInfo){
		this->lightInfo = lightInfo;
	}

protected:
	virtual void DrawScanLine(const Edge& left, const Edge& right, int y) const{
		X_INTEROPLANT
		Z_INTERPOLANT
		DEPTH_INTERPOLANT
		NORMAL_INTERPOLANT
		POS_INTERPOLANT

		float lerpFactor = 0.0f;
		float lerpStep = 1.0f / (xEnd - xStart);

		Uint32* p = &static_cast<Uint32*>(frameBuffer->pixels)[xStart + y * frameBuffer->w];
		float* zIndex = &(*zBuffer)[xStart + y * frameBuffer->w];
		for(int x = xStart; x < xEnd; x++){
			float depth = util::lerp(depthStart, depthEnd, lerpFactor);

			if(depth < *zIndex){
				*zIndex = depth;

				float z = 1.0f / util::lerp(zStart, zEnd, lerpFactor);
				
				LIGHTING_COMPUTATION

					*p = lightColor.Clamp().ToUint32();
			}
			
			p++;
			zIndex++;
			lerpFactor += lerpStep;
		}
	}

	SDL_Surface* frameBuffer;
	std::vector<float>* zBuffer;
	const LightInfo* lightInfo;
};

class Shader_VertexColors : public Shader{
public:
	using Shader::Shader;

	void DrawScanLine(const Edge& left, const Edge& right, int y) const override{
		X_INTEROPLANT
		Z_INTERPOLANT
		DEPTH_INTERPOLANT
		POS_INTERPOLANT
		COLOR_INTERPOLANT
		NORMAL_INTERPOLANT
		

		float lerpFactor = 0.0f;
		float lerpStep = 1.0f / (xEnd - xStart);
		
		Uint32* p = &static_cast<Uint32*>(frameBuffer->pixels)[xStart + y * frameBuffer->w];
		float* zIndex = &(*zBuffer)[xStart + y * frameBuffer->w];
		for(int x = xStart; x < xEnd; x++){
			float depth = util::lerp(depthStart, depthEnd, lerpFactor);

			if(depth < *zIndex){
				*zIndex = depth;

				float z = 1.0f / util::lerp(zStart, zEnd, lerpFactor);
				LIGHTING_COMPUTATION

				*p = (colorStart.Lerp(colorEnd, lerpFactor) * lightColor).Clamp().ToUint32();
			}

			p++;
			zIndex++;
			lerpFactor += lerpStep;
		}
	}
};

class Shader_Textured : public Shader{
public:
	using Shader::Shader;

	void DrawScanLine(const Edge& left, const Edge& right, int y) const override{
		X_INTEROPLANT
		Z_INTERPOLANT
		DEPTH_INTERPOLANT
		POS_INTERPOLANT
		TEX_COORD_INTERPOLANT
		NORMAL_INTERPOLANT

		float lerpFactor = 0.0f;
		float lerpStep = 1.0f / (xEnd - xStart);

		Uint32* p = &static_cast<Uint32*>(frameBuffer->pixels)[xStart + y * frameBuffer->w];
		float* zIndex = &(*zBuffer)[xStart + y * frameBuffer->w];
		for(int x = xStart; x < xEnd; x++){
			float depth = util::lerp(depthStart, depthEnd, lerpFactor);

			if(depth < *zIndex){
				*zIndex = depth;

				float z = 1.0f / util::lerp(zStart, zEnd, lerpFactor);
				LIGHTING_COMPUTATION

				Vec2 texCoords = textureCoordinatesStart.Lerp(textureCoordinatesEnd, lerpFactor) * z;

				*p = (Color(util::get_pixel(texture, static_cast<int>(texCoords.X * texture->w),
													 static_cast<int>(texCoords.Y * texture->h))) * lightColor).Clamp().ToUint32();
			}

			zIndex++;
			p++;
			lerpFactor += lerpStep;
		}
	}

	void setTexture(const SDL_Surface* texture){
		this->texture = texture;
	}

private:
	const SDL_Surface* texture;
};