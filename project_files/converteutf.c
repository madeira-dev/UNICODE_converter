/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WA */
/* Juliana Pinheiro dos Santos 2110516 3WA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    char test;

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    fread(&test, sizeof(char), 1, arquivo_entrada);

    printf("%b\n", test);

    return 0;
}
// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
// }
