#include "FrameBuffer.h"



FrameBuffer::FrameBuffer()
{
}


FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::createFrameBuffer()
{
	glGenFramebuffers(1, &_fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

GLuint FrameBuffer::addTextureAttachment(int width, int height, int index)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture, 0);
	return texture;
}

void FrameBuffer::bindBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
}

void FrameBuffer::unbindBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
