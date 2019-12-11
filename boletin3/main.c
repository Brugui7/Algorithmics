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
    while (option != 3) {
        printf("\n############### MENU BOLETÍN 3 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Ejecutar todos los algoritmos.\n"
               "\t2. TODO.\n"
               "\t3. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                doAllSortings();
                break;
            case 2:
                break;
            case 3:
                printf("Saliendo...");
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
    char savePath[255] = "";
    int *arrayCopy;
    printf("Introduzca la ruta a la carpeta donde se almacenarán los ficheros de salida\n>");
    gets(savePath);
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countElements(file);
    fclose(file);
    arrayCopy = (int*) malloc(sizeof(int) * size);

    arrayCopy = copyArray(array, size, arrayCopy);
    mainBubbleSort(arrayCopy, size, savePath);
    mainSelectionSort(array, size, savePath);
    mainShellSort(array, size, savePath);
    mainQuickSort(array, size, savePath, 1);
    mainQuickSort(array, size, savePath, 2);
    mainQuickSort(array, size, savePath, 3);

}



int main() {
    showMenu();
}