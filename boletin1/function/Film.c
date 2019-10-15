/**
 * @file
 * @brief Independent film functions
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Film.h"

/**
 * reads the films file and saves the data into the hash table using the desired technique
 * @param technique 1 - lineal | 2 - key-depend | 3 - chained
 * @return
 */
film *loadFile(film* hashTable, int technique){
    char fileName[100] = "";
    FILE *file = NULL;
    char *buffer = (char *) malloc(sizeof(char) * 255);
    char *token;
    size_t length, bufferSize = 255;

    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n> ");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }
    printf("Cargando datos...\n");

    fgets(buffer, bufferSize, file); //ignores the headers
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
        printf("película detectada:  %d - %d - %s\n", newFilm->year, newFilm->duration, newFilm->title);
        //addFilm(hashTable, film);
    }

    return hashTable;
}

film *addFilm(film *hashTable, film newFilm){
    //Todo
}

/**
 * Obtains a code by doing a sum of year + duration + popularity applying a mod 400
 * @return int hash code of the film
 *
int hash(struct film){
TODO
}*/

