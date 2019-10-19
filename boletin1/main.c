/**
 * @file
 * @brief Application to manage films
 * @author Alejandro Brugarolas
 * @since 2019-10
 */

#include <stdio.h>
#include <stdlib.h>
#include "model/HashTable.h"


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu(hashtable *hashTable) {

    int option = 0;
    while (option != 3) {
        //Todo seleccionar algoritmo y mostrar menú distinto o más opciones por cada algoritmo
        printf("\n############### MENU BOLETÍN 1 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Cargar el fichero\n"
               "\t2. En construcción\n"
               "\t3. Salir\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                loadFile(hashTable, 1);
                break;
            case 2:
                //TODO
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
    int aux = TABLE_SIZE
    hashtable* hashTable = (hashtable*) malloc(sizeof(hashTable) * aux);
    showMenu(hashTable);
    //destroyEverything(hashTable);
}