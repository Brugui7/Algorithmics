/**
 * @file
 * @brief Exercise 1
 * @author: Alejandro Brugarolas
 * @since: 2019-11
*/
#include <stdio.h>
#include <stdlib.h>
#include "Exercise1.h"


/**
 * Shows a menu asking for the value of N and calls the recursive method
 */
void mainExercise1(){
    int n = 0;
    printf("Introduzca el valor de n para generar el cuadrado mágico\n");
    printf("> ");
    scanf("%d", &n);
    fflush(stdin);

    while (n <= 0){
        printf("Por favor, introduzca un valor mayor que 0");
        printf("> ");
        scanf("%d", &n);
        fflush(stdin);
    }

    int *solution = (int*) malloc(sizeof(int) * n * n);
    if (magicSquareRec(n, solution, 0, -1) == 0){
        printf("No existe solución para este valor de n");
    }
    free(solution);

}


/**
 *
 * @param n
 * @param solution
 * @param step
 * @return
 */
int magicSquareRec(int n, int *solution, int step, int firstRowSum){
    if(step == n*n) return 0;
    int existsSolution = 0;
    int rowSum = firstRowSum;
    //The initial value is 0 so the first value tried is 1 because 0 is not a valid number on a magic square
    solution[step] = 0;
    do{
        solution[step]+=1;
        //TODO: Aquí se crea un nodo nuevo
        if(isReachable(n, solution, step, firstRowSum) == 1){



            if(isSolution(n, solution, step) == 1){
                showSolution(n, solution);
                return 1;
            } else {

                if (step == n-1){
                    int position = 0;
                    rowSum = 0;

                    for (int i = 0; i < n; i++) {
                        rowSum += solution[i];
                    }
                }

                existsSolution = magicSquareRec(n, solution, step + 1, rowSum);
            }
        }

    } while (existsSolution != 1 && solution[step] != n*n);
    return existsSolution;
}


/**
 * Checks if the values could fit on a valid solution
 * @param n
 * @param solution
 * @param step
 * @return 0 false 1 true
 */
int isReachable(int n, int *solution, int step, int firstRowSum){
    for(int i = 0; i < step + 1; i++){
        if(solution[i] > n*n) return 0;
        for(int j = 0; j < step + 1; j++){
            if (i == j) continue;
            if(solution[i] == solution[j]) return 0;
        }
    }

    if (step > n){
        //Sums the values of every row after the first one
        //if the sum of any row is greater than the first, the solution is not reachable
        int rowSum = 0;
        for(int i = n; i < step; i++){
            int column = i % n;
            if(column == 0) rowSum = 0;
            rowSum += solution[i];
            if (rowSum > firstRowSum) return 0;
        }

        //Sums the values of every column
        //if the sum of any column is greater than the sum of the first row, the solution is not reachable
        if (step / n == n - 1){
            for (int i = 0; i < step; i++) {
                int columnSum = 0;
                for(int j = 0; j < n; j++){
                    //Column  Major order to sum the column values
                    int position = j * n + i;
                    if (position > step) break;
                    columnSum += solution[position];
                    if (columnSum > firstRowSum) return 0;
                }
            }
        }

    }


    return 1;
}

/**
 * Checks if its a valid solution for the problem
 * @param n
 * @param solution
 * @param step
 * @return 0 false | 1 true
 */
int isSolution(int n, int *solution, int step){
    if (step != n*n - 1) return 0;
    int firstSum = 0, actualColumnSum = 0, actualRowSum = 0, diagonalSum = 0, inverseDiagonalSum = 0;
    int position = 0;

    for (int i = 0; i < n; i++) {
        actualColumnSum = 0;
        actualRowSum = 0;
        for (int j = 0; j < n; j++) {
            //Row Major order to sum the rows values
            position = i * n + j;
            actualRowSum += solution[position];

            //Sums the diagonal values
            if(i == j){
                diagonalSum += solution[position];
            }

            if (j == n - i - 1){
                inverseDiagonalSum += solution[position];
            }

            //Column Major order to sum the columns values
            position = j * n + i;
            actualColumnSum += solution[position];
        }
        if(actualColumnSum != actualRowSum) return 0;
        //Doesn't matter because row and column sums have the same value
        if(i == 0) firstSum = actualRowSum;
        if (actualRowSum != firstSum) return 0;
    }
    return diagonalSum == firstSum && inverseDiagonalSum == firstSum;
}

/**
 * Shows the solution formatted as a square
 * @param n
 * @param solution
 */
void showSolution(int n, int *solution){
    printf("Solución encontrada:\n");
    int position = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            position = i * n + j; //Row Major order
            printf("%d\t", solution[position]);
        }
        printf("\n");
    }
}
