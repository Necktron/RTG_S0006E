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

	this->resolution[0] = 800.0f;
	this->resolution[1] = 600.0f;

	this->window->SetSize(resolution[0], resolution[1]);

	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Shader::ShaderProgramSource source;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		meshPTR = std::make_shared<Mesh>();
		shaderPTR = std::make_shared<Shader>();
		texturePTR = std::make_shared<Texture>();

		//Model View Projection matrix setup
		matrix3D view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
		matrix3D model = matrix3D::translate(vector3D(0.0f, 0.0f, 0.0f));
		matrix3D projection = matrix3D::perspectiveProj(90.0f, this->resolution[0], this->resolution[1], 0.1f, 100.0f);
		matrix3D MVP = projection * view * model;

		vector3D move(0.0f, 0.0f, 0.0f);

		//Do you want the shader to be printed out for closer inspection?
		shaderPTR->m_DEBUG = true;

		//Setup mesh with VBO, VAO and IBO
		//meshPTR->Cube(0.5f);
		meshPTR->MeshFile("../../../projects/neckGraphics/code/resources/meshes/cat.obj");

		//Select a shader effect, ( You must know what shader makes what effects )
		shaderPTR->shaderEFK = Shader::ShaderEffect::STATIC_RAINBOW;

		//If the shader allows a texture, we may choose a texture below
		texturePTR->textureImage = Texture::TextureImage::CAT;

		if (int(shaderPTR->shaderEFK) == 0)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/StaticRainbow.shader");

		else if(int(shaderPTR->shaderEFK) == 1)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/PulseColor.shader");

		else if (int(shaderPTR->shaderEFK) == 2)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/ImageTexture.shader");
		
		//Bind the shader
		shaderPTR->Bind();

		shaderPTR->SetUniformMat4fv("u_MVP", MVP);
		shaderPTR->SetUniform4f("u_Move", move.vecOrigin[0], move.vecOrigin[1], move.vecOrigin[2], 1.0f);

		if (int(shaderPTR->shaderEFK) == 1)
		{
			shaderPTR->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		}
		//SHADER SETUP DONE


		//Select a texture file if the shader allows for textures
		if (int(shaderPTR->shaderEFK) == 2)
		{
			if (int(texturePTR->textureImage) == 0)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/YellowBrickWall.jpg");

			else if (int(texturePTR->textureImage) == 1)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/TurquoiseWoodWall.jpg");

			else if (int(texturePTR->textureImage) == 2)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/KoreanFlag.png");

			else if (int(texturePTR->textureImage) == 3)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Blueberries.jpg");

			else if (int(texturePTR->textureImage) == 4)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/OpenGLLogo.png");

			else if (int(texturePTR->textureImage) == 5)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/InstaTransparent.png");

			else if (int(texturePTR->textureImage) == 6)
				texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/cat_diff.tga");

			//Bind the texture aswell to the shader
			texturePTR->Bind();
			shaderPTR->SetUniform1i("u_Texture", 0);
		}
		//TEXTURE SETUP DONE

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
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float moveX = 0.0f;
	float moveZ = 1.0f;
	float rot = 0.0f;
	float angleOfRot = 0.0f;
	float rotSpeed = 1.0f;
	float zoomOut = 0.0f;
	float incrementRGB = 0.02f;
	float incrementPOSX = 0.01f;
	float incrementPOSZ = 0.01f;

	matrix3D view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
	matrix3D model = matrix3D::translate(vector3D(0.0f, 0.0f, 0.0f)) * matrix3D::scale(vector3D(1.0f, 1.0f, 1.0f)) * matrix3D::mxRotZ(0);
	matrix3D projection = matrix3D::perspectiveProj(90.0f, this->resolution[0], this->resolution[1], -0.1f, 100.0f);
	matrix3D MVP = projection * view * model;

	while (this->window->IsOpen())
	{
		graphicsPTR->Clear();

		this->window->Update();

		//RENDERING PROCESS AND SETUP
		if (int(shaderPTR->shaderEFK) == 1)
			shaderPTR->SetUniform4f("u_Color", r, 0.4f, 0.5f, 1.0f);
		
		shaderPTR->SetUniformMat4fv("u_MVP", MVP);
		shaderPTR->SetUniform4f("u_Move", 0.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(meshPTR->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPTR->ibo);

		//ACTUAL RENDER
		graphicsPTR->Draw(meshPTR, shaderPTR);

		//COLOR ANIM
		if (r > 1.5f)
			incrementRGB = -0.02f;
		else if (r < -1.5f)
			incrementRGB = 0.02f;

		r += incrementRGB;

		//POS MOVE
		if (moveX > 1.0f)
			incrementPOSX = -0.01f;
		else if (moveX < -1.0f)
			incrementPOSX = 0.01f;

		moveX += incrementPOSX;

		//POS MOVE
		if (moveZ > 1.0f)
			incrementPOSZ = -0.01f;
		else if (moveZ < -1.0f)
			incrementPOSZ = 0.01f;

		moveZ += incrementPOSZ;

		//ROT MOVE
		if(angleOfRot > 360.0f)
			angleOfRot = 0.0f;

		angleOfRot += 1.0f;

		rot = angleOfRot * rotSpeed;
		zoomOut += 0.01f;

		std::cout << "MATRIX VALUES" <<std::endl;
		std::cout << MVP.mxOrigin[0][0] << " " << MVP.mxOrigin[0][1] << " " << MVP.mxOrigin[0][2] << " " << MVP.mxOrigin[0][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[1][0] << " " << MVP.mxOrigin[1][1] << " " << MVP.mxOrigin[1][2] << " " << MVP.mxOrigin[1][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[2][0] << " " << MVP.mxOrigin[2][1] << " " << MVP.mxOrigin[2][2] << " " << MVP.mxOrigin[2][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[3][0] << " " << MVP.mxOrigin[3][1] << " " << MVP.mxOrigin[3][2] << " " << MVP.mxOrigin[3][3] << std::endl;
		std::cout << "                " << std::endl;

		view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
		model = matrix3D::translate(vector3D(0.0f, 0.0f, 0.0f)) * matrix3D::scale(vector3D(1.0f, 1.0f, 1.0f)) * matrix3D::mxRotZ(0);
		projection = matrix3D::perspectiveProj(90.0f, this->resolution[0], this->resolution[1], 0.1f, 100.0f);

		MVP = view * model;

		this->window->SwapBuffers();
	}
}
} // namespace Example