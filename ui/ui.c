/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (ui.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void clear_screen() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void initialize() {
    /* clear_screen(); */
    printf("E-Folio B: Mundo dos retangulos ## 1902551 - Pedro Gaspar\n\n");
}