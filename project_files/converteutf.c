/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WB */
/* Juliana Pinheiro dos Santos 2110516 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converteutf.h"

int count_bits(unsigned char byte);

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char first_byte;
    unsigned char final_value;
    int n_bytes = 0;

    unsigned int BOM_to_write = 0x0000FEFF; /* BOM pra indiciar que o arquivo foi gravado em little endian */
    fwrite(&BOM_to_write, sizeof(unsigned int), 1, arquivo_saida);

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    while (!feof(arquivo_entrada)) /* ALTERAR CONDICAO DO WHILE. DESSE JEITO ELE LE O ÚLTIMO BYTE DUAS VEZES */
    {
        /* lendo o primeiro byte do arquivo para saber quantos bytes o caracter ocupa */
        fread(&first_byte, sizeof(unsigned char), 1, arquivo_entrada);

        final_value = first_byte;

        /* loop para descobrir quantos bits 1 no início o primeiro byte apresenta */
        while ((first_byte & 0b10000000) != 0)
        {
            first_byte = first_byte << 1;
            n_bytes++;
        }

        /* ifs para tratar cada caso de número de bytes e gravar no arquivo novo utf32 */
        if (n_bytes == 0)
        {
            printf("1 byte\n");

            unsigned char byte1;
            unsigned int mask_to_concat = 0x0, concat_bytes = 0x0;

            byte1 = final_value & 0b01111111;
            printf("n_bytes=0 - byte1: %x\n\n", byte1);

            concat_bytes = byte1;
            concat_bytes |= mask_to_concat;
        }

        else if (n_bytes == 2)
        {
            printf("2 bytes\n");

            unsigned char byte1, byte2;
            unsigned int mask_to_concat = 0x0, concat_bytes = 0x0, total_bits = 0;
            // unsigned char endianness_byte1; /* primeiro byte a ser gravado (ficar na extrema direita) */
            // unsigned char endianness_byte2; /* segundo byte a ser gravado (ficar na extrema esquerda) */

            printf("hex: %x\n", final_value);

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bytes de continuacao */

            printf("n_bytes=2 - byte1: %x\n", byte1);
            printf("n_bytes=2 - byte2: %x\n\n", byte2);

            concat_bytes = byte1;
            concat_bytes <<= count_bits(byte2);
            total_bits += count_bits(byte2);
            concat_bytes |= byte2;
            concat_bytes |= mask_to_concat;

            printf("concat_bytes antes de inverter os bytes: %x\n", concat_bytes);

            /* invertendo os bytes para gravar em little endian // ta dando erradozzzzzzzzzzzzzzz*/

            // endianness_byte1 = concat_bytes & 0b1111111100000000; /* talvez tenha q dar bitshift pra direita de 1 byte para fazer o or */
            // endianness_byte1 = endianness_byte1 >> 8;
            // endianness_byte2 = concat_bytes & 0b0000000011111111;

            // concat_bytes = 0x0;

            // concat_bytes |= endianness_byte2;
            // concat_bytes <<= 8;
            // concat_bytes |= endianness_byte1;

            // printf("concat_bytes depois de inverter os bytes: %x\n", concat_bytes);
        }

        else if (n_bytes == 3)
        {
            printf("3 bytes\n");

            unsigned char byte1, byte2, byte3;
            unsigned int concat_bytes = 0x0, total_bits = 0, mask_to_concat = 0x0;
            unsigned char endianness_byte1, endianness_byte2;

            // printf("hex: %x\n", final_value);
            // printf("bin: %b\n", final_value);

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bytes de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bytes de continuacao */

            printf("n_bytes=3 - byte1: %x\n", byte1);
            printf("n_bytes=3 - byte2: %x\n", byte2);
            printf("n_bytes=3 - byte3: %x\n\n", byte3);

            concat_bytes = byte1;
            concat_bytes <<= count_bits(byte2);
            total_bits += count_bits(byte2);
            concat_bytes |= byte2;
            concat_bytes <<= count_bits(byte3);
            total_bits += count_bits(byte3);
            concat_bytes |= byte3;
            concat_bytes |= mask_to_concat;
            printf("concat_bytes bin antes de inverter: %b\n", concat_bytes);
            // printf("concat_bytes bin antes de inverter: %b\n", concat_bytes);

            /* invertendo os bytes para gravar em little endian // ta dando erradozzzzzzzzzzzzzzz*/

            endianness_byte1 = (concat_bytes & 0b1111111100000000) >> 8; /* talvez tenha q dar bitshift pra direita de 1 byte para fazer o or */
            printf("endianness_byte1: %x\n", endianness_byte1);
            endianness_byte2 = concat_bytes & 0b0000000011111111;
            printf("endianness_byte2: %x\n", endianness_byte2);

            concat_bytes = 0x0;

            concat_bytes |= endianness_byte2;
            concat_bytes <<= 8;
            concat_bytes |= endianness_byte1;

            printf("concat_bytes depois de inverter os bytes em hex: %x\n", concat_bytes);
            // printf("concat_bytes depois de inverter os bytes em bin: %b\n", concat_bytes);
        }

        else if (n_bytes == 4)
        {
            printf("4 bytes\n");

            unsigned char byte1, byte2, byte3, byte4;
            unsigned int concat_bytes = 0x0, total_bits = 0, mask_to_concat = 0x0;

            printf("hex: %x\n", final_value);

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte4, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00000111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bytes de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bytes de continuacao */
            byte4 = byte4 & 0b00111111;       /* & operation para remover bytes de continuacao */

            printf("n_bytes=4 - byte1: %x\n", byte1);
            printf("n_bytes=4 - byte2: %x\n", byte2);
            printf("n_bytes=4 - byte3: %x\n", byte3);
            printf("n_bytes=4 - byte4: %x\n\n", byte4);

            concat_bytes = byte1;
            concat_bytes <<= count_bits(byte2);
            total_bits += count_bits(byte2);
            concat_bytes |= byte2;
            concat_bytes <<= count_bits(byte3);
            total_bits += count_bits(byte3);
            concat_bytes |= byte3;
            concat_bytes <<= count_bits(byte4);
            total_bits += count_bits(byte4);
            concat_bytes |= byte4;
            concat_bytes |= mask_to_concat;

            printf("concat_bytes: %x\n", concat_bytes);
        }
    }

    return 0;
}

