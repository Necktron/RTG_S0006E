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
#include "Shader.h"
#include <memory>

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
	void Update();

	std::shared_ptr<Mesh> meshPTR;
	std::shared_ptr<Shader> shaderPTR;

private:
	unsigned int shader;
	Display::Window* window;
};
} // namespace Example