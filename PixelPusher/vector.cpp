#include <cmath>
#include <vector>
#include <iostream>

#include "vector.h"

vector3f::vector3f()
	: x(0.0f), y(0.0f), z(0.0f)
{
	// nothing
}

vector3f::vector3f(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
	// nothing
}

float vector3f::Magnitude()
{
	return sqrtf(x*x + y*y + z*z);
}

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int c = 0; c < 4; c++)
		{
			matrix[i][c] = 0;
		}
	}
}

//TODO: SetPosition Matrix
Matrix SetPosition()
{
	Matrix t;

	return t;
}

Matrix SetScale(float x, float y, float z)
{
	Matrix c;

	c.matrix[0][0] = x;
	c.matrix[1][1] = y;
	c.matrix[2][2] = z;

	return c;
}

//set rotation for 3D axis x, y & z
void Matrix::SetRotationZYX(float x, float y, float z)
{
	//calculates in Z Y X order

	//x
	//
	matrix[0][0] = cos(y) * cos(z);
	matrix[0][1] = cos(z) * sin(x) * sin(y) - cos(x) * sin(z);
	matrix[0][2] = cos(x) * cos(z) * sin(y) + sin(x) * sin(z);
	matrix[0][3] = 0;

	//y
	//
	matrix[1][0] = 0;
	matrix[1][1] = cos(y) * sin(z);
	matrix[1][2] = cos(x) * cos(z) + sin(x) + sin(y) + sin(z);
	matrix[1][3] = -cos(z) * sin(x) + cos(x) * sin(y) * sin(z);

	//z
	//
	matrix[2][0] = 0;
	matrix[2][1] = -sin(y);
	matrix[2][2] = cos(y) * sin(x);
	matrix[2][3] = cos(x) * cos(y);

	//w
	//
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

//rotation matrix around x,y,z
//https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnxnbGVubm11cnJheXxneDoyMTJiZTZlNzVlMjFiZTFi

void Matrix::SetRotationX(float angle)
{
	// convert to radian
	angle = angle * 3.14159265359f / 180.0f;

	//x
	//1 0 0 0
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	//y
	//0 cos(angle) -sin(angle) 0
	matrix[1][0] = 0;
	matrix[1][1] = cos(angle);
	matrix[1][2] = -sin(angle);
	matrix[1][3] = 0;

	//z
	//0 sin(angle) cos(angle) 0
	matrix[2][0] = 0;
	matrix[2][1] = sin(angle);
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;

	//w
	//0 0 0 1
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void Matrix::SetRotationY(float angle)
{
	// convert to radian
	angle = angle * 3.14159265359f / 180.0f;

	//x
	//cos(angle) 0 sin(angle) 0
	matrix[0][0] = cos(angle);
	matrix[0][1] = 0;
	matrix[0][2] = sin(angle);
	matrix[0][3] = 0;

	//y
	//0 1 0 0
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	//z
	//-sin(angle) 0 cos(angle) 0
	matrix[2][0] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;

	//w
	//0 0 0 1
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void Matrix::SetRotationZ(float angle)
{
	// convert to radian
	angle = angle * 3.14159265359f / 180.0f;

	//x
	//cos(angle) -sin(angle) 0 0
	matrix[0][0] = cos(angle);
	matrix[0][1] = -sin(angle);
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	//y
	//sin(angle) cos(angle) 0 0
	matrix[1][0] = sin(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	//z
	//0 0 1 0
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	//w
	//0 0 0 1
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

Matrix MultiplyMatrix(Matrix &a, Matrix &b)
{
	Matrix c;

	//First for loop will sort out columns of the new 4x4 matrix
	for (int i = 0; i < 4; i++)
	{
		//Second for loop will sort out rows of the new 4x4 matrix
		for (int x = 0; x < 4; x++)
		{
			c.matrix[i][x] =
				(a.matrix[i][0] * b.matrix[i][x]) +
				(a.matrix[i][1] * b.matrix[i][x]) +
				(a.matrix[i][2] * b.matrix[i][x]) +
				(a.matrix[i][3] * b.matrix[i][x]);
		}
	}
	return c;
}

void PrintMatrix(Matrix &t)
{
	for (int i = 0; i < 4; i++)
	{
		for (int c = 0; c < 4; c++)
		{
			cout << t.matrix[i][c] << "  ";
		}
		cout << endl;
	}
}

void Matrix::SetIdentityMatrix()
{
	//TODO: Set other values to 0, find a more efficient way to do this.
	for (int i = 0; i < 4; i++)
	{
		for (int ii = 0; ii < 4; ii++)
		{
			matrix[i][ii] = 0;
		}
	}

	for (int c = 0; c < 4; c++)
	{
		matrix[c][c] = 1;
	}
}

float Dot(vector3f &a, vector3f &b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void Print(vector3f x)
{
	cout << "The vector's values are: x[" << x.x << "], y[" << x.y << "], z[" << x.z << "]" << endl;
}

Matrix operator *(Matrix &t1, Matrix &t2)
{
	Matrix t;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			t.matrix[j][i] = 0.0f;
			for (int c = 0; c < 4; c++)
			{
				t.matrix[j][i] += t1.matrix[j][c] * t2.matrix[c][i];
			}
		}
	}

	return t;
}

Matrix operator *(Matrix &t, float f)
{
	Matrix t2;

	for (int i = 0; i < 4; i++)
	{
		for (int c = 0; c < 4; c++)
		{
			t2.matrix[i][c] = t.matrix[i][c] * f;
		}
	}

	return t2;
}

vector3f operator *(Matrix &t, vector3f &v)
{
	vector3f v2;

	v2.x = t.matrix[0][0] * v.x + t.matrix[0][1] * v.y + t.matrix[0][2] * v.z + t.matrix[0][3] * 1.0f;
	v2.y = t.matrix[1][0] * v.x + t.matrix[1][1] * v.y + t.matrix[1][2] * v.z + t.matrix[1][3] * 1.0f;
	v2.z = t.matrix[2][0] * v.x + t.matrix[2][1] * v.y + t.matrix[2][2] * v.z + t.matrix[2][3] * 1.0f;

	return v2;
}

vector3f operator -(vector3f &v1, vector3f &v2)
{
	vector3f v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;

	return v;
}