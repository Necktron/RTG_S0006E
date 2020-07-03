#pragma once
#include "core/app.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "resources/mathLibrary/Matrix3D.h"

using namespace std;

class Shader
{
public:

	enum class ShaderEffect
	{
		NONE = -1,
		STATIC_RAINBOW = 0,
		PULSE_COLOR = 1,
		IMAGE_TEXTURE = 2
	};

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	bool m_DEBUG;
	ShaderEffect shaderEFK = ShaderEffect::NONE;

	void Bind();
	void Unbind();
	void SetupShader(const std::string& filepath); //Parse and compile a shader
	void SetUniform1i(const std::string name, int value);
	void SetUniform1f(const std::string name, float value);
	void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
	void SetUniformMat4fv(const std::string name, const matrix3D& matrix);

private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

}; // namespace Example