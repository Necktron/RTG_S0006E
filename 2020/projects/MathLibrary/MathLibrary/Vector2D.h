#pragma once
#include <iostream>
#include "math.h"

using namespace std;

class vector2D
{
	public:
		//Basic constructor
		vector2D();
		vector2D(float, float);

		//Copy constructor
		vector2D(const vector2D &other);

		//Destructor
		~vector2D();

		//Main vector that you play around with
		float vecOrigin[3];

		//Operators
		float operator* (const vector2D &other);
		vector2D operator*(float);
		vector2D operator+(vector2D other);
		vector2D operator-(vector2D other);
		vector2D operator=(const vector2D &other);
		bool operator==(vector2D &other);
		bool operator!=(vector2D &other);

		//Functions
		vector2D vecAdd(vector2D &other);
		vector2D vecSub(vector2D &other);
		float crossProd(vector2D &other);
		float dotProd(vector2D &other);
		float vecLength();
		float vecNormilisation();
		float vecGet(int i);
		void vecSet(float x, float y);
};

//Empty Constructor
vector2D::vector2D()
{

}

//Constructor with components
vector2D::vector2D(float a, float b)
{
	vecOrigin[0] = a;
	vecOrigin[1] = b;
	vecOrigin[2] = 1;
}

//Copy Constructor
vector2D::vector2D(const vector2D &other)
{
	for (int i = 0; i < 3; ++i)
	{
		vecOrigin[i] = other.vecOrigin[i];
	}
}

//Destructor         
vector2D::~vector2D()
{

}

//Addition - Instance vector added with the sent vector
vector2D vector2D::vecAdd(vector2D &other)
{
	vector2D add(0, 0);

	add.vecOrigin[0] = other.vecOrigin[0] + vecOrigin[0];
	add.vecOrigin[1] = other.vecOrigin[1] + vecOrigin[1];

	return add;
}

//Subtraction - Instance vector minus the sent vector
vector2D vector2D::vecSub(vector2D &other)
{
	vector2D sub(0, 0);

	sub.vecOrigin[0] = other.vecOrigin[0] - vecOrigin[0];
	sub.vecOrigin[1] = other.vecOrigin[1] - vecOrigin[1];

	return sub;
}

//Cross Product
float vector2D::crossProd(vector2D &other)
{
	float crossProduct;

	crossProduct = other.vecOrigin[0] * vecOrigin[1] - other.vecOrigin[1] * vecOrigin[0];

	return crossProduct;
}

//Dot Product
float vector2D::dotProd(vector2D &other)
{
	float dotProduct = 0;

	dotProduct = other.vecOrigin[0] * vecOrigin[0] + other.vecOrigin[1] * vecOrigin[1];

	return dotProduct;
}

//Length
float vector2D::vecLength()
{
	float length;
	float squareA = vecOrigin[0] * vecOrigin[0];
	float squareB = vecOrigin[1] * vecOrigin[1];
	length = sqrt(squareA + squareB);
	return length;
}

//Normalisering
float vector2D::vecNormilisation()
{
	float length;
	float norm;

	float squareA = vecOrigin[0] * vecOrigin[0];
	float squareB = vecOrigin[1] * vecOrigin[1];

	length = sqrt(squareA + squareB);

	norm = ((vecOrigin[0] / length) + (vecOrigin[1] / length));

	return norm;
}

//Get
float vector2D::vecGet(int i)
{
	if (i > 2)
	{
		cout << "Error! Index out of range, max value is 1" << endl;
		return NULL;
	}
	else
	{
		return vecOrigin[i];
	}
}

//Set
void vector2D::vecSet(float x, float y)
{
	this->vecOrigin[0] = x;
	this->vecOrigin[1] = y;
}

//Operator *
float vector2D::operator*(const vector2D &other)
{
	return(this->vecOrigin[0] * other.vecOrigin[0]) + (this->vecOrigin[1] * other.vecOrigin[1]);
}

//Operator *
vector2D vector2D::operator*(float x)
{
	this->vecOrigin[0] *= x;
	this->vecOrigin[1] *= x;
	return *this;
}

//Operator +
vector2D vector2D::operator+(vector2D other)
{
	vector2D addOp(0, 0);

	addOp.vecOrigin[0] = vecOrigin[0] + other.vecOrigin[0];
	addOp.vecOrigin[1] = vecOrigin[1] + other.vecOrigin[1];

	return addOp;
}

//Operator -
vector2D vector2D::operator-(vector2D other)
{
	vector2D subOp(0, 0);

	subOp.vecOrigin[0] = vecOrigin[0] - other.vecOrigin[0];
	subOp.vecOrigin[1] = vecOrigin[1] - other.vecOrigin[1];

	return subOp;
}

//Operator ==
bool vector2D::operator==(vector2D &other)
{
	return vecOrigin[0] == other.vecOrigin[0] && vecOrigin[1] == other.vecOrigin[1];
}

//Operator !=
bool vector2D::operator!=(vector2D &other)
{
	return vecOrigin[0] != other.vecOrigin[0] && vecOrigin[1] != other.vecOrigin[1];
}

//Operator =
vector2D vector2D::operator=(const vector2D &other)
{
	for (int i = 0; i < 3; ++i)
		vecOrigin[i] = other.vecOrigin[i];
	return *this;
}