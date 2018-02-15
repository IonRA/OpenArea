#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include "Window.h"

int main(int argc, char ** argv)
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw SDL_GetError();
		Window w;
		w.color(0x0, 0xFF, 0x0);
	}
	catch (std::string s)
	{
		std::cout << s;
		SDL_Quit();
	}
	SDL_Quit();
	return 0;
}