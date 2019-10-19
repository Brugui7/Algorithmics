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
    cleanTable(hashTable);

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
 * @return hashtable
 */
void cleanTable(hashtable* hashTable){
    int aux = TABLE_SIZE;

    for(int i = 0; i < aux; i++){
        hashTable[i] = (hashitem*) malloc(sizeof(hashitem));
        hashTable[i]->key = FREE
    }
}

/**
 * Adds a film to the hashtable
 * @param hashTable
 * @param newFilm
 */
void addFilm(hashtable *hashTable, film *newFilm, int technique){
    int hashCode = hash(newFilm);
    int index = hashCode % 400;
    int free = FREE;
    int deleted = DELETED;
    if (hashTable[index]->key == free || hashTable[index]->key == deleted){
        hashTable[index]->key = hashCode;
        hashTable[index]->film = newFilm;
        printf("Hashcode añadido: %d", hashCode);

    } else{
        //Collision
        int newIndex = 0;
        switch (technique){
            case 1:
                newIndex = linearCollisionHandler(hashTable, index);
                break;
            case 2:
                //TODO key-dependent
                break;
            case 3://TODO chained
                break;
        }

        //The hash table has no free places
        if(newIndex == -1){
            printf("Error, no se han encontrado posiciones libres en la tabla\n");
        } else if (technique == 1 || technique == 2){
            hashTable[newIndex]->key = hashCode;
            hashTable[newIndex]->film = newFilm;
        } else {
            //TODO chained
        }
    }

}


/**
 * Uses the Linear
 * @param hashTable
 * @param index int original position where the item was going to be inserted in
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