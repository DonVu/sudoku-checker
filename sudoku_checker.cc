/*
	Don Vu

	This program is a sudoku checker
	for 9x9 grid sudokus. The program
	makes use of multithreading to
	check the valid sudoku.

*/
#include <iostream>
#include <fstream>
using namespace std;

// Global sudoku array shared by all threads
int sudoku[9][9];

//  Parameters passed to each thread
struct parameters {
	int row;
	int column;
};

//  Each thread sets their respective
//  array index to 1 for valid row/column/square
//  or 0 for invalid
int sudokuStatus[11];

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <Sudoku solution file name>" 
			<< endl;

		return 1;
	}

	// Fill thread level sudoku array
	ifstream sudokuFile(argv[1]);
	if (sudokuFile.is_open()) {
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				sudokuFile >> sudoku[i][j];
	} else {
		cerr << "Error opening file\n";

		return 1;
	}

	return 0;
}