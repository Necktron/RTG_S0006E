#define ERROR_TRIGGER __debugbreak();
#include "Shader.h"

void Shader::SetupShader(const string& filepath)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

	//Print's the Vertex and Fragment shader source code for inspection in CMD
	if (m_DEBUG)
	{
		printf("VERTEX");
		printf("%s \n", source.VertexSource);
		printf("FRAGMENT");
		printf("%s \n", source.FragmentSource);
	}
}

void Shader::Bind()
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const string name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const string name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const string name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const string name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4fv(const string name, const matrix3D& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix.mxOrigin[0][0]);
}

int Shader::GetUniformLocation(const string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
		printf("Warning: Uniform '%s' dosen't exsist!", name);

	m_UniformLocationCache[name] = location;

	return location;
}

Shader::ShaderProgramSource Shader::ParseShader(const string& filepath)
{
	ifstream stream(filepath);
	string line;
	stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ShaderType mode = ShaderType::NONE;

	if (stream.fail())
	{
		printf("[Necktron OpenGL Error System] : Shader could not be parsed, validate file path!\n");
		ERROR_TRIGGER;
	}

	while(getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
				mode = ShaderType::VERTEX;

			else if (line.find("fragment") != string::npos)
				mode = ShaderType::FRAGMENT;
		}

		else
		{
			ss[(int)mode] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

//SHADER INIT AND LINKING
unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//Attatch the vs and fs to the program, then link it and validate
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	//Return the program for usage with vs and fs linked
	return program;
}

//SHADER VALIDATION
unsigned int Shader::CompileShader(unsigned int type, const string& source)
{
	//Compile the shader and return an error message if it's no
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		type == GL_VERTEX_SHADER ? "vertex" : "fragment";
		printf("[Necktron OpenGL Error System] : Failed to compile %i \n", type);
		printf("%s \n", message);
		glDeleteShader(id);
		ERROR_TRIGGER;
		return 0;
	}

	return id;
}