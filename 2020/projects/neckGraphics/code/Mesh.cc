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
void Mesh::Cube(float scale)
{
	float pos[] =
	{
		//(x, y, z, textureA, textureB)
		//FRONT
		-1.0f * scale, -1.0f * scale, 1.0f * scale, 0.0f, 0.0f,     //0
		-1.0f * scale, 1.0f * scale, 1.0f * scale, 0.0f, 1.0f,      //1
		1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f, 1.0f,       //2
		1.0f * scale, -1.0f * scale, 1.0f * scale, 1.0f, 0.0f,      //3

		//BACK
		1.0f * scale, -1.0f * scale, -1.0f * scale, 0.0f, 0.0f,     //4
		1.0f * scale, 1.0f * scale, -1.0f * scale, 0.0f, 1.0f,      //5
		-1.0f * scale, 1.0f * scale, -1.0f * scale,  1.0f, 1.0f,    //6
		-1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f, 0.0f,    //7

		//RIGHT
		1.0f * scale, -1.0f * scale, 1.0f * scale, 0.0f, 0.0f,      //8
		1.0f * scale, 1.0f * scale, 1.0f * scale, 0.0f, 1.0f,       //9
		1.0f * scale, 1.0f * scale, -1.0f * scale,  1.0f, 1.0f,     //10
		1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f, 0.0f,     //11

		//LEFT
		-1.0f * scale, -1.0f * scale, -1.0f * scale, 0.0f, 0.0f,    //12
		-1.0f * scale, 1.0f * scale, -1.0f * scale, 0.0f, 1.0f,     //13
		-1.0f * scale, 1.0f * scale, 1.0f * scale,  1.0f, 1.0f,     //14
		-1.0f * scale, -1.0f * scale, 1.0f * scale, 1.0f, 0.0f,     //15

		//TOP
		-1.0f * scale, 1.0f * scale, 1.0f * scale, 0.0f, 0.0f,      //16
		-1.0f * scale, 1.0f * scale, -1.0f * scale, 0.0f, 1.0f,     //17
		1.0f * scale, 1.0f * scale, -1.0f * scale,  1.0f, 1.0f,     //18
		1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f, 0.0f,       //19

		//BOT
		-1.0f * scale, -1.0f * scale, -1.0f * scale, 0.0f, 0.0f,    //20
		-1.0f * scale, -1.0f * scale, 1.0f * scale, 0.0f, 1.0f,     //21
		1.0f * scale, -1.0f * scale, 1.0f * scale,  1.0f, 1.0f,     //22
		1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f, 0.0f      //23
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
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), index, GL_STATIC_DRAW);
}

string Mesh::FaceKey(int pos, int uv, int norm)
{
	string posS = to_string(pos);
	string uvS = to_string(uv);
	string normS = to_string(norm);

	string result = posS + uvS + normS;
	return result;
}

//BIND A MESH TO THE BUFFER
void Mesh::MeshFile(const char* filepath)
{
	//TODO: READ FILE FOR VERTEX POS, TEXTURE, UV, INDEX, ETC
	//Aggro showed me this, example from OpenGL tutorial
	dataOBJ = fopen(filepath, "r");

	if (dataOBJ == NULL)
	{
		cout << "No file found..." << endl;
	}

	else
	{
		int index = 0;

		while (true)
		{
			char lineHeader[128];

			int res = fscanf(dataOBJ, "%s", lineHeader);

			if (res == EOF)
			{
				break;
			}

			if (strcmp(lineHeader, "v") == 0)
			{
				vector3D vertexInData;

				fscanf(dataOBJ, "%f %f %f\n", &vertexInData.vecOrigin[0], &vertexInData.vecOrigin[1], &vertexInData.vecOrigin[2]);

				temp_vertices.push_back(vertexInData);
			}

			else if (strcmp(lineHeader, "vt") == 0)
			{
				vector2D uvInData;

				fscanf(dataOBJ, "%f %f\n", &uvInData.vecOrigin[0], &uvInData.vecOrigin[1]);

				temp_uvs.push_back(uvInData);
			}

			else if (strcmp(lineHeader, "vn") == 0)
			{
				vector3D normalsInData;

				fscanf(dataOBJ, "%f %f %f\n", &normalsInData.vecOrigin[0], &normalsInData.vecOrigin[1], &normalsInData.vecOrigin[2]);

				temp_normals.push_back(normalsInData);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(dataOBJ, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

				if (!(matches == 9 || matches == 12))
				{
					cout << "File can't be read" << endl;
					break;
				}

				Faces faceVertexList;
				int verticesPerFace = 4 - (matches % 4);

				for (int i = 0; i < verticesPerFace; i++)
				{
					FaceVertex finals;

					finals.pos = vertexIndex[i] - 1;
					finals.uv = uvIndex[i] - 1;
					finals.norm = normalIndex[i] - 1;

					faceVertexList.push_back(finals);
				}

				faces.push_back(faceVertexList);
			}

			else
			{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, dataOBJ);
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
				string key = this->FaceKey(pos, uv, norm);

				if (this->vertexMap.find(key) == this->vertexMap.end())
				{
					Vertex tempVertex;

					tempVertex.pos = temp_vertices[pos];
					tempVertex.uv = temp_uvs[uv];
					tempVertex.norm = temp_normals[norm];

					this->vertexMap[key] = this->mesh.size();
					faceVertList.verts.push_back(this->mesh.size());
					this->mesh.push_back(tempVertex);
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

		//Vertex Array
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);

		//Vertex Buffer
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Vertex), &mesh[0], GL_STATIC_DRAW);

		//Vertex Array Object, VAO
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 4));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 6));

		//Index Buffer Object, IBO
		glGenBuffers(1, &this->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
}