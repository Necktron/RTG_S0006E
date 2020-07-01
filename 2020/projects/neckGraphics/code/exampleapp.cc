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
		Shader::ShaderProgramSource source;

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		meshPTR = std::make_shared<Mesh>();
		shaderPTR = std::make_shared<Shader>();
		texturePTR = std::make_shared<Texture>();

		//Do you want the shader to be printed out for closer inspection?
		shaderPTR->m_DEBUG = false;

		//Setup mesh with VBO, VAO and IBO
		meshPTR->LoadQuad();

		//Select a shader effect, ( You must know what shader makes what effects )
		shaderPTR->shaderEFK = Shader::ShaderEffect::IMAGE_TEXTURE;

		//If the shader allows a texture, we may choose a texture below
		texturePTR->textureImage = Texture::TextureImage::YELLOW_BRICKS;

		if (int(shaderPTR->shaderEFK) == 0)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/StaticRainbow.shader");

		else if(int(shaderPTR->shaderEFK) == 1)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/PulseColor.shader");

		else if (int(shaderPTR->shaderEFK) == 2)
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/ImageTexture.shader");
		
		//Bind the shader
		shaderPTR->Bind();

		//Retrieve location of u_Color variable if animation shader is chosen
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
	float increment = 0.05f;

	while (this->window->IsOpen())
	{
		graphicsPTR->Clear();

		this->window->Update();

		//RENDERING PROCESS AND SETUP
		if (int(shaderPTR->shaderEFK) == 1)
			shaderPTR->SetUniform4f("u_Color", r, 0.4f, 0.5f, 1.0f);
		
		glBindVertexArray(meshPTR->vertexArr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPTR->indexBuff);

		//ACTUAL RENDER
		graphicsPTR->Draw(meshPTR, shaderPTR);

		//Update();

		//COLOR ANIM
		if (int(shaderPTR->shaderEFK) == 1)
		{
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;
		}

		this->window->SwapBuffers();
	}
}

void ExampleApp::Update()
{

}
} // namespace Example