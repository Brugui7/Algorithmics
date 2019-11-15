/**
 * @file
 * @brief Main menu for the second task
 * @author Alejandro Brugarolas
 * @since 2019-11
 */

#include <stdio.h>
#include "Exercise1.h"
#include "Exercise2.h"




void showMenu();

/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu() {

    int option = 0;
    while (option != 3) {
        printf("\n############### MENU BOLETÍN 2 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Ejercicio 1.\n"
               "\t2. Ejercicio 2.\n"
               "\t3. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                mainExercise1();
                break;
            case 2:
                mainExercise2();
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


int main() {
    showMenu();
}