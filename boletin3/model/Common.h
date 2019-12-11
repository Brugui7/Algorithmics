/**
 * @file
 * @brief Common functions definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#ifndef ALGORITHMICS_COMMON_H
#define ALGORITHMICS_COMMON_H

void writeFile(int *array, int size, char *outputFileName);
int* copyArray(int *arraySource, int size, int *arrayDestination);
FILE *askForFileToLoad();
int *loadFile(FILE *file, int* array);
int countElements(FILE *file);

#endif //ALGORITHMICS_COMMON_H
