#include "pixelpush.h"
#include "vector.h"


#include <thread>
#include <chrono>
#include <iostream>
#include <string>

using namespace std::this_thread;
//using namespace sf;
using namespace std::chrono;
using namespace std;

PixelArray *pixel = nullptr;
int screeHeight;// = PIXEL_HEIGHT / 2;
int screenWidth;// = PIXEL_WIDTH / 2;


Pixel color(int red, int green, int blue, int alpha)
{
	Pixel col;
	//Yellow
	col.r = red;
	col.g = green;
	col.b = blue;
	col.a = alpha;

	return col;
}

//Min/\Max X
float minX(vector3f a, vector3f b, vector3f c)
{
	float value;

	if (a.x < b.x && a.x < c.x)
	{
		value = a.x;
	}
	else if (b.x < c.x)
	{
		value = b.x;
	}
	else
	{
		value = c.x;
	}

	if (value < 0)
		value = 0;

	if (value >= PIXEL_WIDTH)
		value = PIXEL_WIDTH - 1;

	return value;
}
float maxX(vector3f a, vector3f b, vector3f c)
{
	float value;

	if (a.x > b.x && a.x > c.x)
	{
		value = a.x;
	}
	else if (b.x > c.x)
	{
		value = b.x;
	}
	else
	{
		value = c.x;
	}

	if (value < 0)
		value = 0;

	if (value >= PIXEL_WIDTH)
		value = PIXEL_WIDTH - 1;

	return value;
}
//Min/\Max Y
float minY(vector3f a, vector3f b, vector3f c)
{
	float value;

	if (a.y < b.y && a.y < c.y)
	{
		value = a.y;
	}
	else if (b.y < c.y)
	{
		value = b.y;
	}
	else
	{
		value = c.y;
	}

	if (value < 0)
		value = 0;

	if (value >= PIXEL_HEIGHT)
		value = PIXEL_HEIGHT - 1;

	return value;
}
float maxY(vector3f a, vector3f b, vector3f c)
{
	float value;

	if (a.y > b.y && a.y > c.y)
	{
		value = a.y;
	}
	else if (b.y > c.y)
	{
		value = b.y;
	}
	else
	{
		value = c.y;
	}

	if (value < 0)
		value = 0;

	if (value >= PIXEL_HEIGHT)
		value = PIXEL_HEIGHT - 1;

	return value;
}

/*

To fill triangle, calculate if the point you are trying to color in is greater than the point to its right
initiate the starting point from the highest point in space, check it against the lowest, then to the horizontal to increase performance instead of checking the entire screen
each frame

check each of the vectors against each other to start

*/



void DrawFilledTriangle(vector3f a, vector3f b, vector3f c, Pixel col)
{
	//cout << ".";

	vector3f AB = a - b;
	vector3f BC = b - c;
	vector3f CA = c - a;
		  
	vector3f AB_Perp(-AB.y, AB.x, 0);
	vector3f BC_Perp(-BC.y, BC.x, 0);
	vector3f CA_Perp(-CA.y, CA.x, 0);

	//Draw Imaginary Box to check filled triangle
	float top = minY(a, b, c),
		bottom = maxY(a, b, c),
		left = minX(a, b, c),
		right = maxX(a, b, c);

	//bool value = true;
	//int intvalue = (value == true) ? 5 : 45; //ternary operator 
	
	for (int j = bottom; j > top; j--)
	{
		for (int i = left; i < right; i++)
		{
			vector3f vec(i,j,0);
			
			float dotproductA = Dot(AB_Perp, vec - a);
			float dotproductB = Dot(BC_Perp, vec - b);
			float dotproductC = Dot(CA_Perp, vec - c);

			//cout << dotproductA << endl;
			//cout << dotproductB << endl;
			//cout << dotproductC << endl;
			//cout << endl << endl;

			/*if (dotproductA < 0 && dotproductB < 0 && dotproductC < 0)
			{	
				pixel->pixel[(int)j][(int)i] = col;				
			}*/

			if (dotproductA > 0 && dotproductB > 0 && dotproductC > 0)
			{
				pixel->pixel[(int)j][(int)i] = col;
			}
		}
	}

}


