#pragma once

#include "renderContext.h"

class Stars3D{
public:
	Stars3D(int numStars, float speed, float spread, float fov = 90.0f){
		this->numStars = numStars;
		this->speed = speed;
		this->spread = spread;
		tanHalfFov = tanf(fov / 2.0f);
		stars = new Vector[numStars];
	}

	~Stars3D(){
		delete[] stars;
	}
	
	void Render(RenderContext& target, float deltaTime){
		float halfWidth = target.getWidth() / 2.0f;
		float halfHeight = target.getHeight() / 2.0f;

		for(int i = 0; i < numStars; i++){
			stars[i].Z -= speed * deltaTime;

			if(stars[i].Z <= 0.0f)
				InitStar(i);

			int x = static_cast<int>(stars[i].X / stars[i].Z * tanHalfFov * halfWidth + halfWidth);
			int y = static_cast<int>(stars[i].Y / stars[i].Z * tanHalfFov * halfHeight + halfHeight);

			if(x < 0 || x > target.getWidth() || y < 0 || y > target.getHeight())
				InitStar(i);
			else
				target.DrawPixel(x, y);
		}
	}

private:
	int numStars;
	float speed, spread, tanHalfFov;
	Vector* stars;

	void InitStar(int index){
		stars[index].X = util::random(-1.0f, 1.0f) * spread;
		stars[index].Y = util::random(-1.0f, 1.0f) * spread;
		stars[index].Z = util::random(0.01f, 1.0f) * spread;
	}
};