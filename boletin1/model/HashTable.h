//
// Created by Brugui on 19/10/2019.
//

#ifndef ALGORITHMICS_HASHTABLE_H
#define ALGORITHMICS_HASHTABLE_H


#include "Film.h"
#define FREE -1;
#define DELETED -2;
#define TABLE_SIZE 400;
#define CHAINED_TABLE_SIZE 40;

typedef struct hashitem {
    int key;
    film *film;
    //This field will be only used with the chained technique
    struct hashitem *next;
} hashitem, *hashtable;

hashtable *loadFile(hashtable* hashtable, int technique);

void cleanTable(hashtable* hashtable, int technique);

//To manually add a new film
void insertFilm(hashtable *hashTable, film *newFilm);

//To add a film to the hashTable
void addFilm(hashtable *hashTable, film *newFilm, int technique);

int linearCollisionHandler(hashtable *hashTable, int index);

int keyDependentCollisionHandler(hashtable *hashTable, int hashCode);

int chainedCollisionHandler(hashtable *hashTable, film *newFilm, int hashcode);

//TODO: LoadFactor

#endif //ALGORITHMICS_HASHTABLE_H
