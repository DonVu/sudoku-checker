/*
  Don Vu

  This program is a sudoku checker
  for 9x9 grid sudokus. The program
  makes use of multithreading to
  check the valid sudoku.

*/
#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;

//  11 threads are created - 2 for row/column
//  and 9 for each 3x3 square
#define NUM_THREADS 11

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
int sudokuStatus[NUM_THREADS];

//  Threads will execute this function
void *runner(void *param);

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

void *runner(void *param){

}
