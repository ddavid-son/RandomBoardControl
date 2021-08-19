#include "Q2Header.h"

int display(movesList* moves_list, boardPos start, char** board) {
	int delcount = 0;
	char r = start[ROWLETTER] - 'A', c = start[COLNUMBER] - '1', moveindex = 1;
	moveCell* temphead = moves_list->head;
	char** boardtoprint = makeboard(); // allocate new board
	init(boardtoprint, board); // copy board to new board and counts asterisks
	boardtoprint[r][c] = '#';// putting starting point on new board

	while (temphead) {

		if (is_valid_move(r + temphead->move.rows, c + temphead->move.cols, boardtoprint)) { // prevent case in which a path is stepping on itself
			r += temphead->move.rows;
			c += temphead->move.cols;
			boardtoprint[r][c] = moveindex++;// put the number of the move and "++" for the next one
			temphead = temphead->next;
		}
		else
			temphead = dellink(moves_list, temphead, &delcount); // will free the the current move, advance delcount by 1, and advance temphead
	}

	printboard(boardtoprint);// print the updated board
	freearr(boardtoprint);
	return delcount;
}

BOOL is_valid_move(char r, char c, char** boardtoprint) {

	if ((r >= 0) && (c < M) && (r < N) && (c >= 0) && (boardtoprint[r][c] == 0))
		return TRUE;
	else
		return FALSE;
}

moveCell* dellink(movesList* list, moveCell* remove, int* delcount) {
	moveCell* temp = NULL;
	(*delcount)++;
	if (list->head == list->tail) { //  base case - if theres only one move in array, empty it
		list->head = list->tail = NULL; // will return NULL for the list is empty
	}
	else if (remove->next == NULL) { // if remove is the tail make new tail
		remove->prev->next = NULL;
		list->tail = remove->prev;
		remove->prev = NULL;// avoid leaving acsses to the program memory
	}
	else if (remove->prev == NULL) { // if remove is the head make new head
		temp = remove->next; // advancing temp to next move
		temp->prev = NULL;
		remove->next = NULL; // avoid leaving acsses to the program memory
		list->head = temp;
	}
	else {
		temp = remove->next; // advancing temp to next move
		temp->prev = remove->prev;
		temp->prev->next = temp;
		remove->prev = NULL; // avoid leaving acsses to the program memory
		remove->next = NULL;
	}

	free(remove);
	return temp;
}

void freearr(char** board) {
	for (int i = 0; i < N; i++)
		free(board[i]);
	free(board);
}

char** makeboard() {
	char** newboard = calloc(sizeof(char*), N);
	assert(newboard);
	for (int i = 0; i < N; i++) {
		newboard[i] = calloc(sizeof(char), M);
		assert(newboard[i]);
	}
	return newboard;
}

void init(char** newboard, char** board) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if(board[i][j] == '*')
				newboard[i][j] = board[i][j]; // copy the * to newboard
}

void printboard(char** board) {
	int i;
	for (i = 0; i <= (N + 1) * 2; i++) {
		if (i % 2 == 0)
			printline();
		else {
			if (i == 1)
				printhead();
			else
				printcontent(board, i / 2); // sending i/2 to represent the current row
		}
	}
}

void printcontent(char** board, int i) { // for improve readability replace "j / 2 - 1" with t
	int j;
	for (j = 0; j <= (M + 1) * 2; j++) {
		if (j % 2 == 0)
			printf("|");
		else {
			if (j == 1)
				printf(" %c ", (i + 64)); //64 is the ascii before A can be changed to ('A'-1) instead
			else {
				if (board[i - 1][j / 2 - 1] == 35 || board[i - 1][j / 2 - 1] == 42 || board[i - 1][j / 2 - 1] == 32 || board[i - 1][j / 2 - 1] == 0) //if the cell has  space/null/*/# then print it as char
					printf("  %c  ", board[i - 1][j / 2 - 1]);
				else
					printf("%3d  ", board[i - 1][j / 2 - 1]);
			}
		}
	}
	printf("\n");
}

void printhead() {
	for (int i = 0; i <= (M + 1) * 2; i++) {
		if (i % 2 == 0)
			printf("|");
		else
		{
			if (i == 1)
				printf("   ");
			else
				printf("  %d  ", i / 2);
		}
	}
	printf("\n");
}

void printline() {
	for (int i = 0; i < M + 1; i++) {
		if (i == 0)
			printf(" --- ");
		else
			printf("----- ");
	}
	printf("\n");
}