# FunctionsForRandomBoardControl
For a board (matrix) of size MxN, where M is countable by letters and N is countable by numbers,
the following functions implement different algorithms according to specific rules for a random game.
In the game each spot in the board gets random spots on the board, which the player is allowed to move to. some of the allowed moves may be "illegal", either if the spot is filled with the symbol '*', or if the spot is out of bound.

### Function 1: 
From a given position, find all valid moves, and return an array of structs of them.

### Function 2:
Display given a starting position and a linked list of moves, display the board and the movements upon it.

### Function 3: 
given a starting position, this function creates a full tree with all the possible full paths from that starting point through the board.

### Function 4:
Using "Function 3" this function searches the tree of "all possible paths" for a given starting point, untill it finds a path which covers the whole board (excluding spots with the symbol '*').

### Function 5: 
This function saves a list of of the spots from the board to a binary file, where each spot is represented with only 6 bits. the first 3 bits represent a line - 1, and the later 3 bits represent the row - 1.

### Function 6: 
This function reads a path from a binary file (represented in the same way as in "Function 5"). 
If the path is illegal the function ends and returns 1.
Otherwise the function prints the board with the help of "Function 2", but ignores previously visited spots. If the path covers the whole board returns 2, otherwise returns 3. If the file doesn't exist it returns -1.

## Tester
The tester is a main function file, it reads a board and a list of moves from given text files matr.txt for the board and movesFile.txt. for each function the tester creates whatever the function needs according to the text files, and prints for each function weather it worked succesfully or not.
