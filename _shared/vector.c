/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (vector.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/** 
 * Inicializa um vetor com tamanho máximo a 2, e aloca espaço em memória para
 * os seus valores
 * @param vector Vetor a inicializar
*/
void vector_initialize(Vector *vector)
{
    vector->size = 2;
    vector->count = 0;
    vector->items = malloc(sizeof(void *) * v->size);
}

/** 
 * Altera a capacidade do vetor.
 * @param vector Vetor a alterar a capacidade
 * @param size Capacidade após o redimensionamento
 */
static void vector_resize(Vector *vector, int size)
{
    void **items = realloc(vector->items, sizeof(void *) * size);
    
    if (items) {
        vector->items = items;
        vector->size = size;
    }
}

/**
 * Adiciona um item a um vetor.
 * Caso o tamanho máximo do vetor seja alcaçado,
 * o tamanho do vetor é duplicado.
 * @param vector Vetor onde será adicionado o item
 * @param item Item a adicionar ao vetor
 */
void vector_push(Vector *vector, void *item)
{
    if (vector->size == vector->count) {
        vector_resize(vector, vector->size * 2);
    }

    vector->items[vector->count++] = item;
}

/** 
 * Adquire um valor de um vetor.
 * Se o índice estiver fora dos limites do vetor, 
 * será retornado um ponteiro null.
 * @param vector Vetor de onde será procurado o item
 * @param index Índice do item a procurar
 */
void *vector_get(Vector *vector, int index)
{
    if (index >= 0 && index < vector->count) {
        return vector->items[index];
    }

    return NULL;
}