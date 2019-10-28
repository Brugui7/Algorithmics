/**
 * @file
 * @brief Independent film functions
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/

#include <stdio.h>
#include <stdlib.h>

#include "Film.h"


/**
 * Obtains a code by doing a sum of year + duration + popularity of a film
 * @param year
 * @param duration
 * @param popularity
 * @return int hash code of the film
 */
int hash(int year, int duration, int popularity){
    return year + duration + popularity;
}

void showFilm(film *film){
    printf(
            "Titulo: %s\nGenero: %s\nDuracion: %d\nAnyo: %d\nPopularidad: %d\n\n",
            film->title, film->genre, film->duration, film->year, film->popularity
            );
}

/**
 * Frees all the fields of a film
 * @param film
 */
void delete(film *film){
    if (film != NULL){
        free(film->title);
        free(film->genre);
        free(film);
    }
}
