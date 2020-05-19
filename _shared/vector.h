/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (vector.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __SHARED_VECTOR_H   /* Include guard */
#define __SHARED_VECTOR_H

#include "helpers.h"

#define VECTOR_INITIALIZE(vector) Vector vector; vector_initialize(&vector);
#define VECTOR_INITIALIZE_PTR(vector) Vector *vector = malloc_wrapper(sizeof(Vector)); vector_initialize(vector);
#define VECTOR_PUSH(vector, item) vector_push(&vector, (void *) item);
#define VECTOR_PUSH_PTR(vector, item) vector_push(vector, (void *) item);
#define VECTOR_GET(vector, type, index) (type) vector_get(&vector, index);

/** 
 * Simples implementação de um vetor. Em conjunção com os métodos da classe
 * vector.c, permite controlar estruturas de dados com tamanhos dinâmicos
 * com facilidade
 */
typedef struct Vector {
    /** Valores do vetor */
    void **items;

    /** Tamanho máximo do vetor */
    int size;

    /** Quantidade de valores no vetor atualmente */
    int count;
} Vector;

/** 
 * Inicializa um vetor com tamanho máximo a 2, e aloca espaço em memória para
 * os seus valores
 * @param vector Vetor a inicializar
*/
void vector_initialize(Vector *vector);

/**
 * Adiciona um item a um vetor.
 * Caso o tamanho máximo do vetor seja alcaçado,
 * o tamanho do vetor é duplicado.
 * @param vector Vetor onde será adicionado o item
 * @param item Item a adicionar ao vetor
 */
void vector_push(Vector *vector, void *item);

/** 
 * Adquire um valor de um vetor.
 * Se o índice estiver fora dos limites do vetor, 
 * será retornado um ponteiro null.
 * @param vector Vetor de onde será procurado o item
 * @param index Índice do item a procurar
 */
void *vector_get(Vector *vector, int index);

#endif