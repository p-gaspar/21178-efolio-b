/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (canvas.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include "structs.h"
#include "../_shared/helpers.h"

/** Plano atual */
Canvas *canvas;

/** 
 * Indica se o canvas já foi inicializado.
 * O canvas só poderá ser utilizado se tiver inicializado 
 */
int canvas_initialized = 0;

/**
 * Lança um erro que o canvas não foi inicializado e termina a execução
 * do programa.
 */
void throw_uninitialized_error()
{
    printf("ERRO: O plano não foi inicializado.\n"
           "      Para manipular retângulos, terá de ser inicializado "
           "primeiro\n");

    exit(0);
}

/**
 * Inicializa o canvas com valores por defeito
 */
void canvas_initialize()
{
    canvas = malloc_wrapper(sizeof(Canvas));

    canvas->width = 80;
    canvas->height = 25;

    canvas_initialized = 1;
}

/**
 * Define as dimensões do canvas.
 * O canvas terá de ser inicializado primeiro
 */
void canvas_set_dimensions(int width, int height)
{
    if (!canvas_initialized)
    {
        throw_uninitialized_error();
    }

    canvas->width = width;
    canvas->height = height;
}

/** 
 * Executa a limpeza das variáveis alocadas em memória do canvas 
 */
void canvas_destroy()
{
    canvas_initialized = 0;
    free(canvas);
}