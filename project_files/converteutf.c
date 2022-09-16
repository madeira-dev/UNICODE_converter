/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WB */
/* Juliana Pinheiro dos Santos 2110516 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

/* ok na vdd a leitura do utf8 ta errada, foi testada apenas a leitura de um arquivo com só um caracter.
nesse caso a leitura funciona, para ler com mais de um caracter precisa considerar que o divisor entre
todos eles é um espaço em branco ' '. imagino que basta ler o caracter e testar se é um espaço em hex
é 20 e em binário é 0010 0000, se for um espaço pula ele de algum jeito e lê o próximo caracter */

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char first_byte;
    unsigned char final_value;
    int n_bytes = 0;

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    /* lendo o primeiro byte do arquivo para saber quantos bytes o caracter ocupa */
    fread(&first_byte, sizeof(unsigned char), 1, arquivo_entrada);
    final_value = first_byte;

    /* verificando se o caracter é um espaço para pular para o próximo */
    if (first_byte == 0x20)
    {
        unsigned char jmp_space;
        fread(&jmp_space, sizeof(unsigned char), 1, arquivo_entrada);
        final_value = jmp_space;
    }

    /* loop para descobrir quantos bits 1 no início o primeiro byte apresenta */
    while ((final_value & 0b10000000) != 0)
    {
        final_value = final_value << 1;
        n_bytes++;
    }

    if (n_bytes == 0)
        printf("tmp first_byte n_bytes=0\n");

    else if (n_bytes == 2)
        printf("tmp first_byte n_bytes=2\n");

    else if (n_bytes == 3)
    {
        unsigned char byte1, byte2, byte3;

        /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
        byte1 = final_value & 0b00011111;

        fread(&byte2, sizeof(char), 1, arquivo_entrada);
        fread(&byte3, sizeof(char), 1, arquivo_entrada);

        byte2 = byte2 & 0b00111111; /* & operation para remover bytes de continuacao */
        byte3 = byte3 & 0b00111111; /* & operation para remover bytes de continuacao */
    }

    else if (n_bytes == 4)
    {
        // unsigned char byte1, byte2, byte3, byte4;
        printf("tmp first_byte n_bytes=4\n");
    }

    return 0;
}

// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
//     unsigned int utf32_BOM;
//     unsigned int utf32_conteudo;

//     if (!arquivo_entrada)
//     {
//         fprintf(stderr, "erro ao abrir arquivo para leitura\n");
//         return -1;
//     }

//     fread(&utf32_BOM, sizeof(int), 1, arquivo_entrada);      /* lendo BOM do arquivo */
//     fread(&utf32_conteudo, sizeof(int), 1, arquivo_entrada); /* lendo valores do arquivo */

//     printf("utf32_BOM: %x\n", utf32_BOM);
//     printf("utf32_conteudo: %x\n", utf32_conteudo);

//     if (utf32_BOM == 0xFEFF) /* verificando se BOM é little endian */
//     {

//         fwrite(&utf32_conteudo, sizeof(unsigned int), 1, arquivo_saida);
//         printf("little endian\n");
//     }

//     else if (0x0000FEFF) /* verificando se BOM é big endian */
//     {
//         unsigned char byte_final, byte_inicial;

//         byte_final = utf32_conteudo & 0b0000000011111111;
//         byte_inicial = utf32_conteudo & 0b1111111100000000;
//         printf("byte_final: %x\n", byte_final);
//         printf("byte_inicial: %x\n", byte_inicial);

//         fwrite(&byte_inicial, sizeof(unsigned char), 1, arquivo_saida);
//         fwrite(&byte_final, sizeof(unsigned char), 1, arquivo_saida);

//         printf("big endian");
//     }

//     else /* caso de BOM inválido */
//     {
//         fprintf(stderr, "BOM invalido");
//         return -1;
//     }

//     return 0;
// }
