#pragma once
#include <iostream>

class ErrorHandler
{
	public:
		void GLClearError();
		void GLCheckError();
};

inline void ErrorHandler::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline void ErrorHandler::GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
	}
}