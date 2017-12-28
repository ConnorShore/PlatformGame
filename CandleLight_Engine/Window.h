#pragma once

#include <SDL\SDL.h>
#include <string>

#include "Vertex.h"

enum class WindowFlags
{
	NONE,
	WINDOWED,
	FULLSCREEN,
	FULLSCREEN_WINDOWED
};

class Window
{
public:
	Window();
	~Window();

	void createWindow(const std::string& title, int x, int y, int width, int height, WindowFlags flags = WindowFlags::NONE);
	void setBackgroundColor(Color color);
	void swapWindow();
	void destroyWindow();

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	Color getBackgroundColor() const { return _backgroundColor; }
	SDL_Window* getWindow() { return _window; }

private:
	SDL_Window* _window;
	Color _backgroundColor;
	int _width, _height;
};

