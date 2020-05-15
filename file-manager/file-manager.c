/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (file-manager.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include "helpers.h";
#include "../canvas/structs.h";

Rectangle *parse_input(char input[]) {
    FILE *input_file = fopen_wrapper(input, "r");

    Rectangle *rectangles;

    char *line;
    while (fgets_wrapper(line, ))
}

/* REMOVE THIS */
extern int make_iso_compilers_happy;