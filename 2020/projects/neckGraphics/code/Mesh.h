#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "core/app.h"
#include "resources/mathLibrary/Vector3D.h";
#include "resources/mathLibrary/Vector2D.h";

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void Triangle(); //Set triangle
		void Quad(); //Set quad
		void Cube(); //Set cube

		void Bind();
		void Unbind();
		//void MeshFile(const char* filepath); //Get mesh from file
		
		bool m_DEBUG; //Debug bool for matrix values of the mesh

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vbo; //VBO
		unsigned int vao; //VAO
		unsigned int ibo; //IBO
}; // namespace Example