
#include "Q1Header.h"
#include "Q2Header.h"
#include "Q3Header.h"
#include "Q4Header.h"
#include "Q5Header.h"
#include "Q6Header.h"

#define ROWLETTER 0
#define COLNUMBER 1
#define ROWS N
#define COLS M
#define STARTlet 'A' ///letter of start for function 2, 3 and 4
#define STARTnum '1' ///number of start
/*aMovesArr is an array used to create a linked list of moves,
each 2 integers represent a move (first int row, second col, third row, etc...)
each move is added to previous move, so 'start' is not part of arr*/
#define aMovesArrSize 6
int aMovesArr[aMovesArrSize] = { 0,-1,0,-1,1,0 }; // r, c, r, c, r, c....


/**************Functions for Checking only*************/

/*This function prints boardPosArray, meaning all squares and legal moves from them*/
void printForCheck(boardPosArray** boardPosArrayTemp)
{
	for (int iR = 0; iR < N; iR++)
	{
		for (int iC = 0; iC < M; iC++)
		{
			printf("%d %d (%c%c): ", iR, iC, iR + 'A', iC + '1');
			for (unsigned int i = 0; i < boardPosArrayTemp[iR][iC].size; i++)
			{
				printf("%c%c ", boardPosArrayTemp[iR][iC].positions[i][0], boardPosArrayTemp[iR][iC].positions[i][1]);
			}
			printf("\n");
		}
	}
}

/* This function converts a list of moves to a moves
 * array which can be used for checking fucntion 5 */
 /*version 1
 boardPosArray* convertListToArray(movesList* allCoverPath, boardPos start)
 {
	 boardPosArray* boardPosArr = (boardPosArray*)malloc(sizeof(boardPosArray));
	 boardPosArr->positions = (boardPos*)malloc(sizeof(boardPos));
	 moveCell *tempNode = allCoverPath->head;
	 boardPosArr->positions[boardPosArr->size - 1][ROWLETTER] = start[ROWLETTER];
	 boardPosArr->positions[boardPosArr->size - 1][COLNUMBER] = start[COLNUMBER];
	 boardPosArr->size = 1;
	 while (tempNode != NULL)
	 {
		 boardPosArr->size++;
		 boardPosArr->positions = realloc(boardPosArr->positions, sizeof(boardPosArray) * boardPosArr->size);
		 assert(boardPosArr->positions != NULL);
		 boardPosArr->positions[boardPosArr->size - 1][ROWLETTER] = boardPosArr->positions[boardPosArr->size - 2][ROWLETTER] + tempNode->move.rows;
		 boardPosArr->positions[boardPosArr->size - 1][COLNUMBER] = boardPosArr->positions[boardPosArr->size - 2][COLNUMBER] + tempNode->move.cols;
		 tempNode = tempNode->next;
	 }
	 return boardPosArr;
 }
 */

 /*version 2*/
boardPosArray* convertListToArray(movesList* allCoverPath, boardPos start)
{
	boardPosArray* boardPosArr = (boardPosArray*)malloc(sizeof(boardPosArray));
	boardPosArr->positions = (boardPos*)malloc(sizeof(boardPos) * 64);
	moveCell* tempNode = allCoverPath->head;
	boardPosArr->size = 1;
	boardPosArr->positions[0][ROWLETTER] = start[ROWLETTER];
	boardPosArr->positions[0][COLNUMBER] = start[COLNUMBER];

	for (unsigned int i = 1; tempNode != NULL; i++)
	{
		boardPosArr->size++;
		boardPosArr->positions[i][ROWLETTER] = boardPosArr->positions[i - 1][ROWLETTER] + tempNode->move.rows;
		boardPosArr->positions[i][COLNUMBER] = boardPosArr->positions[i - 1][COLNUMBER] + tempNode->move.cols;
		printf("\n%c%c\n", boardPosArr->positions[i][ROWLETTER], boardPosArr->positions[i][COLNUMBER]);
		tempNode = tempNode->next;
	}

	return boardPosArr;
}
/**/

