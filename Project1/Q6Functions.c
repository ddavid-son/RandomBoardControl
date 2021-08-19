#include "Q6Header.h"



int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board) {

	FILE* f = fopen(file_name, "rb");
	if (fileok(f))// checkes if fopen faild
		return -1;
	short size, asterisk = countasterisk(board), delcount;
	boardPos start, * arr; // starting point for moves
	fread(&size, sizeof(short), 1, f); // get size of moves in file ||| if read fail or size is 0 
	movesList* molist = initlist();
	arr = buildcordarr(f, (double)size, &start);

	molist = arrtomovelist(arr, molist, size); // builds movelist according to the the stsrt point

	if (checkforvalidmoves(arr, size, board, molist, moves)) { //// checks if the path is valid ||| goes to the starting point possible moves
		freefunc(molist, arr); /// frees all te allocated memory
		return 1; // not all moves in list are valid
	}

	delcount = (short)display(molist, start, board); // will print the path and ignore the double appearances if exist
	freefunc(molist, arr);

	if (size - delcount == ((M * N) - asterisk))
		return 2; // the board is fully printed
	else
		return 3;/// if the pathe is valid and does not cover the whole screen
}

short countasterisk(char** board) {
	short counter = 0; // couter for asterisks
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == '*')
				counter++;
		}
	}
	return counter;
}

int fileok(FILE* f) {

	if (f == NULL)
		return 1; // fopen faild
	return 0; // fopen was successful
}

void freefunc(movesList* molist, boardPos* arr) {
	free(arr);
	moveCell* head = molist->head, * temp;
	while (head) { // frees the linked list 
		temp = head;
		head = head->next;
		temp->next = temp->prev = NULL;
		free(temp);
	}
	free(molist);
}

int checkforvalidmoves(boardPos* arr, int size, char** board, movesList* molist, movesArray** moves) {
	moveCell* step = molist->head;

	char r = arr[0][0], c = arr[0][1]; // given  - the starting point is valid
	for (int i = 1; i < size; i++) {
		if (moveisfound(step, moves[r - 'A'][c - '1'])) return 1;
		r = arr[i][0];
		c = arr[i][1];
		if (r < 'A' || (r - 'A') >= N || c < '1' || (c - '1') >= M) // check for bundries validity
			return 1;
		if (board[(r - 'A')][(c - '1')] == '*') // checkes for * in the path
			return 1;
		step = step->next;
	}
	return 0; // means no changes has been commited so the
}

int moveisfound(moveCell* step, movesArray moves) {

	Move* arr = moves.moves;
	for (unsigned int i = 0; i < moves.size; i++) {
		if ((step->move.cols == arr[i].cols) && (step->move.rows == arr[i].rows))
			return 0;
	}
	return 1;
}

movesList* arrtomovelist(boardPos* arr, movesList* molist, short size) {

	moveCell* newnode;
	for (int i = 1; i < size; i++) {
		newnode = createnewnode(arr[i][ROWLETTER] - arr[i - 1][ROWLETTER], arr[i][COLNUMBER] - arr[i - 1][COLNUMBER]);
		inserttoend(molist, newnode);
	}
	return molist;
}

boardPos* buildcordarr(FILE* f, double size, boardPos* start) {
	int left = 3, i = 0, readsize = (int)ceil((size * 6) / 8); // ceilling func size is double form casting to make ceil accurate
	BYTE* read = malloc(sizeof(BYTE) * readsize); // allocating array for entire file usine ceilling func
	assert(read);

	fread(read, sizeof(BYTE), readsize, f);
	boardPos* arr = malloc(sizeof(boardPos) * (size_t)size);
	assert(arr);

	for (int t = 0; t < size; ) { // gets all the coordinates from file  

		if (left <= 8)
			arr[t][0] = nomerg(&left, read[i]) + 'A'; // puts the decoded bits in its row
		else
			arr[t][0] = merg(read[i++], read[i], &left) + 'A'; // means thet we finished with the current read byte advancing to the next one

		if (left <= 8)
			arr[t++][1] = nomerg(&left, read[i]) + '1'; // puts the decoded bits in its colomn
		else
			arr[t++][1] = merg(read[i++], read[i], &left) + '1'; // means thet we finished with the current read byte advancing to the next one
	}
	(*start)[0] = arr[0][0]; // update start point 
	(*start)[1] = arr[0][1];

	free(read);
	fclose(f); // note - closing the file here and not in the calling function
	return arr;
}

void inserttoend(movesList* molist, moveCell* newnode) {

	if (molist->head == NULL) {
		molist->head = newnode;
		molist->tail = newnode;
	}
	else
	{
		newnode->prev = molist->tail;
		molist->tail->next = newnode;
		molist->tail = newnode;
	}
}

moveCell* createnewnode(char rows, char cols) {

	moveCell* newnode = malloc(sizeof(moveCell));

	newnode->move.cols = cols;
	newnode->move.rows = rows;

	newnode->next = NULL;
	newnode->prev = NULL;

	return newnode;
}

char merg(BYTE part1, BYTE part2, int* left) {

	BYTE cell = (part1 << ((*left) - 3));
	cell = cell >> BTR;
	cell |= (part2 >> (16 - (*left))); // number of bits to shift left in the next BYTE so we get the full number 

	(*left) = 3 - (8 - (*left)); // updating left for the next read BYTE

	return cell;
}

char nomerg(int* left, char read) {

	BYTE temp = ((read >> (8 - (*left))) & MASK);
	(*left) += 3;
	return temp;
}

movesList* initlist() { // initiate movelist
	movesList* molist = malloc(sizeof(movesList));
	molist->head = NULL;
	molist->tail = NULL;
	return molist;
}