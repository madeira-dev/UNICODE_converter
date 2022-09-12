/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WA */
/* Juliana Pinheiro dos Santos 2110??? 3WA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// ler o arquivo identificando o numero de bytes que o simbolo ocupa lendo o primeiro byte dele
// uma vez identificado, fazer switch(?) pra declarar variavel com o tamanho de bytes correspondente

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    char test;
    int bin_res;
    char result;
    int bom_num;

    arquivo_entrada = fopen("utf8_testFile", "rb");
    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    fread(&bom_num, sizeof(int), 1, arquivo_entrada);

    // printf("%b\n", test); // por que o resultado dele ta dando 1000011????????????????? ta lendo como byte de continuacao??????
    // printf("%b\n", 0b11110);

    // result = test & 0b11110;
    // printf("%b\n", result);

    printf("%b\n", bom_num);

    // switch (result)
    // {
    // case 0b0:
    //     printf("case 0\n");
    //     break;

    // case 0b10:
    //     printf("case 10\n"); // byte de continuação
    //     break;

    // case 0b110:
    //     printf("case 110\n");
    //     break;

    // case 0b1110:
    //     printf("case 1110\n");
    //     break;

    // case 0b11110:
    //     printf("case 11110\n");
    //     break;
    // }

    return 0;
}
// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
// }

/* qual a diferenca entre esse arquivo e o conv_utf.c??? */
/* se eu modificar o arquivo acaba a codificação???????? */