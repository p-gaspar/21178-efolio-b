/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (ui.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __UI_H   /* Include guard */
#define __UI_H

#include "../_shared/vector.h"

/**
 * Pede ao utilizador o nome do ficheiro a carregar.
 * Se o utilizador introduzir um caminho para um ficheiro que não existe,
 * continua a pedir até obter um caminho para um ficheiro válido e mostra uma
 * mensagem de erro adequada.
 */
char *ui_request_filename();

/**
 * Pede ao utilizador que opção pretende escolher para manipular o plano.
 * Continua a pedir ao utilizador até que obtenha uma opção válida, ou até que
 * escolha a opção para sair.
 * @param rectangles Retângulos a manipular
 */
void ui_request_canvas_option(Vector *rectangles);

/** 
 * Limpa o ecrã e mostra a mensagem de título.
 */
void ui_initialize();

#endif