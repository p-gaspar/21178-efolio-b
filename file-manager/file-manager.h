/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (file-manager.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __FILE_MANAGER_H   /* Include guard */
#define __FILE_MANAGER_H

#include "../_shared/vector.h"

/**
 * Lê um ficheiro e converte as suas linhas para
 * structs de retângulos
 */
Vector *parse_file(char input[]);

#endif