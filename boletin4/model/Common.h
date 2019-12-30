/**
 * @file
 * @brief Common functions definitions
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#ifndef ALGORITHMICS_COMMON_H
#define ALGORITHMICS_COMMON_H

#include <stdio.h>

FILE *askForFileToLoad();
char *loadFile(FILE *file, char* array);
char *askForPattern();

#endif //ALGORITHMICS_COMMON_H
