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
#include <cstdlib>
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
  int threadId;
};

//  Each thread sets their respective
//  array index to 1 for valid row/column/square
//  or 0 for invalid
int sudokuStatus[NUM_THREADS];

//  Threads will execute this function
void *Runner(void *param);

void CreateParam(int threadId, struct parameters param[]);
 
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

  pthread_t threads [NUM_THREADS];
  struct parameters param[NUM_THREADS];
  int threadCreate;

  for (int i = 0; i < NUM_THREADS; ++i) {
    cout << "main() : creating thread, " << i << endl;
    CreateParam(i, param);

    threadCreate = pthread_create(&threads[i], NULL, Runner, (void *)&param[i]);

    if (threadCreate) {
      cerr << "Error: unable to create thread" << endl;

      return 1;
    }
  }
 
  //  wait and join other threads
  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);

    cout << "Main() -- Thread with ID: " << i << " ... " 
      << "joined. " << endl;
  }
  
  //  check the results of all the threads
  bool isValid = true;
  for (int i = 0; i < NUM_THREADS; ++i) {
    if (sudokuStatus[i] == 0) isValid = false;
    cout << "Thread " << i << " reports: " << sudokuStatus[i] << endl;
  } 

  if (isValid) {
    cout << "This sudoku is a valid solution!" << endl;
  } else {
    cout << "This is not a valid sudoku solution." << endl;
  }

  pthread_exit(NULL);
  return 0;
}

void *Runner(void *param) {
  struct parameters *paramPtr;
  paramPtr = (struct parameters *) param;

  //  Row checking thread
  if (paramPtr->threadId == 0) {
    int sudokuList[9];
    
    bool isValid = true;
    for (int i = paramPtr->row; i < 9; ++i) 
      for (int j = paramPtr->column; j < 9; ++j)
        sudokuList[sudoku[i][j] - 1] = 1;
        
    for (int k = 0; k < 9; ++k)
      if (sudokuList[k] == 0) isValid = false;

    if (isValid) sudokuStatus[paramPtr->threadId] = 1;
  } else if (paramPtr->threadId == 1) {
      //  column checking thread
      int sudokuList[9];
    
      bool isValid = true;
      for (int i = paramPtr->row; i < 9; ++i)
        for (int j = paramPtr->column; j < 9; ++j)
          sudokuList[sudoku[j][i] - 1] = 1;
        
      for (int k = 0; k < 9; ++k)
        if (sudokuList[k] == 0) isValid = false;
      

      if (isValid) sudokuStatus[paramPtr->threadId] = 1;
  } else {
    
      //  3x3 checking thread
      int sudokuList[9];
    
      bool isValid = true;
      int paramRow = paramPtr->row;
      int paramColumn = paramPtr->column;
      for (int i = paramRow; i < (paramRow + 3); ++i) 
        for (int j = paramColumn; j < (paramColumn + 3); ++j)
          sudokuList[sudoku[i][j] - 1] = 1; 
      
      
      for (int k = 0; k < 9; ++k)
        if (sudokuList[k] == 0) isValid = false;

      if (isValid) sudokuStatus[paramPtr->threadId] = 1;
  }

  pthread_exit(NULL);
}

void CreateParam(int threadId, struct parameters param[]) {
    // create a row and column checking thread
    int i = threadId;
 
    if (i == 0 || i == 1) {
    param[i].row = 0;
    param[i].column = 0;
    param[i].threadId = i;
    } else if (i == 2 || i == 3 || i == 4) {
      //  Create the starting locations
      //  for 3x3 checking threads to begin
      //  starting at row 0
      param[i].row = 0;
      param[i].column = (0 + i - 2) * 3;
      param[i].threadId = i;
    } else if (i == 5 || i == 6 || i == 7) {
      //  Create the starting locations
      //  for 3x3 checking threads to begin
      //  starting at row 3
      param[i].row = 3;
      param[i].column = (0 + i - 5) * 3;
      param[i].threadId = i;
    } else if (i == 8 || i == 9 || i == 10) {
      //  Create the starting locations
      //  for 3x3 checking threads to begin
      //  starting at row 6
      param[i].row = 6;
      param[i].column = (0 + i - 8) * 3;
      param[i].threadId = i;
    }
}
