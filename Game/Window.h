#pragma once

class Window
{
	SDL_Window* window;
	SDL_Surface* screenSurface;
	int width;
	int height;
public:
	Window(int w = 640, int h = 480);
	~Window()
	{
		SDL_DestroyWindow(window);
	}
	SDL_Window* getWin() { return window; }
	SDL_Surface* getSurf() { return screenSurface; }
	Window& color(Uint8, Uint8, Uint8);
	void loadImg(std::string);
};