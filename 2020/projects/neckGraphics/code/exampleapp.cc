//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#define TASK_COMPLETED ShellExecute(NULL, "open", "https://www.youtube.com/watch?v=5r06heQ5HsI", NULL, NULL, SW_SHOWNORMAL);

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

	resolution[0] = 1920.0f;
	resolution[1] = 1080.0f;

	this->window->SetSize(resolution[0], resolution[1]);

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		renderInstance = Renderer(resolution[0], resolution[1]);
		rasterInstance = Rasterizer(256, 256);
		controlManager = ControlManager(renderInstance, rasterInstance);

		//Entity A
		Entity entA = Entity("Rasterizer Canvas");
		entA.shaderPTR->m_DEBUG = false;
		entA.SetMesh(Mesh::OBJ::QUAD);
		entA.SetShader(Shader::ShaderEffect::BLINN_PHONG);
		entA.SetTexture(Texture::TextureImage::LAGER);

		//Entity B
		/*Entity entB = Entity("Korean Flag");
		entB.shaderPTR->m_DEBUG = false;
		entB.SetMesh(Mesh::OBJ::CUBE);
		entB.SetShader(Shader::ShaderEffect::BLINN_PHONG);
		entB.SetTexture(Texture::TextureImage::MICKE);*/

		renderInstance.AddEntity(entA);
		//renderInstance.AddEntity(entB);

		/*int element = 0;
		int row = 0;

		for (int i = 0; i < 100; i++)
		{
			Entity entTest = Entity("LoopObject_" + std::to_string(i));
			entTest.shaderPTR->m_DEBUG = false;
			entTest.SetMesh(Mesh::OBJ::CAT);
			entTest.SetShader(Shader::ShaderEffect::BLINN_PHONG);
			entTest.SetTexture(Texture::TextureImage::CAT);

			renderInstance.AddEntity(entTest);

			renderInstance.entityList[i].SetTransform(vector3D(element * 2, row * 2, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));
			element++;

			if (element > 9)
			{
				element = 0;
				row++;
			}
		}*/

		//RASTERIZER SETUP
		rasterInstance.SetupFrameBuffer(); //Setup the FBO for the rasterizer
		rasterInstance.SetMesh(Mesh::OBJ::PENGUIN);
		rasterInstance.SetTexture(Texture::TextureImage::PENGUIN);

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
	int currentController = 0;

	//Set transform of models & raster
	renderInstance.entityList[0].SetTransform(vector3D(0.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));
	//renderInstance.entityList[1].SetTransform(vector3D(0.0f, 2.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));
	rasterInstance.SetTransform(vector3D(0.0f, 0.0f, 0.0f), vector3D(1.0f, 1.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f));

	//Set light source pos and cam pos
	renderInstance.SetLightPos(vector3D(0.0f, 0.0f, 2.0f));
	renderInstance.SetCamPos(vector3D(0.0f, 0.0f, 10.0f));

	renderInstance.entityList[0].controlAccess = true;

	while (this->window->IsOpen())
	{
		//CLEAR
		renderInstance.Clear();

		//INPUT
		controlManager.InputScan();

		//Switch control between all entities, one by one
		/*if (GetAsyncKeyState('B') < 0 && !switchingControl)
		{
			if (currentController == renderInstance.entityList.size() - 1)
			{
				renderInstance.entityList[currentController].controlAccess = false;
				renderInstance.entityList[0].controlAccess = true;
				currentController = 0;
			}

			else
			{
				renderInstance.entityList[currentController].controlAccess = false;
				renderInstance.entityList[currentController + 1].controlAccess = true;
				currentController++;
			}

			switchingControl = true;
		}*/

		//Switch control between entity and raster OBJ
		if (GetAsyncKeyState('B') < 0 && !switchingControl)
		{
			if (renderInstance.entityList[0].controlAccess == true)
			{
				renderInstance.entityList[0].controlAccess = false;
				rasterInstance.controlAccess = true;
				printf("Rasterizer is now in control");
			}

			else
			{
				renderInstance.entityList[0].controlAccess = true;
				rasterInstance.controlAccess = false;
				printf("Renderer is now in control");
			}

			switchingControl = true;
		}

		if (GetAsyncKeyState('B') == 0 && switchingControl)
			switchingControl = false;

		//Rasterizer Draw
		rasterInstance.Draw();
		//renderInstance.entityList[0].SetTexture(rasterInstance.renderTarget->renderTexture);

		//Draw
		renderInstance.Draw();
		TASK_COMPLETED;

		rasterInstance.Flush();

		this->window->Update();

		this->window->SwapBuffers();
	}
}
} // namespace Example