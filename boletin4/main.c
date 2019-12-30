/**
 * @file
 * @brief Main menu for the third task
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "DirectSearch.h"

void showMenu();
void doAllSearchs();


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu() {

    int option = 0;
    while (option != 5) {
        printf("\n############### MENU BOLETÍN 4 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Ejecutar todos los algoritmos.\n"
               "\t2. Búsqueda directa.\n"
               "\t3. KMP.\n"
               "\t4. BMP.\n"
               "\t5. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                doAllSearchs();
                break;
            case 2:
                readFileAndExecuteDirectSearch();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Por favor seleccione una opción válida\n");
                break;
        }
    }
}



/**
 * Calls all the algorithms' functions to search a given string in a file
 */
void doAllSearchs(){
    char *array = NULL;
    FILE *file = askForFileToLoad();
    array = loadFile(file, array);
    fclose(file);
    printf("%s", array);
    free(array);
}



int main() {
    showMenu();
}