#include "display.h"

bool Display::IsOpen() const{
	return open;
}

void Display::Update(){
	SDL_UpdateTexture(displayImage, nullptr, frameBuffer->pixels, frameBuffer->pitch);
	SDL_RenderCopy(renderer, displayImage, nullptr, nullptr);
	SDL_RenderPresent(renderer);

	SDL_Event e;
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_WINDOWEVENT){
			switch(e.window.event){
				case SDL_WINDOWEVENT_CLOSE:
					open = false;
					break;
				case SDL_WINDOWEVENT_RESIZED:
					SDL_GetWindowSize(window, &width, &height);
					break;
				default:
					break;
			}
		}
	}

	if(util::KEYS[SDL_SCANCODE_ESCAPE])
		open = false;

	if(util::KEYS[SDL_SCANCODE_F11])
		ToggleFullscreen();

	if(util::KEYS[SDL_SCANCODE_F12])
		SaveScreenShotBMP();
}

void Display::ToggleFullscreen(){
	if(fullscreen)
		fullscreen = SDL_SetWindowFullscreen(window, 0) == 0 ? false : true;
	else
		fullscreen = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0 ? true : false;

	SDL_GetWindowSize(window, &width, &height);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Display::SaveScreenShotBMP() const{
	SDL_Surface* surface;
	char buffer[1000];
	time_t t = time(nullptr);
	tm tm = *localtime(&t);

	strftime(buffer, 1000, "%d-%m-%Y %H-%M-%S", &tm);
	std::string fileName = buffer;
	CreateDirectory("../Screenshots/", nullptr);
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGB888, surface->pixels, surface->pitch);
	SDL_SaveBMP(surface, ("../ScreenShots/" + fileName + ".bmp").c_str());
	SDL_FreeSurface(surface);
}

RenderContext& Display::getContext() const{
	return *context;
}

int Display::getWidth() const{
	return width;
}

int Display::getHeight() const{
	return height;
}

float Display::getAspectRatio() const{
	return static_cast<float>(width) / height;
}