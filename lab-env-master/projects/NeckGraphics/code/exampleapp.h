#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2016 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "Mesh.h"

namespace Example
{
	class NeckGraphics : public Core::App
	{
	public:
		/// constructor
		NeckGraphics();
		/// destructor
		~NeckGraphics();

		/// open app
		bool Open();
		/// run app
		void Run();

		Mesh meshPTR;

	private:

		GLuint program;
		GLuint vertexShader;
		GLuint pixelShader;
		GLuint triangle;
		Display::Window* window;
	};
} // namespace Example