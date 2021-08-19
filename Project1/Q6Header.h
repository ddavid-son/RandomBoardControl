#pragma once
#include "Q2Header.h"
typedef unsigned char BYTE;

/*QUESTION 6 DECLERATIONS*/
#define MASK 0x7
#define BTR 5

int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);
int fileok(FILE* f);
void freefunc(movesList* molist, boardPos* arr);
int checkforvalidmoves(boardPos* arr, int size, char** board, movesList* molist, movesArray** moves);
int moveisfound(moveCell* step, movesArray moves);
movesList* arrtomovelist(boardPos* arr, movesList* molist, short size);
boardPos* buildcordarr(FILE* f, double size, boardPos* start);
void inserttoend(movesList* molist, moveCell* newnode);
moveCell* createnewnode(char rows, char cols);
char merg(BYTE part1, BYTE part2, int* left);
char nomerg(int* left, char read);
movesList* initlist();
short countasterisk(char** board);