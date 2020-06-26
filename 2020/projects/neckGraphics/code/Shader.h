#pragma once
#include "core/app.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class Shader
{
public:

	//static unsigned int CreateShader();
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	ShaderProgramSource ParseShader(const std::string& filepath);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static unsigned int CompileShader(unsigned int type, const string& source);

}; // namespace Example