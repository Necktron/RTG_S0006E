#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "resources/mathLibrary/Matrix3D.h"
#include <memory>
#include <Windows.h>

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	bool Open();
	void Run();

	Renderer renderInstanceA;
	Renderer renderInstanceB;
	Renderer renderInstanceC;
	shared_ptr<Rasterizer> rasterInstance;

private:
	unsigned int shader;
	Display::Window* window;
	float resolution[2];
};
} // namespace Example