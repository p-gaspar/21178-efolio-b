/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (ui.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "ui.h"
#include "../_shared/helpers.h"
#include "../_shared/vector.h"
#include "../file-manager/helpers.h"
#include "../canvas/canvas.h"

/* ************************************************************************  */
/* Métodos privados */

/** 
 * Pede ao utilizador a opção que pretende para manipular o plano, e
 * retorna-a. Se o utilizador enviar uma opção inválida, continua a pedir até
 * obter uma opção válida.
 */
static char __get_canvas_option() {
    char option = 0;

    wprintf(L"\nAção a executar:\n");
    wprintf(
        ANSI_COLOR_BLUE L"      (1)" ANSI_COLOR_RESET " Aplicar gravidade\n"
        ANSI_COLOR_BLUE L"      (2)" ANSI_COLOR_RESET " Rodar 90° "
        "(sentido dos ponteiros do relógio)\n\n"
        ANSI_COLOR_RED L"      (0)" ANSI_COLOR_RESET " Sair\n");

    while (option != '1' && option != '2' && option != '0') {
        if (option != 0) {
            wprintf(L"" ANSI_COLOR_RED 
                "        (!) Opção não reconhecida. "
                "Verifique a opção e volte a tentar."
                ANSI_COLOR_RESET);

        }

        wprintf(ANSI_COLOR_YELLOW L"\n      > " ANSI_COLOR_RESET);
        scanf(" %c", &option);
    }

    return option;
}

/** 
 * Limpa o ecrã da consola.
 * Nos sistemas *nix, utiliza o comando clear.
 * Em Windows, utiliza o comando cls.
 */
static void __clear_screen() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

/* ************************************************************************  */
/* Métodos públicos */

/**
 * Pede ao utilizador o nome do ficheiro a carregar.
 * Se o utilizador introduzir um caminho para um ficheiro que não existe,
 * continua a pedir até obter um caminho para um ficheiro válido e mostra uma
 * mensagem de erro adequada.
 */
char *ui_request_filename() {
    char input[255];
    char *return_val;
    int open_success = 0;

    wprintf(L"Introduza o caminho para o ficheiro de entrada:");

    do {
        wprintf(ANSI_COLOR_YELLOW L"\n      > " ANSI_COLOR_RESET);
        fgets_wrapper(input, 255, stdin);
        
        if (!(open_success = file_exists(input))) {
            wprintf(L"" ANSI_COLOR_RED 
                "        (!) Ocorreu um erro ao abrir o ficheiro. "
                "Verifique o caminho e volte a tentar."
                ANSI_COLOR_RESET);

            memset(input, 0, 255);
        } else {
            wprintf(L"" ANSI_COLOR_GREEN
                "        (!) Ficheiro encontrado. A carregar..."
                ANSI_COLOR_RESET);
        }
    } while (open_success == 0);

    printf("\n");

    return_val = (char *)malloc_wrapper(strlen(input) + 1);
    strcpy(return_val, input);

    return return_val;
}

/**
 * Pede ao utilizador que opção pretende escolher para manipular o plano.
 * Continua a pedir ao utilizador até que obtenha uma opção válida, ou até que
 * escolha a opção para sair.
 * @param rectangles Retângulos a manipular
 */
void ui_request_canvas_option(Vector *rectangles) {
    char option = 0;

    do {
        if (option != 0) {
            canvas_clear();

            switch (option)
            {
                /* Aplicar gravidade */
                case '1':
                    canvas_apply_gravity(rectangles);
                    break;
                /* Rodar 90 graus */
                case '2':
                    canvas_rotate_90deg(rectangles);
                    break;
            }
        }

        ui_initialize();
        canvas_insert(rectangles);
        canvas_draw();

        option = __get_canvas_option();
    } while (option != '0');
}

/** 
 * Limpa o ecrã e mostra a mensagem de título.
 */
void ui_initialize() {
    __clear_screen();
    wprintf(L"E-Fólio B: Mundo dos retângulos ## 1902551 - Pedro Gaspar\n\n");
}