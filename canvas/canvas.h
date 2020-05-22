/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (canvas.h)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#ifndef __CANVAS_H   /* Include guard */
#define __CANVAS_H

#include "structs.h"
#include "../_shared/vector.h"

#define CANVAS_DEFAULT_WIDTH 30
#define CANVAS_DEFAULT_HEIGHT 12    

/** Carácter a utilizar em espaços não preenchidos por retângulos */
#define CANVAS_WHITESPACE ' '

/** 
 * Carácter a utilizar nas arestas das bordas do plano:
 * (0, 0); (0, HEIGHT); (WIDTH, 0); (WIDTH; HEIGHT)
 */ 
#define CANVAS_BORDER_CORNER_CHAR '0'

/** Carácter a utilizar nas linhas (x=0 ou x=width) das bordas do plano */
#define CANVAS_BORDER_ROW_CHAR  'R'

/** Carácter a utilizar nas colunas (y=0 ou y=height) das bordas do plano */
#define CANVAS_BORDER_COLUMN_CHAR  'C'

/** Carácter a utilizar nas arestas dos retângulos */
#define CANVAS_RECTANGLE_CORNER_CHAR  '+'

/** Carácter a utilizar nas linhas horizontais dos retângulos */
#define CANVAS_RECTANGLE_ROW_CHAR  '-'

/** Carácter a utilizar nas linhas verticais dos retângulos */
#define CANVAS_RECTANGLE_COLUMN_CHAR  '|'

/* Carácter a utilizar no espaço interior dos retângulos */
#define CANVAS_RECTANGLE_INNER_CHAR ' '

/**
 * Inicializa o canvas com valores por defeito
 */
void canvas_initialize();

/** 
 * Insere um vetor de retângulos no plano 
 */
void canvas_insert(Vector *rectangles);

void canvas_draw();

/**
 * Altera a coordenada y do retângulo tal que os pontos 0,0 do plano e do
 * retângulo sejam o canto superior esquerdo, ao invés de serem o canto
 * inferior esquerdo.
 */ 
void canvas_normalize_coordinates(Rectangle *rectangle);

Vector *canvas_sort_rectangles(Vector *rectangles);

#endif