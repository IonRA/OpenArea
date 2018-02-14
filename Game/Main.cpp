#include <iostream>
#include <string>
#include <SDL/SDL.h>

#define UNDEF SDL_WINDOWPOS_UNDEFINED

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv) 
{
	SDL_Window* window = NULL;
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw SDL_GetError();
		SDL_Surface* screenSurface = NULL;
		window = SDL_CreateWindow("Window", UNDEF, UNDEF, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			throw "The window cannot be open";
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(3000);
		SDL_DestroyWindow(window);
		SDL_Quit;
	}
	catch (std::string s)
	{
		std::cout << s;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	return 0;
}