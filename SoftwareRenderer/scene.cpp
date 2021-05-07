#include "scene.h"

void Scene::Draw(RenderContext& target) const{
	for(int i = 0; i < meshes.size(); i++){
		meshes[i]->Draw(target, camera.getViewProjection(), &lightInfo);
	}
}

void Scene::Update(float deltaTime){
	camera.Update(deltaTime);
}

void Scene::AddMesh(Mesh& mesh){
	meshes.push_back(&mesh);
}

void Scene::RemoveMesh(int index){
	meshes.erase(meshes.begin() + index);
}

void Scene::AddDirectionalLight(DirectionalLight& directionalLight){
	directionalLights.push_back(&directionalLight);
}

void Scene::RemoveDirectionalLight(int index){
	directionalLights.erase(directionalLights.begin() + index);
}

void Scene::AddPointLight(PointLight& pointLight){
	pointLights.push_back(&pointLight);
}

void Scene::RemovePointLight(int index){
	pointLights.erase(pointLights.begin() + index);
}