void DrawTriangle(int size, vector3f a, Pixel col)
{
	pixel->pixel[(int)a.y][(int)a.x] = col;

	for (int i = 0; i < size; i++)
	{
		pixel->pixel[(int)a.y  + i][(int)a.x + i] = col;

		for (int x = 0; x < size; x++)
		{
			pixel->pixel[(int)a.y + x][(int)a.x - x] = col;

			for (int z = 0; z < size; z++)
			{
				pixel->pixel[(int)a.y + size][(int)a.x + z] = col;
				pixel->pixel[(int)a.y + size][(int)a.x - z] = col;
			}
		}
	}
}


//TODO: Draw a 2D triangle in 3D space rotating with arbitrary axis

void DrawTriangle3D(int size, vector3f a, Pixel col)
{
	
	pixel->pixel[(int)a.y][(int)a.x] = col;

	for (int i = 0; i < size; i++)
	{
		pixel->pixel[(int)a.y + i][(int)a.x + i] = col;

		for (int x = 0; x < size; x++)
		{
			pixel->pixel[(int)a.y + x][(int)a.x - x] = col;

			for (int z = 0; z < size; z++)
			{
				pixel->pixel[(int)a.y + size][(int)a.x + z] = col;
				pixel->pixel[(int)a.y + size][(int)a.x - z] = col;
			}
		}
	}
}


void cls(PixelArray *pixelData, Pixel col)
{
	for (int j = 0; j < PIXEL_HEIGHT; j++)
	{
		for (int i = 0; i < PIXEL_WIDTH; i++)
		{
			pixel->pixel[j][i] = col;
		}
	}
}

void MyGame(PixelArray *pixelData, const bool *bQuit)
{
	pixel = pixelData;
	//pixelData-> pointer



	//TODO: REMOVE FAKE CRAP
	float c = 1.0f,
		g = 1.0f;
	vector3f vec = vector3f(180, 120, 0);

	while (!*bQuit)
	{
		cls(pixelData , color(0, 0, 0, 255));



		Matrix t, r, v;
		vector3f v1 = { 45,90,0 };
		vector3f v2 = vector3f(75, 20,0);
		vector3f v3 = vector3f(22, 13,0);
		
		const int numTris = 4;
		vector3f tri[numTris][3] =
		{
			{
				{ -40,-40,-40 },
				{   0,+40,-40 },
				{   0,  0, 40}
			},
			{
				{   0,  0, 40 },
				{   0,+40,-40 },
				{ +40,-40,-40 }
			},
			{
				{ -40,-40,-40 },
				{   0,  0, 40 },
				{ +40,-40,-40 }
			},
			{
				{ -40,-40,-40 },
				{ +40,-40,-40 },
				{   0, 40,-40 }
			}

		};
		
		Pixel col[numTris] =
		{
			color(255, 0, 0, 255),
			color(0, 255, 0, 255),
			color(0, 0, 255, 255),
			color(255, 255, 0, 255)
		};
		
		//vec.y -= 1.0f;
		t.SetTranslation(vec);
		//TODO: Fix 
		r.SetRotationY(c++);		
		v =  t * r;
		//t.TrasformMatrix(v1);
		//t.TrasformMatrix(v2);
		//t.TrasformMatrix(v3);

		for (int i = 0; i < numTris; i++)
		{
			DrawFilledTriangle(v * tri[i][0], v * tri[i][1], v * tri[i][2], col[i]);
		}

		sleep_for(std::chrono::milliseconds(30));
	}
}

int main()
{
	// So we've got an indie-game look, we're going to use a classic 320x240 resolution
	// and scale up the window four times. This should give us nice & fat pixels
	const int scale = 3;
	screeHeight = PIXEL_HEIGHT / 2;
	screenWidth = PIXEL_WIDTH / 2;

	PixelPusher::Initialise(scale);

	PixelPusher::Run(MyGame);

	PixelPusher::Cleanup();

	return EXIT_SUCCESS;
}