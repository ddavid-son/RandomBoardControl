#include "Q3Header.h"

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board)
{
	boardPosArray **boardPosArrayTemp;
	pathTree startPaths;

	boardPosArrayTemp = validMoves(moves, board);
	printForCheck(boardPosArrayTemp);
	boardPos* prevMoves = NULL;
	buildTheTreeRec(start, &(startPaths.head), boardPosArrayTemp, &prevMoves, 0); ///create empty paths tree with start as head

	FreeBoardPosArray(boardPosArrayTemp);
	return startPaths;
}

/*This function creates a tree of all possible paths recursively, connecting the nodes through pointers*/
void buildTheTreeRec(boardPos root, treeNode** node, boardPosArray** boardPosArrayTemp, boardPos** prevMoves, int numOfPrevMoves)
{
	boardPos nextPosition;
	treeNodeListCell* temp = NULL;
	char rootRowI = root[ROWLETTER] - 'A', rootColI = root[COLNUMBER] - '1';
	char numOfMoves = boardPosArrayTemp[rootRowI][rootColI].size, i;
	*node = createEmptyTree(root);

		for (i = 0; i < numOfMoves; i++)
		{
			nextPosition[ROWLETTER] = boardPosArrayTemp[rootRowI][rootColI].positions[i][ROWLETTER];
			nextPosition[COLNUMBER] = boardPosArrayTemp[rootRowI][rootColI].positions[i][COLNUMBER];
			if (moveIsNotPrevMove(root, *prevMoves, numOfPrevMoves)) ///if new root wasn't a previous move, add it now to be one
			{
				addMoveToPrevMoves(root, prevMoves, numOfPrevMoves);
				numOfPrevMoves++;
			}
			if (moveIsNotPrevMove(nextPosition, *prevMoves, numOfPrevMoves)) ///if next position wasn't a previous move, create a new sub-tree
			{	
				(*node)->next_possible_positions = createNextPossiblePosition();
				temp = (*node)->next_possible_positions; ////delte
				buildTheTreeRec(nextPosition, &(temp->node), boardPosArrayTemp, prevMoves, numOfPrevMoves);
				(*node)->next_possible_positions = (*node)->next_possible_positions->next;
			}
			numOfPrevMoves--; ///remove last added "prevMove"
		}
		(*node)->next_possible_positions = temp; ///redirect next_possible_positions to original value
		if (numOfPrevMoves == 0) ///free prevMoves array when end of last iteration
			free(*prevMoves);
}

/*This function creates a tree with a single leaf - the root*/
treeNode* createEmptyTree(boardPos position)
{
	treeNode* node;
	node = (treeNode*)malloc(sizeof(treeNode));
	node->position[ROWLETTER] = position[ROWLETTER];
	node->position[COLNUMBER] = position[COLNUMBER];
	node->next_possible_positions = NULL;
	return node;
}

treeNodeListCell* createNextPossiblePosition()
{
	treeNodeListCell* newListCell;
	newListCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	newListCell->next = NULL;
	newListCell->node = NULL;
	return newListCell;
}

/*This function checks to see if currentMove was an earlier move of the branch via prevMvoes array*/
BOOL moveIsNotPrevMove(boardPos currentMove, boardPos* prevMoves, int numOfPrevMoves)
{
	int i;
	for (i = 0; i < numOfPrevMoves; i++)
	{
		if (currentMove[ROWLETTER] == prevMoves[i][ROWLETTER]
			&& currentMove[COLNUMBER] == prevMoves[i][COLNUMBER])
			return FALSE; ///false -> move was a previous move
	}
	return TRUE;
}

/*This function adds moves to an array indicating moves already looked through, in an all-paths-tree*/
void addMoveToPrevMoves(boardPos toAdd, boardPos** prevMoves, int numOfPrevMoves)
{
	static int allocationCounter = 1;
	if (numOfPrevMoves == 0) ///why is it doing a new malloc?????
	{
		allocationCounter = 1; ///for re-use of function purposes
		if (*prevMoves == NULL)
		{
			(*prevMoves) = (boardPos*)malloc(sizeof(boardPos));
			assert((*prevMoves) != NULL);
		}
	}
	else if (numOfPrevMoves == allocationCounter)
	{
		allocationCounter *= 2;
		(*prevMoves) = (boardPos*)realloc((*prevMoves), sizeof(boardPos) * allocationCounter);
		assert((*prevMoves) != NULL);
	}
	(*prevMoves)[numOfPrevMoves][ROWLETTER] = toAdd[ROWLETTER];
	(*prevMoves)[numOfPrevMoves][COLNUMBER] = toAdd[COLNUMBER];
}

/*This function frees an all-paths-tree*/
void freePathsTree(pathTree startPaths)
{
	freePathsTreeRec(startPaths.head);
	free(startPaths.head);
}

/*Helper function recursively to free an all-paths-tree*/
void freePathsTreeRec(treeNode* node)
{
	treeNodeListCell* tempListCell = node->next_possible_positions;
	while (node->next_possible_positions != NULL)
	{
		tempListCell = node->next_possible_positions;
		if (tempListCell->node != NULL)
			freePathsTreeRec(tempListCell->node);
		node->next_possible_positions = node->next_possible_positions->next;
		free(tempListCell->node);
		free(tempListCell);
	}
}