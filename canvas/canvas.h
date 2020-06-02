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

#define CANVAS_DEFAULT_WIDTH 81
#define CANVAS_DEFAULT_HEIGHT 26    

/** Carácter a utilizar em espaços não preenchidos por retângulos */
#define CANVAS_WHITESPACE ' '

/** 
 * Carácter a utilizar nas arestas das bordas do plano:
 * (0, 0); (0, HEIGHT); (WIDTH, 0); (WIDTH; HEIGHT)
 */ 
#define CANVAS_BORDER_CORNER_CHAR '0'

/** Carácter a utilizar nas linhas (x=0 ou x=width) das bordas do plano */
#define CANVAS_BORDER_ROW_CHAR  'Y'

/** Carácter a utilizar nas colunas (y=0 ou y=height) das bordas do plano */
#define CANVAS_BORDER_COLUMN_CHAR  'X'

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
 * Aplica a gravidade a um vetor de retângulos com base nas definições do 
 * plano atual. Os retângulos deverão ser ordenados, desde o retângulo mais
 * a baixo para o retângulo mais a cima.
 * @param rectangles Vetor de retângulos a alterar
 */
void canvas_apply_gravity(Vector *rectangles);

/**
 * Roda o plano 90 graus no sentido dos ponteiros do relógio, e roda também
 * os retângulos recebidos.
 * @param rectangles Retângulos a rodar 90 graus
 */
void canvas_rotate_90deg(Vector *rectangles);

/** 
 * Insere um vetor de retângulos no plano 
 */
void canvas_insert(Vector *rectangles);

/**
 * Limpa os valores dos pontos já guardados no plano.
 */
void canvas_clear();

/**
 * Desenha na consola os valores guardados no plano.
 */
void canvas_draw();

/**
 * Altera a coordenada y do retângulo tal que os pontos 0,0 do plano e do
 * retângulo sejam o canto superior esquerdo, ao invés de serem o canto
 * inferior esquerdo.
 */ 
void canvas_normalize_coordinates(Rectangle *rectangle);

/** 
 * Executa a limpeza das variáveis alocadas em memória do canvas 
 */
void canvas_destroy();

#endif