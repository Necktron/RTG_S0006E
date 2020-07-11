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

	renderInstanceA.window_Width = resolution[0];
	renderInstanceA.window_Height = resolution[1];

	renderInstanceB.window_Width = resolution[0];
	renderInstanceB.window_Height = resolution[1];

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

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		renderInstanceA.Init();
		renderInstanceB.Init();

		//Model View Projection matrix setup
		matrix3D view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
		matrix3D model = matrix3D::translate(vector3D(0.0f, 0.0f, 0.0f));
		matrix3D projection = matrix3D::perspectiveProj(90.0f, this->resolution[0], this->resolution[1], 0.1f, 100.0f);
		matrix3D MVP = projection * view * model;

		//Do you want the shader to be printed out for closer inspection?
		renderInstanceA.meshPTR->m_DEBUG = false;
		renderInstanceA.shaderPTR->m_DEBUG = true;

		renderInstanceB.meshPTR->m_DEBUG = false;
		renderInstanceB.shaderPTR->m_DEBUG = false;

		//Setup mesh with VBO, VAO and IBO
		renderInstanceA.meshPTR->Cube();

		//Select a shader effect, ( You must know what shader makes what effects )
		renderInstanceA.shaderPTR->shaderEFK = Shader::ShaderEffect::IMAGE_TEXTURE;

		//If the shader allows a texture, we may choose a texture below, ( *# )
		renderInstanceA.texturePTR->textureImage = Texture::TextureImage::IKEA;

		renderInstanceB.meshPTR->Cube();
		renderInstanceB.shaderPTR->shaderEFK = Shader::ShaderEffect::IMAGE_TEXTURE;
		renderInstanceB.texturePTR->textureImage = Texture::TextureImage::KOREAN_FLAG;
		
		if (int(renderInstanceA.shaderPTR->shaderEFK) == 0)
			renderInstanceA.shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/StaticRainbow.shader");

		else if(int(renderInstanceA.shaderPTR->shaderEFK) == 1)
			renderInstanceA.shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/PulseColor.shader");

		else if (int(renderInstanceA.shaderPTR->shaderEFK) == 2)
			renderInstanceA.shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/ImageTexture.shader");
		
		renderInstanceB.shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/ImageTexture.shader");

		//Bind the shader
		renderInstanceA.shaderPTR->Bind();
		renderInstanceA.shaderPTR->SetUniformMat4fv("u_MVP", MVP);
		renderInstanceA.shaderPTR->SetUniform4f("u_Move", 0.0f, 0.5f, 0.0f, 1.0f);

		renderInstanceB.shaderPTR->Bind();
		renderInstanceB.shaderPTR->SetUniformMat4fv("u_MVP", MVP);
		renderInstanceB.shaderPTR->SetUniform4f("u_Move", 0.0f, -0.5f, 0.0f, 1.0f);
		//SHADER SETUP DONE

		//Select a texture file if the shader allows for textures
		if (int(renderInstanceA.shaderPTR->shaderEFK) == 2)
		{
			//Get the file path to right texture based upon value set att textureImage at *#
			renderInstanceA.texturePTR->TextureFilepath(renderInstanceA.texturePTR);
			renderInstanceA.texturePTR->SetupTexture(renderInstanceA.texturePTR->m_FilePath);

			//Bind the texture aswell to the shader
			renderInstanceA.texturePTR->Bind();
			renderInstanceA.shaderPTR->SetUniform1i("u_Texture", 0);

			renderInstanceB.texturePTR->TextureFilepath(renderInstanceB.texturePTR);
			renderInstanceB.texturePTR->SetupTexture(renderInstanceB.texturePTR->m_FilePath);
			renderInstanceB.texturePTR->Bind();
			renderInstanceB.shaderPTR->SetUniform1i("u_Texture", 0);
		}
		//TEXTURE SETUP DONE

		renderInstanceA.ConfigUniforms();
		renderInstanceB.ConfigUniforms();

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
	renderInstanceA.moveX = 1.6f;
	renderInstanceB.moveX = 1.6f;

	renderInstanceA.moveY = 0.9f;
	renderInstanceB.moveY = -0.9f;

	while (this->window->IsOpen())
	{

		renderInstanceA.Clear();
		renderInstanceB.Clear();

		renderInstanceA.Bind();
		renderInstanceA.Update();
		renderInstanceA.Draw();
		renderInstanceA.Unbind();

		renderInstanceB.Bind();
		renderInstanceB.Update();
		renderInstanceB.Draw();
		renderInstanceB.Unbind();

		this->window->Update();

		this->window->SwapBuffers();

	}
}
} // namespace Example