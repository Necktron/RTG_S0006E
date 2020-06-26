#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	//Used for objects with a signle triangle
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//Used for objects with and Index Buffer attached, (sevral triangles requiered to form the mesh)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


//BIND A QUAD TO THE BUFFER
void Mesh::LoadTriangle()
{
	float triPos[6] =
	{
		//( x, y )
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f,
	};

	//Vertex Buffer Object, VBO
	glGenBuffers(1, &this->vertexBuff);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuff);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triPos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//BIND A QUAD TO THE BUFFER
void Mesh::LoadQuad()
{
	float quadPos[8] =
	{
		//( x, y, )
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f
	};

	unsigned int quadIndex[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//Vertex Buffer Object, VBO
	glGenBuffers(1, &this->vertexBuff);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuff);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), quadPos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->indexBuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quadIndex, GL_STATIC_DRAW);
}

//BIND A CUBE TO THE BUFFER
void Mesh::LoadCube()
{
	float cubePos[24] =
	{
		//(x, y, z, textureA, textureB)
		//BACK SIDE
		-0.5f, -0.5f, -0.5f, //0
		-0.5f, 0.5f, -0.5f, //1
		0.5f, 0.5f, -0.5f, //2
		0.5f, -0.5f, -0.5f, //3

		//FRONT SIDE
		-0.5f, -0.5f, 0.5f, //4
		-0.5f, 0.5f, 0.5f, //5
		0.5f, 0.5f, 0.5f, //6
		0.5f, -0.5f, 0.5f //7
	};

	unsigned int cubeIndex[] =
	{
		//Back
		0, 1, 2,
		2, 3, 0,

		//Front
		4, 5, 6,
		6, 7, 4,

		//Top
		1, 2, 6,
		6, 5, 1,

		//Bottom
		0, 3, 7,
		7, 4, 3,

		//Left
		0, 1, 5,
		5, 4, 0,

		//Right
		7, 6, 2,
		2, 3, 7
	};

	//Vertex buffer
	glGenBuffers(1, &this->vertexBuff);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuff);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), cubePos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->indexBuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), cubeIndex, GL_STATIC_DRAW);
}

void Mesh::LoadMeshFile()
{
	
}