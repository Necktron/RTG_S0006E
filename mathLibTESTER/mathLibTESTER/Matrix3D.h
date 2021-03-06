#pragma once
#include <iostream>
#include "Vector3D.h"
#include "math.h"
#include <cmath>

using namespace std;

class matrix3D
{
public:
	//Basic constructors
	matrix3D();
	matrix3D(float, float, float, float, float, float, float, float, float);
	matrix3D(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

	//Identity constructor
	matrix3D(char flag);

	//Copy constructor
	matrix3D(const matrix3D &other);

	//Destructor
	~matrix3D();

	//Main matrix that you play around with
	float mxOrigin[4][4];

	//Operators
	matrix3D operator*(matrix3D other);
	vector3D operator*(const vector3D &other);
	matrix3D operator=(const matrix3D &other);

	//Functions		
	float getmxComp(int x, int y);
	void setmxComp(int x, int y, float value);
	vector3D vectorToMatrix(vector3D other);
	matrix3D transpose();
	matrix3D inverse();
	matrix3D mxRotX(float angle);
	matrix3D mxRotY(float angle);
	matrix3D mxRotZ(float angle);
	matrix3D mxRotAroundVec(vector3D arbit, float angle);
	matrix3D translationMatrix(vector3D pos);
	void setPosition(vector3D);
	vector3D getPosition();
};

//Empty constructor
matrix3D::matrix3D()
{

}

//Constructor with components
matrix3D::matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
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

//Constructor with components
matrix3D::matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	mxOrigin[0][0] = a;
	mxOrigin[0][1] = b;
	mxOrigin[0][2] = c;
	mxOrigin[0][3] = d;

	mxOrigin[1][0] = e;
	mxOrigin[1][1] = f;
	mxOrigin[1][2] = g;
	mxOrigin[1][3] = h;

	mxOrigin[2][0] = i;
	mxOrigin[2][1] = j;
	mxOrigin[2][2] = k;
	mxOrigin[2][3] = l;

	mxOrigin[3][0] = m;
	mxOrigin[3][1] = n;
	mxOrigin[3][2] = o;
	mxOrigin[3][3] = p;
}

//Index matrix constructor
matrix3D::matrix3D(char flag)
{
	if (flag == 'I')
	{
		mxOrigin[0][0] = 1;
		mxOrigin[0][1] = 0;
		mxOrigin[0][2] = 0;
		mxOrigin[0][3] = 0;

		mxOrigin[1][0] = 0;
		mxOrigin[1][1] = 1;
		mxOrigin[1][2] = 0;
		mxOrigin[1][3] = 0;

		mxOrigin[2][0] = 0;
		mxOrigin[2][1] = 0;
		mxOrigin[2][2] = 1;
		mxOrigin[2][3] = 0;

		mxOrigin[3][0] = 0;
		mxOrigin[3][1] = 0;
		mxOrigin[3][2] = 0;
		mxOrigin[3][3] = 1;
	}
}

//Copy Constructor
matrix3D::matrix3D(const matrix3D &other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
}

//Destructor
matrix3D::~matrix3D()
{

}

//Get element
float matrix3D::getmxComp(int x, int y)
{
	if (x > 2 || y > 2)
	{
		cout << "Error! Index out of range, max value is 2" << endl;
		return 0;
	}
	else
	{
		return mxOrigin[x][y];
	}
}

//Set element
void matrix3D::setmxComp(int x, int y, float value)
{
	mxOrigin[x][y] = value;
}

