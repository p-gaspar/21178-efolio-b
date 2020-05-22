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
    wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
           " O plano não foi inicializado.\n"
           "      Para manipular retângulos, terá de ser inicializado "
           "primeiro\n");

    exit(0);
}

/** 
 * Verifica se o retângulo recebido intercepta a coordenada x,y recebida.
 * Apenas é considerado intercessão se o ponto estiver dentro do retângulo,
 * se o ponto estiver na borda de um retângulo, não é considerado, pois podemos
 * ter retângulos adjacentes.
 */
static int __point_in_use(Rectangle *rect, int x, int y) {
    int ix, iy;

    for (ix = rect->x + 1; ix < rect->x + rect->width - 1; ix++)
    {
        if (ix == x) {
            for (iy = rect->y + 1; iy < rect->y + rect->height - 1; iy++) {
                if (iy == y) {
                    return 1;
                }
            }
        }
    }

    printf("Gravity/Point in use: Rectangle %d;%d;%d;%d does not use the point (%d, %d).\n", rect->x, rect->y, rect->width, rect->height, x, y);
    
    return 0;
}

/** Verifica se um ponto x,y corresponde a um dos vértices de um retângulo */
static int __is_corner_point(
    int x, int y, int r_x, int r_y, int r_width, int r_height) 
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

static void __add_point(
    int x, int y, int r_x, int r_y, int r_width, int r_height, int r_index) 
{
    if (__is_corner_point(x, y, r_x, r_y, r_width, r_height))
    {
        /* Vértices do retângulo */
        canvas->points[x][y] = CANVAS_RECTANGLE_CORNER_CHAR;
    } else if (x == r_x || x == r_x + r_width - 1) {
        /* Arestas verticais do retângulo */
        if (canvas->points[x][y] != CANVAS_RECTANGLE_CORNER_CHAR) {
            canvas->points[x][y] = CANVAS_RECTANGLE_COLUMN_CHAR;
        }
    } else if (y == r_y || y == r_y + r_height - 1) {
        /* Arestas horizontais do retângulo */
        if (canvas->points[x][y] != CANVAS_RECTANGLE_CORNER_CHAR) {
            canvas->points[x][y] = CANVAS_RECTANGLE_ROW_CHAR;
        }
    } else {
        /* Espaço interior do retângulo. Se já estiver um carácter
            * neste espaço, é lançado um erro pois significa que
            * este espaço já está ocupado por outro retângulo */

        if (canvas->points[x][y] == (char)0) {
            canvas->points[x][y] = CANVAS_RECTANGLE_INNER_CHAR;
        } else {
            wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
                    " Ocorreu um erro ao introduzir um "
                    "retângulo no plano:\n"
                    "      O %dº retângulo sobrepõe espaço "
                    "já utilizado por outro(s) retângulo(s).\n", 
                r_index + 1);
            exit(0);
        }
    }
}

int __compare_rectangles(const void *elem1, const void *elem2) {
    Rectangle rect1 = *((Rectangle *)elem1);
    Rectangle rect2 = *((Rectangle *)elem1);

    if (rect1.y + rect1.height - 1 > rect2.y + rect2.height - 1) {
        return 1;
    }

    if (rect1.y + rect1.height - 1 < rect2.y + rect2.height - 1) {
        return -1;
    }

    return 0;
}

/**
 * Aplica a gravidade a um vetor de retângulos com base nas definições do 
 * plano atual. Os retângulos deverão ser ordenados, desde o retângulo mais
 * a baixo para o retângulo mais a cima.
 * @param rectangles Vetor de retângulos a alterar
 */
