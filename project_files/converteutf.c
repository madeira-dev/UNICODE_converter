/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WA */
/* Juliana Pinheiro dos Santos 2110??? 3WA */

#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    // FILE *entry_file;
    unsigned int buffer[10];

    arquivo_entrada = fopen("utf8_testFile", "rb");
    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro para abrir arquivo para leitura\n");
        return -1;
    }

    fread(buffer, sizeof(unsigned int), 1, arquivo_entrada);

    // printf("%02x", buffer[0]);

    for (int i = 0; i < 2; i++)
    {
        printf("%02x ", buffer[i]);
    }

    puts("");

    return 0;
}
// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
// }

/* qual a diferenca entre esse arquivo e o conv_utf.c??? */
