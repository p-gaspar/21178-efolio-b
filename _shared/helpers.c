/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (helpers.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Método que implementa "graceful degradation"
 * ao utilizar a função malloc. Se ocorrer um erro
 * ao alocar a memória, mostra uma mensagem no ecrã
 * e aborta a execução do programa.
 */
void *malloc_wrapper(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("ERRO: Ocorreu um erro ao alocar memória.\n"
               "      A execução do programa terminou.\n");
        exit(0);
    }

    return ptr;
}