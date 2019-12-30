#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Common.h"
#include "kmp.h"

#define TRUE 1
#define FALSE 0

// Función para mostrar la tabla siguiente
void mostrar_tablaKMP(int *t, int size, const char *nombre_tabla) {
    printf("Tabla %s: ", nombre_tabla);
    for (int i = 0; i < size; i++) {
        printf("%i ", t[i]);
    }
    printf("\n");
}


// p es el patrón, size es el tamaño del patron y tablaNext es la tabla "siguiente" asociada a p
// Esta función se encarga de calcular la tabla siguiente
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


// s es la cadena madre, p es el patrón, y posiciones es un array de enteros
// que contendrá las posiciones iniciales del patrón p detectado en la cadena s
int *KMPSearch(char *s, char *p) {
    int i, j; // i índice de S, j índice de P
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


    gettimeofday(&start, NULL);
    int *foundPositions = KMPSearch(array, pattern);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    printf(//TODO iterations
            "\n-------------------- \nKMP\n--------------------\n"
            "Tiempo Invertido: %f\nReinicios: %.2f\n",
            timeInvested, restarts
    );

    if (foundPositions[0] == -1) {
        printf("No se ha encontrado ninguna coincidencia\n");
    } else {
        printf("Se ha encontrado la subcadena en las siguientes posiciones:\n");
        int i = 0;
        while (foundPositions[i] != -1) {
            printf("%d, ", foundPositions[i++]);
        }
        printf("\n");
    }

    free(foundPositions);
}