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
	//Aggro showed me this, example from OpenGL tutorial
	FILE* file = fopen(filepath, "r");

	if (file == NULL)
	{
		cout << "No file found..." << endl;
		ERROR_TRIGGER;
	}

	else
	{
		int index = 0;

		while (true)
		{
			char lineHeader[128];

			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
			{
				break;
			}

			if (strcmp(lineHeader, "v") == 0)
			{
				vector3D vertexInData;
				fscanf(file, "%f %f %f\n", &vertexInData.vecOrigin[0], &vertexInData.vecOrigin[1], &vertexInData.vecOrigin[2]);
				temp_vertices.push_back(vertexInData);
			}

			else if (strcmp(lineHeader, "vt") == 0)
			{
				vector2D uvInData;
				fscanf(file, "%f %f\n", &uvInData.vecOrigin[0], &uvInData.vecOrigin[1]);
				temp_uvies.push_back(uvInData);
			}

			else if (strcmp(lineHeader, "vn") == 0)
			{
				vector3D normalsInData;
				fscanf(file, "%f %f %f\n", &normalsInData.vecOrigin[0], &normalsInData.vecOrigin[1], &normalsInData.vecOrigin[2]);
				temp_normals.push_back(normalsInData);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

				if (!(matches == 9 || matches == 12))
				{
					cout << "File can't be read" << endl;
					break;
				}

				//Calculate amount of data per face, if it's 3 or 4
				faceCalculations faceVertexList; //List of all data for the verticies in this face
				int verticesPerFace = 4 - (matches % 4);

				if (verticesPerFace == 3)
				{
					for (int i = 0; i < verticesPerFace; i++)
					{
						faceVertex finals;

						finals.pos = vertexIndex[i] - 1;
						finals.uv = uvIndex[i] - 1;
						finals.norm = normalIndex[i] - 1;

						faceVertexList.push_back(finals);
					}
				}

				else if (verticesPerFace == 4)
				{
					//Calculate first face of this zone, 0 / 1 / 2
					for (int i = 0; i < verticesPerFace - 1; i++)
					{
						faceVertex finalsA;

						finalsA.pos = vertexIndex[i] - 1;
						finalsA.uv = uvIndex[i] - 1;
						finalsA.norm = normalIndex[i] - 1;

						faceVertexList.push_back(finalsA);
					}

					faces.push_back(faceVertexList);
					faceCalculations faceVertexListB; //List of all data for the verticies in this face

					//Calculate second face of this zone, 0 / 2 / 3
					faceVertex finalsBFirst;

					finalsBFirst.pos = vertexIndex[0] - 1;
					finalsBFirst.uv = uvIndex[0] - 1;
					finalsBFirst.norm = normalIndex[0] - 1;

					faceVertexListB.push_back(finalsBFirst);


					for (int i = 2; i < verticesPerFace; i++)
					{
						faceVertex finalsB;

						finalsB.pos = vertexIndex[i] - 1;
						finalsB.uv = uvIndex[i] - 1;
						finalsB.norm = normalIndex[i] - 1;

						faceVertexListB.push_back(finalsB);
					}

					faces.push_back(faceVertexListB);
				}

				else
				{
					std::cout << "FAIL... Check verticies per face data in OBJ" << std::endl;
					ERROR_TRIGGER;
				}

				//List of faceVertexLists
				if (verticesPerFace == 3)
					faces.push_back(faceVertexList);
			}

			else
			{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}
		}

		//Get's rid of dupe verticies
		for (int i = 0; i < faces.size(); i++)
		{
			Face faceVertList;

			for (int j = 0; j < faces[i].size(); j++)
			{
				int pos = faces[i][j].pos;
				int uv = faces[i][j].uv;
				int norm = faces[i][j].norm;
				string key = this->FaceValidation(pos, uv, norm);

				if (this->vertexMap.find(key) == this->vertexMap.end())
				{
					vertex tempVertex;

					tempVertex.pos = temp_vertices[pos];
					tempVertex.uv = temp_uvies[uv];
					tempVertex.norm = temp_normals[norm];

					this->vertexMap[key] = this->vboV.size();
					faceVertList.verts.push_back(this->vboV.size());
					this->vboV.push_back(tempVertex);
				}

				else
				{
					faceVertList.verts.push_back(this->vertexMap[key]);
				}
			}

			this->meshFaces.push_back(faceVertList);
		}

		//Final mesh
		for (auto i = 0; i < this->meshFaces.size(); ++i)
		{
			for (auto j = 1; j < this->meshFaces[i].verts.size() - 1; ++j)
			{
				this->indices.push_back(this->meshFaces[i].verts[0]);
				this->indices.push_back(this->meshFaces[i].verts[j]);
				this->indices.push_back(this->meshFaces[i].verts[j + 1]);
			}
		}

		std::cout << "Positions are setup!" << std::endl;
	}

	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex buffer
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vboV.size() * sizeof(vertex), &vboV[0], GL_STATIC_DRAW);

	//Vertex Array Object, VAO
	glEnableVertexAttribArray(0); //Pos
	glEnableVertexAttribArray(1); //UV
	glEnableVertexAttribArray(2); //Normal
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 4));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 7));

	//Index Buffer
	glGenBuffers(1, &this->ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

string Mesh::FaceValidation(int pos, int uv, int norm)
{
	string posS = to_string(pos);
	string uvS = to_string(pos);
	string normS = to_string(pos);

	string result = posS + uvS + normS;
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