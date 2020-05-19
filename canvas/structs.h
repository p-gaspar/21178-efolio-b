/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (structs.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __CANVAS_STRUCTS_H   /* Include guard */
#define __CANVAS_STRUCTS_H

typedef struct Canvas {
    int width;

    int height;

    char **points;
} Canvas;

typedef struct Rectangle {
    /** Coordenada X do topo esquerdo do retângulo */
    int x;

    /** Coordenada Y do topo esquerdo do retângulo */
    int y;

    /** Comprimento, em unidades, do retângulo */
    int width;

    /** Altura, em unidades, do retângulo */
    int height;
} Rectangle;

#endif