int count_bits(unsigned char byte)
{
    unsigned int count = 0;
    while (byte)
    {
        count++;
        byte >>= 1;
    }

    return count;
}

// int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
// {
//     unsigned int utf32_BOM, utf32_conteudo, final_value, endianness, num_bytes = 0;

//     if (!arquivo_entrada)
//     {
//         fprintf(stderr, "erro ao abrir arquivo para leitura\n");
//         return -1;
//     }

//     fread(&utf32_BOM, sizeof(unsigned int), 1, arquivo_entrada); /* lendo BOM do arquivo */

//     if (utf32_BOM == 0x0000FEFF) /* verificando se BOM é little endian */
//     {
//         endianness = 1;
//     }

//     else if (utf32_BOM == 0xFEFF0000) /* verificando se BOM é big endian */
//     {
//         printf("utf32_BOM: %x\n", utf32_BOM);
//         printf("big endian\n");
//         endianness = 0;
//     }

//     else /* caso de BOM inválido */
//     {
//         fprintf(stderr, "BOM invalido\n");
//         return -1;
//     }

//     while (!feof(arquivo_entrada)) /* alterar esta condicao do while pq esta repetindo o ultimo byte */
//     {

//         if (endianness == 1) /* caso little endian */
//         {
//             num_bytes = 0;

//             fread(&utf32_conteudo, sizeof(unsigned int), 1, arquivo_entrada); /* lendo valores do arquivo */
//             final_value = utf32_conteudo;

//             /* verificando quantidade de bytes usados para cada o caracter */
//             while ((utf32_conteudo & 0x000000FF) != 0)
//             {
//                 utf32_conteudo = utf32_conteudo >> 8;
//                 num_bytes++;
//             }

//             /* tratando gravação de cada caracter dependendo da quantidade de bytes que ocupa */
//             if (num_bytes == 1)
//             {
//                 unsigned char byte_to_write;
//                 byte_to_write = final_value & 0x000000FF;
//                 printf("byte_to_write 1: %x\n", byte_to_write);
//                 fwrite(&byte_to_write, sizeof(unsigned char), 1, arquivo_saida);
//             }

//             else if (num_bytes == 2)
//             {
//                 unsigned char byte1_to_write, byte2_to_write;

//                 byte1_to_write = final_value & 0x000000FF;
//                 byte2_to_write = (final_value & 0x0000FF00) >> 8;
//                 printf("byte_to_write 1: %x\n", byte1_to_write);
//                 printf("byte_to_write 2: %x\n", byte2_to_write);
//                 fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
//             }

//             else if (num_bytes == 3)
//             {

//                 unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
//                 byte1_to_write = final_value & 0x000000FF;
//                 byte2_to_write = (final_value & 0x0000FF00) >> 8;
//                 byte3_to_write = (final_value & 0x00FF0000) >> 16;

//                 printf("byte_to_write 1: %x\n", byte1_to_write);
//                 printf("byte_to_write 2: %x\n", byte2_to_write);
//                 printf("byte_to_write 3: %x\n", byte3_to_write);

//                 fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
//             }

//             else if (num_bytes == 4)
//             {

//                 unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
//                 byte1_to_write = final_value & 0x000000FF;
//                 byte2_to_write = (final_value & 0x0000FF00) >> 8;
//                 byte3_to_write = (final_value & 0x00FF0000) >> 16;
//                 byte4_to_write = (final_value & 0xFF000000) >> 24;

//                 printf("byte_to_write 1: %x\n", byte1_to_write);
//                 printf("byte_to_write 2: %x\n", byte2_to_write);
//                 printf("byte_to_write 3: %x\n", byte3_to_write);
//                 printf("byte_to_write 4: %x\n", byte4_to_write);

//                 fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
//                 fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
//             }
//         }

//         else /* caso big endian */
//         {
//             /* se for big endian tem que inverter e gravar em little endian? */
//             unsigned char byte_final, byte_inicial;

//             byte_final = final_value & 0x00FF;
//             byte_inicial = final_value & 0xFF00;
//             unsigned char complete_value = byte_inicial | byte_final;

//             /* LEMBRAR DE TIRAR ESSES PRINTS */
//             printf("byte_final: %x\n", byte_final);
//             printf("byte_inicial: %x\n", byte_inicial);
//             printf("complete_value: %x\n\n", complete_value);

//             fwrite(&byte_inicial, sizeof(unsigned char), 1, arquivo_saida);
//             fwrite(&byte_final, sizeof(unsigned char), 1, arquivo_saida);
//         }
//     }

//     return 0;
// }
