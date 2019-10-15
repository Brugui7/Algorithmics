/**
 * @file
 * @brief Functions definition for Film
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/
#ifndef ALGORITHMICS_FILM_H
#define ALGORITHMICS_FILM_H

#define FREE -1;
#define TABLE_SIZE 400;

typedef struct film {
    int year;
    int duration;
    char* title;
    char* genre;
    int popularity;
} film;

film *loadFile(film* hashtable, int technique);

void insertFilm(film *hashTable, film *newFilm);

int hash(film);

#endif //ALGORITHMICS_FILM_H