void printTreeRec(treeNode* node, int level)
{
	level++;
	printf("Level %d: %c%c\n", level, node->position[ROWLETTER], node->position[COLNUMBER]);
	treeNodeListCell* temp = node->next_possible_positions;
	while (node != NULL && temp != NULL)
	{
		printTreeRec(temp->node, level + 1);
		temp = temp->next;
	}
}

void printTree(pathTree tree)
{
	printTreeRec(tree.head, 0);
}



movesList* CreateSomeMovesList(int* aMovesArr)
{
	int i;
	movesList* List = (movesList*)malloc(sizeof(movesList));
	List->head = (moveCell*)malloc(sizeof(moveCell));
	moveCell* temp = List->head;

	temp->prev = NULL;
	for (i = 0; i < aMovesArrSize; i += 2)
	{
		temp->move.rows = aMovesArr[i];
		temp->move.cols = aMovesArr[i + 1];
		if (i < aMovesArrSize - 2)
		{
			temp->next = (moveCell*)malloc(sizeof(moveCell));
			assert(temp->next != NULL);
			temp->next->prev = temp;
			temp = temp->next;
		}
	}
	List->tail = temp;
	List->tail->next = NULL;
	return List;
}

void freeBoard2(char** board)
{
	for (int i = 0; i < N; i++)
	{
		free(board[i]);
	}
	free(board);
}

void FreeBoardPosArray2(boardPosArray** boardPosArr)
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

void freeMoves2DArray2(movesArray** moves)
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

void freeFunc2(char** board, movesArray** moves, boardPosArray** boardPosArr)
{
	freeBoard2(board);
	FreeBoardPosArray2(boardPosArr);
	freeMoves2DArray2(moves);
}

void freeCoverPathsListRec2(moveCell* node)
{
	if (node->next != NULL)
		freeCoverPathsListRec2(node->next);
	free(node);
}

void freeCoverPathsList2(movesList* coverAllPaths)
{
	if (coverAllPaths->head != NULL)
		freeCoverPathsListRec2(coverAllPaths->head);
	free(coverAllPaths);
}

void freePathsTreeRec2(treeNode* node)
{
	treeNodeListCell* tempListCell = node->next_possible_positions;
	while (node->next_possible_positions != NULL)
	{
		tempListCell = node->next_possible_positions;
		if (tempListCell->node != NULL)
			freePathsTreeRec2(tempListCell->node);
		node->next_possible_positions = node->next_possible_positions->next;
		free(tempListCell->node);
		free(tempListCell);
	}
}
void freePathsTree2(pathTree startPaths)
{
	freePathsTreeRec2(startPaths.head);
	free(startPaths.head);
}

/******************************************************/
/*char fullBoard[6 * N + 5][2 * M + 3];*/ // <--- no use for this anymore//


