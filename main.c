/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (main.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ui/ui.h"
#include "_shared/vector.h"
#include "canvas/canvas.h"
#include "canvas/structs.h"
#include "file-manager/file-manager.h"

int main(void) {
    char *filename;
    Vector *v_rectangles;

    setlocale(LC_ALL, "");

    ui_initialize();
    canvas_initialize();

    v_rectangles = parse_file((filename = ui_request_filename()));

    ui_request_canvas_option(v_rectangles);

    /* ***************************** */

    canvas_destroy();
    free(filename);
    free(v_rectangles);

    return 1;
}