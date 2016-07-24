#pragma once

#include <SDL\SDL.h>
#include <string>

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
	void swapWindow();
	void destroyWindow();

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	SDL_Window* getWindow() { return _window; }

private:
	SDL_Window* _window;
	int _width, _height;
};

