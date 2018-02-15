#include <SDL\SDL_video.h>
#include <SDL\SDL_timer.h>
#include "Window.h"

Window::Window(int width, int height)
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
	SDL_Delay(3000);
	return *this;
}