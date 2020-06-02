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

/* ************************************************************************  */
/* Métodos privados */

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
 * Aloca espaço necessário para o plano ter (largura*altura) pontos.
 * @param width Largura do plano (x)
 * @param height Altura do plano (y)
 */
static void __canvas_alloc(int width, int height) {
    int i;

    canvas = malloc_wrapper(sizeof(Canvas));

    canvas->width = width;
    canvas->height = height;

    /* 
     * É iniciado o array dinâmico de duas dimensões. Basicamente,
     * é alocado espaço em memória para cada um dos caracteres do nosso plano,
     * que irá conter até (width * height) caracteres.
     */
    canvas->points = (char **)malloc_wrapper(sizeof(char *) * canvas->width);
    for (i = 0; i < canvas->width; i++) {
        /* Aqui é utilizado calloc porque é de suprema importância que os
         * valores sejam inicializados a 0 (coisa que o malloc não faz).
         * O programa sabe que um espaço está preenchido se o valor do ponteiro
         * for vazio. No entanto, se for alocado espaço, libertado, e alocado
         * de novo, o ponteiro pode ficar com valores de lixo. 
         * Ao fazer calloc isto não acontece, pois é sempre inicializado a 0. */
        canvas->points[i]
            = (char *)calloc_wrapper(canvas->height, sizeof(char));
    }

}

/**
 * Liberta o espaço ocupado pelo plano e pelos seus pontos
 */
static void __canvas_dealloc() {
    int i;

    /* 
     * Primeiro limpa-se os espaços alocados à segunda dimensão dos items do
     * plano, depois à primeira, e finalmente ao próprio plano. Assim 
     * garantimos que toda a memória alocada é libertada
     */
    for (i = 0; i < canvas->width; i++) free(canvas->points[i]);
    free(canvas->points);
    free(canvas);
}

/** 
 * Altera as dimensões do plano.
 * AVISO: Ao utilizar este método, todos os caracteres já presentes no plano
 *        serão perdidos.
 * @param width Nova largura do plano (x)
 * @param height Nova altura do plano (y)
 */
static void __canvas_resize(int width, int height) {
    if (!canvas_initialized) {
        __throw_uninitialized_error();
    }

    __canvas_dealloc();
    __canvas_alloc(width, height);
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

    return 0;
}

/** 
 * Verifica se um ponto x,y corresponde a um dos vértices de um retângulo
 * @param x Coordenada x do ponto a verificar
 * @param y Coordenada y do ponto a verificar
 * @param rectangle Retângulo a verificar
 * */
static int __is_corner_point(int x, int y, Rectangle *rectangle) 
{
    if ((x == rectangle->x && y == rectangle->y)
        || (x == rectangle->x && y == rectangle->y + rectangle->height - 1)
        || (x == rectangle->x + rectangle->width - 1 && y == rectangle->y)
        || (x == rectangle->x + rectangle->width - 1 
            && y == rectangle->y + rectangle->height - 1))
    {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Adiciona ao plano um carácter no ponto x,y com base no retângulo recebido
 * @param x Coordenada x do ponto/carácter a adicionar
 * @param y Coordenada x do ponto/carácter a adicionar
 * @param rectangle Retângulo a verificar
 * @param rect_index Índice atual do retângulo (para mostrar mensagem de erro,
 *                   caso necessário)
 */
static void __add_point(int x, int y, Rectangle *rectangle, int rect_index) 
{
    if (__is_corner_point(x, y, rectangle))
    {
        /* Vértices do retângulo */
        canvas->points[x][y] = CANVAS_RECTANGLE_CORNER_CHAR;
    } else if (x == rectangle->x || x == rectangle->x + rectangle->width - 1) {
        /* Arestas verticais do retângulo */
        if (canvas->points[x][y] != CANVAS_RECTANGLE_CORNER_CHAR) {
            canvas->points[x][y] = CANVAS_RECTANGLE_COLUMN_CHAR;
        }
    } else if (y == rectangle->y || y == rectangle->y + rectangle->height - 1){
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
                rect_index + 1);
            exit(0);
        }
    }
}

/* ************************************************************************  */
/* Métodos públicos */

/**
 * Inicializa o canvas com valores por defeito
 */
void canvas_initialize() {
    if (canvas_initialized) {
        wprintf(ANSI_COLOR_RED L"ERRO:" ANSI_COLOR_RESET
           " O plano já foi inicializado.\n"
           "      Não é permitido voltar a inicializar o plano.\n");
        
        exit(0);
    }


    __canvas_alloc(CANVAS_DEFAULT_WIDTH, CANVAS_DEFAULT_HEIGHT);

    canvas_initialized = 1;
}

