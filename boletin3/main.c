/**
 * @file
 * @brief Main menu for the third task
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "QuickSort.h"




void showMenu();
void doAllSortings();


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu() {

    int option = 0;
    while (option != 6) {
        printf("\n############### MENU BOLETÍN 3 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Ejecutar todos los algoritmos.\n"
               "\t2. BubbleSort.\n"
               "\t3. SelectionSort.\n"
               "\t4. ShellSort.\n"
               "\t5. QuickSort.\n"
               "\t6. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                doAllSortings();
                break;
            case 2:
                readFileAndExecuteBubbleSort();
                break;
            case 3:
                readFileAndExecuteSelectionSort();
                break;
            case 4:
                readFileAndExecuteShellSort();
                break;
            case 5:
                readFileAndExecuteQuickSort();
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Por favor seleccione una opción válida\n");
                break;
        }
    }
}



/**
 * Calls all the algorithms' functions to sort a given file
 */
void doAllSortings(){
    FILE *file = askForFileToLoad();
    char* savePath = askForSavePath();
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countElements(file);
    fclose(file);

    mainBubbleSort(array, size, savePath);
    mainSelectionSort(array, size, savePath);
    mainShellSort(array, size, savePath);
    mainQuickSort(array, size, savePath, 1);
    mainQuickSort(array, size, savePath, 2);
    mainQuickSort(array, size, savePath, 3);

    free(array);
    free(savePath);
}



int main() {
    showMenu();
}