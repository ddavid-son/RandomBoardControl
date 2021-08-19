#pragma once
#include "Q1Header.h"

/*QUESTION 3 DECLERATIONS*/
typedef struct _treeNodeListCell treeNodeListCell;
typedef struct _treeNode treeNode;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell* next_possible_positions; /// location list
} treeNode;
typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;
typedef struct _pathTree {
	treeNode* head;
} pathTree;

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);
void buildTheTreeRec(boardPos root, treeNode** node, boardPosArray** boardPosArrayTemp, boardPos** prevMoves, int numOfPrevMoves);
treeNode* createEmptyTree(boardPos position);
treeNodeListCell* createNextPossiblePosition();
BOOL moveIsNotPrevMove(boardPos currentMove, boardPos* prevMoves, int numOfPrevMoves);
void printForCheck(boardPosArray** boardPosArrayTemp);
void addMoveToPrevMoves(boardPos toAdd, boardPos** prevMoves, int numOfPrevMoves);
void freePathsTree(pathTree startPaths);
void freePathsTreeRec(treeNode* node);