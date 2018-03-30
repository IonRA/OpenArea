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
int SCREEN_H = 640;
int SCREEN_W = 900;

glm::vec3 operator+(glm::vec3 a, double d)
{
	a.z += d;
	a.y += d;
	a.x += d;
	return a;
}

glm::vec3 operator+(double d, glm::vec3 a)
{
	a.z += d;
	a.y += d;
	a.x += d;
	return a;
}

glm::vec3 operator-(double d, glm::vec3 a)
{
	a.z -= d;
	a.y -= d;
	a.x -= d;
	return a;
}

glm::vec3 operator-(glm::vec3 a, double d)
{
	a.z -= d;
	a.y -= d;
	a.x -= d;
	return a;
}

bool operator>=(glm::vec3 a, glm::vec3 b)
{
	if (a.x >= b.x && a.y >= b.y && a.z >= b.z)
		return true;
	return false;
}

bool operator<=(glm::vec3 a, glm::vec3 b)
{
	if (a.x <= b.x && a.y <= b.y && a.z <= b.z)
		return true;
	return false;
}


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

		Mesh m(v, 24, indices, 36);
		Texture t("Resources/container.jpg");
		Transformation tr;
		Camera cam(glm::vec3(0, 0, 3), 70.0f, (float)SCREEN_W / SCREEN_H, 0.01f, 1000.0f);

		int mouseX, mouseY, i;
		float mX, mY;
		float c = -PI / 2;

		s.useProgram();

		std::vector<glm::vec3> posistions;
		while (!d.isClosed())
		{
			d.clear();
		/*	for (i = 0; i < 4; ++i)
			{
				tr.getRotate().x = c + i;
				tr.getTranslate().z = -i * i;
				tr.getTranslate().x = i;
				s.actualize(tr, cam);
				m.bind();
				m.draw();
			}*/

			for (auto a : posistions)
			{
				tr.getTranslate() = a;
				s.actualize(tr, cam);
				m.bind();
				m.draw();
			}

			d.actualize();

			c += 0.02;

			SDL_Event e;
			while (SDL_PollEvent(&e) && !d.isClosed())
				switch (e.type)
				{
				case SDL_QUIT:
						d.setState(true);
						break;
				case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_w:
							cam.moveForward();
							for (auto a : posistions)
								if (cam.getPos() <= a + 0.5 && cam.getPos() >= a - 0.5)
								{
									cam.moveBack();
									break;
								}
							break;
						case SDLK_s:
							cam.moveBack();
							for (auto a : posistions)
								if (cam.getPos() <= a + 0.5 && cam.getPos() >= a - 0.5)
								{
									cam.moveForward();
									break;
								}
							break;
						case SDLK_a:
							cam.moveLeft();
							for (auto a : posistions)
								if (cam.getPos() <= a + 0.5 && cam.getPos() >= a - 0.5)
								{
									cam.moveRight();
									break;
								}
							break;
						case SDLK_d:
							cam.moveRight();
							for (auto a : posistions)
								if (cam.getPos() <= a + 0.5 && cam.getPos() >= a - 0.5)
								{
									cam.moveLeft();
									break;
								}
							break;
						case SDLK_f:
							SDL_DisplayMode dm;
							if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
								throw SDL_GetError();
							SCREEN_W = dm.w;
							SCREEN_H= dm.h;
							SDL_SetWindowSize(d.getWindow(), SCREEN_W, SCREEN_H);
							cam.chPerspective(70.0f, (float)SCREEN_W / SCREEN_H, 0.01f, 1000.0f);
							glViewport(0, 0, SCREEN_W, SCREEN_H);
							break;
						case SDLK_ESCAPE:
							d.setState(true);
							break;
						default:
							glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

							glClear(GL_COLOR_BUFFER_BIT);
							d.actualize();
						}
						break;
				case SDL_MOUSEMOTION:
					
						SDL_GetMouseState(&mouseX, &mouseY);
						mX = 2.0 * mouseX / SCREEN_W - 1;
						mY = -2.0 * mouseY / SCREEN_H + 1;
						cam.rotate(30 * mX, 30 * mY);
						SDL_WarpMouseInWindow(d.getWindow(), SCREEN_W / 2, SCREEN_H / 2);
						break;
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT)
						posistions.push_back(cam.getPos() + cam.getForward() + cam.getForward());
					break;
				case SDL_WINDOWEVENT:
						if (e.window.event == SDL_WINDOWEVENT_RESIZED)
						{
							SDL_GetWindowSize(d.getWindow(), &SCREEN_W, &SCREEN_H);
							cam.chPerspective(70.0f, (float)SCREEN_W / SCREEN_H, 0.01f, 1000.0f);
							glViewport(0, 0, SCREEN_W, SCREEN_H);
						}
						break;
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