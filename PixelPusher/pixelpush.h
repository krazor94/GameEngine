// [ pixelpush.h ]
// This header helps you easily build a pixel rendering system that will
// handle all the refreshing and updating work, letting you just focus on
// setting values for the pixels
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <windows.h>

const int PIXEL_WIDTH = 320;
const int PIXEL_HEIGHT = 240;

struct Pixel
{
	sf::Uint8 r, g, b, a;
};

struct PixelArray
{
	union {
	
		sf::Uint8	raw[PIXEL_WIDTH * PIXEL_HEIGHT * 4];
		Pixel		pixel[PIXEL_HEIGHT][PIXEL_WIDTH];

	};
};

typedef void(*GameFunction)(PixelArray *pixelData, const bool *bQuit);

class PixelPusher
{
public:
	static void Initialise(int scale);
	static void Run( GameFunction g );
	static void Cleanup();

private:
	static void PixelRenderThreadFn();

	static HINSTANCE				instance;
	static HWND						window;

	static PixelArray	*			pixelData;
	static sf::RenderWindow *		sfmlView;
	static sf::Texture *			pixelTexture;
	static sf::Sprite *				pixelSprite;

	static bool						bQuit;
};

