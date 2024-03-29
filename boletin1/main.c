/**
 * @file
 * @brief Application to manage films
 * @author Alejandro Brugarolas
 * @since 2019-10
 */

#include <stdio.h>
#include <stdlib.h>
#include "model/HashTable.h"


int selectAlgorithm();
void showMenu(hashtable *hashTable);

/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu(hashtable *hashTable) {

    int option = 0;
    int technique = selectAlgorithm();
    //Cleans the HashTable
    cleanTable(hashTable, technique);
    while (option != 6) {
        printf("\n############### MENU BOLETÍN 1 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Cargar el fichero.\n"
               "\t2. Insertar manualmente.\n"
               "\t3. Buscar.\n"
               "\t4. Eliminar.\n"
               "\t5. Consultar factor de carga.\n"
               "\t6. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                loadFile(hashTable, technique);
                break;
            case 2:
                insertFilm(hashTable, technique);
                break;
            case 3:
                searchOrDeleteOption(hashTable, technique, 1);
                break;
            case 4:
                searchOrDeleteOption(hashTable, technique, 2);
                break;
            case 5:
                printf("Factor de carga del %d%%\n", getLoadFactor(hashTable, technique));
                break;
            case 6:
                printf("Saliendo...");
                destroyEverything(hashTable, technique);
                break;
            default:
                printf("Por favor seleccione una opción válida\n");
                break;
        }
    }
}

/**
 * Asks the user for the technique to be used to handle collisions
 * @return int technique 1 - lineal | 2 - key-depend | 3 - chained
 */
int selectAlgorithm(){
    int option = 0;
    while (option != 1 && option != 2 && option != 3){

        printf("\n############### MENU BOLETÍN 1 ###############\n"
               "Indique el algoritmo que se va a usar para el manejo de colisiones\n"
               "\t1. Prueba lineal\n"
               "\t2. Dependiente de la clave\n"
               "\t3. Encadenamiento\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
            case 2:
            case 3:
                return option;
            default:
                printf("Por favor, seleccione una opción válida");
        }
    }

}


int main() {
    int aux = TABLE_SIZE
    hashtable* hashTable = (hashtable*) malloc(sizeof(hashTable) * aux);
    showMenu(hashTable);
}