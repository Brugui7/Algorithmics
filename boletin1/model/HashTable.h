//
// Created by Brugui on 19/10/2019.
//

#ifndef ALGORITHMICS_HASHTABLE_H
#define ALGORITHMICS_HASHTABLE_H


#include "Film.h"
#define FREE -1;
#define DELETED -2;
#define TABLE_SIZE 400;

typedef struct hashitem {
    int key;
    film *film;
} hashitem, *hashtable;

hashtable *loadFile(hashtable* hashtable, int technique);

void cleanTable(hashtable* hashtable);

//To manually add a new film
void insertFilm(hashtable *hashTable, film *newFilm);

//To add a film to the hashTable
void addFilm(hashtable *hashTable, film *newFilm, int technique);

int linearCollisionHandler(hashtable *hashTable, int index);

#endif //ALGORITHMICS_HASHTABLE_H
