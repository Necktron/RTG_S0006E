#define ERROR_TRIGGER __debugbreak();
#include "Framebuffer.h"

FrameBuffer::FrameBuffer()
{
	resX = 0;
	resY = 0;

	frameBuffer = 0;
	renderTexture = 0;
	depthBuffer = 0;
}

FrameBuffer::FrameBuffer(unsigned int x, unsigned int y)
{
	resX = x;
	resY = y;

	//Setup Framebuffer
	frameBuffer = 0;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//Texture to render to
	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture); //Bind the texture to modify
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resX, resY, 0, GL_RGB, GL_UNSIGNED_BYTE, 0); //Set a empty image to the Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Depth buffer
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, resX, resY);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	//Configure framebuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture, 0); //Set "renderTexture" as our color attachment
	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	//Check so everything works!
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		ERROR_TRIGGER; //Something does not work properly!
}

FrameBuffer::~FrameBuffer()
{

}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Back to normal frameBuffer
void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1920, 1080);
}