//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "../../../engine/config.h"
#include "../../../exts/glew/include/GL/glew.h"
#include "exampleapp.h"
<<<<<<< HEAD
#include "tinyxml2-master/tinyxml2.h"
=======
>>>>>>> master
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace Display;

namespace Example
{

	//------------------------------------------------------------------------------
	/**
	*/
	NackensGrafik::NackensGrafik()
	{

	}

	//------------------------------------------------------------------------------
	/**
	*/
	NackensGrafik::~NackensGrafik()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool NackensGrafik::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 a, int32 b, int32 c, int32 d)
		{
			//Keycode for A, position
			if (a == 65)
			{
				movmentX -= 0.02f;
			}

			//Keycode for D, position
			if (a == 68)
			{
				movmentX += 0.02f;
			}

			//Keycode for S, position
			if (a == 83)
			{
				movmentY -= 0.02f;
			}

			//Keycode for W, position
			if (a == 87)
			{
				movmentY += 0.02f;
			}

			//Keycode for Q, position
			if (a == 81)
			{
				scaleSize -= 0.02f;
			}

			//Keycode for E, position
			if (a == 69)
			{
				scaleSize += 0.02f;
			}


			/* ****************************** */

			//Keycode for J, rotation
			if (a == 74)
			{
				rotIntY += 1.5f;
			}

			//Keycode for K, rotation
			if (a == 75)
			{
				rotIntX -= 1.5f;
			}

			//Keycode for L, rotation
			if (a == 76)
			{
				rotIntY -= 1.5f;
			}

			//Keycode for I, rotation
			if (a == 73)
			{
				rotIntX += 1.5f;
			}
		});

		if (this->window->Open())
		{
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			
			meshPTR  = std::make_shared<MeshResource>();
			meshRastPTR = std::make_shared<MeshResource>();
			texPTR = std::make_shared<TextureResource>();
			shadePTR  = std::make_shared<ShaderObject>();
			lightPTR = std::make_shared<LightResource>();
			rastPTR = std::make_shared<Rasterizer>();

<<<<<<< HEAD
			//Old reference to code place
			///home/nacken/ojaaho-6/S0008E - GPOA/lab-env-master/projects/NackensGrafik/code/

			shadePTR->LoadVertShader("../../../code/VertexShade.hlsl");
			shadePTR->LoadFragShader("../../../code/FragmentShade.hlsl");
=======
			shadePTR->LoadVertShader("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/VertexShade.hlsl");
			shadePTR->LoadFragShader("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/FragmentShade.hlsl");
>>>>>>> master

			//setup vbo
			if(renderMode == 0)
			{
<<<<<<< HEAD
				meshPTR->loadFromOBJ("../../../code/cube.obj");
				texPTR->loadFromFile("../../../code/RedPix.tga");
=======
				meshPTR->loadFromOBJ("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/cube.obj");
				texPTR->loadFromFile("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/Ace.jpg");
>>>>>>> master
				lightPTR->getPointLight();
				shadePTR->apply();
				graphic.setMesh(meshPTR);
				graphic.setTex(texPTR);
				graphic.setShade(shadePTR);
			}

			else if (renderMode == 1)
			{
<<<<<<< HEAD
				meshPTR->loadFromOBJ("../../../code/cat.obj");
				meshRastPTR->loadFromOBJ("../../../code/cube.obj");
=======
				meshPTR->loadFromOBJ("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/cat.obj");
				meshRastPTR->loadFromOBJ("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/quad.obj");
>>>>>>> master

				lightPTR->getPointLight();
				shadePTR->apply();

				rastPTR->setMesh(meshPTR);
<<<<<<< HEAD
				//rastPTR->textureRetriver("/home/nacken/ojaaho-6/S0008E - GPOA/lab-env-master/projects/NackensGrafik/code/RedPix.tga");
				rastPTR->textureRetriver("../../../code/cat.tga");
=======
				rastPTR->textureRetriver("/home/necktron/Documents/GitLab University/LTU/RTG_S0006E/lab-env-master/projects/NackensGrafik/code/cat_diff.tga");
>>>>>>> master
			}

			auto vertShader = [](vector3D pos, vector3D norm, matrix3D nMat) -> vector3D
			{
				vector3D aColor(1.0f, 1.0f, 1.0f);
				vector3D ambientColor(0.6f, 0.6f, 0.6f);
				vector3D lightPos(0, 3, -3);
				matrix3D mvMat = nMat;

				vector3D modelViewVertex = (mvMat * pos);
				vector3D modelViewNormal = (mvMat * norm);

				vector3D tempLightDir = (lightPos - modelViewVertex);
				vector3D lightVector = tempLightDir.vecNormilisation();

				float diffuse = std::max(modelViewNormal.dotProd(lightVector), 0.1f);
				float ambient = ambientColor.dotProd(vector3D(1.0f, 1.0f, 1.0f));

				vector3D v_Color = aColor * (diffuse + ambient);

				return v_Color;
			};

			auto fragShader = [](vector2D tex, vector3D norm, unsigned char* image, int w, int h, int n) -> Rasterizer::PixelColor
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

			if(renderMode == 0)
			{
				graphic.setMesh(meshPTR);
			}

			else if(renderMode == 1)
			{
				rastPTR->vertexShade(vertShader);
				rastPTR->fragmentShade(fragShader);
				graphic.setMesh(meshRastPTR);
			}

			graphic.setTex(texPTR);
			graphic.setShade(shadePTR);

			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void NackensGrafik::Run()
	{
		matrix3D matrix;
		matrix3D matrixRast;
		matrix3D modelview; //Matrix f�r transformering
		matrix3D trans; //Translationmatrix
		matrix3D transRast; //Translationmatrix
		matrix3D proj;
		shadePTR->setupMatrix3fv("projection", proj);

		while (this->window->IsOpen())
		{			
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			Update();

			this->window->Update();

			modelview = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));

			if(renderMode == 0)
			{
				matrix = matrix3D::scalematrix(scaleSize)* rotA * rotB * trans * modelview;
			}

			else if(renderMode == 1)
			{
				matrixRast = matrix3D::scalematrix(scaleSize)* rotA * rotB * transRast * modelview.transpose();
			}
			
			proj = matrix3D::ProjectionMatrix(90.0f, 0.1f, 100.0f, this->window->GetWidth(), this->window->GetHeight()).transpose();

			shadePTR->setupMatrix3fv("matrix", matrix * proj);

			if(renderMode == 0)
			{
				// do stuff
<<<<<<< HEAD
=======
				trans.setPosition(vector3D(movmentX, movmentY, movmentZ));
				meshPTR->DrawOBJ();
>>>>>>> master
				this->graphic.Draw();
			}

			else if(renderMode == 1)
			{
				transRast.setPosition(vector3D(movmentX, movmentY, movmentZ));
				rastPTR->draw(modelview * proj, matrixRast);
				texPTR->loadFromRast(rastPTR);
				
				// do stuff
				this->graphic.Draw();

				rastPTR->flush();
			}

			this->window->SwapBuffers();
		}
	}

	void NackensGrafik::Update()
	{
		rotA = matrix3D::mxRotX(rotIntX);
		rotB = matrix3D::mxRotY(rotIntY);
	}
} // namespace Example