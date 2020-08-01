#pragma once
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "config.h"
#include "core/app.h"
#include "resources/mathLibrary/Vector3D.h";
#include "resources/mathLibrary/Vector2D.h";

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		enum class OBJ
		{
			NONE = -1,
			TRIANGLE = 0,
			QUAD = 1,
			CUBE = 2,
			CAT = 3,
			STOOL = 4,
			BOX = 5,
			WINDMILL = 6
		};

		struct Vertex {
			vector3D pos;
			vector2D texCoord;
			vector3D norm;
		};

		//A vertex in a face with pos, texCoord and norm
		struct FaceSetup
		{
			int pos;
			int texCoord;
			int norm;
		};

		struct Face
		{
			vector<unsigned int> verts;
		};

		OBJ meshOBJ = OBJ::NONE;

		void Triangle(); //Set triangle
		void Quad(); //Set quad
		void Cube(); //Set cube
		void CustomMesh(const char* filepath); //Set OBJ
		string FaceKey(int pos, int uv, int norm);

		void Bind();
		void Unbind();

		bool m_DEBUG; //Debug bool for matrix values of the mesh

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vbo; //VBO
		unsigned int vao; //VAO
		unsigned int ibo; //IBO

		vector<Vertex> vertices;
		vector<unsigned int> indices;

		vector<vector3D> temp_vertices;
		vector<vector2D> temp_uvs;
		vector<vector3D> temp_normals;

		typedef vector<FaceSetup> Faces;
		map<string, int> vertexMap;
		vector<Face> meshFaces;
		vector<Faces> faces;
}; // namespace Example