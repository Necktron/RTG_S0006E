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
#include "resources/mathLibrary/Matrix2D.h"
#include "resources/mathLibrary/Matrix3D.h"
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
	std::shared_ptr<Texture> texturePTR;
	std::shared_ptr<Renderer> graphicsPTR;

private:
	unsigned int shader;
	Display::Window* window;
	GLFWwindow* windowGUI;
	float resolution[2];
};
} // namespace Example