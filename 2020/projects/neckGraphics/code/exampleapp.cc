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
		meshPTR->LoadMeshFile();

		Shader::ShaderProgramSource source = shaderPTR->ParseShader("../../../projects/neckGraphics/code/Basic.shader");
		std::cout << "VERTEX" << std::endl;
		std::cout << source.VertexSource << std::endl;
		std::cout << "FRAGMENT" << std::endl;
		std::cout << source.FragmentSource << std::endl;

		//Shader setup with vertex shader and fragment shader
		this->shader = shaderPTR->CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(this->shader);

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

	//Retrieve location of u_Color variable
	int color = glGetUniformLocation(this->shader, "u_Color");
	assert(color != -1);
	glUniform4f(color, 0.0f, 0.0f, 0.0f, 1.0f);

	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		//RENDERING PROCESS AND SETUP
		glUniform4f(color, r, g, b, 1.0f);
		glBindVertexArray(meshPTR->vertexArr);

		if(int(meshPTR->drawSettings) != 0)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPTR->indexBuff);

		//ACTUAL RENDER
		meshPTR->Draw();

		//COLOR ANIM
		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;


		this->window->SwapBuffers();
	}
}

void ExampleApp::Update()
{

}
} // namespace Example