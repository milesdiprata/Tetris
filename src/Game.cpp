#include <stdlib.h>
#include "Game.h"


Game::Game(Board * board, Pieces * pieces, IO * ioService)
{
	_board = board;
	_pieces = pieces;
	_ioService = ioService;

	InitializeGame();
}

Game::~Game()
{
}

void Game::DrawAll()
{
	DrawBoard();
	DrawStoredPieces();
	DrawPiece(CurrentPiece, CurrentPiecePosX, CurrentPiecePosY, CurrentPieceRotation);
    DrawPieceFuturePos();
	DrawPiece(_nextPiece, _nextPiecePosX, _nextPiecePosY, _nextPieceRotation);
}

void Game::CreatePiece()
{
	CurrentPiece = _nextPiece;
	CurrentPiecePosX = _pieces->GetPieceInitialPosX(CurrentPiece, CurrentPieceRotation) + (BOARD_WIDTH_BLOCKS / 2) - 1;
	CurrentPiecePosY = _pieces->GetPieceInitialPosY(CurrentPiece, CurrentPieceRotation);
	CurrentPieceRotation = GetRandomInt(0, 3);

	_nextPiece = (PieceType)GetRandomInt(SQUARE, T);
}

int Game::GetRandomInt(const int min, const int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}

void Game::InitializeGame()
{
	_nextPiece = (PieceType)GetRandomInt(SQUARE, T);
	_nextPiecePosX = BOARD_WIDTH_BLOCKS + 5;
	_nextPiecePosY = 5;
	_nextPieceRotation = GetRandomInt(0, 3);

	CreatePiece();
}

Color Game::GetPieceTypeColor(const PieceType pieceType)
{
	switch (pieceType)
	{
	case SQUARE:
		return YELLOW;
	case L:
		return RED;
	case L_MIRRORED:
		return CYAN;
	case N:
		return AMBER;
	case N_MIRRORED:
		return MAGENTA;
	case I:
		return ORANGE;
	case T:
		return GREEN;
	default:
		return BLUE;
	}
}

void Game::DrawPiece(const PieceType pieceType, const int posX, const int posY, const int rotation)
{
	Color color = GetPieceTypeColor(pieceType);

	int posXPixels = _board->GetBoardPosXInPixels(posX);
	int posYPixels = _board->GetBoardPosYInPixels(posY) - 1;

	for (int i = 0; i < PIECE_BLOCK_SIZE; i++)
		for (int j = 0; j < PIECE_BLOCK_SIZE; j++)
			if (_pieces->GetBlockType(pieceType, j, i, rotation) != 0)
				_ioService->DrawRectangle(posXPixels + (i*BLOCK_SIZE), posYPixels + (j*BLOCK_SIZE), BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);
}

void Game::DrawPieceFuturePos()
{
    int translatePosY = GetPieceMaxPosY();
    
    Color color = BLUE;
    int posXPixels = _board->GetBoardPosXInPixels(CurrentPiecePosX);
    int posYPixels = _board->GetBoardPosYInPixels(CurrentPiecePosY + translatePosY);
    
    for (int i = 0; i < PIECE_BLOCK_SIZE; i++)
        for (int j = 0; j < PIECE_BLOCK_SIZE; j++)
            if (_pieces->GetBlockType(CurrentPiece, j, i, CurrentPieceRotation) != 0)
                _ioService->DrawRectangleOutline(posXPixels + (i*BLOCK_SIZE), posYPixels + (j*BLOCK_SIZE), BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);}

void Game::DrawBoard()
{
	_ioService->DrawRectangle(BOARD_SEPERATOR_MARGIN,
		SCREEN_HEIGHT - (BOARD_HEIGHT_BLOCKS * BLOCK_SIZE),
		BOARD_SEPERATOR_THICKNESS,
		BOARD_HEIGHT_BLOCKS * BLOCK_SIZE,
		BLUE);

	_ioService->DrawRectangle(SCREEN_WIDTH - BOARD_SEPERATOR_MARGIN - BOARD_SEPERATOR_THICKNESS,
		SCREEN_HEIGHT - (BOARD_HEIGHT_BLOCKS * BLOCK_SIZE),
		BOARD_SEPERATOR_THICKNESS,
		BOARD_HEIGHT_BLOCKS * BLOCK_SIZE,
		BLUE);
}

void Game::DrawStoredPieces()
{
	PieceType boardState;
	Color color;

	for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++)
		{
			boardState =_board->GetBoardState(i, j );
			if (boardState != UNFILLED)
			{
				color = GetPieceTypeColor(boardState);
				_ioService->DrawRectangle(BOARD_SEPERATOR_MARGIN + BOARD_SEPERATOR_THICKNESS + (i * BLOCK_SIZE),
					SCREEN_HEIGHT - (BOARD_HEIGHT_BLOCKS * BLOCK_SIZE) + (j * BLOCK_SIZE),
					BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);
			}
		}
	}
}

void Game::RotatePiece()
{
    if (CurrentPieceRotation < 3)
    {
        if (_board->IsLegalMove(CurrentPiece, CurrentPiecePosX, CurrentPiecePosY, CurrentPieceRotation + 1))
            CurrentPieceRotation++;
    }
    else
    {
        if (_board->IsLegalMove(CurrentPiece, CurrentPiecePosX, CurrentPiecePosY, 0))
            CurrentPieceRotation = 0;
    }
}

int Game::GetPieceMaxPosY()
{
    int y = 0;
    while (_board->IsLegalMove(CurrentPiece, CurrentPiecePosX, CurrentPiecePosY + y, CurrentPieceRotation))
        y++;
    
    return y - 1;
}

void Game::DropPiece()
{
    int dropLength = GetPieceMaxPosY();
    
    CurrentPiecePosY += dropLength;
    _board->StorePiece(CurrentPiece, CurrentPiecePosX, CurrentPiecePosY, CurrentPieceRotation);
    _board->DeleteCompletedLines();
    CreatePiece();
}
