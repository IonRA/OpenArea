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
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			w.loadImg("Resources/wi.bmp");
		}
		
	}
	catch (std::string s)
	{
		std::cout << s;
		SDL_Quit();
	}
	SDL_Quit();
	return 0;
}