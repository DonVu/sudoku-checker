# Sudoku-checker

This is a multithreaded sudoku solution checker for a 9x9 grid. This program creates 11 threads to check the sudoku solution. One thread checks each row, one thread checks each column, and one thread is generated for each of the 9 3x3 squares.

This project was created for my operating system class. To compile, use the -lpthread option with g++ for enabling pthreads. Usage of the program is as follows: ./a.out file-name-of-sudoku-solution
