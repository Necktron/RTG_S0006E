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

		struct Face
		{
			vector<unsigned int> verts;
		};

		struct Vertex
		{
			vector3D pos;
			vector2D uv;
			vector3D norm;
		};

		struct FaceVertex
		{
			int pos = 0;
			int uv = 0;
			int norm = 0;
		};

		void Triangle(); //Get a triangle
		void Quad(); //Get a quad
		void Cube(float scale); //Get a cube
		void MeshFile(const char* filepath); //Get mesh from file
		
		string FaceKey(int pos, int uv, int norm); //Search for duplicates among faces
		vector<unsigned int> indices;
		vector<Vertex> mesh;

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vbo; //VBO
		unsigned int vao; //VAO
		unsigned int ibo; //IBO

		//Variables for custom mesh scan
		FILE* dataOBJ;
		vector<vector3D> temp_vertices;
		vector<vector2D> temp_uvs;
		vector<vector3D> temp_normals;
		typedef vector<FaceVertex> Faces;
		map<string, int> vertexMap;
		vector<Face> meshFaces;
		vector<Faces> faces;
}; // namespace Example