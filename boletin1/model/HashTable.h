/**
 * @file
 * @brief Functions definition for HashTable
 * @author: Alejandro Brugarolas
 * @since: 2019-10
*/
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
hashtable *insertFilm(hashtable *hashTable, int technique);

//To add a film to the hashTable
void addFilm(hashtable *hashTable, film *newFilm, int technique, int showCollisions);

int linearCollisionHandler(hashtable *hashTable, int index, int showCollisions);

int keyDependentCollisionHandler(hashtable *hashTable, int hashCode, int showCollisions);

int chainedCollisionHandler(hashtable *hashTable, film *newFilm, int hashcode, int showCollisions);

// SEARCH
void searchOrDeleteOption(hashtable *hashTable, int technique, int action);

int linearSearchCollisionHandler(hashtable *hashTable, int hashcode, char* title);

int keyDependentSearchCollisionHandler(hashtable *hashTable, int hashCode, char* title);

int getLoadFactor(hashtable *hashTable, int technique);

// AUX
void destroyEverything(hashtable* hashTable, int technique);

int getTableSize(int technique);

int isPrimeNumber(int number);
#endif //ALGORITHMICS_HASHTABLE_H
