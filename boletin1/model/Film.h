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
} film;

int hash(int year, int duration, int popularity);

void showFilm(film *film);

void delete(film *film);

#endif //ALGORITHMICS_FILM_H

