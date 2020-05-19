/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (helpers.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __FILE_MANAGER_HELPERS_H   /* Include guard */
#define __FILE_MANAGER_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/**
 * Verifica se um ficheiro existe.
 * Se existir retorna 1, caso contrário retorna 0.
 */
int file_exists(char filename[]);

/**
 * Implementação do fopen que, quando ocorre um erro ao abrir o ficheiro,
 * é disparado um erro e a execução do programa é parada.
 */
FILE *fopen_wrapper(char *filename, char *mode);

/**
 * Adquire um campo de uma linha do ficheiro "CSV" (neste caso semi colon).
 * Os campos têm de estar separados por um ponto e vírgula (;).
 * Os campos são 1-index (ou one-based), ou seja, o primeiro campo
 * tem o index 1.
 */
char* get_csv_field(char* line, int index);

/**
 * Implementação do fgets que remove a newline no final da string.
 */
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp);

#endif