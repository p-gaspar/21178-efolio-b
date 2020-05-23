/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (ui.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __UI_H   /* Include guard */
#define __UI_H

#include "../_shared/vector.h"

char *ui_request_filename();

void ui_handle_canvas(Vector *rectangles);

void ui_initialize();

#endif