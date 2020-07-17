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

	resolution[0] = 800.0f;
	resolution[1] = 600.0f;

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

		renderInstanceA.Init(resolution[0], resolution[1], "Instance A");

		//Do you want the shader to be printed out for closer inspection? Simply comment out this line if you don't want to. It's disabled by default
		renderInstanceA.shaderPTR->m_DEBUG = true;

		//Setup mesh with VBO, VAO and IBO
		renderInstanceA.SetMesh(2);

		//Select a shader, ( You must know what shader makes what effects )
		renderInstanceA.SetShader(Shader::ShaderEffect::IMAGE_TEXTURE);

		//Select a texture, we must make sure we got a shader that support textures above
		renderInstanceA.SetTexture(Texture::TextureImage::LAGER);

		//Select a light source
		//renderInstanceA.SetLight(Light::LightSource::POINT_LIGHT);

		//RENDER B
		renderInstanceB.Init(resolution[0], resolution[1], "Instance B");
		renderInstanceB.shaderPTR->m_DEBUG = true;
		renderInstanceB.SetMesh(2);
		renderInstanceB.SetShader(Shader::ShaderEffect::IMAGE_TEXTURE);
		renderInstanceB.SetTexture(Texture::TextureImage::MICKE);

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
	renderInstanceA.SetStartTransform(vector3D(-1.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));
	renderInstanceB.SetStartTransform(vector3D(1.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));

	while (this->window->IsOpen())
	{
		//CLEAR
		renderInstanceA.Clear();
		renderInstanceB.Clear();

		//INPUT
		renderInstanceA.InputScan();
		renderInstanceB.InputScanOnlyCamera();

		//DRAW
		renderInstanceA.Draw();
		renderInstanceB.Draw();

		this->window->Update();

		this->window->SwapBuffers();
	}
}
} // namespace Example