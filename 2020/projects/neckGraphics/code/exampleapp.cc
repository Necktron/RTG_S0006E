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
		renderInstanceA.SetMesh(Mesh::OBJ::CUBE);

		//Select a shader, ( You must know what shader makes what effects )
		renderInstanceA.SetShader(Shader::ShaderEffect::BLINN_PHONG);

		//Select a texture, we must make sure we got a shader that support textures above
		renderInstanceA.SetTexture(Texture::TextureImage::IKEA);

		//Select a light source
		renderInstanceA.SetLight(Light::LightSource::POINT_LIGHT);

		//RENDER B
		renderInstanceB.Init(resolution[0], resolution[1], "Instance B");
		renderInstanceB.shaderPTR->m_DEBUG = true;
		renderInstanceB.SetMesh(Mesh::OBJ::CUBE);
		renderInstanceB.SetShader(Shader::ShaderEffect::BLINN_PHONG);
		renderInstanceB.SetTexture(Texture::TextureImage::KOREAN_FLAG);
		renderInstanceB.SetLight(Light::LightSource::POINT_LIGHT);

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
	bool switchingControl = false;

	renderInstanceA.SetStartTransform(vector3D(-2.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(20.0f, 0.0f, 10.0f));
	renderInstanceB.SetStartTransform(vector3D(2.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(30.0f, -25.0f, 0.0f));

	renderInstanceA.controlAccess = true;

	while (this->window->IsOpen())
	{
		//CLEAR
		renderInstanceA.Clear();
		renderInstanceB.Clear();

		//INPUT
		renderInstanceA.InputScan();
		renderInstanceB.InputScan();

		//Not very modular, but it works!
		//Switch control between renderInstanceA and B
		if (GetAsyncKeyState('B') < 0 && !switchingControl)
		{
			if (renderInstanceA.controlAccess == true)
			{
				renderInstanceA.controlAccess = false;
				renderInstanceB.controlAccess = true;
			}

			else if (renderInstanceB.controlAccess == true)
			{
				renderInstanceA.controlAccess = true;
				renderInstanceB.controlAccess = false;
			}

			switchingControl = true;
		}

		if (GetAsyncKeyState('B') == 0 && switchingControl)
			switchingControl = false;

		//DRAW
		renderInstanceA.Draw();
		renderInstanceB.Draw();

		this->window->Update();

		this->window->SwapBuffers();
	}
}
} // namespace Example