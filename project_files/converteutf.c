/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WB */
/* Juliana Pinheiro dos Santos 2110516 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char test;
    unsigned char tmp = 1;
    int n_bytes = 0;

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    fread(&test, sizeof(char), 1, arquivo_entrada);

    while ((test & 0b10000000) != 0)
    {
        test = test << 1;
        n_bytes++;
    }

    printf("%d\n", n_bytes);

    return 0;
}

// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
// }
