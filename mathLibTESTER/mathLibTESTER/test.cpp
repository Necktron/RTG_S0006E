#pragma once
#include <iostream>
#include "Matrix3D.h"
#include "Vector3D.h"

matrix3D matrix(4, 5, 1, 2, 3, 4, 5, 6, 2, 2, 7, 1, 2, 4, 3, 5);
vector3D vector(7, 2, 7)

cout << matrix.vectorToMatrix(vector); << endl;