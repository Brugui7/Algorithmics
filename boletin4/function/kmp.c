/**
 * @file
 * @brief KMP Search implementations
 * @author Andr�s Mu�oz
 * @since 2019-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Common.h"
#include "kmp.h"

#define TRUE 1
#define FALSE 0

/**
 * Funci�n para mostrar la tabla siguiente
 * @param t
 * @param size
 * @param nombre_tabla
 */
void mostrar_tablaKMP(int *t, int size, const char *nombre_tabla) {
    printf("Tabla %s: ", nombre_tabla);
    for (int i = 0; i < size; i++) {
        printf("%i ", t[i]);
    }
    printf("\n");
}


/**
 * Esta funci�n se encarga de calcular la tabla siguiente
 * @param p patten
 * @param size of the pattern
 * @param tablaNext associated to p
 */
void preKMP(char *p, int size, int *tablaNext) {
    int i, j;
    i = 0;
    j = tablaNext[0] = -1;
    while (i < size - 1) {
        while (j > -1 && p[i] != p[j]) {
            j = tablaNext[j];
        }
        i++;
        j++;
        if (p[i] == p[j])
            tablaNext[i] = tablaNext[j];
        else
            tablaNext[i] = j;
    }
}


/**
 *
 * @param s string
 * @param p pattern
 * @param restarts
 * @return
 */
int *KMPSearch(char *s, char *p, double *restarts) {
    int i, j; // i �ndice de S, j �ndice de P
    int *foundPositions = (int*) malloc(sizeof(int));
    foundPositions[0] = -1;
    int foundPositionsCounter = 0;

    int s_len, p_len;   // Obtener las longitudes de s y p
    p_len = strlen(p);
    s_len = strlen(s);

    if (p_len > s_len){
        foundPositions[0] = -1;
        return foundPositions;
    }


    int tablaNext[p_len];  // Crear la tabla siguiente de P y calcularla
    preKMP(p, p_len, tablaNext);
    mostrar_tablaKMP(tablaNext, p_len, "Sgte");
    i = j = 0;
    while (i < s_len) {
        while (j > -1 && s[i] != p[j]) {
            j = tablaNext[j];
        }
        i++;
        j++;
        if (j >= p_len) {
            foundPositionsCounter++;
            foundPositions = (int*) realloc(foundPositions, sizeof(int) * (foundPositionsCounter + 1));
            foundPositions[foundPositionsCounter - 1] = i - j; //Saves the first position of the pattern
            foundPositions[foundPositionsCounter] = -1; //To know the end of the array
            j = 0;
        } else {
            (*restarts)++;
        }
    }

    return foundPositions;
}

/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteKMP(){
    FILE *file = askForFileToLoad();
    char* array = NULL;
    char* pattern = askForPattern();
    array = loadFile(file, array);
    fclose(file);


    mainKMP(array, pattern);

    free(array);
    free(pattern);
}

void mainKMP(char *array, char *pattern) {
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    double restarts = 0;

    printf("\n-------------------- \nKMP\n--------------------\n");

    gettimeofday(&start, NULL);
    int *foundPositions = KMPSearch(array, pattern, &restarts);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    printf(//TODO iterations
            "\nTiempo Invertido: %f\nReinicios: %.2f\n",
            timeInvested, restarts
    );

    if (foundPositions[0] == -1) {
        printf("No se ha encontrado ninguna coincidencia\n");
    } else {
        printf("Se ha encontrado la subcadena en las siguientes posiciones:\n");
        int i = 0;
        while (foundPositions[i] != -1) {
            printf("%d ", foundPositions[i++]);
        }
        printf("\n");
    }

    free(foundPositions);
}