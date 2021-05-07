#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL_image.h>
#include "color.h"


namespace util{
	extern const Uint8* KEYS;

	void init();
	void quit();
	float random(float min = 0.0f, float max = 1.0f);
	float to_radians(float degrees);
	float clamp(float value, float min = 0.0f, float max = 1.0f);
	float lerp(float value1, float value2, float lerpFactor);
	Uint32 get_pixel(const SDL_Surface* src, int x, int y);
}