/*
	Don Vu

	This program is a sudoku checker
	for 9x9 grid sudokus. The program
	makes use of multithreading to
	check the valid sudoku.

*/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <Sudoku solution file name>" 
			<< endl;

		return 1;
	}

	return 0;
}