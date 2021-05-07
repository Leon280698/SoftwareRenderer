#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include "renderContext.h"

class Display{
public:
	Display(int width, int height, const std::string& title){
		open = true;
		this->width = width;
		this->height = height;
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		displayImage = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
		frameBuffer = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		context = new RenderContext(frameBuffer);
	}

	~Display(){
		delete context;
		SDL_FreeSurface(frameBuffer);
		SDL_DestroyTexture(displayImage);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	bool IsOpen() const;
	void Update();
	RenderContext& getContext() const;
	int getWidth() const;
	int getHeight() const;
	float getAspectRatio() const;

private:
	SDL_Surface* frameBuffer;
	SDL_Texture* displayImage;
	SDL_Renderer* renderer;
	SDL_Window* window;
	RenderContext* context;
	int width, height;
	bool open, fullscreen;

	void ToggleFullscreen();
	void SaveScreenShotBMP() const;
};