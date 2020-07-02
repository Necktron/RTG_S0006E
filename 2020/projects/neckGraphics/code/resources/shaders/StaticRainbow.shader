#shader vertex
#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 0) out vec4 Color;

uniform vec4 u_Move;
uniform mat4 u_MVP;

void main()
{
	gl_Position = (u_MVP * position) + u_Move;
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