#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include "Window.h"
#include <windows.h>


int main(int argc, char ** argv)
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw SDL_GetError();
		if (!(IMG_Init(IMG_INIT_PNG) && IMG_Init(IMG_INIT_JPG) && IMG_Init(IMG_INIT_TIF)))
			throw IMG_GetError();
		Window w;
		std::string CurrentSurface("Resources/wi.bmp");
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
				else 
					if (e.type == SDL_KEYDOWN)
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							CurrentSurface = "Resources/wi1.bmp";
							break;

						case SDLK_DOWN:
							CurrentSurface = "Resources/wi2.bmp";
							break;

						case SDLK_LEFT:
							CurrentSurface = "Resources/wi3.bmp";
							break;

						case SDLK_RIGHT:
							CurrentSurface = "Resources/wi4.bmp";
							break;

						default:
							CurrentSurface = "Resources/wi.bmp";
							break;
						}
			}
			w.loadImg(CurrentSurface);
		}	
	}
	catch (std::string s)
	{
		std::cout << s;
		SDL_Quit();
	}
	IMG_Quit();
	SDL_Quit();
	return 0;
}