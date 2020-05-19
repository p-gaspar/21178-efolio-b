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
    int i;
    char *filename;
    Vector *v_rectangles;

    setlocale(LC_ALL, "");

    ui_initialize();
    canvas_initialize();

    v_rectangles = parse_file((filename = ui_request_filename()));

    printf("rectangles count: %d\n", v_rectangles->count);

    for (i = 0; i < v_rectangles->count; i++)
    {
        printf("x: %d, y: %d, w: %d, h: %d\n",
            ((Rectangle *)(v_rectangles->items[i]))->x,
            ((Rectangle *)(v_rectangles->items[i]))->y,
            ((Rectangle *)(v_rectangles->items[i]))->width,
            ((Rectangle *)(v_rectangles->items[i]))->height
        );
    }

    canvas_insert(v_rectangles);
    canvas_draw();

    /* ***************************** */

    free(filename);

    return 1;
}