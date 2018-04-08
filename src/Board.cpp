#include "Board.h"

Board::Board(Pieces * pieces)
{
	_pieces = pieces;

	InitalizeBoard();
}

Board::~Board()
{
}

int Board::GetBoardPosXInPixels(const int posX)
{
	return (posX * BLOCK_SIZE) + BOARD_SEPERATOR_MARGIN + BOARD_SEPERATOR_THICKNESS + 1;
}

int Board::GetBoardPosYInPixels(const int posY)
{
	return (posY * BLOCK_SIZE) + SCREEN_HEIGHT - (BOARD_HEIGHT_BLOCKS * BLOCK_SIZE) + 1;
}

PieceType Board::GetBoardState(const int posX, const int posY)
{
	return (PieceType)_board[posX][posY];
}

bool Board::IsLegalMove(const PieceType pieceType, const int posX, const int posY, const int rotation)
{
	/*
	Check each cell of the matrix and comapre it with the corresponding 5x5 area of the board
	-> Board limits
	-> Stored pieces
	*/

	// Used to iterate through the 5x5 board area
	int boardPosX = posX;
	int boardPosY = posY;

	for (int i = 0; i < PIECE_BLOCK_SIZE; i++)
	{
		boardPosY = posY;
		for (int j = 0; j < PIECE_BLOCK_SIZE; j++)
		{
			if (_pieces->GetBlockType(pieceType, j, i, rotation) != 0)
			{
				// Check board limits
				if (boardPosX < 0 || boardPosX > BOARD_WIDTH_BLOCKS - 1 || boardPosY > BOARD_HEIGHT_BLOCKS - 1)
					return false;

				// Check for stored piece
				if (posY >= 0 && _board[boardPosX][boardPosY] != UNFILLED)
					return false;
			}
			boardPosY++;
		}
		boardPosX++;
	}

	return true;
}

void Board::StorePiece(const PieceType pieceType, const int posX, const int posY, const int rotation)
{
	int boardPosX = posX;
	int boardPosY = posY;

	for (int i = 0; i < PIECE_BLOCK_SIZE; i++)
	{
		boardPosY = posY;
		for (int j = 0; j < PIECE_BLOCK_SIZE; j++)
		{
			if (_pieces->GetBlockType(pieceType, j, i, rotation) != 0)
				_board[boardPosX][boardPosY] = pieceType;

			boardPosY++;
		}
		boardPosX++;
	}
}

void Board::DeleteCompletedLines()
{
    for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++)
    {
        for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++)
        {
            if (_board[i][j] == UNFILLED)
                break;
            else if (i == BOARD_WIDTH_BLOCKS - 1)
                DeleteLine(j);
        }
    }
}

bool Board::IsGameOver()
{
    for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++)
        if (_board[i][0] != UNFILLED)
            return true;
            
	return false;
}

void Board::InitalizeBoard()
{
	for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++)
		for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++)
			_board[i][j] = UNFILLED;
}

void Board::DeleteLine(const int posY)
{
    for (int j = posY; j > 0; j--)
        for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++)
            _board[i][j] = _board[i][j - 1];
}
