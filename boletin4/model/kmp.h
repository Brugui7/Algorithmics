//
// Created by Brugui on 30/12/2019.
//

#ifndef ALGORITHMICS_KMP_H
#define ALGORITHMICS_KMP_H

#endif //ALGORITHMICS_KMP_H


void mostrar_tablaKMP(int *t, int size, const char *nombre_tabla);
void preKMP(char *p, int size, int *tablaNext);
int *KMPSearch(char *s, char *p);
void readFileAndExecuteKMP();
void mainKMP(char *array, char *pattern);