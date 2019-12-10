/**
 * @file
 * @brief QuickSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#ifndef ALGORITHMICS_QUICKSORT_H
#define ALGORITHMICS_QUICKSORT_H
void mainQuickSort(int *array, int size, char *outputFilePath, int pivotOption);
void quickSortRec(int *array, int ini, int fin, int pivotOption, int *comparisons, int *swaps);
int getMidAsPivot(int startPosition, int endPosition);
int getRandAsPivot(int startPosition, int endPosition);
int getMedianAsPivot(const int *array, int startPosition, int endPosition, int *comparisons);

#endif //ALGORITHMICS_QUICKSORT_H
