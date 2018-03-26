#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#define PI 3.1415926
#define SCREEN_H 640
#define SCREEN_W 900

unsigned int indices[]{

	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23
};
int main(int argc, char ** argv)
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			throw "SDL fail to initialize!";

		if (!(IMG_Init(IMG_INIT_PNG) && IMG_Init(IMG_INIT_JPG) && IMG_Init(IMG_INIT_TIF)))
			throw IMG_GetError();

		Display d(SCREEN_W, SCREEN_H, "3D_Scene");

		glewExperimental = GL_TRUE;
		GLenum glew = glewInit();
		if (glew != GLEW_OK)
		{
			const GLubyte* c = glewGetErrorString(glew);
			throw  c;
		}

		glEnable(GL_DEPTH_TEST);

		Shader s("vert.glsl", "frag.glsl");

		Vertex v[] = {

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0)),

			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0)),

			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0)),

			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0)),

			Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0)),

			Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0))

		};
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetWindowGrab(d.getWindow(), SDL_TRUE);
		SDL_WarpMouseInWindow(d.getWindow(), SCREEN_W/2, SCREEN_H/2);
		Mesh m(v, 24, indices, 36);

		Texture t("Resources/container.jpg");

		Transformation tr;

		Camera cam(glm::vec3(0, 0, 3), 70.0f, (float)SCREEN_W / SCREEN_H, 0.01f, 1000.0f);

		glm::vec3 z, x;
		int mouseX, mouseY, i;
		float mX, mY, cX = 0, cY = 0;
		float c = -PI / 2;

		s.useProgram();
		while (!d.isClosed())
		{
			m.actualize();
			for (int i = 0; i < 4; ++i)
			{
				tr.getRotate().x = c + i;
				tr.getTranslate().z = -i * i;
				tr.getTranslate().x = i;

				s.actualize(tr, cam);
				glm::mat4 aa = glm::mat4(1.0);;
				m.draw();
			}
			d.actualize();

			c += 0.02;

			SDL_Event e;
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
				{
					d.setState(true);
					break;
				}
				else if (e.type == SDL_KEYDOWN)
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						cam.moveForward();
						break;
					case SDLK_DOWN:
						cam.moveBack();
						break;
					case SDLK_LEFT:
						cam.moveLeft();
						break;
					case SDLK_RIGHT:
						cam.moveRight();
						break;
					default:
						glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

						glClear(GL_COLOR_BUFFER_BIT);
						d.actualize();
					}
				else if (e.type == SDL_MOUSEMOTION)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					mX = -2.0 * mouseX / SCREEN_W + 1;
					mY = -2.0 * mouseY / SCREEN_H + 1;
					cam.rotate(glm::rotate(mX, glm::vec3(0.0, 1.0, 0.0)));
					cam.rotate(glm::rotate(mY, glm::vec3(1.0, 0.0, 0.0)));
					SDL_WarpMouseInWindow(d.getWindow(), SCREEN_W / 2, SCREEN_H / 2);
				}
			}
	}

	catch (const char* e)
	{
		SDL_Quit();
		IMG_Quit();
		std::cout << e;
		int a;
		std::cin >> a;
	}
	catch (const GLubyte * e)
	{
		SDL_Quit();
		IMG_Quit();
		std::cout << e;
		int a;
		std::cin >> a;
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}