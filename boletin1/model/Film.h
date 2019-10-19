/**
 * @file
 * @brief Functions definition for Film
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/
#ifndef ALGORITHMICS_FILM_H
#define ALGORITHMICS_FILM_H


typedef struct film {
    int year;
    int duration;
    char* title;
    char* genre;
    int popularity;
    //These two fields will be only used with the chained technique
    struct film *previous;
    struct film *next;
} film;

int hash(film *film);

void showFilm(film *film);

#endif //ALGORITHMICS_FILM_H

