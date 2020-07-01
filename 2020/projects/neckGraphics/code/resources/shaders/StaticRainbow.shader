#shader vertex
#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 0) out vec4 Color;

void main()
{
	gl_Position = position;
	Color = color;
}

#shader fragment
#version 430

layout(location = 0) in vec4 color;
out vec4 Color;

void main()
{
	Color = color;
}