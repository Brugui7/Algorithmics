//
// Created by Brugui on 02/01/2020.
//

#ifndef ALGORITHMICS_BM_H
#define ALGORITHMICS_BM_H

#endif //ALGORITHMICS_BM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define ALPHABET_SIZE 25  // Tamaño del alfabeto espanol
static void prepare_badcharacter_heuristic(const char *p, int size, int D1[ALPHABET_SIZE]);
static void compute_prefix(const char *str, int size, int result[]);
void prepare_goodsuffix_heuristic(const char *p, int size, int D2[]);
void mostrar_tabla(int *s, int size, const char *nombre_tabla);
int *boyermoore_search(char *s, char *p, double *restarts);
void readFileAndExecuteBM();
void mainBM(char *array, char *pattern);