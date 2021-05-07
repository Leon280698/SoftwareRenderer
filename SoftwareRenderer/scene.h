#pragma once

#include "camera.h"
#include "mesh.h"
#include "light.h"

class Scene{
public:
	Scene(Camera& camera, float ambientBrightness = 1.0f, const Color& ambientColor = Color()) : camera(camera){
		lightInfo.brightness = ambientBrightness;
		lightInfo.color = ambientColor;
		lightInfo.directionalLights = &directionalLights;
		lightInfo.pointLights = &pointLights;
	}

	void Draw(RenderContext& target) const;
	void Update(float deltaTime);
	void AddMesh(Mesh& mesh);
	void RemoveMesh(int index);
	void AddDirectionalLight(DirectionalLight& directionalLight);
	void RemoveDirectionalLight(int index);
	void AddPointLight(PointLight& pointLight);
	void RemovePointLight(int index);

private:
	LightInfo lightInfo;
	std::vector<Mesh*> meshes;
	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	Camera& camera;
};