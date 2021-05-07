#include "display.h"
#include "scene.h"

#undef main

int main(){
	util::init();

	Display display(1024, 576, "Software Renderer");
	RenderContext& target = display.getContext();

	Mesh m("../res/monkey_smooth.ply", SHADER_TEXTURED, "../res/box.bmp");
	Mesh m1("../res/terrain.ply", SHADER_TEXTURED, "../res/concrete.bmp");
	
	DirectionalLight d(Vec3(0.0f, 0.0f, 1.0f));
	PointLight p(Vec4(), 10.0f);
	PointLight p1(Vec4(), 10.0f);

	Scene scene(Camera(display), 0.0f);
	scene.AddMesh(m);
	scene.AddMesh(m1);
	//scene.AddDirectionalLight(d);
	scene.AddPointLight(p);
	scene.AddPointLight(p1);
	
	float counter = 0.0f;

	Uint32 currentTime, previousTime = SDL_GetTicks();
	while(display.IsOpen()){
		currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - previousTime) / 1000.0f;
		previousTime = currentTime;

		counter += deltaTime;
		m.setRotation(Rotator(0.0f, counter, 0.0f));
		m1.setPosition(Vec4(0.0f, -2.0f, 0.0f));
		p.setPosition(Vec4(sinf(counter) * 8, 3.0f, 5.0f));
		p1.setPosition(Vec4(-sinf(counter) * 8, 3.0f, -5.0f));

		scene.Update(deltaTime);
		scene.Draw(target);

		display.Update();
		target.Clear();
		target.ClearZBuffer();
	}

	util::quit();
}