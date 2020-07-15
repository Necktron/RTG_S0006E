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

	resolution[0] = 1920.0f;
	resolution[1] = 1080.0f;

	this->window->SetSize(resolution[0], resolution[1]);

	/*window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});*/

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Shader::ShaderProgramSource source;

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		renderInstanceA.Init(resolution[0], resolution[1]);

		//Do you want the shader to be printed out for closer inspection? Simply comment out this line if you don't want to. It's disabled by default
		renderInstanceA.shaderPTR->m_DEBUG = true;

		//Setup mesh with VBO, VAO and IBO
		renderInstanceA.SetMesh(2);

		//Select a shader, ( You must know what shader makes what effects )
		renderInstanceA.SetShader(Shader::ShaderEffect::IMAGE_TEXTURE);

		//Select a texture, we must make sure we got a shader that support textures above
		renderInstanceA.SetTexture(Texture::TextureImage::IKEA);

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
	renderInstanceA.SetStartTransform(vector3D(0.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));

	while (this->window->IsOpen())
	{
		//CLEAR
		renderInstanceA.Clear();

		//INPUT
		renderInstanceA.InputScan();

		//DRAW
		renderInstanceA.Draw();

		this->window->Update();

		this->window->SwapBuffers();
	}
}
} // namespace Example