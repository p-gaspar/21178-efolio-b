/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (file-manager.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "../_shared/helpers.h"
#include "../_shared/vector.h"
#include "../canvas/canvas.h"
#include "../canvas/structs.h"

/**
 * Converte uma única linha de um ficheiro de entrada que obedeça ao formato
 * x;y;c;a para uma struct Rectangle
 */
static Rectangle *parse_rectangle_line(char line[]) {
    char *line_cpy = malloc_wrapper(strlen(line) + 1);

    Rectangle *rect = malloc(sizeof(Rectangle));

    strcpy(line_cpy, line);
    rect->x = string_to_int(get_csv_field(line_cpy, 1));

    strcpy(line_cpy, line);
    rect->y = string_to_int(get_csv_field(line_cpy, 2));

    strcpy(line_cpy, line);
    rect->width = string_to_int(get_csv_field(line_cpy, 3));

    strcpy(line_cpy, line);
    rect->height = string_to_int(get_csv_field(line_cpy, 4));

    free(line_cpy);

    return rect;
}

/** 
 * Lê o ficheiro recebido no input, e por cada linha,
 * preenche uma struct Rectangle. No fim é retornado um pointer para
 * o conjunto de retângulos que foram retirados do ficheiro
 */
Vector *parse_file(char input[]) {
    FILE *input_file = fopen_wrapper(input, "r");
    char *line = malloc(sizeof(char) * 21);

    VECTOR_INITIALIZE_PTR(v_rectangles);

    while (fgets_wrapper(line, 20, input_file)) {
        Rectangle *rectangle = parse_rectangle_line(line);
        canvas_normalize_coordinates(rectangle);
        
        VECTOR_PUSH_PTR(v_rectangles, rectangle);
    }

    free(line);

    return v_rectangles;
}
