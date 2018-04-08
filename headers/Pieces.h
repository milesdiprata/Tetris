#pragma once

const int PIECE_BLOCK_SIZE = 5;

enum PieceType
{
	SQUARE, I, L, L_MIRRORED, N, N_MIRRORED, T, UNFILLED
};

class Pieces
{
public:
	Pieces();
	~Pieces();

	int GetBlockType(const PieceType pieceType, const int xIndex, const int yIndex, const int rotation);
	int GetPieceInitialPosX(const PieceType pieceType, const int rotation);
	int GetPieceInitialPosY(const PieceType pieceType, const int rotation);
};

