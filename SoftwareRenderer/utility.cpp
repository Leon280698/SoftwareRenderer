#include "utility.h"

extern const Uint8* util::KEYS = util::KEYS = SDL_GetKeyboardState(nullptr);

void util::init(){
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	srand(static_cast<unsigned>(time(nullptr)));
}

void util::quit(){
	IMG_Quit();
	SDL_Quit();
}

float util::random(float min, float max){
	return static_cast<float>(rand() / static_cast<double>(RAND_MAX)) * (max - min) + min;
}

float util::to_radians(float degrees){
	return static_cast<float>(degrees * M_PI / 180);
}

float util::clamp(float value, float min, float max){
	if(value > max)
		return max;

	if(value < min)
		return min;

	return value;
}

float util::lerp(float value1, float value2, float lerpFactor){
	return value1 + lerpFactor * (value2 - value1);
}

Uint32 util::get_pixel(const SDL_Surface* src, int x, int y){
	if(src == nullptr)
		return COL_MAGENTA;

	int bpp = src->format->BytesPerPixel;
	Uint8* p = static_cast<Uint8*>(src->pixels) + (x & (src->w - 1)) * bpp + (y & (src->h - 1)) * src->pitch;

	switch(bpp){
		case 1:
			return p[0] << 16 | p[0] << 8 | p[0];
		case 2:
			break;
		case 3:
		case 4:
			return p[2] << 16 | p[1] << 8 | p[0];
		default:
			return 0;
	}
}