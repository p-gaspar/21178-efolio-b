/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (helpers.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __SHARED_HELPERS_H   /* Include guard */
#define __SHARED_HELPERS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/**
 * Método que implementa "graceful degradation"
 * ao utilizar a função malloc. Se ocorrer um erro
 * ao alocar a memória, mostra uma mensagem no ecrã
 * e aborta a execução do programa.
 */
void *malloc_wrapper(size_t size);

/**
 * Valida e converte uma string para um int.
 * Esta função faz tambem error handling e caso 
 * o valor recebido seja válido, é retornado o próprio número.
 * Se o valor não for válido, é retornado 0 e deverá ser verificado o errno.
 * @param arg Argumento a converter para número inteiro
 */
int string_to_int(char *arg);

#endif