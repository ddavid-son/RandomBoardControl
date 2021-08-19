#pragma once
#include "Q3Header.h"
#include "Q2Header.h"

/*QUESTION 4 DECLERATIONS*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
char findNumToCoverBoard(char** board);
movesList* CreateEmptyList();
BOOL buildCoverListFromTreeRec(treeNode* node, movesList* coverAllPaths, char numCoverBoard);
void insertToStartOfList(treeNode* node, movesList* coverAllPaths);
moveCell* createNewMoveCell(boardPos position, moveCell* next, moveCell* prev);
void freeCoverPathsList(movesList* coverAllPaths);
void freeCoverPathsListRec(moveCell* node);
void fixListToMoves(movesList* coverAllPaths);
void fixListToMovesRec(moveCell* node);