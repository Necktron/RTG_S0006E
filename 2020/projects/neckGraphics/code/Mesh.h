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

		enum class OBJ
		{
			NONE = -1,
			TRIANGLE = 0,
			QUAD = 1,
			CUBE = 2,
			CAT = 3,
			RIO = 4
		};

		struct vertex {
			vector3D pos;
			vector2D uv;
			vector3D norm;
		};

		struct uv {
			float U, V;
		};

		struct normal {
			float X, Y, Z;
		};

		struct faceVertex {
			int pos, uv, norm;
		};

		struct Face {
			vector<unsigned int> verts;
		};

		typedef vector<faceVertex> faceCalculations;
		vector<faceCalculations> faces;
		vector<vertex> vboV;
		vector<unsigned int> indices;
		vector<Face> meshFaces;

		OBJ meshOBJ = OBJ::NONE;

		void Triangle(); //Set triangle
		void Quad(); //Set quad
		void Cube(); //Set cube
		void CustomMesh(const char* filepath); //Set cube
		string FaceValidation(int pos, int uv, int norm);

		void Bind();
		void Unbind();
		
		//TEMP
		vector<vector3D> temp_vertices;
		vector<vector2D> temp_uvies;
		vector<vector3D> temp_normals;
		
		map<string, int> vertexMap;

		bool m_DEBUG; //Debug bool for matrix values of the mesh

		//Variables assigned and used to render the mnesh, Vertex Buffer, Vertex Assosiation, Index Buffer, etc
		unsigned int vbo; //VBO
		unsigned int vao; //VAO
		unsigned int ibo; //IBO

	private:
		string file;
}; // namespace Example