//Transformation of 3D vector
vector3D matrix3D::vectorToMatrix(vector3D other)
{
	vector3D vecMx(0, 0, 0);

	vecMx.vecOrigin[0] = mxOrigin[0][0] * other.vecOrigin[0] + mxOrigin[0][1] * other.vecOrigin[1] + mxOrigin[0][2] * other.vecOrigin[2] + mxOrigin[0][3] * other.vecOrigin[3];
	vecMx.vecOrigin[1] = mxOrigin[1][0] * other.vecOrigin[0] + mxOrigin[1][1] * other.vecOrigin[1] + mxOrigin[1][2] * other.vecOrigin[2] + mxOrigin[1][3] * other.vecOrigin[3];
	vecMx.vecOrigin[2] = mxOrigin[2][0] * other.vecOrigin[0] + mxOrigin[2][1] * other.vecOrigin[1] + mxOrigin[2][2] * other.vecOrigin[2] + mxOrigin[2][3] * other.vecOrigin[3];
	vecMx.vecOrigin[3] = mxOrigin[3][0] * other.vecOrigin[0] + mxOrigin[3][1] * other.vecOrigin[1] + mxOrigin[3][2] * other.vecOrigin[2] + mxOrigin[3][3] * other.vecOrigin[3];

	return vecMx;
}

