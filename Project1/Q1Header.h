#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define N 5 ///rows
#define M 4 ///cols
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define ROWLETTER 0
#define COLNUMBER 1

/*QUESTION 1 DECLERATIONS*/
typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move *moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos *positions;
} boardPosArray;

void freeFunc(char** board, movesArray** moves, boardPosArray** boardPosArr);
void freeBoard(char** board);
void FreeBoardPosArray(boardPosArray** boardPosArr);
void freeMoves2DArray(movesArray** moves);
boardPosArray ** validMoves(movesArray **moves, char **board);
boardPosArray ** makeEmptyboardPosArray();
BOOL isValidMove(Move aMove, int row, int col, char **board);