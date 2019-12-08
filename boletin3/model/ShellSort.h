/**
 * @file
 * @brief ShellSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#ifndef ALGORITHMICS_SHELLSORT_H
#define ALGORITHMICS_SHELLSORT_H

void shellSort(int *array, int size, char *outputFilePath);
int calcIncrementSize(int size);
int calcNextIncrement(int size, int interval);

#endif //ALGORITHMICS_SHELLSORT_H
