#pragma once

using namespace std;
#include <iostream>

struct vector3f
{
	float x, y, z;
	vector3f();

	explicit vector3f(float a) : x(a), y(a), z(a) {}
	vector3f(float a, float b, float c);
	float Magnitude();
	explicit operator float() { return Magnitude(); }
};

struct Matrix
{
	float matrix[4][4];

	Matrix(int r, int c)
	{
		matrix[r][c];

		for (int i = 0; i < r; i++)
		{
			for (int z = 0; z < c; z++)
			{
				matrix[i][z] = 0;
				cout << matrix[i][z] << "  ";
			}
			cout << endl;
		}
	}

	//4v4 matrix
	//float matrix[4][4];

	//TODO: Create a Scale matrix

	Matrix();

	void SetRotationZYX(float z, float y, float x);

	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);

	void SetIdentityMatrix();

	void SetTranslation(const vector3f &v)
	{
		SetIdentityMatrix();
		matrix[0][3] = v.x;
		matrix[1][3] = v.y;
		matrix[2][3] = v.z;
	}
};

//Matrix SetTranslation(vector3f &v);
Matrix SetPosition();
Matrix SetScale(float x, float y, float z);

void PrintMatrix(Matrix &t);

float Dot(vector3f &a, vector3f &b);

Matrix operator *(Matrix &t1, Matrix &t2);

vector3f operator *(Matrix &t, vector3f &v2);
vector3f operator -(vector3f &v1, vector3f &v2);
