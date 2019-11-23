/**
 * @file
 * @brief Exercise 1 header file
 * @author: Alejandro Brugarolas
 * @since: 2019-11
*/

#ifndef ALGORITHMICS_EXERCISE1_H
#define ALGORITHMICS_EXERCISE1_H

void mainExercise1();

int isReachable(int n, int *solution, int step, int firstRowSum);

int magicSquareRec(int n, int *solution, int step, int firstRowSum);

int isSolution(int n, int *solution, int step, int magicConstant);

void showSolution(int n, int *solution);

int getMagicConstant(int n);


#endif //ALGORITHMICS_EXERCISE1_H
