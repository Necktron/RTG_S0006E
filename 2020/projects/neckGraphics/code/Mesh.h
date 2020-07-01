#pragma once
#include <vector>
#include "core/app.h"

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void LoadTriangle(); //Get a triangle
		void LoadQuad(); //Get a quad
		void LoadCube(); //Get a cube
		void LoadMeshFile(); //Get mesh from file

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vertexBuff; //VBO
		unsigned int vertexArr; //VAO
		unsigned int indexBuff; //IBO
}; // namespace Example