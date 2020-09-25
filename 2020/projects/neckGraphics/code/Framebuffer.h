#pragma once
#include "core/app.h"

// HELPFUL SOURCE: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(unsigned int x, unsigned int y);
	~FrameBuffer();

	void Bind();
	void Unbind();

	unsigned int resX;
	unsigned int resY;

	unsigned int frameBuffer;
	unsigned int renderTexture;
	unsigned int depthBuffer;
};