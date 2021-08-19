#include "Q4Header.h"

/*This function will counter home many squares are needed to cover the "board" for "start,
 * using function from Q3, which returns a tree with no repeating moves*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board)
{
	pathTree startPaths;
	movesList* coverAllPaths;
	char numCoverBoard; ///number of squares to cover the board for start
	BOOL listExists = FALSE; ///boolean to hold if a board-covering-path exists or not

	startPaths = findAllPossiblePaths(start, moves, board); ///create tree of all possible paths from start
	numCoverBoard = findNumToCoverBoard(board); ///find how many moves are required to cover board from start

	coverAllPaths = CreateEmptyList(); ///creates empty list without dummy tail or dummy head
	listExists = buildCoverListFromTreeRec(startPaths.head, coverAllPaths, numCoverBoard); ///try to make list of path which covers board
	
	freePathsTree(startPaths); ///free "all-paths" tree
	if (listExists == FALSE)
	{
		freeCoverPathsList(coverAllPaths);
		return NULL;
	}
	else
	{
		fixListToMoves(coverAllPaths);
		return coverAllPaths;
	}
}

/*This function finds how many moves to different squares are
 *required to fill the whole board, excluding illegal squares*/
char findNumToCoverBoard(char **board)
{
	char num;
	char i, j;

	num = M * N;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (board[i][j] == '*')
				num--;
		}
	}
	return num;
}


movesList* CreateEmptyList()
{
	movesList* emptyList;
	emptyList = (movesList*)malloc(sizeof(movesList));
	emptyList->head = NULL;
	emptyList->tail = NULL;
	return emptyList;
}


/*This function  goes recursively through an all-possible-paths tree for specific start square
 *in order to look for a path (a branch) long enough to cover the whole board (according to numCoverBoard)
 *if such branch is found, a linked-list of the moves creating the branch will be created and 'TRUE' will return*/
BOOL buildCoverListFromTreeRec(treeNode* node, movesList* coverAllPaths, char numCoverBoard)
{
	treeNodeListCell* tempListCell;
	BOOL coverAllBoard = FALSE;
	numCoverBoard--;
	if (numCoverBoard == 0) ///indicates branch of moves reached length to cover board
	{
		insertToStartOfList(node, coverAllPaths); ///insert the last move of branch to start of list
		return TRUE;
	}

	tempListCell = node->next_possible_positions;
	while (tempListCell != NULL && coverAllBoard == FALSE) 
	{
		if (tempListCell->node != NULL)
			coverAllBoard = buildCoverListFromTreeRec(tempListCell->node, coverAllPaths, numCoverBoard);
		tempListCell = tempListCell->next;
	}

	if (coverAllBoard == TRUE)
	{
		insertToStartOfList(node, coverAllPaths); ///insert next move from last to first to start of list
		return TRUE;
	}

	else
		return FALSE;
}

void insertToStartOfList(treeNode* node, movesList* coverAllPaths)
{
	if (coverAllPaths->head == NULL)///if this is the first node
	{
		coverAllPaths->head = createNewMoveCell(node->position, NULL, NULL);
		coverAllPaths->tail = coverAllPaths->head;
	}
	else if (coverAllPaths->head->next == NULL)
	{
		coverAllPaths->head = createNewMoveCell(node->position, coverAllPaths->tail, NULL);
		coverAllPaths->tail->prev = coverAllPaths->head;
	}
	else
	{
		coverAllPaths->head = createNewMoveCell(node->position, coverAllPaths->head, NULL);
		coverAllPaths->head->next->prev = coverAllPaths->head;
	}
}

moveCell* createNewMoveCell(boardPos position, moveCell* next, moveCell* prev)
{
	moveCell* newNode;
	newNode = (moveCell*)malloc(sizeof(moveCell));
	newNode->next = next;
	newNode->prev = prev;
	newNode->move.rows = position[ROWLETTER] - 'A';
	newNode->move.cols = position[COLNUMBER] - '1';
	return newNode;
}

void freeCoverPathsList(movesList* coverAllPaths)
{
	if (coverAllPaths->head != NULL)
		freeCoverPathsListRec(coverAllPaths->head);
	free(coverAllPaths);
}

void freeCoverPathsListRec(moveCell* node)
{
	if (node->next != NULL)
		freeCoverPathsListRec(node->next);
	free(node);
}

void fixListToMoves(movesList* coverAllPaths)
{
	fixListToMovesRec(coverAllPaths->head);
	moveCell* temp = coverAllPaths->tail;
	coverAllPaths->tail = coverAllPaths->tail->prev;
	coverAllPaths->tail->next = NULL;
	free(temp);
}

void fixListToMovesRec(moveCell* node)
{
	if ((node->next) != NULL)
	{
		node->move.rows = node->next->move.rows - node->move.rows;
		node->move.cols = node->next->move.cols - node->move.cols;
		fixListToMovesRec(node->next);
	}
}