/*******************MAIN for Checking*****************/
void main() {


	/******Create board 2D array from file************/
	FILE* boardFile = fopen("matr.txt", "rt");
	char** board = malloc(sizeof(char*) * N);
	for (int i = 0; i < N; i++)
	{
		board[i] = malloc(sizeof(char) * (M + 2)); /// + 1 for '\0'
		fread(board[i], sizeof(char), M + 1, boardFile);
		board[i][M + 1] = '\0';
		printf("%s ", board[i]);
	}
	/**************************************************/

	/**********Create moves 2D array from file*********/
	movesArray** moves = malloc(sizeof(movesArray*) * (N));
	FILE* movesFile = fopen("movesFile.txt", "rt");
	int movesCounter, charCounter;
	char tempChar;
	char tempRow, tempCol;
	int i, t, k;
	for (int i = 0; i < N; i++)
	{
		moves[i] = malloc(sizeof(movesArray) * (M));
	}

	for (i = 0; i < N; i++)
	{
		for (t = 0; t < M; t++)
		{
			movesCounter = 1, charCounter = 1;;
			tempChar = fgetc(movesFile);
			if (tempChar >= '0' && tempChar <= '9')
				movesCounter++;
			while (tempChar != '\n')
			{
				tempChar = fgetc(movesFile);
				if (tempChar >= '0' && tempChar <= '9')
					movesCounter++;
				charCounter++;
			}
			fseek(movesFile, -(charCounter + 1), SEEK_CUR);
			movesCounter /= 2;
			moves[i][t].size = movesCounter;

			if (movesCounter != 0)
			{
				moves[i][t].moves = malloc(sizeof(Move) * movesCounter);
				for (k = 0; k < movesCounter; k++)
				{
					tempRow = fgetc(movesFile);

					if (tempRow == '-')
					{
						tempRow = fgetc(movesFile);
						tempRow -= '0';
						tempRow *= -1;
					}
					else
						tempRow -= '0';
					moves[i][t].moves[k].rows = tempRow;

					tempCol = fgetc(movesFile);

					if (tempCol == '-')
					{
						tempCol = fgetc(movesFile);
						tempCol -= '0';
						tempCol *= -1;
					}
					else
						tempCol -= '0';
					moves[i][t].moves[k].cols = tempCol;

				}
			}
			else ///if empty moves
				moves[i][t].moves = NULL;
			tempChar = fgetc(movesFile); ///re-read newline
			assert(tempChar == '\n');
		}
	}
	/**************************************************/

	/*create a start boardPos for Function 4 and 3*/
	boardPos start;
	start[ROWLETTER] = STARTlet;
	start[COLNUMBER] = STARTnum;
	/*************************************************/

	/***************Check function 1******************/
	boardPosArray** validMovesArray;
	validMovesArray = validMoves(moves, board);
	printForCheck(validMovesArray); //compare print to file yourself
	/*************************************************/

	/***************Check function 2******************/
	movesList* someRoad;
	someRoad = CreateSomeMovesList(aMovesArr);

	int deletedMoves = display(someRoad, start, board);
	printf("\nNumber of deleted moves are:%d \n", deletedMoves);
	/*************************************************/

	/***************Check function 3******************/
	pathTree tree;
	tree = findAllPossiblePaths(start, moves, board);
	printTree(tree);
	freePathsTree2(tree);
	/*************************************************/

	/***************Check function 4******************/
	movesList* allCoverPath;
	int DisplayCounter;
	allCoverPath = findPathCoveringAllBoard(start, moves, board);
	if (allCoverPath != NULL)
	{
		DisplayCounter = display(allCoverPath, start, board);
		printf("\nReturned value from AllCoverPath: %d", DisplayCounter);
	}

	/*************************************************/

	/***************Check function 5******************/
	char* file_name = "movesBinFile";
	boardPosArray* pos_arr;
	if (allCoverPath != NULL)
	{
		pos_arr = convertListToArray(allCoverPath, start);
		saveListToBinFile(file_name, pos_arr);
		free(pos_arr->positions);
		free(pos_arr);
		freeCoverPathsList2(allCoverPath);
	}
	else if (someRoad != NULL)
	{
		pos_arr = convertListToArray(someRoad, start);
		saveListToBinFile(file_name, pos_arr);
		free(pos_arr->positions);
		free(pos_arr);
		freeCoverPathsList2(someRoad);
	}
	/*************************************************/

	/***************Check function 6******************/
	int returnedFromSix;
	returnedFromSix = checkAndDisplayPathFromFile(file_name, moves, board);
	if (returnedFromSix == 1)
		printf("\n1: No legal route found");
	else if (returnedFromSix == 2)
		printf("\n2: Succesful board was created");
	else if (returnedFromSix == 3)
		printf("\n3: A different scenario was encountered");
	else if (returnedFromSix == -1)
		printf("\n-1: No file with the name %s was found", file_name);
	else
		printf("\nUnknown number: Unknown ERROR");
	/*************************************************/
	freeFunc2(board, moves, validMovesArray);
}