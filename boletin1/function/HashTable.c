/**
 * @file
 * @brief Independent HashTable functions
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"
/**
 * reads the films file and saves the data into the hash table using the desired technique
 * @param technique 1 - lineal | 2 - key-depend | 3 - chained
 * @return
 */
hashtable *loadFile(hashtable* hashTable, int technique){
    //Cleans the HashTable
    cleanTable(hashTable, technique);

    char fileName[100] = "";
    FILE *file = NULL;
    char *buffer = (char *) malloc(sizeof(char) * 255);
    char *token;
    size_t length, bufferSize = 255;

    //Asks for the file to load the data
    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n> ");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }
    printf("Cargando datos...\n");

    fgets(buffer, bufferSize, file); //Ignores the csv headers
    while(fgets(buffer, bufferSize, file) != NULL){
        film *newFilm = (film*) malloc(sizeof(film));
        token = strtok(buffer, ";");

        //fills the film data
        newFilm->year = atoi(token);
        token = strtok(NULL, ";");

        newFilm->duration = atoi(token);
        token = strtok(NULL, ";");

        length = strlen(token);
        //the ++length is for the null terminator
        newFilm->title = (char *) malloc(++length * sizeof(char));
        strncpy(newFilm->title, token, length);
        token = strtok(NULL, ";");


        length = strlen(token);
        newFilm->genre = (char *) malloc(++length * sizeof(char));
        strncpy(newFilm->genre, token, length);
        token = strtok(NULL, ";");

        newFilm->popularity = atoi(token);
        printf("Película detectada\n");
        addFilm(hashTable, newFilm, technique);
        showFilm(newFilm);
    }
    free(buffer);
    return hashTable;
}

/**
 * Sets every position in the table as free
 * @param hashtable
 * @param technique
 * @return hashtable
 */
void cleanTable(hashtable* hashTable, int technique){
    int aux;
    if (technique == 3){
        aux = CHAINED_TABLE_SIZE;
        for(int i = 0; i < aux; i++){
            hashTable[i] = (hashitem*) malloc(sizeof(hashitem));
            hashTable[i]->key = FREE;
            hashTable[i]->next = NULL;
        }
    } else {
        aux = TABLE_SIZE;
        for(int i = 0; i < aux; i++){
            hashTable[i] = (hashitem*) malloc(sizeof(hashitem));
            hashTable[i]->key = FREE;
        }
    }


}

/**
 * Adds a film to the hashtable
 * @param hashTable
 * @param newFilm
 */
void addFilm(hashtable *hashTable, film *newFilm, int technique){
    int index = 0;
    int hashCode = hash(newFilm);
    int free = FREE;
    int deleted = DELETED;

    if (technique == 3){
        index = hashCode % CHAINED_TABLE_SIZE;
    } else {
        index = hashCode % TABLE_SIZE;
    }

    if (hashTable[index]->key == free || hashTable[index]->key == deleted){
        hashTable[index]->key = hashCode;
        hashTable[index]->film = newFilm;
    } else{
        //Collision
        int newIndex = 0;
        switch (technique){
            case 1:
                newIndex = linearCollisionHandler(hashTable, index);
                break;
            case 2:
                newIndex = keyDependentCollisionHandler(hashTable, hashCode);
                break;
            case 3:
                newIndex = chainedCollisionHandler(hashTable, newFilm, hashCode);
                break;
            default:
                //The code should never reach this point
                printf("Error, algoritmo de manejo de colisiones no soportado\n");
                break;
        }

        //The hash table has no free places
        if(newIndex == -1){
            printf("Error, no se han encontrado posiciones libres en la tabla\n");
        } else if (technique == 1 || technique == 2){
            hashTable[newIndex]->key = hashCode;
            hashTable[newIndex]->film = newFilm;
        }
        //If the technique is the chained one, the newIndex will be just an error code, 1 if ok, -1 if an error has happened
    }

}


/**
 * Uses the Linear technique to handle a collision
 * @param hashTable
 * @param index int original position where the film was going to be inserted in
 * @return int position to insert the film in or -1 if no position have been found
 */
int linearCollisionHandler(hashtable *hashTable, int index){
    int free = FREE;
    int deleted = DELETED;
    int tableSize = TABLE_SIZE;
    for(int i = 0; i < tableSize - 1; i++){
        int newIndex = (index + i) % TABLE_SIZE;
        if (hashTable[newIndex]->key == free || hashTable[newIndex]->key == deleted){
            return newIndex;
        }
    }
    return -1;

}

/**
 * Uses the Key-Dependent technique to handle a collision
 * @param hashTable
 * @param int hashcode of the film
 * @return int position to insert the film in or -1 if no position have been found
 */
int keyDependentCollisionHandler(hashtable *hashTable, int hashCode){
    int free = FREE;
    int deleted = DELETED;
    int tableSize = TABLE_SIZE;
    int d = 0;
    int index = hashCode % tableSize;
    for(int i = 0; i < tableSize - 1; i++){
        d = __max(1, hashCode / tableSize);
        //To ensure a full exploration of the table, d and tableSize should be prime numbers between them
        while (d % tableSize == 0){
            d += 1;
        }

        int newIndex = (index + d * i) % TABLE_SIZE;
        if (hashTable[newIndex]->key == free || hashTable[newIndex]->key == deleted){
            return newIndex;
        }
    }
    return -1;
}

/**

 * @param hashTable
 *

 */
 /**
  * Uses the chained technique to handle a collision
  * @param hashTable
  * @param newFilm film to insert
  * @param hashcode int hashcode of the film
  * @return int 1 if the film has been inserted | -1 if not
  */
int chainedCollisionHandler(hashtable *hashTable, film *newFilm, int hashcode){
    int free = FREE;
    int deleted = DELETED;
    int tableSize = CHAINED_TABLE_SIZE;
    int index = hashcode % tableSize;

    hashitem *auxItem = hashTable[index];

    //Iterates over the list until a free space is found
    while (auxItem->next != NULL) {
        auxItem = auxItem->next;
    }

    if (auxItem->next == NULL){
        auxItem->next = (hashitem*) malloc(sizeof(hashitem));
        auxItem = auxItem->next;
        auxItem->key = hashcode;
        auxItem->film = newFilm;
        auxItem->next = NULL;
        return 1;
    }

    return -1;

}