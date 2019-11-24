/**
 * @file
 * @brief Exercise 2 header file
 * @author: Alejandro Brugarolas
 * @since: 2019-11
*/

#ifndef ALGORITHMICS_EXERCISE2_H
#define ALGORITHMICS_EXERCISE2_H
#include <stdio.h>

typedef  struct song{
    char* id;
    int duration;
    int popularity;
    struct song *next;
} song;

void mainExercise2();

song *loadFile(FILE *file, song* songList);

void createAlbumRec(int n, int *solution, int step, int *bestSolution, song* songList);

int isValid(int n, int *solution, int step, song* songList);

void keepBetterSolution(int n, int *solution, int *bestSolution, song* songList);

void showAlbum(int n, int *solution, song* songList);

#endif //ALGORITHMICS_EXERCISE2_H
