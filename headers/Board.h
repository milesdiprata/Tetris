#pragma once

#include "Pieces.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 16;
const int BOARD_WIDTH_BLOCKS = 10;
const int BOARD_HEIGHT_BLOCKS = 20;
const int BOARD_SEPERATOR_THICKNESS = 6;
const int BOARD_SEPERATOR_MARGIN = (640 / 2) - ((BOARD_WIDTH_BLOCKS * BLOCK_SIZE) / 2) - BOARD_SEPERATOR_THICKNESS;

class Board
{
public:
	Board(Pieces *pieces);
	~Board();

	int GetBoardPosXInPixels(const int posX);
	int GetBoardPosYInPixels(const int posY);
	PieceType GetBoardState(const int posX, const int posY);
	bool IsLegalMove(const PieceType pieceType, const int posX, const int posY, const int rotation);
	void StorePiece(const PieceType pieceType, const int posX, const int posY, const int rotation);
	void DeleteCompletedLines();
	bool IsGameOver();

private:
	PieceType _board[BOARD_WIDTH_BLOCKS][BOARD_HEIGHT_BLOCKS];
	Pieces *_pieces;

	void InitalizeBoard();
	void DeleteLine(const int posY);
};

