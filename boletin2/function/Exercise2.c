/**
 * @file
 * @brief Exercise 2 logic
 * @author: Alejandro Brugarolas
 * @since: 2019-11
*/

#include "Exercise2.h"

#include <stdlib.h>
#include <string.h>

void mainExercise2(){
    char fileName[100] = "";
    FILE *file = NULL;
    song* songList = NULL;

    //Asks for the file to load the data
    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n> ");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }

    songList = loadFile(file, songList);


}

/**
 * Loads the file and returns a list of songs
 * @param songList
 * @param file
 * @return songs list
 */
song *loadFile(FILE *file, song* songList){
    char *buffer = (char *) malloc(sizeof(char) * 255);
    //To set the song id. Overkill but effective if the number of songs is unknown
    char *idBuffer = (char *) malloc(sizeof(char) * 255);

    char *token;
    size_t bufferSize = 255;
    int i = 0; //Aux variable to get the song id

    while(fgets(buffer, bufferSize, file) != NULL){
        song *newSong = (song*) malloc(sizeof(song));

        //Sets the song id
        sprintf(idBuffer, "C%d", ++i);
        newSong->id = (char*) malloc(sizeof(char) * strlen(idBuffer) + 1);
        strncpy(newSong->id, idBuffer, strlen(idBuffer) + 1);

        strtok(buffer, ";");
        //The duration comes in format minutes:seconds
        token = strtok(buffer, ":");

        //fills the song data
        newSong->duration = atoi(token) * 60;
        token = strtok(NULL, ";");
        newSong->duration += atoi(token); //To get the seconds
        token = strtok(NULL, ";");


        newSong->popularity = atoi(token);

        newSong->next = (struct song*) malloc(sizeof(song));
        newSong->next = songList;
        songList = newSong;
    }

    free(buffer);
    free(idBuffer);
    fclose(file);

    return songList;
}