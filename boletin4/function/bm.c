/**
 * @file
 * @brief Booyer Moore Search implementations
 * @author Andrés Muñoz
 * @since 2019-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bm.h>
#include <sys/time.h>
#include <Common.h>

#define TRUE 1
#define FALSE 0

// Funcion para calcular la tabla D1 (regla del mal caracter).
// p es el patron, size es el tamaño del patrón y D1 es la tabla que se debe rellenar
// en la funcion
static void prepare_badcharacter_heuristic(const char *p, int size, int D1[ALPHABET_SIZE]) {

    int i;

    for (i = 0; i < ALPHABET_SIZE; i++)
        D1[i] = -1;

    for (i = 0; i < size; i++) {
        int t = (size_t) p[i] - 97; // Obtiene el código ascii de la letra del patron en la posicion i
        D1[t] = i;
    }

}

// Funcion auxiliar necesaria para calcular la tabla D2.
static void compute_prefix(const char *str, int size, int result[]) {
    int q;
    int k;
    result[0] = 0;

    k = 0;
    for (q = 1; q < size; q++) {
        while (k > 0 && str[k] != str[q])
            k = result[k - 1];

        if (str[k] == str[q])
            k++;
        result[q] = k;
    }
}

// Funcion para calcular la tabla D2 (regla del buen sufijo).
// p es el patron, size es el tamaño del patrón y D2 es la tabla que se debe rellenar
// en la funcion
void prepare_goodsuffix_heuristic(const char *p, int size, int D2[]) {

    char *left = (char *) p;
    char *right = left + size;
    char reversed[size + 1];
    char *tmp = reversed + size;
    int i;

    *tmp = 0;
    while (left < right)
        *(--tmp) = *(left++);

    int prefix_normal[size];
    int prefix_reversed[size];

    compute_prefix(p, size, prefix_normal);
    compute_prefix(reversed, size, prefix_reversed);

    for (i = 0; i <= size; i++) {
        D2[i] = size - prefix_normal[size - 1];
    }

    for (i = 0; i < size; i++) {
        const int j = size - prefix_reversed[i];
        const int k = i - prefix_reversed[i] + 1;

        if (D2[j] > k)
            D2[j] = k;
    }
}


// Función para mostrar las tablas D1 o D2
void mostrar_tabla(int *s, int size, const char *nombre_tabla) {
    printf("Tabla %s: ", nombre_tabla);
    for (int i = 0; i < size; i++) {
        printf("%i ", s[i]);
    }
    printf("\n");
}


/*
 * Algoritmo de busqueda Boyer-Moore
 * s es la cadena madre, p es el patrón, y posiciones es un array de enteros
 * que contendrá las posiciones iniciales del patrón p detectado en la cadena s cuando acabe el algoritmo
 */
int *boyermoore_search(char *s, char *p, double *restarts) {
    int s_len, p_len;
    int *foundPositions = (int *) malloc(sizeof(int));
    foundPositions[0] = -1;
    int foundPositionsCounter = 0;

    //Calcula el tamaño de las cadenas
    p_len = strlen(p);
    s_len = strlen(s);


    //Comprobaciones simples
    if (s_len == 0)
        return foundPositions;
    if (p_len == 0)
        return foundPositions;
    if (p_len > s_len)
        return foundPositions;
    //Obtener tablas D1 y D2

    int D1[ALPHABET_SIZE];  // D1 = mal caracter
    int D2[p_len + 1]; // D2 = buen sufijo


    prepare_badcharacter_heuristic(p, p_len, D1);
    prepare_goodsuffix_heuristic(p, p_len, D2);

    mostrar_tabla(D1, ALPHABET_SIZE, "D1");
    mostrar_tabla(D2, p_len, "D2");

    // Busqueda Boyer-Moore

    int i = 0; // indice de la cadena s
    while (i <= (s_len - p_len)) {
        int j = p_len;  // indice del patron p (desde el ultimo caracter)
        while (j > 0 && p[j - 1] == s[i + j - 1]){
            j--;
        }

        if (j > 0) {
            int z = D1[((size_t) s[i + j - 1]) - 97];
            int m;
            if (z < j && (m = j - z - 1) > D2[j]){
                i += m;
            } else {
                i += D2[j];
            }
            (*restarts)++;
        } else {
            foundPositionsCounter++;
            foundPositions = (int *) realloc(foundPositions, sizeof(int) * (foundPositionsCounter + 1));
            foundPositions[foundPositionsCounter - 1] = i; //Saves the first position of the pattern
            foundPositions[foundPositionsCounter] = -1; //To know the end of the array
            i++;
        }
    }
    return foundPositions;
}

/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteBM() {
    FILE *file = askForFileToLoad();
    char *array = NULL;
    char *pattern = askForPattern();
    array = loadFile(file, array);
    fclose(file);


    mainBM(array, pattern);

    free(array);
    free(pattern);
}

void mainBM(char *array, char *pattern) {
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    double restarts = 0;

    printf("\n-------------------- \nBM\n--------------------\n");

    gettimeofday(&start, NULL);
    int *foundPositions = boyermoore_search(array, pattern, &restarts);
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