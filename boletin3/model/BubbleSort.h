/**
 * @file
 * @brief BubbleSort definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */
#ifndef ALGORITHMICS_BUBBLESORT_H
#define ALGORITHMICS_BUBBLESORT_H

void basicBubbleSort(int *array, int size, double *comparisons, double *swaps);
void mainBubbleSort(int *array, int size, char *outputFilePath);
void readFileAndExecuteBubbleSort();
void improvedBubbleSort(int *array, int size, double *comparisons, double *swaps);

#endif //ALGORITHMICS_BUBBLESORT_H
