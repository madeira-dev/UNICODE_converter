/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WB */
/* Juliana Pinheiro dos Santos 2110516 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char test;
    unsigned char tmp_test;
    int n_bytes = 0;

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    fread(&test, sizeof(char), 1, arquivo_entrada);
    /* lendo o primeiro byte do arquivo para saber quantos bytes o caracter ocupa */
    tmp_test = test; // salvando o valor deste primeiro byte para usá-lo depois de fazer bit shift

    while ((test & 0b10000000) != 0) /* loop para descobrir quantos bits 1 no início o primeiro byte apresenta */
    {
        test = test << 1;
        n_bytes++;
    }

    if (n_bytes == 0)
        printf("tmp test n_bytes=0\n");

    else if (n_bytes == 2)
        printf("tmp test n_bytes=2\n");

    else if (n_bytes == 3)
    {
        unsigned char byte1, byte2, byte3;
        unsigned char concat_result;
        byte1 = tmp_test & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais
        representando o numero de bytes */
        unsigned char top;             /* variavel top feita pra testar se tem mais alguma coisa depois dos
        3 bytes e tem (??), porém depois desse top não tem mais nada */
        fread(&byte2, sizeof(char), 1, arquivo_entrada);
        fread(&byte3, sizeof(char), 1, arquivo_entrada);
        // fread(&top, sizeof(char), 1, arquivo_entrada);
        printf("byte2 in bin before & operation: %b\n", byte2);
        printf("byte3 in bin before & operation: %b\n\n", byte3);
        byte2 = byte2 & 0b00111111; // & operation para remover bytes de continuacao
        byte3 = byte3 & 0b00111111; // & operation para remover bytes de continuacao
        printf("test in bin: %b\n\n", tmp_test);
        printf("byte1 in bin: %b\n", byte1);
        printf("byte2 in bin: %b\n", byte2);
        printf("byte3 in bin: %b\n", byte3);
        printf("\n");
        // printf("top in bin: %b\n", top); /* aparentemente o top não é byte de continuação, já que quando representado
        // ele só tem 4 bits, ou seja, os 4 primeiros são zero, porém como esses bits não mudam a cada execução do código
        // eles não são lixo da memória. o que ele é??? algum padrão de fim de arquivo utf8?? */
        printf("\n");
        printf("byte1 in hex: %x\n", byte1);
        printf("byte2 in hex: %x\n", byte2);
        printf("byte3 in hex: %x\n", byte3);
        // printf("top in hex: %x\n\n", top);
        // concatenate byte1 byte2 and byte3
        concat_result = (byte1 << 12) | (byte2 << 6) | byte3;
        printf("concat result in hex: %b\n", concat_result);
        // 00100011
    }

    else if (n_bytes == 4)
    {
        unsigned char byte1, byte2, byte3, byte4;
        printf("tmp test n_bytes=4\n");
    }

    printf("n_bytes: %d\n", n_bytes);

    return 0;
}

// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
// }
