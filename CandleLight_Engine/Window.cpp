#include "Window.h"

#include <iostream>
#include <GL\glew.h>


Window::Window()
{
}


Window::~Window()
{
}

void Window::createWindow(const std::string & title, int x, int y, int width, int height, WindowFlags flags /* NONE */)
{
	_width = width;
	_height = height;

	SDL_Init(SDL_INIT_EVERYTHING);

	switch (flags) {
	case WindowFlags::NONE:
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL);
		break;
	case WindowFlags::WINDOWED:
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		break;
	case WindowFlags::FULLSCREEN:
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
		break;
	case WindowFlags::FULLSCREEN_WINDOWED:
		_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);
		break;
	}

	if (_window == nullptr) {
		printf("Failed to create SDL Window");
	}

	SDL_GLContext glContext;
	glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		printf("Failed to create GL Context");
	}

	glewExperimental = GL_TRUE;

	GLenum error;
	error = glewInit();
	if (error != GLEW_OK) {
		printf("Failed to initialize glew");
	}

	glClearColor(0.05f, 0.0f, 0.25f, 1.0f);
	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::swapWindow()
{
	SDL_GL_SwapWindow(_window);
}

void Window::destroyWindow()
{
	SDL_DestroyWindow(_window);
}
