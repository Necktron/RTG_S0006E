//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <iostream>

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	this->window->SetTitle("Necktronian Graphics Inc.");
	this->window->SetSize(850, 850);
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		meshPTR = std::make_shared<Mesh>();
		shaderPTR = std::make_shared<Shader>();

		//Setup mesh with VBO, VAO and IBO { WIP }
		meshPTR->LoadQuad();

		Shader::ShaderProgramSource source = shaderPTR->ParseShader("../../../projects/neckGraphics/code/Basic.shader");
		std::cout << "VERTEX" << std::endl;
		std::cout << source.VertexSource << std::endl;
		std::cout << "FRAGMENT" << std::endl;
		std::cout << source.FragmentSource << std::endl;

		//Shader setup with vertex shader and fragment shader
		unsigned int shader = shaderPTR->CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(shader);

		return true;

	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		// do stuff
		meshPTR->Draw();

		this->window->SwapBuffers();
	}
}

void ExampleApp::Update()
{
}
} // namespace Example