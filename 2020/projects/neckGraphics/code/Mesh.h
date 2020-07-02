#pragma once
#include <vector>
#include "core/app.h"

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void Triangle(); //Get a triangle
		void Quad(); //Get a quad
		void Cube(); //Get a cube
		void MeshFile(); //Get mesh from file

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vbo; //VBO
		unsigned int vao; //VAO
		unsigned int ibo; //IBO
}; // namespace Example