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
 * Reads the films file and saves the data into the hash table using the desired technique
 * @param technique 1 - lineal | 2 - key-depend | 3 - chained
 * @return the table filled
 */
hashtable *loadFile(hashtable* hashTable, int technique){

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
        addFilm(hashTable, newFilm, technique, 0);
        showFilm(newFilm);
    }

    free(buffer);
    return hashTable;
}

/**
 * Inserts a film manually
 * @param hashTable
 * @return hashtable the table with the new film added
 */
hashtable *insertFilm(hashtable *hashTable, int technique){
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t length;
    film *newFilm = (film*) malloc(sizeof(film));

    printf("Introduzca el nombre de la película\n> ");
    gets(buffer);
    fflush(stdin);
    length = strlen(buffer);
    //the ++length is for the null terminator
    newFilm->title = (char *) malloc(++length * sizeof(char));
    strncpy(newFilm->title, buffer, length);

    printf("Introduzca el género de la película\n> ");
    gets(buffer);
    fflush(stdin);
    length = strlen(buffer);
    //the ++length is for the null terminator
    newFilm->genre = (char *) malloc(++length * sizeof(char));
    strncpy(newFilm->genre, buffer, length);

    printf("Introduzca el año de la película\n> ");
    scanf("%d", &newFilm->year);
    fflush(stdin);

    printf("Introduzca la duración de la película\n> ");
    scanf("%d", &newFilm->duration);
    fflush(stdin);

    printf("Introduzca la popularidad de la película\n> ");
    scanf("%d", &newFilm->popularity);
    fflush(stdin);

    printf("Guardando datos...\n");
    showFilm(newFilm);
    addFilm(hashTable, newFilm, technique, 1);
    int loadFactor = getLoadFactor(hashTable, technique);
    printf("Factor de carga del %d%%\n", loadFactor);
    free(buffer);
    return hashTable;
}

/**
 * Resturns the load factor
 * @param hashTable
 * @return
 */
int getLoadFactor(hashtable *hashTable, int technique){
    double tableSize = getTableSize(technique);
    double totalElements = 0;
    double result;
    int free = FREE;
    int deleted = DELETED;
    for(int i = 0; i < tableSize; i++){
        totalElements += hashTable[i]->key != free && hashTable[i]->key != deleted ? 1 : 0;
    }
    result = totalElements / tableSize;
    return result * 100;
}

/**
 * Sets every position in the table as free
 * @param hashtable
 * @param technique
 * @return hashtable
 */
void cleanTable(hashtable* hashTable, int technique){
    int tableSize = getTableSize(technique);
    if (technique == 3){
        for(int i = 0; i < tableSize; i++){
            hashTable[i] = (hashitem*) malloc(sizeof(hashitem));
            hashTable[i]->key = FREE;
            hashTable[i]->next = NULL;
        }
    } else {
        for(int i = 0; i < tableSize; i++){
            hashTable[i] = (hashitem*) malloc(sizeof(hashitem));
            hashTable[i]->key = FREE;
        }
    }


}

/**
 * Adds a film to the hashtable
 * @param hashTable
 * @param newFilm
 * @param int 1 to show a message on collisions, 0 if not
 *
 */
void addFilm(hashtable *hashTable, film *newFilm, int technique, int showCollisions){
    int hashCode = hash(newFilm);
    int index = hashCode % getTableSize(technique);
    int free = FREE;
    int deleted = DELETED;



    if (hashTable[index]->key == free || hashTable[index]->key == deleted){
        hashTable[index]->key = hashCode;
        hashTable[index]->film = newFilm;
        if(technique == 3){
            hashTable[index]->next = NULL;
        }
    } else{
        //Collision
        int newIndex = 0;
        switch (technique){
            case 1:
                newIndex = linearCollisionHandler(hashTable, index, showCollisions);
                break;
            case 2:
                newIndex = keyDependentCollisionHandler(hashTable, hashCode, showCollisions);
                break;
            case 3:
                newIndex = chainedCollisionHandler(hashTable, newFilm, hashCode, showCollisions);
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
 * @param int 1 to show a message on collisions, 0 if not
 * @return int position to insert the film in or -1 if no position have been found
 */
int linearCollisionHandler(hashtable *hashTable, int index, int showCollisions){
    if (showCollisions) printf("Colisión en la posición: %d\n", index);
    int free = FREE;
    int deleted = DELETED;
    int tableSize = getTableSize(1);;
    for(int i = 0; i < tableSize; i++){
        int newIndex = (index + i) % tableSize;
        if (hashTable[newIndex]->key == free || hashTable[newIndex]->key == deleted){
            return newIndex;
        }
        if (showCollisions) printf("Colisión en la posición: %d\n", newIndex);

    }
    return -1;

}

/**
 * Uses the Key-Dependent technique to handle a collision
 * @param hashTable
 * @param int hashcode of the film
 * @param int 1 to show a message on collisions, 0 if not
 * @return int position to insert the film in or -1 if no position have been found
 */
int keyDependentCollisionHandler(hashtable *hashTable, int hashCode, int showCollisions){
    int free = FREE;
    int deleted = DELETED;
    int tableSize = getTableSize(2);
    int d = 0;
    int index = hashCode % tableSize;
    if (showCollisions) printf("Colisión en la posición: %d\n", index);
    for(int i = 0; i < tableSize; i++){
        d = __max(1, hashCode / tableSize);
        //To ensure a full exploration of the table, d and tableSize should be prime numbers between them
        while (d >= tableSize && d % tableSize == 0){
            d += 1;
        }

        int newIndex = (index + d * i) % tableSize;
        if (hashTable[newIndex]->key == free || hashTable[newIndex]->key == deleted){
            return newIndex;
        }
        if (showCollisions) printf("Colisión en la posición: %d\n", newIndex);
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
  * @param int 1 to show a message on collisions, 0 if not
  * @return int 1 if the film has been inserted | -1 if not
  */
int chainedCollisionHandler(hashtable *hashTable, film *newFilm, int hashcode, int showCollisions){
    int tableSize = getTableSize(3);
     int index = hashcode % tableSize;
     if (showCollisions) printf("Colisión en la posición: %d\n", index);

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

/**
 * Returns the table size based in the technique used
 * @param technique int technique 1 - lineal | 2 - key-depend | 3 - chained
 * @return int size
 */
int getTableSize(int technique){
    if(technique == 1) {
        return TABLE_SIZE;
    } else if(technique == 2){
        //If it's using the key-dependent technique the size will be a prime number to ensure a full iteration
        int size = TABLE_SIZE;
        while (!isPrimeNumber(size)){
            size++;
        }
        return size;
    }

    return CHAINED_TABLE_SIZE;
}

/**
 * Aux function to check if a number is prime, for the table size of the key-dependent technique
 * @see https://stackoverflow.com/questions/1538644/c-determine-if-a-number-is-prime
 * @param number
 * @return int 0 if not | 1 if yes
 */
int isPrimeNumber(int number) {
    if (number <= 1) return 0;
    int i;
    for (i=2; i*i<=number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}