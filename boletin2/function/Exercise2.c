/**
 * @file
 * @brief Exercise 2 logic
 * @author: Alejandro Brugarolas
 * @since: 2019-11
*/

#include "Exercise2.h"

#include <stdlib.h>
#include <string.h>
#define ALBUM_SIZE 12
#define ALBUM_LENGTH 40

void mainExercise2(){
    char fileName[100] = "";
    FILE *file = NULL;
    song* songList = NULL;
    int n = 0; //songs number

    //Asks for the file to load the data
    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n>");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }

    songList = loadFile(file, songList);
    song *aux = songList;
    while (aux != NULL){
        n++;
        aux = aux->next;
    }

    int *solution = (int*) malloc(sizeof(int) * n);
    int *bestSolution = (int*) malloc(sizeof(int) * n);

    createAlbumRec(n, solution, 0, bestSolution, songList);
    showAlbum(n, bestSolution, songList);

    free(solution);
    free(bestSolution);
}

/**
 *
 * @param n
 * @param solution
 * @param step
 * @param bestSolution
 * @return
 */
void createAlbumRec(int n, int *solution, int step, int *bestSolution, song* songList){
    if(step == n) return;
    int aux = 0;
    do{
        //The first try is not taking the song to make the album
        solution[step] = aux;
        if(isValid(n, solution, step, songList) == 1){
            if(step == n - 1){
                keepBetterSolution(n, solution, bestSolution, songList);
            } else {
                createAlbumRec(n, solution, step + 1, bestSolution, songList);
            }
        }
        aux++;
    } while (solution[step] != 1);
    solution[step] = -1;
}

/**
 * Checks if the album matches all the conditions
 * @param n
 * @param solution
 * @param step
 * @param songList
 * @return
 */
int isValid(int n, int *solution, int step, song* songList){
    int seconds = 0;
    int secondsLength = ALBUM_LENGTH * 60;
    int songsNumber = 0;
    song *aux = songList;

    for (int i = 0; i <= step; i++) {
        if(solution[i] == 1){
            songsNumber++;
            seconds += aux->duration;
            if (seconds > secondsLength || songsNumber > ALBUM_SIZE) return 0;
        }
        aux = aux->next;
    }

    if (step == n - 1){
        if (songsNumber != ALBUM_SIZE || secondsLength - seconds > 120) return 0;
    }

    return 1;
}

/**
 *
 * @param n
 * @param solution
 * @param bestSolution
 * @param songList
 */
void keepBetterSolution(int n, int *solution, int *bestSolution, song* songList){
    int bestSolutionPopularity = 0;
    int actualSolutionPopularity = 0;
    song *aux = songList;
    for (int i = 0; i < n; ++i) {
        if (solution[i] == 1) actualSolutionPopularity += aux->popularity;
        if (bestSolution[i] == 1) bestSolutionPopularity += aux->popularity;
        aux = aux->next;
    }
    if (bestSolutionPopularity >= actualSolutionPopularity) return;

    for (int i = 0; i < n; ++i) {
        bestSolution[i] = solution[i];
    }

}

/**
 *
 * @param n
 * @param solution
 * @param songList
 */
void showAlbum(int n, int *solution, song* songList){

    printf("\nMejor propuesta encontrada\nGRANDES ÉXITOS MURCIANOS | 1Pimiento Records\n");

    int totalSeconds = 0;
    int totalPopularity = 0;
    song *aux = songList;
    for (int i = 0; i < n; ++i) {
        if (solution[i] == 1){
            totalSeconds += aux->duration;
            totalPopularity += aux->popularity;
            printf("%s\tDuración (segundos): %d\t Popularidad: %d\n", aux->id, aux->duration, aux->popularity);
        }
        aux = aux->next;
    }

    printf("\nTiempo Total (segundos): %d\t Popularidad Total: %d\n", totalSeconds, totalPopularity);
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
    song *lastSong = (song*) malloc(sizeof(song));

    while(fgets(buffer, bufferSize, file) != NULL){
        song *newSong = (song*) malloc(sizeof(song));
        if (i == 0) songList = lastSong;

        //Sets the song id
        sprintf(idBuffer, "C%d", ++i);
        newSong->id = (char*) malloc(sizeof(char) * strlen(idBuffer) + 1);
        strncpy(newSong->id, idBuffer, strlen(idBuffer) + 1);

        //strtok(buffer, ";");
        //The duration comes in format minutes:seconds
        token = strtok(buffer, ":");

        //fills the song data
        newSong->duration = atoi(token) * 60;
        token = strtok(NULL, ";");
        newSong->duration += atoi(token); //To get the seconds
        token = strtok(NULL, ";");

        newSong->popularity = atoi(token);


        //To insert the list ordered keeps the track of the first song
        if (i == 1){
            songList = newSong;
        } else{
            lastSong->next = newSong;
            newSong->next = NULL;
        }
        lastSong = newSong;
    }

    free(buffer);
    free(idBuffer);
    fclose(file);

    return songList;
}