void __apply_gravity(Vector *rectangles) {
    /* Indica se ocorreu alguma alteração nas posições dos retângulos na
     * iteração atual. Caso não ocorram alterações numa iteração, signfica que 
     * os retângulos já estão todos nos sitios corretos.
     */
    int changes;
    int i;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    printf("Gravity: Canvas settings => width: %d; height: %d\n", canvas->width, canvas->height);

    do {
        changes = 0;

        for (i = 0; i < rectangles->count; i++) {
            Rectangle *rect = (Rectangle *)(rectangles->items[i]);
            
            int safe_to_move = 1;
            int target_x;
            int target_y = rect->y + rect->height;

            printf("Gravity: Verifying rectangle %d;%d;%d;%d.\n", rect->x, rect->y, rect->width, rect->height);

            if (rect->y + rect->height - 1 == canvas->height - 1) {
                /* Se o fundo do retângulo já estiver na base, não precisa
                 * de ser mexido */
                printf("Gravity: Rectangle %d;%d;%d;%d is already at the bottom, skipping.\n", rect->x, rect->y, rect->width, rect->height);
                continue;
            }

            printf("Gravity: Rectangle %d;%d;%d;%d is not at the bottom, verifying if space below is available.\n", rect->x, rect->y, rect->width, rect->height);

            for (target_x = rect->x; target_x < rect->x + rect->width; target_x++)
            {
                int k;
                printf("Gravity: Rectangle %d;%d;%d;%d. Verifying if point (%d,%d) is free.\n", rect->x, rect->y, rect->width, rect->height, target_x, target_y);
                for (k = 0; k < rectangles->count; k++)
                {
                    Rectangle *rect2 = (Rectangle *)(rectangles->items[k]);
                    int point_in_use;
                    if (k == i) { 
                        continue;
                    }

                    printf("Gravity: Verifying if point (%d,%d) is in use by rectangle %d;%d;%d;%d.\n", target_x, target_y, rect2->x, rect2->y, rect2->width, rect2->height);
                    point_in_use = __point_in_use(
                        rect2, 
                        target_x,
                        target_y);

                    if (point_in_use) {
                        safe_to_move = 0;
                    } else {
                        safe_to_move = 1;
                    }

                    if (!safe_to_move) {
                        printf("Gravity: Rectangle %d;%d;%d;%d cannot move lower because the point (%d,%d) is already in use.\n", rect->x, rect->y, rect->width, rect->height, target_x, target_y);
                        break;
                    }
                }

                if (!safe_to_move) {
                    break;
                }
            }
            
            if (safe_to_move) {
                printf("Gravity: Space below rectangle %d;%d;%d;%d is available. New coordinates: %d;%d;%d;%d.\n", rect->x, rect->y, rect->width, rect->height, rect->x, rect->y + 1, rect->width, rect->height);
                rect->y++;
                changes = 1;
            }
        }
    } while (changes);
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

    __apply_gravity(rectangles);

    for (i = 0; i < rectangles->count; i++) {
        Rectangle *rect = (Rectangle *)(rectangles->items[i]);

        printf("Adding rectangle %d;%d;%d;%d to canvas.\n",
            rect->x, rect->y, rect->width, rect->height);

        for (x = rect->x; x < rect->x + rect->width; x++) {
            for (y = rect->y; y < rect->y + rect->height; y++) {
                /* Verifica se o retângulo está dentro dos limites do plano */
                if (x == 0 
                    || x == canvas->width 
                    || y == 0 
                    || y == canvas->height) {
                    wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
                        " Ocorreu um erro ao introduzir um "
                        "retângulo no plano:\n"
                        "      O %dº retângulo ocupa espaço fora "
                        "dos limites do plano.\n",

                        i + 1);

                    exit(0);
                }

                __add_point(
                    x, y, rect->x, rect->y, rect->width, rect->height, i);
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
void canvas_normalize_coordinates(Rectangle *rectangle) {
    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    /* 
     * Neste programa, e em aplicações de consola, os caracteres são imprimidos
     * de baixo para cima, e da esquerda para a direita. Portanto, é mais fácil
     * e mais intuitivo considerar que o ponto 0,0 é o canto superior esquerdo,
     * em vez do canto inferior esquerdo. Para calcular a real posição de y, 
     * basta subtrair à altura do plano a posição y do retângulo e também a sua
     * altura. A coordenada x mantém-se inalterada.
     */
    rectangle->y = canvas->height - rectangle->y - rectangle->height + 1;
}

Vector *canvas_sort_rectangles(Vector *rectangles) {
    /*qsort(
        *(rectangles->items),
        rectangles->count,
        sizeof(Rectangle *),
        __compare_rectangles);*/

    return rectangles;
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