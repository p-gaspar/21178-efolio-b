/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (helpers.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "helpers.h"
#include "vector.h"
#include "../canvas/structs.h"

/**
 * Método que implementa "graceful degradation"
 * ao utilizar a função malloc. Se ocorrer um erro
 * ao alocar a memória, mostra uma mensagem no ecrã
 * e aborta a execução do programa.
 */
void *malloc_wrapper(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
               " Ocorreu um erro ao alocar memória.\n"
               "      A execução do programa terminou.\n");
        exit(0);
    }

    return ptr;
}

/**
 * Método que implementa "graceful degradation"
 * ao utilizar a função calloc. Se ocorrer um erro
 * ao alocar a memória, mostra uma mensagem no ecrã
 * e aborta a execução do programa.
 */
void *calloc_wrapper(int count, size_t size) {
    void *ptr = calloc(count, size);
    if (ptr == NULL) {
        wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
               " Ocorreu um erro ao alocar memória.\n"
               "      A execução do programa terminou.\n");
        exit(0);
    }

    return ptr;
}

/**
 * Valida e converte uma string para um int.
 * Esta função faz tambem error handling e caso 
 * o valor recebido seja válido, é retornado o próprio número.
 * Se o valor não for válido, é retornado 0 e deverá ser verificado o errno.
 * @param arg Argumento a converter para número inteiro
 */
int string_to_int(char *arg) {
    /*
    * Variável que vai receber o valor após o valor numérico
    * na string.
    * Se não houver nenhum valor após o número, então o valor será o próprio
    * número (de acordo com a documentação da função strtol)
    */
    char *end_ptr = NULL;

    long converted_val = strtol(arg, &end_ptr, 10);

    /*
    * Reset ao errno para 0. Isto significa que não há erros na aplicação
    * para já. 
    */
    errno = 0;

    /* 
    * Verificamos agora se a função converteu corretamente
    * para o valor que estamos à espera.
    *
    * Primeiro vemos se o argumento é diferente do end_ptr.
    * O end_ptr só será igual ao argumento caso o argumento
    * contenha apenas letras ou contenha letras antes do número 
    * ("abc" ou "a5").
    *
    * Em segundo lugar verificamos se o end_ptr está a apontar para uma string
    * vazia.
    * Se o argumento contiver letras após o número ("5a"), o end_ptr vai ser 
    * igual a essas letras (neste exemplo será "a").
    * Só será vazia se não houver qualquer letras no input (o que pretendemos).
    *
    * Em terceiro lugar verificamos se o erro é diferente do erro 
    * ERANGE (range error). A função strtol coloca o errno igual a ERANGE
    * quando o valor recebido está fora do alcance de um long.
    *
    * Em quarto e quinto lugar, verificamos se o valor está dentro do alcance
    * mínimo e máximo de um int. Isto porque a função strtol converte
    * um valor para long, neste caso apenas queremos um int.
    */
    if (arg != end_ptr
        && *end_ptr == 0
        && errno != ERANGE 
        && converted_val >= INT_MIN 
        && converted_val <= INT_MAX)
    {
        return (int)converted_val;
    }

    return 0;
}