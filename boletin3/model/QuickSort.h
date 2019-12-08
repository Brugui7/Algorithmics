/**
 * @file
 * @brief QuickSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#ifndef ALGORITHMICS_QUICKSORT_H
#define ALGORITHMICS_QUICKSORT_H
void quickSort(int *array, int size, char *outputFilePath, int pivotOption);
void quickSortRec(int *array, int ini, int fin, int pivotOption);
int getMidAsPivot(int startPosition, int endPosition);

#endif //ALGORITHMICS_QUICKSORT_H
