#pragma once
#include "Q1Header.h"

/*QUESTION 5 DECLERATIONS*/
typedef unsigned char BYTE;
#define CELL_SIZE 3; // cell representaion using 3 bits 

void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
BYTE split(char data, BYTE write, int cr, int* offset, int* full, FILE* f);
BYTE nosplit(char data, int cr, int offset, int* full);