#include <iostream>
#include "IO.h"

using namespace std;

IO::IO()
{
	_renderer = nullptr;
	_window = nullptr;
	InitalizeGraphics();
}

IO::~IO()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = nullptr;
	_window = nullptr;
	SDL_Quit();
}

void IO::InitalizeGraphics()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "Error initalizing SDL! SDL Error: " << SDL_GetError() << endl;
		return;
	}
	_window = SDL_CreateWindow("Tetris in C++!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		cerr << "Error creating the SDL window! SDL Error: " << SDL_GetError() << endl;
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		cerr << "Error creating the SDL renderer! SDL Error: " << SDL_GetError() << endl;
		return;
	}

}

void IO::SetRendererColor(const Color color)
{
    switch (color)
    {
        case RED:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
            break;
        case BLUE:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
            break;
        case AMBER:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xBF, 0xF0, 0xFF);
            break;
        case GREEN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0x00, 0xFF);
            break;
        case CYAN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0xFF, 0xFF);
            break;
        case MAGENTA:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0xFF, 0xFF);
            break;
        case ORANGE:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xA5, 0x00, 0xFF);
            break;
        case YELLOW:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0x00, 0xFF);
            break;
    }
}

void IO::ClearScreen()
{
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF); // Background Color
	SDL_RenderClear(_renderer);
}

void IO::UpdateScreen()
{
	SDL_RenderPresent(_renderer);
}

void IO::DrawRectangle(const int x, const int y, const int width, const int height, const Color color)
{
	SDL_Rect fillArea = { x, y, width, height };
    SetRendererColor(color);
	SDL_RenderFillRect(_renderer, &fillArea);
}

void IO::DrawRectangleOutline(const int x, const int y, const int width, const int height, const Color color)
{
    SDL_Rect outlineArea = { x, y, width, height };
    SetRendererColor(color);
    SDL_RenderDrawRect(_renderer, &outlineArea);
}


int IO::GetKeyPress()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			return e.key.keysym.sym;
		case SDL_QUIT:
			exit(1);
		}
	}

	return -1;
}

bool IO::HasUserQuit()
{
	return false;
}
