#include "Texture.h"
#include <SDL\SDL_image.h>
#include <GL\glew.h>


Texture::Texture(const char * tex)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_Surface * imgSurface = IMG_Load(tex);
	if (imgSurface == NULL)
		throw "Image cannot load";

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSurface->w, imgSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(imgSurface);
}


Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}