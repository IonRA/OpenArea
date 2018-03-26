#pragma once


class Display
{
	SDL_Window * window;
	SDL_GLContext context;
	bool quit;
	Display(const Display& d) {}
	Display& operator=(const Display& d) {}

public:
	Display(int width = 640, int height = 480, std::string dname = "Title");
	void actualize();
	virtual ~Display();
	bool isClosed();
	SDL_Window * getWindow() { return window; }
	void setState(bool);
};