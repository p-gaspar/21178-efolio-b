/*
** UC: 21178 - Laboratório de Programação
** e-fólio B 2019-20 (helpers.c)
**
** Aluno: 1902551 - Pedro Gaspar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/**
 * Verifica se um ficheiro existe ao tentar abri-lo.
 * Se o ponteiro para o ficheiro não for null, sabemos que o ficheiro foi
 * aberto com sucesso.
 */
int file_exists(char filename[]) {
    FILE *file;

    if ((file = fopen(filename, "r")) != NULL) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}

/**
 * Método que implementa "graceful degradation"
 * ao utilizar a função fopen. Se ocorrer um erro ao
 * abrir o ficheiro, mostra uma mensagem de erro no ecrã
 * e aborta a execução do programa.
 */
FILE *fopen_wrapper(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);

    if (file == NULL) 
    { 
        printf("ERRO: Não foi possível abrir o ficheiro %s.\n"
               "      A execução do programa terminou.\n", filename); 
        exit(0);
    } 

    return file;
}

/**
 * Adquire um campo de uma linha do ficheiro "CSV" (neste caso semi colon).
 * Os campos têm de estar separados por um ponto e vírgula (;).
 * Os campos são 1-index (ou one-based), ou seja, o primeiro campo
 * tem o index 1
 */
char* get_csv_field(char* line, int index) {
    char* token;
    for (token = strtok(line, ";");
        token && *token; 
        token = strtok(NULL, ";\n"))
    {
        if (!--index) {
            return token;
        }
    }
    return NULL;
}

/**
 * Este wrapper para a função fgets é utilizada
 * porque, ao contrário do gets (o qual a sua utilização
 * não é recomendada), o fgets inclui uma newline no final.
 * este método serve para retirar a newline do final da string.
 */
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp) {
    if (fgets(buffer, buflen, fp) != 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        return buffer;
    };

    return 0;
}