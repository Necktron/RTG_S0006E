#pragma once
#include <vector>
#include "core/app.h"

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void Draw(); //Draw the content assigned to the Mesh PTR
		void LoadTriangle(); //Get a triangle
		void LoadQuad(); //Get a quad
		void LoadCube(); //Get a cube
		void LoadMeshFile(); //Get mesh from file

		//Variables for manipulating and automatically assign draw calls to be correct
		enum class DrawMode
		{
			TRIANGLE = 0,
			QUAD = 1,
			CUBE = 2,
			COMPLEX = 3,
			MULTIPLE = 4
		};

		DrawMode drawSettings;

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vertexBuff; //VBO
		unsigned int vertexArr; //VAO
		unsigned int indexBuff; //IBO
}; // namespace Example