/**
 * Aplica a gravidade a um vetor de retângulos com base nas definições do 
 * plano atual. Os retângulos deverão ser ordenados, desde o retângulo mais
 * a baixo para o retângulo mais a cima.
 * @param rectangles Vetor de retângulos a alterar
 */
void canvas_apply_gravity(Vector *rectangles) {
    /* Indica se ocorreu alguma alteração nas posições dos retângulos na
     * iteração atual. Caso não ocorram alterações numa iteração, signfica que 
     * os retângulos já estão todos nos sitios corretos.
     */
    int changes;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    do {
        int i;

        /** Indica se ocorreu alguma alteração nas posições dos retângulos
         * nesta iteração */
        changes = 0;

        for (i = 0; i < rectangles->count; i++) {
            Rectangle *rect = (Rectangle *)(rectangles->items[i]);
            
            int safe_to_move = 1;
            int target_x;
            int target_y = rect->y + rect->height;

            if (rect->y + rect->height - 1 == canvas->height - 1) {
                /* Se o fundo do retângulo já estiver na base, não precisa
                 * de ser mexido */
                continue;
            }

            for (target_x = rect->x; target_x < rect->x + rect->width; target_x++)
            {
                int k;
                for (k = 0; k < rectangles->count; k++)
                {
                    Rectangle *rect2 = (Rectangle *)(rectangles->items[k]);
                    if (k == i) {
                        /* Se o retângulo que estamos a ver se colide com o
                         * ponto que pretendemos é igual ao retângulo que
                         * estamos a querer movimentar, passa à frente. */
                        continue;
                    }

                    safe_to_move = !__point_in_use(rect2, target_x,target_y);

                    if (!safe_to_move) {
                        break;
                    }
                }

                if (!safe_to_move) {
                    break;
                }
            }
            
            if (safe_to_move) {
                rect->y++;
                changes = 1;
            }
        }
    } while (changes);
}

/**
 * Roda o plano 90 graus no sentido dos ponteiros do relógio, e roda também
 * os retângulos recebidos.
 * @param rectangles Retângulos a rodar 90 graus
 */
void canvas_rotate_90deg(Vector *rectangles) {
    int i;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    for (i = 0; i < rectangles->count; i++)
    {
        Rectangle *rect = (Rectangle *)(rectangles->items[i]);

        int x = rect->x;
        int width = rect->width;

        /* O novo ponto x vai ser o canto inferior esquerdo do retângulo */
        rect->x = canvas->height - rect->y - rect->height + 1;
        rect->y = x;

        rect->width = rect->height;
        rect->height = width;
    }

    __canvas_resize(canvas->height, canvas->width);
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

                __add_point(x, y, rect, i);
            }
        }
    }
}

/**
 * Limpa os valores dos pontos já guardados no plano.
 */
void canvas_clear() {
    int i;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    for (i = 0; i < canvas->width; i++) {
        free(canvas->points[i]);
        canvas->points[i]
            = (char *)calloc_wrapper(canvas->height, sizeof(char));
    }
}

/**
 * Desenha na consola os valores guardados no plano.
 */
void canvas_draw() {
    int x, y;

    if (!canvas_initialized)
    {
        __throw_uninitialized_error();
    }

    printf("\n");

    for (y = 0; y <= canvas->height; y++) {
        for (x = 0; x <= canvas->width; x++) {
            if ((x == 0 || x == canvas->width) 
                && (y == 0 || y == canvas->height))
            {
                /* Cantos do plano */

                if (x == 0) { /* DEBUGGING */
                    wprintf(ANSI_COLOR_CYAN L"%3d " ANSI_COLOR_RESET, y);
                }

                wprintf(ANSI_COLOR_GREEN L"%c" ANSI_COLOR_RESET, CANVAS_BORDER_CORNER_CHAR);
            } else if (x == 0 || x == canvas->width) {
                /* Bordas horizontais do plano */

                if (x == 0) { /* DEBUGGING */
                    wprintf(ANSI_COLOR_CYAN L"%3d " ANSI_COLOR_RESET, y);
                }

                wprintf(ANSI_COLOR_GREEN L"%c" ANSI_COLOR_RESET, CANVAS_BORDER_ROW_CHAR);
            } else if (y == 0 || y == canvas->height) {
                /* Bordas verticais do plano */

                wprintf(ANSI_COLOR_GREEN L"%c" ANSI_COLOR_RESET, CANVAS_BORDER_COLUMN_CHAR);
            } else if (canvas->points[x][y] == (char)0) {
                /* Espaço vazio do plano */

                wprintf(ANSI_COLOR_MAGENTA L"%c" ANSI_COLOR_RESET, CANVAS_WHITESPACE);
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

/** 
 * Executa a limpeza das variáveis alocadas em memória do canvas 
 */
void canvas_destroy()
{
    __canvas_dealloc();
    canvas_initialized = 0;
}