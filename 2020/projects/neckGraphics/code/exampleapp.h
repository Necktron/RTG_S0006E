#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "Entity.h"
#include "Light.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include "ControlManager.h"
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

	Renderer renderInstance;
	Rasterizer rasterInstance;
	ControlManager controlManager;

private:
	unsigned int shader;
	Display::Window* window;
	float resolution[2];
};
} // namespace Example