#include "Q1Header.h"

boardPosArray ** validMoves(movesArray **moves, char **board)
{
	boardPosArray ** validMovesArray;
	unsigned int iR, iC, i, newIndex = 0, specialIndex;
	char moveRows, moveCols;

	validMovesArray = makeEmptyboardPosArray();

	for (iR = 0; iR < N; iR++)
	{
		for (iC = 0; iC < M; iC++)
		{
			validMovesArray[iR][iC].size = 0; ///start counter for valid moves for specific coordinations
			validMovesArray[iR][iC].positions = malloc(sizeof(boardPos) * moves[iR][iC].size); ///max possible size for positions, reallocated later
			assert(validMovesArray[iR][iC].positions != NULL);
	
			for (specialIndex = 0, i = 0, newIndex = 0; i < moves[iR][iC].size; i++)
			{
				if (isValidMove(moves[iR][iC].moves[i], iR, iC, board))
				{
					
					moveRows = moves[iR][iC].moves[i].rows;
					moveCols = moves[iR][iC].moves[i].cols;
					validMovesArray[iR][iC].positions[specialIndex][ROWLETTER] = (char)(iR + 'A' + moveRows); ///Letter of row
					validMovesArray[iR][iC].positions[specialIndex][COLNUMBER] = (char)(iC + '1' + moveCols); ///Number of col
					validMovesArray[iR][iC].size++;
					moves[iR][iC].moves[newIndex] = moves[iR][iC].moves[i]; ///copy a valid move back to the movesArray
					newIndex++;		
					specialIndex++;
				}
			}
			if (validMovesArray[iR][iC].size > 0) ///resize allocated arrays according to updated size
			{
				validMovesArray[iR][iC].positions = realloc(validMovesArray[iR][iC].positions, sizeof(boardPos) * validMovesArray[iR][iC].size);
				assert(validMovesArray[iR][iC].positions != NULL);
				moves[iR][iC].moves = realloc(moves[iR][iC].moves, sizeof(Move) * validMovesArray[iR][iC].size);
				assert(moves[iR][iC].moves != NULL);
			}
			else
			{
				free(validMovesArray[iR][iC].positions);
				free(moves[iR][iC].moves);
				validMovesArray[iR][iC].positions = NULL;
				moves[iR][iC].moves = NULL;
			}
			moves[iR][iC].size = validMovesArray[iR][iC].size;
		}
	}
	return validMovesArray;
}

boardPosArray ** makeEmptyboardPosArray()
{
	boardPosArray ** validMovesArray;
	unsigned int iR;

	validMovesArray = malloc(sizeof(boardPosArray*) * N);
	assert(validMovesArray != NULL);

	for (iR = 0; iR < N; iR++)
	{
		validMovesArray[iR] = malloc(sizeof(boardPosArray) * M);
		assert(validMovesArray[iR] != NULL);
	}
	return validMovesArray;
}

BOOL isValidMove(Move aMove, int row, int col, char **board)
{
	if (row + aMove.rows < 0 || N - 1 < row + aMove.rows)
		return FALSE;
	else if (col + aMove.cols < 0 || M - 1 < col + aMove.cols)
		return FALSE;
	else if (board[row + aMove.rows][col + aMove.cols] == '*')
		return FALSE;
	else
		return TRUE;
}

void freeFunc(char **board, movesArray **moves, boardPosArray **boardPosArr)
{
	freeBoard(board);
	FreeBoardPosArray(boardPosArr);
	freeMoves2DArray(moves);
}

void freeBoard(char** board)
{
	for (int i = 0; i < N; i++)
	{
		free(board[i]);
	}
	free(board);
}

void FreeBoardPosArray(boardPosArray** boardPosArr)
{
	boardPosArray* tempBPA;
	for (int i = 0; i < N; i++)
	{
		tempBPA = boardPosArr[i];
		for (int t = 0; t < M; t++)
		{
			if (boardPosArr[i][t].positions != NULL)
				free(boardPosArr[i][t].positions);
		}
		free(tempBPA);
	}
	free(boardPosArr);
}

void freeMoves2DArray(movesArray** moves)
{
	movesArray* tempMoves;
	for (int i = 0; i < N; i++)
	{
		tempMoves = moves[i];
		for (int t = 0; t < M; t++)
		{
			if (moves[i][t].moves != NULL)
				free(moves[i][t].moves);
		}
		free(tempMoves);
	}
	free(moves);
}
