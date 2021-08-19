#pragma once
#include "Q1Header.h"

/*QUESTION 2 DECLERATIONS*/
typedef struct _moveCell {
	Move move;
	struct _moveCell* next, *prev;
} moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;

void init(char** newboard, char** board);
int display(movesList* moves_list, boardPos start, char** board);
void freearr(char** board);
void printboard(char** board);
void printcontent(char** board, int i);
void printhead();
void printline();
char** makeboard();
moveCell* dellink(movesList* list, moveCell* remove, int* delcount);
BOOL is_valid_move(char r, char c, char** boardtoprint);