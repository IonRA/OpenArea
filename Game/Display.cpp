#include <GL\glew.h>
#include <SDL\SDL.h>
#include <string>
#include <iostream>
#include "Display.h"

Display::Display(int width, int height, std::string dname): quit(false)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	window = SDL_CreateWindow(dname.c_str(), 10, 34, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); 
	if (window == NULL)
	{
		SDL_DestroyWindow(window);
		throw SDL_GetError();
	}
	context = SDL_GL_CreateContext(window);
	if (context = NULL)
	{
		SDL_DestroyWindow(window);
		throw SDL_GetError();
	}
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Display::setState(bool state)
{
	quit = state;
}

void Display::actualize()
{
		 SDL_GL_SwapWindow(window);
}

bool Display::isClosed()
{
	return quit;
}
