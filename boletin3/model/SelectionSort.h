/**
 * @file
 * @brief SelectionSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#ifndef ALGORITHMICS_SELECTIONSORT_H
#define ALGORITHMICS_SELECTIONSORT_H


void basicSelectionSort(int *array, int size, int *comparisons, int *swaps);
void mainSelectionSort(int *array, int size, char *outputFilePath);
void improvedSelectionSort(int *array, int size, int *comparisons, int *swaps);

#endif //ALGORITHMICS_SELECTIONSORT_H
