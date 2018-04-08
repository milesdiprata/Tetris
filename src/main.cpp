//
//  Tetris
//
//  Created by Miles di Prata on 2018-03-30.
//  Copyright � 2018 Miles di Prata. All rights reserved.
//

#include <SDL2/SDL.h>
#include "IO.h"
#include "Pieces.h"
#include "Board.h"
#include "Game.h"

const int WAIT_TIME = 700;

int main(int argc, char * args[])
{
	IO IOService;
	Pieces pieces;
	Board board(&pieces);
	Game game = Game(&board, &pieces, &IOService);

	unsigned long timeBefore = SDL_GetTicks(); // ms

	while (!IOService.HasUserQuit() && !board.IsGameOver())
	{
		IOService.ClearScreen();
		game.DrawAll();
		IOService.UpdateScreen();

		// Horizontal movement
		int keyPressed = IOService.GetKeyPress();
		switch (keyPressed)
		{
		case SDLK_LEFT:
			if (board.IsLegalMove(game.CurrentPiece, game.CurrentPiecePosX - 1, game.CurrentPiecePosY, game.CurrentPieceRotation))
				game.CurrentPiecePosX--;
			break;
		case SDLK_RIGHT:
			if (board.IsLegalMove(game.CurrentPiece, game.CurrentPiecePosX + 1, game.CurrentPiecePosY, game.CurrentPieceRotation))
				game.CurrentPiecePosX++;
			break;
		case SDLK_DOWN:
			if (board.IsLegalMove(game.CurrentPiece, game.CurrentPiecePosX, game.CurrentPiecePosY + 1, game.CurrentPieceRotation))
				game.CurrentPiecePosY++;
			break;
		case SDLK_x:
                game.DropPiece();
			break;
		case SDLK_z:
                game.RotatePiece();
			break;
		}

		// Vertical movement
		unsigned long timeAfter = SDL_GetTicks();
		if (timeAfter - timeBefore > WAIT_TIME)
		{
			if (board.IsLegalMove(game.CurrentPiece, game.CurrentPiecePosX, game.CurrentPiecePosY + 1, game.CurrentPieceRotation))
			{
				game.CurrentPiecePosY++;
			}
			else
			{
				board.StorePiece(game.CurrentPiece, game.CurrentPiecePosX, game.CurrentPiecePosY, game.CurrentPieceRotation);
				board.DeleteCompletedLines();
				game.CreatePiece();
			}

			timeBefore = SDL_GetTicks();
		}

	}

	return 0;
}

