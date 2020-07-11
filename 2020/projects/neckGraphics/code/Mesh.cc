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
		//(x, y, z, textureA, textureB)
		//FRONT
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,     //0
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,      //1
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,       //2
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,      //3

		//BACK
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,     //4
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f,      //5
		-1.0f, 1.0f, -1.0f,  1.0f, 1.0f,    //6
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,    //7

		//RIGHT
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,      //8
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,       //9
		1.0f, 1.0f, -1.0f,  1.0f, 1.0f,     //10
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,     //11

		//LEFT
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,    //12
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,     //13
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f,     //14
		-1.0f, -1.0f, 1.0f, 1.0f, 0.0f,     //15

		//TOP
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,      //16
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,     //17
		1.0f, 1.0f, -1.0f,  1.0f, 1.0f,     //18
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,       //19

		//BOT
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,    //20
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,     //21
		1.0f, -1.0f, 1.0f,  1.0f, 1.0f,     //22
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f      //23
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