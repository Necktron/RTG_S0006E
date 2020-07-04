#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

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
		-1.0f * scale, -1.0f * scale, 1.0f * scale, 0.0f, 0.0f,   //0
		-1.0f * scale, 1.0f * scale, 1.0f * scale, 0.0f, 1.0f,    //1
		1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f, 1.0f,     //2
		1.0f * scale, -1.0f * scale, 1.0f * scale, 1.0f, 0.0f,    //3

		1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f, 0.0f,   //4
		1.0f * scale, 1.0f * scale, -1.0f * scale, 1.0, 1.0f,     //5
		-1.0f * scale, 1.0f * scale, -1.0f * scale, 0.0f, 1.0f,   //6
		-1.0f * scale, -1.0f * scale, -1.0f * scale, 0.0f, 0.0f   //7
	};

	unsigned int index[] =
	{
		//FRONT
		0, 1, 2,
		2, 3, 0,

		//TOP
		1, 6, 5,
		5, 2, 1,

		//RIGHT
		3, 2, 5,
		5, 4, 3,

		//LEFT
		7, 6, 1,
		1, 0, 7,

		//BOT
		7, 0, 3,
		3, 4, 7,

		//BACK
		6, 7, 4,
		4, 5, 6
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

//BIND A MESH TO THE BUFFER
void Mesh::MeshFile()
{
	//TODO: READ FILE FOR VERTEX POS, TEXTURE, UV, INDEX, ETC

	//COLORFUL SHADER
	float pos[] =
	{
		//( x, y, z, R, G, B, A)
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 4, 0
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid*)(sizeof(float) * 3));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}