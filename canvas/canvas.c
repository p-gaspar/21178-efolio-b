/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (canvas.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "canvas.h"
#include "structs.h"
#include "../_shared/helpers.h"
#include "../_shared/vector.h"

/** Plano atual */
static Canvas *canvas;

/** 
 * Indica se o canvas já foi inicializado.
 * O canvas só poderá ser utilizado se tiver inicializado 
 */
int canvas_initialized = 0;

/**
 * Lança um erro que o canvas não foi inicializado e termina a execução
 * do programa.
 */
static void __throw_uninitialized_error()
{
    printf("ERRO: O plano não foi inicializado.\n"
           "      Para manipular retângulos, terá de ser inicializado "
           "primeiro\n");

    exit(0);
}

/** Verifica se um ponto x,y corresponde a um dos vértices de um retângulo */
static int __is_corner_point(
    int x, 
    int y, 
    int r_x, 
    int r_y, 
    int r_width, 
    int r_height) 
{
    if ((x == r_x && y == r_y)
        || (x == r_x && y == r_y + r_height - 1)
        || (x == r_x + r_width - 1 && y == r_y)
        || (x == r_x + r_width - 1 && y == r_y + r_height - 1))
    {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Inicializa o canvas com valores por defeito
 */
void canvas_initialize()
{
    int i;

    canvas = malloc_wrapper(sizeof(Canvas));

    canvas->width = CANVAS_DEFAULT_WIDTH;
    canvas->height = CANVAS_DEFAULT_HEIGHT;

    /* 
     * É iniciado o array dinâmico de duas dimensões. Basicamente,
     * é alocado espaço em memória para cada um dos caracteres do nosso plano,
     * que irá conter até (width * height) caracteres.
     */
    canvas->points = (char **)malloc_wrapper(sizeof(char *) * canvas->width);
    for (i = 0; i < canvas->width; i++) {
        canvas->points[i]
            = (char *)malloc_wrapper(sizeof(char) * canvas->height);
    }

    canvas_initialized = 1;
}

/** 
 * Insere um vetor de retângulos no plano 
 */
void canvas_insert(Vector *rectangles) {
    int i, x, y;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    for (i = 0; i < rectangles->count; i++) {
        Rectangle *rect = (Rectangle *)(rectangles->items[i]);

        printf("Adding rectangle %d;%d;%d;%d to canvas.\n",
            rect->x, rect->y, rect->width, rect->height);

        for (x = rect->x; x < rect->x + rect->width; x++) {
            for (y = rect->y; y < rect->y + rect->height; y++) {
                if (__is_corner_point(
                    x, y, rect->x, rect->y, rect->width, rect->height))
                {
                    /* Vértices do retângulo */
                    canvas->points[x][y] = CANVAS_RECTANGLE_CORNER_CHAR;
                } else if (x == rect->x || x == rect->x + rect->width - 1) {
                    /* Arestas verticais do retângulo */
                    if (canvas->points[x][y] != CANVAS_RECTANGLE_CORNER_CHAR) {
                        canvas->points[x][y] = CANVAS_RECTANGLE_COLUMN_CHAR;
                    }
                } else if (y == rect->y || y == rect->y + rect->height - 1) {
                    /* Arestas horizontais do retângulo */
                    if (canvas->points[x][y] != CANVAS_RECTANGLE_CORNER_CHAR) {
                        canvas->points[x][y] = CANVAS_RECTANGLE_ROW_CHAR;
                    }
                } else {
                    /* Espaço interior do retângulo. Se já estiver um carácter
                     * neste espaço, é lançado um erro pois iriam colidir */

                    if (canvas->points[x][y] == (char)0) {
                        canvas->points[x][y] = CANVAS_RECTANGLE_INNER_CHAR;
                    } else {
                        printf("ERRO: Ocorreu um erro ao introduzir um "
                               "retângulo no plano:\n"
                               "      O retângulo com as dimensões %d,%d,%d,%d"
                               " sobrepõe espaço já utilizado por outro(s)"
                               " retângulos.\n",
                            rect->x, rect->y, rect->width, rect->height);
                        exit(0);
                    }
                }
            }
        }
    }
}

void canvas_draw() {
    int x, y;

    printf("\n");

    for (y = 0; y <= canvas->height; y++) {
        for (x = 0; x <= canvas->width; x++) {
            if ((x == 0 || x == canvas->width) 
                && (y == 0 || y == canvas->height))
            {
                /* Cantos do plano */

                if (x == 0) { /* DEBUGGING */
                    wprintf(L"%3d ", y);
                }

                wprintf(L"%c", CANVAS_BORDER_CORNER_CHAR);
            } else if (x == 0 || x == canvas->width) {
                /* Bordas horizontais do plano */

                if (x == 0) { /* DEBUGGING */
                    wprintf(L"%3d ", y);
                }

                wprintf(L"%c", CANVAS_BORDER_ROW_CHAR);
            } else if (y == 0 || y == canvas->height) {
                /* Bordas verticais do plano */

                wprintf(L"%c", CANVAS_BORDER_COLUMN_CHAR);
            } else if (canvas->points[x][y] == (char)0) {
                /* Espaço vazio do plano */

                wprintf(L"%c", CANVAS_WHITESPACE);
            } else {
                /* Espaço ocupado do plano */
                
                wprintf(L"%c", canvas->points[x][y]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/** 
 * Converte as coordenadas de um retângulo em que o ponto 0,0 do plano é no
 * canto inferior esquerdo e o ponto 0,0 do retângulo é no vértice inferior
 * esquerdo, para as coordenadas em que o ponto 0,0 do plano é no canto
 * superior esquerdo, e o ponto 0,0 do retângulo é no vértice superior esquerdo
 */
Rectangle canvas_normalize_coordinates(Rectangle rectangle) {
    /* 
     * Neste programa, e em aplicações de consola, os caracteres são imprimidos
     * de baixo para cima, e da esquerda para a direita. Portanto, é mais fácil
     * e mais intuitivo considerar que o ponto 0,0 é o canto superior esquerdo,
     * em vez do canto inferior esquerdo. Para calcular a real posição de y, 
     * basta subtrair à altura do plano a posição y do retângulo e também a sua
     * altura. A coordenada x mantém-se inalterada.
     */
    rectangle.y = canvas->height - rectangle.y - rectangle.height;
    
    return rectangle;
}

/** 
 * Executa a limpeza das variáveis alocadas em memória do canvas 
 */
void canvas_destroy()
{
    int i;

    /* 
     * Primeiro limpa-se os espaços alocados à segunda dimensão dos items do
     * plano, depois à primeira, e finalmente ao próprio plano. Assim 
     * garantimos que toda a memória alocada é libertada
     */
    for (i = 0; i < canvas->width; i++) free(canvas->points[i]);
    free(canvas->points);
    free(canvas);

    canvas_initialized = 0;
}