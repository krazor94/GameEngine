#include "pixelpush.h"

#include <SFML/Graphics.hpp>
#include <thread>

LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Quit when we close the main window
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

	}

	return DefWindowProc(handle, message, wParam, lParam);
}

HINSTANCE				PixelPusher::instance = nullptr;
HWND					PixelPusher::window = nullptr;

PixelArray	*			PixelPusher::pixelData = nullptr;
sf::RenderWindow *		PixelPusher::sfmlView = nullptr;
sf::Texture *			PixelPusher::pixelTexture = nullptr;
sf::Sprite *			PixelPusher::pixelSprite = nullptr;
bool					PixelPusher::bQuit = false;

void PixelPusher::Initialise(int scale)
{
	instance = GetModuleHandle(NULL);

	// Define a class for our main window
	WNDCLASS windowClass;
	windowClass.style = 0;
	windowClass.lpfnWndProc = &onEvent;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = NULL;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = TEXT("SFML App");
	RegisterClass(&windowClass);

	// Let's create the main window
	window = CreateWindow(TEXT("SFML App"), TEXT("SFML Win32"), WS_SYSMENU | WS_VISIBLE, 200, 200, PIXEL_WIDTH * scale, PIXEL_HEIGHT * scale, NULL, NULL, instance, NULL);

	// Render window
	sfmlView = new sf::RenderWindow(window);

	pixelData = new PixelArray;
	pixelTexture = new sf::Texture;
	pixelTexture->create(PIXEL_WIDTH, PIXEL_HEIGHT);

	pixelTexture->setSmooth(false);
	pixelSprite = new sf::Sprite(*pixelTexture);
	pixelSprite->setScale((float)scale, (float)scale);
}

void PixelPusher::PixelRenderThreadFn()
{
	// Loop until a WM_QUIT message is received
	MSG message;
	message.message = static_cast<UINT>(~WM_QUIT);
	while (!bQuit)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// Clear views
			sfmlView->clear();

			pixelTexture->update(pixelData->raw);
			sfmlView->draw(*pixelSprite);

			// Display each view on screen
			sfmlView->display();
		}

		if (message.message == WM_QUIT) bQuit = true;
	}
}

void PixelPusher::Run(GameFunction g)
{
	// Launch the pixel pusher thread:
	//std::thread RenderThread(PixelRenderThreadFn);
	
	// Launch the user's game function:
	std::thread GameFunction(g,pixelData, &bQuit);
	PixelRenderThreadFn();
	//RenderThread.join();
	GameFunction.join();
}

void PixelPusher::Cleanup()
{
	DestroyWindow(window);
	UnregisterClass(TEXT("SFML App"), instance);

	delete pixelSprite;
	delete pixelTexture;
	delete pixelData;
	delete sfmlView;

}

