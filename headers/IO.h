#pragma once
#include <SDL2/SDL.h>

enum Color { RED, BLUE, GREEN, ORANGE, CYAN, YELLOW, MAGENTA, AMBER };

class IO
{
public:
	IO();
	~IO();

	void InitalizeGraphics();
	void ClearScreen();
	void UpdateScreen();
	void DrawRectangle(const int x, const int y, const int width, const int height, const Color color);
    void DrawRectangleOutline(const int x, const int y, const int width, const int height, const Color color);
	int GetKeyPress();
	bool HasUserQuit();

private:
	SDL_Window * _window;
	SDL_Renderer * _renderer;
    void SetRendererColor(const Color color);
};
