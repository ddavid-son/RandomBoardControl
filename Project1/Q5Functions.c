#include "Q5Header.h"

void saveListToBinFile(char* file_name, boardPosArray* pos_arr) {
	FILE* f = fopen(file_name, "wb");
	assert(f);
	BYTE write = 0;
	int t = 8, cr = 0, full = 0; // t - byte border , cr - [even is letter ,odd is digit],  full - CURRENT CPACITY IN WRITE
	fwrite(&(pos_arr->size), sizeof(short), 1, f);

	for (unsigned int i = 0; i < pos_arr->size; ) { // countes per char in positions

		t -= CELL_SIZE; // update the space left in the current byte

		if (t > 0 && full < 6)  // if no split is necessary
			write |= nosplit(pos_arr->positions[i][cr % 2], cr, t, &full);

		else // if split is required
			write = split(pos_arr->positions[i][cr % 2], write, cr, &t, &full, f); // keeping only the the wanted bit
		cr++;
		if (cr % 2 == 0 && cr > 0) // only advancing i when we finish bothe the letter and digit of evrey boardpos cell
			i++;
	}
	if (pos_arr->size % 4) // when if is true "write" was not written to "f" buffer (it means the last function that was activated inside the loop was nosplit)
		fwrite(&write, sizeof(char), 1, f);
	fflush(f);
	fclose(f);
}


BYTE split(char data, BYTE write, int cr, int* offset, int* full, FILE* f) { // will print to the file and update write to be the next cell

	BYTE mask = 0;
	if (cr % 2 == 0)
		mask = data - 'A';
	else
		mask = data - '1';

	write |= (mask >> (3 - (8 - (*full)))); // if full is 8 then no change will be applied to write
	(*offset) = 8 - (3 - (8 - (*full))); // places to be filled
	(*full) = 3 - (8 - (*full)); // places already taken

	fwrite(&write, sizeof(char), 1, f);
	return (mask << (*offset));// keeping only the the wanted bit
}


BYTE nosplit(char data, int cr, int offset, int* full) {
	(*full) += 3;

	if (cr % 2 == 0)
		return (data - 'A') << offset;// return letter
	else
		return (data - '1') << offset;// return num
}