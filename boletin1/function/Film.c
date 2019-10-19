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
 * Obtains a code by doing a sum of year + duration + popularity
 * @return int hash code of the film
 */
int hash(film *film){
    return film->year + film->duration + film->popularity;
}

void showFilm(film *film){
    printf(
            "Titulo: %s\nGenero: %s\nDuracion: %d\nAnyo: %d\nPopularidad: %d\n\n",
            film->title, film->genre, film->duration, film->year, film->popularity
            );
}