//Transpose of 3D matrix
matrix3D matrix3D::transpose()
{
	matrix3D mxTranspose(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	mxTranspose.mxOrigin[0][0] = mxOrigin[0][0];
	mxTranspose.mxOrigin[0][1] = mxOrigin[1][0];
	mxTranspose.mxOrigin[0][2] = mxOrigin[2][0];
	mxTranspose.mxOrigin[0][3] = mxOrigin[3][0];

	mxTranspose.mxOrigin[1][0] = mxOrigin[0][1];
	mxTranspose.mxOrigin[1][1] = mxOrigin[1][1];
	mxTranspose.mxOrigin[1][2] = mxOrigin[2][1];
	mxTranspose.mxOrigin[1][3] = mxOrigin[3][1];

	mxTranspose.mxOrigin[2][0] = mxOrigin[0][2];
	mxTranspose.mxOrigin[2][1] = mxOrigin[1][2];
	mxTranspose.mxOrigin[2][2] = mxOrigin[2][2];
	mxTranspose.mxOrigin[2][3] = mxOrigin[3][2];

	mxTranspose.mxOrigin[3][0] = mxOrigin[0][3];
	mxTranspose.mxOrigin[3][1] = mxOrigin[1][3];
	mxTranspose.mxOrigin[3][2] = mxOrigin[2][3];
	mxTranspose.mxOrigin[3][3] = mxOrigin[3][3];

	return mxTranspose;
}

//Inverse
matrix3D matrix3D::inverse()
{
	matrix3D mxInverse(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	float* A11 = &this->mxOrigin[0][0];
	float* A12 = &this->mxOrigin[0][1];
	float* A13 = &this->mxOrigin[0][2];
	float* A14 = &this->mxOrigin[0][3];

	float* A21 = &this->mxOrigin[1][0];
	float* A22 = &this->mxOrigin[1][1];
	float* A23 = &this->mxOrigin[1][2];
	float* A24 = &this->mxOrigin[1][3];

	float* A31 = &this->mxOrigin[2][0];
	float* A32 = &this->mxOrigin[2][1];
	float* A33 = &this->mxOrigin[2][2];
	float* A34 = &this->mxOrigin[2][3];

	float* A41 = &this->mxOrigin[3][0];
	float* A42 = &this->mxOrigin[3][1];
	float* A43 = &this->mxOrigin[3][2];
	float* A44 = &this->mxOrigin[3][3];

	//Calculates the determinant
	float detA = ((*A11 * *A22 * *A33 * *A44) + (*A11 * *A23 * *A34 * *A42) + (*A11 * *A24 * *A32 * *A42) + (*A12 * *A21 * *A34 * *A43) + (*A12 * *A23 * *A31 * *A44) + (*A12 * *A24 * *A33 * *A41) + (*A13 * *A21 * *A32 * *A44) + (*A13 * *A22 * *A34 * *A41) + (*A13 * *A24 * *A31 * *A42) + (*A14 * *A21 * *A33 * *A42) + (*A14 * *A22 * *A31 * *A43) + (*A14 * *A23 * *A32 * *A41) - (*A11 * *A22 * *A34 * *A43) - (*A11 * *A23 * *A32 * *A44) - (*A11 * *A24 * *A33 * *A42) - (*A12 * *A21 * *A33 * *A44) - (*A12 * *A23 * *A34 * *A41) - (*A12 * *A24 * *A31 * *A43) - (*A13 * *A21 * *A34 * *A42) - (*A13 * *A22 * *A31 * *A44) - (*A13 * *A24 * *A32 * *A41) - (*A14 * *A21 * *A32 * *A43) - (*A14 * *A22 * *A33 * *A41) - (*A14 * *A23 * *A31 * *A42));

	if (detA == 0)
	{
		cout << "The determinant is equal to zero, no inverse exsists!" << endl;
		return mxInverse;
	}

	else
	{
		cout << detA << endl;

		mxInverse.mxOrigin[0][0] = (1 / detA) * (*A22 * *A33 * *A44 + *A23 * *A34 * *A42 + *A24 * *A32 * *A43 - *A22 * *A34 * *A43 - *A23 * *A32 * *A44 - *A24 * *A33 * *A42); //KLAR
		mxInverse.mxOrigin[0][1] = (1 / detA) * (*A12 * *A34 * *A43 + *A13 * *A32 * *A44 + *A14 * *A33 * *A42 - *A12 * *A33 * *A44 - *A13 * *A34 * *A42 - *A14 * *A32 * *A43); //KLAR
		mxInverse.mxOrigin[0][2] = (1 / detA) * (*A12 * *A23 * *A44 + *A13 * *A24 * *A42 + *A14 * *A22 * *A43 - *A12 * *A24 * *A43 - *A13 * *A22 * *A44 - *A14 * *A23 * *A42); //KLAR
		mxInverse.mxOrigin[0][3] = (1 / detA) * (*A12 * *A24 * *A33 + *A13 * *A22 * *A34 + *A14 * *A23 * *A32 - *A12 * *A23 * *A34 - *A13 * *A24 * *A32 - *A14 * *A22 * *A33); //KLAR


		mxInverse.mxOrigin[1][0] = (1 / detA) * (*A21 * *A34 * *A43 + *A23 * *A31 * *A44 + *A24 * *A33 * *A41 - *A21 * *A33 * *A44 - *A23 * *A34 * *A41 - *A24 * *A31 * *A43); //KLAR
		mxInverse.mxOrigin[1][1] = (1 / detA) * (*A11 * *A33 * *A44 + *A13 * *A34 * *A41 + *A14 * *A31 * *A43 - *A11 * *A34 * *A43 - *A13 * *A31 * *A44 - *A14 * *A33 * *A41); //KLAR
		mxInverse.mxOrigin[1][2] = (1 / detA) * (*A11 * *A24 * *A43 + *A13 * *A21 * *A44 + *A14 * *A23 * *A41 - *A11 * *A23 * *A44 - *A13 * *A24 * *A41 - *A14 * *A21 * *A43); //KLAR
		mxInverse.mxOrigin[1][3] = (1 / detA) * (*A11 * *A23 * *A34 + *A13 * *A24 * *A31 + *A14 * *A21 * *A33 - *A11 * *A24 * *A33 - *A13 * *A21 * *A34 - *A14 * *A23 * *A31); //KLAR


		mxInverse.mxOrigin[2][0] = (1 / detA) * (*A21 * *A32 * *A44 + *A22 * *A34 * *A41 + *A24 * *A31 * *A42 - *A21 * *A34 * *A42 - *A22 * *A31 * *A44 - *A24 * *A32 * *A41); //KLAR
		mxInverse.mxOrigin[2][1] = (1 / detA) * (*A11 * *A34 * *A42 + *A12 * *A31 * *A44 + *A14 * *A32 * *A41 - *A11 * *A32 * *A44 - *A12 * *A34 * *A41 - *A14 * *A31 * *A42); //KLAR
		mxInverse.mxOrigin[2][2] = (1 / detA) * (*A11 * *A22 * *A44 + *A12 * *A24 * *A41 + *A14 * *A21 * *A42 - *A11 * *A24 * *A42 - *A12 * *A21 * *A44 - *A14 * *A22 * *A41); //KLAR	
		mxInverse.mxOrigin[2][3] = (1 / detA) * (*A11 * *A24 * *A32 + *A12 * *A21 * *A34 + *A14 * *A22 * *A31 - *A11 * *A22 * *A34 - *A12 * *A24 * *A31 - *A14 * *A21 * *A32); //KLAR


		mxInverse.mxOrigin[3][0] = (1 / detA) * (*A21 * *A33 * *A42 + *A22 * *A31 * *A43 + *A23 * *A32 * *A41 - *A21 * *A32 * *A43 - *A22 * *A33 * *A41 - *A23 * *A31 * *A42); //KLAR
		mxInverse.mxOrigin[3][1] = (1 / detA) * (*A11 * *A32 * *A43 + *A12 * *A33 * *A41 + *A13 * *A31 * *A42 - *A11 * *A33 * *A42 - *A12 * *A31 * *A43 - *A13 * *A32 * *A41); //KLAR
		mxInverse.mxOrigin[3][2] = (1 / detA) * (*A11 * *A23 * *A42 + *A12 * *A21 * *A43 + *A13 * *A22 * *A41 - *A11 * *A22 * *A43 - *A12 * *A23 * *A41 - *A13 * *A21 * *A42); //KLAR	
		mxInverse.mxOrigin[3][3] = (1 / detA) * (*A11 * *A22 * *A33 + *A12 * *A23 * *A31 + *A13 * *A21 * *A32 - *A11 * *A23 * *A32 - *A12 * *A21 * *A33 - *A13 * *A22 * *A31); //KLAR

		return mxInverse;
	}
}

//Rotation for matrix around X
matrix3D matrix3D::mxRotX(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (mxOrigin[0][0] * 1);
	mxRotated.mxOrigin[0][1] = (mxOrigin[0][1] * 0);
	mxRotated.mxOrigin[0][2] = (mxOrigin[0][2] * 0);
	mxRotated.mxOrigin[0][3] = (mxOrigin[0][3] * 0);

	mxRotated.mxOrigin[1][0] = (mxOrigin[1][0] * 0);
	mxRotated.mxOrigin[1][1] = (mxOrigin[1][1] * cos(degToRad));
	mxRotated.mxOrigin[1][2] = (mxOrigin[1][2] * -sin(degToRad));
	mxRotated.mxOrigin[1][3] = (mxOrigin[1][3] * 0);

	mxRotated.mxOrigin[2][0] = (mxOrigin[2][0] * 0);
	mxRotated.mxOrigin[2][1] = (mxOrigin[2][1] * sin(degToRad));
	mxRotated.mxOrigin[2][2] = (mxOrigin[2][2] * cos(degToRad));
	mxRotated.mxOrigin[2][3] = (mxOrigin[2][3] * 0);

	mxRotated.mxOrigin[3][0] = (mxOrigin[3][0] * 0);
	mxRotated.mxOrigin[3][1] = (mxOrigin[3][1] * 0);
	mxRotated.mxOrigin[3][2] = (mxOrigin[3][2] * 0);
	mxRotated.mxOrigin[3][3] = (mxOrigin[3][3] * 1);

	return mxRotated;
}

//Rotation for matrix around Y
matrix3D matrix3D::mxRotY(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (mxOrigin[0][0] * cos(degToRad));
	mxRotated.mxOrigin[0][1] = (mxOrigin[0][1] * 0);
	mxRotated.mxOrigin[0][2] = (mxOrigin[0][2] * sin(degToRad));
	mxRotated.mxOrigin[0][3] = (mxOrigin[0][3] * 0);

	mxRotated.mxOrigin[1][0] = (mxOrigin[1][0] * 0);
	mxRotated.mxOrigin[1][1] = (mxOrigin[1][1] * 1);
	mxRotated.mxOrigin[1][2] = (mxOrigin[1][2] * 0);
	mxRotated.mxOrigin[1][3] = (mxOrigin[1][3] * 0);

	mxRotated.mxOrigin[2][0] = (mxOrigin[2][0] * -sin(degToRad));
	mxRotated.mxOrigin[2][1] = (mxOrigin[2][1] * 0);
	mxRotated.mxOrigin[2][2] = (mxOrigin[2][2] * cos(degToRad));
	mxRotated.mxOrigin[2][3] = (mxOrigin[2][3] * 0);

	mxRotated.mxOrigin[3][0] = (mxOrigin[3][0] * 0);
	mxRotated.mxOrigin[3][1] = (mxOrigin[3][1] * 0);
	mxRotated.mxOrigin[3][2] = (mxOrigin[3][2] * 0);
	mxRotated.mxOrigin[3][3] = (mxOrigin[3][3] * 1);

	return mxRotated;
}

//Rotation for matrix around Z
matrix3D matrix3D::mxRotZ(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (mxOrigin[0][0] * cos(degToRad));
	mxRotated.mxOrigin[0][1] = (mxOrigin[0][1] * -sin(degToRad));
	mxRotated.mxOrigin[0][2] = (mxOrigin[0][2] * 0);
	mxRotated.mxOrigin[0][3] = (mxOrigin[0][3] * 0);

	mxRotated.mxOrigin[1][0] = (mxOrigin[1][0] * sin(degToRad));
	mxRotated.mxOrigin[1][1] = (mxOrigin[1][1] * cos(degToRad));
	mxRotated.mxOrigin[1][2] = (mxOrigin[1][2] * 0);
	mxRotated.mxOrigin[1][3] = (mxOrigin[1][3] * 0);

	mxRotated.mxOrigin[2][0] = (mxOrigin[2][0] * 0);
	mxRotated.mxOrigin[2][1] = (mxOrigin[2][1] * 0);
	mxRotated.mxOrigin[2][2] = (mxOrigin[2][2] * 1);
	mxRotated.mxOrigin[2][3] = (mxOrigin[2][3] * 0);

	mxRotated.mxOrigin[3][0] = (mxOrigin[3][0] * 0);
	mxRotated.mxOrigin[3][1] = (mxOrigin[3][1] * 0);
	mxRotated.mxOrigin[3][2] = (mxOrigin[3][2] * 0);
	mxRotated.mxOrigin[3][3] = (mxOrigin[3][3] * 1);

	return mxRotated;
}


//*********************************

//Rotation for matrix around arbitrary vector
matrix3D matrix3D::mxRotAroundVec(vector3D arbit, float angle)
{
	matrix3D arbitRot(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	float u = arbit.vecGet(0);
	float v = arbit.vecGet(1);
	float w = arbit.vecGet(2);

	float L = (u*u + v * v + w * w);

	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);
	
	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w;

	arbitRot.mxOrigin[0][0] = (u2 + (v2 + w2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[0][1] = (u * v * (1 - cos(degToRad)) - w * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[0][2] = (u * w * (1 - cos(degToRad)) + v * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[0][3] = 0.0;

	arbitRot.mxOrigin[1][0] = (u * v * (1 - cos(degToRad)) + w * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[1][1] = (v2 + (u2 + w2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[1][2] = (v * w * (1 - cos(degToRad)) - u * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[1][3] = 0.0;

	arbitRot.mxOrigin[2][0] = (u * w * (1 - cos(degToRad)) - v * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[2][1] = (v * w * (1 - cos(degToRad)) + u * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[2][2] = (w2 + (u2 + v2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[2][3] = 0.0;

	arbitRot.mxOrigin[3][0] = 0.0;
	arbitRot.mxOrigin[3][1] = 0.0;
	arbitRot.mxOrigin[3][2] = 0.0;
	arbitRot.mxOrigin[3][3] = 1.0;

	return arbitRot;
}

//Operator *, vector and matrix
vector3D matrix3D::operator*(const vector3D &other)
{
	vector3D ockelbo;

	ockelbo.vecOrigin[0] = (this->mxOrigin[0][0] * other.vecOrigin[0]) + (this->mxOrigin[0][1] * other.vecOrigin[1]) + (this->mxOrigin[0][2] * other.vecOrigin[2]) + (this->mxOrigin[0][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[1] = (this->mxOrigin[1][0] * other.vecOrigin[0]) + (this->mxOrigin[1][1] * other.vecOrigin[1]) + (this->mxOrigin[1][2] * other.vecOrigin[2]) + (this->mxOrigin[1][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[2] = (this->mxOrigin[2][0] * other.vecOrigin[0]) + (this->mxOrigin[2][1] * other.vecOrigin[1]) + (this->mxOrigin[2][2] * other.vecOrigin[2]) + (this->mxOrigin[2][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[3] = (this->mxOrigin[3][0] * other.vecOrigin[0]) + (this->mxOrigin[3][1] * other.vecOrigin[1]) + (this->mxOrigin[3][2] * other.vecOrigin[2]) + (this->mxOrigin[3][3] * other.vecOrigin[3]);

	return ockelbo;
}

//Operator *, matrix and matrix
matrix3D matrix3D::operator*(matrix3D other)
{
	matrix3D mxMult(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	mxMult.mxOrigin[0][0] = other.mxOrigin[0][0] * mxOrigin[0][0] + other.mxOrigin[0][1] * mxOrigin[1][0] + other.mxOrigin[0][2] * mxOrigin[2][0] + other.mxOrigin[0][3] * mxOrigin[3][0];
	mxMult.mxOrigin[0][1] = other.mxOrigin[0][0] * mxOrigin[0][1] + other.mxOrigin[0][1] * mxOrigin[1][1] + other.mxOrigin[0][2] * mxOrigin[2][1] + other.mxOrigin[0][3] * mxOrigin[3][1];
	mxMult.mxOrigin[0][2] = other.mxOrigin[0][0] * mxOrigin[0][2] + other.mxOrigin[0][1] * mxOrigin[1][2] + other.mxOrigin[0][2] * mxOrigin[2][2] + other.mxOrigin[0][3] * mxOrigin[3][2];
	mxMult.mxOrigin[0][3] = other.mxOrigin[0][0] * mxOrigin[0][3] + other.mxOrigin[0][1] * mxOrigin[1][3] + other.mxOrigin[0][2] * mxOrigin[2][3] + other.mxOrigin[0][3] * mxOrigin[3][3];

	mxMult.mxOrigin[1][0] = other.mxOrigin[1][0] * mxOrigin[0][0] + other.mxOrigin[1][1] * mxOrigin[1][0] + other.mxOrigin[1][2] * mxOrigin[2][0] + other.mxOrigin[1][3] * mxOrigin[3][0];
	mxMult.mxOrigin[1][1] = other.mxOrigin[1][0] * mxOrigin[0][1] + other.mxOrigin[1][1] * mxOrigin[1][1] + other.mxOrigin[1][2] * mxOrigin[2][1] + other.mxOrigin[1][3] * mxOrigin[3][1];
	mxMult.mxOrigin[1][2] = other.mxOrigin[1][0] * mxOrigin[0][2] + other.mxOrigin[1][1] * mxOrigin[1][2] + other.mxOrigin[1][2] * mxOrigin[2][2] + other.mxOrigin[1][3] * mxOrigin[3][2];
	mxMult.mxOrigin[1][3] = other.mxOrigin[1][0] * mxOrigin[0][3] + other.mxOrigin[1][1] * mxOrigin[1][3] + other.mxOrigin[1][2] * mxOrigin[2][3] + other.mxOrigin[1][3] * mxOrigin[3][3];

	mxMult.mxOrigin[2][0] = other.mxOrigin[2][0] * mxOrigin[0][0] + other.mxOrigin[2][1] * mxOrigin[1][0] + other.mxOrigin[2][2] * mxOrigin[2][0] + other.mxOrigin[2][3] * mxOrigin[3][0];
	mxMult.mxOrigin[2][1] = other.mxOrigin[2][0] * mxOrigin[0][1] + other.mxOrigin[2][1] * mxOrigin[1][1] + other.mxOrigin[2][2] * mxOrigin[2][1] + other.mxOrigin[2][3] * mxOrigin[3][1];
	mxMult.mxOrigin[2][2] = other.mxOrigin[2][0] * mxOrigin[0][2] + other.mxOrigin[2][1] * mxOrigin[1][2] + other.mxOrigin[2][2] * mxOrigin[2][2] + other.mxOrigin[2][3] * mxOrigin[3][2];
	mxMult.mxOrigin[2][3] = other.mxOrigin[2][0] * mxOrigin[0][3] + other.mxOrigin[2][1] * mxOrigin[1][3] + other.mxOrigin[2][2] * mxOrigin[2][3] + other.mxOrigin[2][3] * mxOrigin[3][3];

	mxMult.mxOrigin[3][0] = other.mxOrigin[3][0] * mxOrigin[0][0] + other.mxOrigin[3][1] * mxOrigin[1][0] + other.mxOrigin[3][2] * mxOrigin[2][0] + other.mxOrigin[3][3] * mxOrigin[3][0];
	mxMult.mxOrigin[3][1] = other.mxOrigin[3][0] * mxOrigin[0][1] + other.mxOrigin[3][1] * mxOrigin[1][1] + other.mxOrigin[3][2] * mxOrigin[2][1] + other.mxOrigin[3][3] * mxOrigin[3][1];
	mxMult.mxOrigin[3][2] = other.mxOrigin[3][0] * mxOrigin[0][2] + other.mxOrigin[3][1] * mxOrigin[1][2] + other.mxOrigin[3][2] * mxOrigin[2][2] + other.mxOrigin[3][3] * mxOrigin[3][2];
	mxMult.mxOrigin[3][3] = other.mxOrigin[3][0] * mxOrigin[0][3] + other.mxOrigin[3][1] * mxOrigin[1][3] + other.mxOrigin[3][2] * mxOrigin[2][3] + other.mxOrigin[3][3] * mxOrigin[3][3];

	return mxMult;
}

//Operator =
matrix3D matrix3D::operator=(const matrix3D &other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
	return *this;
}

//Translation Matrix
matrix3D matrix3D::translationMatrix(vector3D pos)
{
	matrix3D translation;

	translation.mxOrigin[0][0] = 1;
	translation.mxOrigin[0][1] = 0;
	translation.mxOrigin[0][2] = 0;
	translation.mxOrigin[0][3] = 0;

	translation.mxOrigin[1][0] = 0;
	translation.mxOrigin[1][1] = 1;
	translation.mxOrigin[1][2] = 0;
	translation.mxOrigin[1][3] = 0;

	translation.mxOrigin[2][0] = 0;
	translation.mxOrigin[2][1] = 0;
	translation.mxOrigin[2][2] = 1;
	translation.mxOrigin[2][3] = 0;

	translation.mxOrigin[3][0] = pos.vecGet(0);
	translation.mxOrigin[3][1] = pos.vecGet(1);
	translation.mxOrigin[3][2] = pos.vecGet(2);
	translation.mxOrigin[3][3] = 1;

	return translation;
}

//Set 3D
void matrix3D::setPosition(vector3D pos)
{
	mxOrigin[2][0] = pos.vecGet(0);
	mxOrigin[2][1] = pos.vecGet(1);
	mxOrigin[2][2] = pos.vecGet(2);
}

vector3D matrix3D::getPosition()
{
	return vector3D(mxOrigin[2][0], mxOrigin[2][1], mxOrigin[2][2]);
}