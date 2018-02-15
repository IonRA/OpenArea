#pragma once

class Window
{
	SDL_Window* window;
	SDL_Surface* screenSurface;
public:
	Window(int width = 640, int height = 480);
	~Window()
	{
		SDL_DestroyWindow(window);
	}
	SDL_Window* getWin() { return window; }
	SDL_Surface* getSurf() { return screenSurface; }
	Window& color(Uint8, Uint8, Uint8);
};