/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (vector.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __SHARED_VECTOR_H   /* Include guard */
#define __SHARED_VECTOR_H

#include <stdio.h>

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
 * Altera a capacidade do vetor.
 * @param vector Vetor a alterar a capacidade
 * @param size Capacidade após o redimensionamento
 */
static void vector_resize(Vector *vector, int size);

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