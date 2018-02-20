#include <SDL\SDL_video.h>
#include <SDL\SDL_timer.h>
#include <SDL\SDL_image.h>
#include <string>
#include <iostream>
#include "Window.h"


Window::Window(int w, int h): width(w), height(h)
{
	window = SDL_CreateWindow("Window", 10, 34, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		SDL_DestroyWindow(window);
		throw "The window cannot be opened";
	}
	screenSurface = SDL_GetWindowSurface(window);
}

Window& Window::color(Uint8 R, Uint8 G, Uint8 B)
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, R, G, B));
	SDL_UpdateWindowSurface(window);
	return *this;
}

void Window::loadImg(std::string s)
{
	SDL_Surface * imgSurface = IMG_Load(s.c_str());
	if (imgSurface == NULL)
		throw "Image cannot load";
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(imgSurface, screenSurface->format, NULL);
	SDL_FreeSurface(imgSurface);
	if (optimizedSurface == NULL)
		throw "Image cannot load";
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = width;
	stretchRect.h = height;
	SDL_BlitScaled(optimizedSurface, NULL, screenSurface, &stretchRect);
	SDL_UpdateWindowSurface(window);
	SDL_FreeSurface(optimizedSurface);
}