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

int createAlbumRec(int n, int solution[], int step, int bestSolution[]);

#endif //ALGORITHMICS_EXERCISE2_H
