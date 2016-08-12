#pragma once

#include <GL/glew.h>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void createFrameBuffer();
	GLuint addTextureAttachment(int width, int height, int index);
	void bindBuffer();
	void unbindBuffer();

private:
	GLuint _fboID;
};

