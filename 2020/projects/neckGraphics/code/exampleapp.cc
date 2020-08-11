//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <iostream>
#include <algorithm> 

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

	rasterInstance.Init(resolution[0], resolution[1]);

	this->window->SetSize(resolution[0], resolution[1]);

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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

		//RENDER C
		renderInstanceC.Init(resolution[0], resolution[1], "Rasterizer Canvas");
		renderInstanceC.shaderPTR->m_DEBUG = true;
		renderInstanceC.SetMesh(Mesh::OBJ::QUAD);
		renderInstanceC.SetShader(Shader::ShaderEffect::PULSE_COLOR);
		renderInstanceC.SetLight(Light::LightSource::POINT_LIGHT);

		//RASTERIZER SETUP
		rasterInstance.SetupMVP();
		//rasterInstance.SetupFrameBuffer();
		//rasterInstance.SetupRasterizerBuffer();
		//unsigned int* results = rasterInstance.GetFrameBufferPointer();
		//cout << "FrameBuffer (" << *results <<") Size is: " << rasterInstance.GetFrameBufferSize() << endl; //Print results from frame buffer

		//Lambda functions for Rasterizer usage
		auto lambdaVS = [](vector3D pos, vector3D norm, matrix3D nMat) -> vector3D
		{
			vector3D aColor(1.0f, 1.0f, 1.0f);
			vector3D ambientColor(0.6f, 0.6f, 0.6f);
			vector3D lightPos(0, 3, -3);
			matrix3D mvMat = nMat;

			vector3D modelViewVertex = (mvMat * pos);
			vector3D modelViewNormal = (mvMat * norm);

			vector3D tempLightDir = (lightPos - modelViewVertex);
			vector3D lightVector = tempLightDir.vecNormilisation();

			float diffuse = max(modelViewNormal.dotProd(lightVector), 0.1f);
			float ambient = ambientColor.dotProd(vector3D(1.0f, 1.0f, 1.0f));

			vector3D v_Color = aColor * (diffuse + ambient);

			return v_Color;
		};
		auto lambdaFS = [](vector2D tex, vector3D norm, unsigned char* image, int w, int h, int n) -> Rasterizer::PixelColor
		{
			int u = abs((int)(tex.vecOrigin[0] * (w - 1)) % w);
			int v = abs((int)(tex.vecOrigin[1] * (h - 1)) % h);

			int index = (u * n + v * n * w);

			Rasterizer::PixelColor color;
			color.r = image[index];
			color.g = image[index + 1];
			color.b = image[index + 2];

			return color;
		};

		rasterInstance.SetVertexShader(lambdaVS);
		rasterInstance.SetPixelShader(lambdaFS);

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

	renderInstanceA.SetStartTransform(vector3D(-4.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(30.0f, 20.0f, 0.0f));
	renderInstanceB.SetStartTransform(vector3D(4.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(80.0f, 0.0f, 0.0f));
	renderInstanceC.SetStartTransform(vector3D(0.0f, 0.0f, 3.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));

	renderInstanceA.controlAccess = true;

	while (this->window->IsOpen())
	{
		//CLEAR
		renderInstanceA.Clear();
		renderInstanceB.Clear();
		renderInstanceC.Clear();

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

		//Rasterizer Draw
		//rasterInstance.Draw();

		//DRAW, back at normal buffer 0
		renderInstanceA.Draw();
		renderInstanceB.Draw();
		renderInstanceC.Draw();

		this->window->Update();

		this->window->SwapBuffers();
	}
}
} // namespace Example