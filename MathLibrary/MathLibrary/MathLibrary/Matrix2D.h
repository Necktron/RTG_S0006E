#pragma once
#include <iostream>
#include "Vector2D.h"
#include "math.h"

using namespace std;

class matrix2D
{
	public:
		//Basic constructors
		matrix2D();
		matrix2D(float, float, float, float);
		matrix2D(float, float, float, float, float, float, float, float, float);
		
		//Identity constructor
		matrix2D(char flag);

		//Copy constructor
		matrix2D(const matrix2D &other);

		//Destructor
		~matrix2D();

		//Main matrix that you play around with
		float mxOrigin[3][3];

		//Operators
		matrix2D operator*(matrix2D other);
		vector2D operator*(const vector2D &other);
		matrix2D operator=(const matrix2D &other);

		//Functions		
		float getmxComp(int x, int y);
		void setmxComp(int x, int y, float value);
		vector2D vectorToMatrix(vector2D other);
		static matrix2D transpose(matrix2D &mx);
		static matrix2D mxRot(float angle);
		matrix2D translationMatrix(vector2D pos);
		void setPosition(vector2D);
		vector2D getPosition();
};

//Empty constructor
matrix2D::matrix2D()
{

}

//Constructor with components
matrix2D::matrix2D(float a, float b, float c, float d)
{
	mxOrigin[0][0] = a;
	mxOrigin[0][1] = b;
	mxOrigin[1][0] = c;
	mxOrigin[1][1] = d;
}

//Constructor with components
matrix2D::matrix2D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	mxOrigin[0][0] = a;
	mxOrigin[0][1] = b;
	mxOrigin[0][2] = c;

	mxOrigin[1][0] = d;
	mxOrigin[1][1] = e;
	mxOrigin[1][2] = f;

	mxOrigin[2][0] = g;
	mxOrigin[2][1] = h;
	mxOrigin[2][2] = i;
}

//Index matrix constructor
matrix2D::matrix2D(char flag)
{
	if (flag == 'I')
	{
		mxOrigin[0][0] = 1;
		mxOrigin[0][1] = 0;
		mxOrigin[0][2] = 0;

		mxOrigin[1][0] = 0;
		mxOrigin[1][1] = 1;
		mxOrigin[1][2] = 0;

		mxOrigin[2][0] = 0;
		mxOrigin[2][1] = 0;
		mxOrigin[2][2] = 1;
	}
}

//Copy Constructor
matrix2D::matrix2D(const matrix2D &other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
}

//Destructor
matrix2D::~matrix2D()
{

}

//Get
float matrix2D::getmxComp(int x, int y)
{
	if (x > 2 || y > 2)
	{
		cout << "Error! Index out of range, max value is 1" << endl;
		return NULL;
	}
	else
	{
		return mxOrigin[x][y];
	}
}

//Set
void matrix2D::setmxComp(int x, int y, float value)
{
	mxOrigin[x][y] = value;
}

//Transformation of 2D vector
vector2D matrix2D::vectorToMatrix(vector2D other)
{
	vector2D vecMx(0, 0);

	vecMx.vecOrigin[0] = mxOrigin[0][0] * other.vecOrigin[0] + mxOrigin[0][1] * other.vecOrigin[0];
	vecMx.vecOrigin[1] = mxOrigin[1][0] * other.vecOrigin[1] + mxOrigin[1][1] * other.vecOrigin[1];

	return vecMx;
}

//Transpose of 2D matrix
matrix2D matrix2D::transpose(matrix2D &other)
{
	return matrix2D(other.mxOrigin[0][0], other.mxOrigin[1][0], other.mxOrigin[0][1], other.mxOrigin[1][1]);
}

//Rotation matrix
matrix2D matrix2D::mxRot(float angle)
{
	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);
	return matrix2D(cos(degToRad), -sin(degToRad), sin(degToRad), cos(degToRad));
}

//Operator *
vector2D matrix2D::operator*(const vector2D &other)
{
	vector2D ockelbo;

	ockelbo.vecOrigin[0] = (this->mxOrigin[0][0] * other.vecOrigin[0]) + (this->mxOrigin[0][1] * other.vecOrigin[1]) + (this->mxOrigin[0][2] * other.vecOrigin[2]);
	ockelbo.vecOrigin[1] = (this->mxOrigin[1][0] * other.vecOrigin[0]) + (this->mxOrigin[1][1] * other.vecOrigin[1]) + (this->mxOrigin[1][2] * other.vecOrigin[2]);
	ockelbo.vecOrigin[2] = (this->mxOrigin[2][0] * other.vecOrigin[0]) + (this->mxOrigin[2][1] * other.vecOrigin[1]) + (this->mxOrigin[2][2] * other.vecOrigin[2]);

	return ockelbo;
}

//Operator *
matrix2D matrix2D::operator*(matrix2D other)
{
	matrix2D mxMult(0, 0, 0, 0, 0, 0, 0, 0, 0);

	mxMult.mxOrigin[0][0] = other.mxOrigin[0][0] * mxOrigin[0][0] + other.mxOrigin[0][1] * mxOrigin[1][0];
	mxMult.mxOrigin[0][1] = other.mxOrigin[0][0] * mxOrigin[0][1] + other.mxOrigin[0][1] * mxOrigin[1][1];
	mxMult.mxOrigin[0][2] = other.mxOrigin[0][0] * mxOrigin[0][2] + other.mxOrigin[0][1] * mxOrigin[1][2];

	mxMult.mxOrigin[1][0] = other.mxOrigin[1][0] * mxOrigin[0][0] + other.mxOrigin[1][1] * mxOrigin[1][0];
	mxMult.mxOrigin[1][1] = other.mxOrigin[1][0] * mxOrigin[0][1] + other.mxOrigin[1][1] * mxOrigin[1][1];
	mxMult.mxOrigin[1][2] = other.mxOrigin[2][0] * mxOrigin[0][2] + other.mxOrigin[2][1] * mxOrigin[1][2];

	mxMult.mxOrigin[2][0] = other.mxOrigin[2][0] * mxOrigin[0][0] + other.mxOrigin[2][1] * mxOrigin[1][0];
	mxMult.mxOrigin[2][1] = other.mxOrigin[1][0] * mxOrigin[0][1] + other.mxOrigin[2][1] * mxOrigin[1][1];
	mxMult.mxOrigin[2][2] = other.mxOrigin[2][0] * mxOrigin[0][2] + other.mxOrigin[2][1] * mxOrigin[1][2];

	return mxMult;
}

//Operator =
matrix2D matrix2D::operator=(const matrix2D &other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
	return *this;
}

//Translation Matrix
matrix2D matrix2D::translationMatrix(vector2D pos)
{
	matrix2D translation;

	translation.mxOrigin[0][0] = 1;
	translation.mxOrigin[0][1] = 0;
	translation.mxOrigin[0][2] = 0;

	translation.mxOrigin[1][0] = 0;
	translation.mxOrigin[1][1] = 1;
	translation.mxOrigin[1][2] = 0;

	translation.mxOrigin[2][0] = pos.vecGet(0);
	translation.mxOrigin[2][1] = pos.vecGet(1);
	translation.mxOrigin[2][2] = 1;

	return translation;
}

//Set 3D
void matrix2D::setPosition(vector2D pos)
{
	mxOrigin[2][0] = pos.vecGet(0);
	mxOrigin[2][1] = pos.vecGet(1);
}

vector2D matrix2D::getPosition()
{
	return vector2D(mxOrigin[2][0], mxOrigin[2][1]);
}