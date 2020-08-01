#define ERROR_TRIGGER __debugbreak();
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ibo);
}

//BIND A QUAD TO THE BUFFER
void Mesh::Triangle()
{
	float pos[] =
	{
		//( x, y )
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0,
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	unsigned int index[] =
	{
		0, 1, 2
	};

	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex Buffer Object, VBO
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(pos), pos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 2));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
}

//BIND A QUAD TO THE BUFFER
void Mesh::Quad()
{
	float pos[] =
	{
		//( x, y, textureA, textureB)
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	unsigned int index[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex Buffer Object, VBO
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(pos), pos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float) * 2));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
}

//BIND A CUBE TO THE BUFFER
void Mesh::Cube()
{
	float pos[] =
	{
		//(x, y, z, textureA, textureB, normalX, normalY, normalZ)
		//FRONT
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    //0
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,     //1
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,      //2
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,     //3

		//BACK
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,   //4
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,    //5
		-1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  //6
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f, //7

		//RIGHT
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,     //8
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,      //9
		1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,    //10
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,    //11

		//LEFT
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  //12
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,   //13
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,   //14
		-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,   //15

		//TOP
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,     //16
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //17
		1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //18
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,      //19

		//BOT
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  //20
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,   //21
		1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,  //22
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f    //23
	};

	unsigned int index[] =
	{
		//FRONT
		0, 1, 2,
		2, 3, 0,

		//BACK
		4, 5, 6,
		6, 7, 4,

		//RIGHT
		8, 9, 10,
		10, 11, 8,

		//LEFT
		12, 13, 14,
		14, 15, 12,

		//TOP
		16, 17, 18,
		18, 19, 16,

		//BOT
		20, 21, 22,
		22, 23, 20
	};

	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex Buffer
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	//Vertex Array Object, VAO
	glEnableVertexAttribArray(0); //Pos
	glEnableVertexAttribArray(1); //Texture
	glEnableVertexAttribArray(2); //Normal
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 5));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), index, GL_STATIC_DRAW);
}

//BIND A CUSTOM MESH TO THE BUFFER
void Mesh::CustomMesh(const char* filepath)
{
	stringstream ss;
	ifstream file(filepath);
	string line = "";
	string prefix = "";
	size_t validation;

	Faces faceVertexList;

	vector3D tempVec3;
	vector2D tempVec2;
	int tempInt;

	if (!file.is_open()) { ERROR_TRIGGER; }

	while (getline(file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//VERTEX POS
		if (prefix == "v")
		{
			ss >> tempVec3.vecOrigin[0] >> tempVec3.vecOrigin[1] >> tempVec3.vecOrigin[2];
			temp_vertices.push_back(tempVec3);
		}

		//VERTEX TEXCOORD
		else if (prefix == "vt")
		{
			ss >> tempVec2.vecOrigin[0] >> tempVec2.vecOrigin[1];
			temp_uvs.push_back(tempVec2);
		}

		//VERTEX NORMALS
		else if (prefix == "vn")
		{
			ss >> tempVec3.vecOrigin[0] >> tempVec3.vecOrigin[1] >> tempVec3.vecOrigin[2];
			temp_normals.push_back(tempVec3);
		}

		//FACES
		else if (prefix == "f")
		{
			int C = 0;
			int vertexCount = 0;

			vector<unsigned int> vertexIndex, uvIndex, normalIndex;

			validation = count(line.begin(), line.end(), '/'); //Check how many / we got, if it's 6 it's a triangulated. 8 or poly

			while (ss >> tempInt)
			{
				if (C == 0)
					vertexIndex.push_back(tempInt);

				else if (C == 1)
					uvIndex.push_back(tempInt);

				else if (C == 2)
					normalIndex.push_back(tempInt);

				if (ss.peek() == '/')
				{
					C++;
					ss.ignore(1, '/');
				}

				else if (ss.peek() == ' ')
				{
					C++;
					ss.ignore(1, ' ');
				}

				if (C > 2)
				{
					C = 0;
					vertexCount++;
				}
			}

			int VPF = 0;

			if (validation == 6)
				VPF = 3;

			else if (validation == 8)
				VPF = 4;

			for (int i = 0; i < VPF; i++)
			{
				FaceSetup A;

				A.pos = vertexIndex[i] - 1;
				A.texCoord = uvIndex[i] - 1;
				A.norm = normalIndex[i] - 1;

				faceVertexList.push_back(A);
			}

			faces.push_back(faceVertexList);
			faceVertexList.clear();
		}
	}

	//Triangulate Quad faces
	if (faces[0].size() > 3)
	{
		vector<Faces> tempFaces;
		Faces A;
		Faces B;

		for (int i = 0; i < faces.size(); i++)
		{
			for (int j = 0; j < faces[i].size(); j++)
			{
				A.push_back(faces[i][j]);

				if (j != 1)
					B.push_back(faces[i][j]);
			}

			A.pop_back();
			tempFaces.push_back(A);
			tempFaces.push_back(B);
			A.clear();
			B.clear();
		}

		faces.clear();
		faces = tempFaces;
	}

	//Get's rid of dupe verticies
	for (int i = 0; i < faces.size(); i++)
	{
		Face faceVertList;

		for (int j = 0; j < faces[i].size(); j++)
		{
			int pos = faces[i][j].pos;
			int uv = faces[i][j].texCoord;
			int norm = faces[i][j].norm;
			string key = this->FaceKey(pos, uv, norm);

			if (this->vertexMap.find(key) == this->vertexMap.end())
			{
				Vertex tempVertex;

				tempVertex.pos = temp_vertices[pos];
				tempVertex.texCoord = temp_uvs[uv];
				tempVertex.norm = temp_normals[norm];

				this->vertexMap[key] = this->vertices.size();
				faceVertList.verts.push_back(this->vertices.size());
				this->vertices.push_back(tempVertex);
			}

			else
			{
				faceVertList.verts.push_back(this->vertexMap[key]);
			}
		}

		this->meshFaces.push_back(faceVertList);
	}

	//Final mesh
	for (auto i = 0; i < this->meshFaces.size(); i++)
	{
		for (auto j = 1; j < this->meshFaces[i].verts.size() - 1; j++)
		{
			this->indices.push_back(this->meshFaces[i].verts[0]);
			this->indices.push_back(this->meshFaces[i].verts[j]);
			this->indices.push_back(this->meshFaces[i].verts[j + 1]);
		}
	}

	//Load success
	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex Buffer
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//Vertex Array Object, VAO
	glEnableVertexAttribArray(0); //Pos
	glEnableVertexAttribArray(1); //Texture
	glEnableVertexAttribArray(2); //Normal
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 4));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 7));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

//Search for dupes in vecticies
string Mesh::FaceKey(int pos, int texCoord, int norm)
{
	string posS = to_string(pos);
	string texCoordS = to_string(pos);
	string normS = to_string(pos);

	string result = posS + texCoordS + normS;
	return result;
}

void Mesh::Bind()
{
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}