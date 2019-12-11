/**
 * @file
 * @brief ShellSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#ifndef ALGORITHMICS_SHELLSORT_H
#define ALGORITHMICS_SHELLSORT_H

void mainShellSort(int *array, int size, char *outputFilePath);
void shellSort(int *array, int size, int *comparisons, int *swaps);
int calcIncrementSize(int size);

#endif //ALGORITHMICS_SHELLSORT_H
