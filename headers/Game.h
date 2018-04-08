#pragma once

#include "IO.h"
#include "Board.h"
#include "Pieces.h"

class Game
{
public:
	Game(Board * board, Pieces * pieces, IO * ioService);
	~Game();

	PieceType CurrentPiece;
	int CurrentPiecePosX;
	int CurrentPiecePosY;
	int CurrentPieceRotation;

	void DrawAll();
	void CreatePiece();
    void RotatePiece();
    void DropPiece();

private:

	Board * _board;
	Pieces * _pieces;
	IO * _ioService;

	PieceType _nextPiece;
	int _nextPiecePosX;
	int _nextPiecePosY;
	int _nextPieceRotation;

	int GetRandomInt(const int min, const int max);
	void InitializeGame();
	Color GetPieceTypeColor(const PieceType pieceType);
    int GetPieceMaxPosY();
	void DrawPiece(const PieceType pieceType, const int posX, const int posY, const int rotation);
    void DrawPieceFuturePos();
	void DrawBoard();
	void DrawStoredPieces();
};

