/* Gabriel de Oliveira Rosa Mariano Madeira 2111471 3WB */
/* Juliana Pinheiro dos Santos 2110516 3WB */

#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int count_bits(unsigned char byte);

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned char first_byte, final_value;
    int n_bytes = 0;

    unsigned int BOM_to_write = 0x0000FEFF; /* BOM pra indicar que o arquivo foi gravado em little endian */
    // unsigned int tmp_bigEndian_BOM = 0xFFFE0000;
    fwrite(&BOM_to_write, sizeof(unsigned int), 1, arquivo_saida);

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    while (fread(&first_byte, sizeof(unsigned char), 1, arquivo_entrada) == 1)
    {
        n_bytes = 0;
        final_value = first_byte;

        /* loop para descobrir quantos bits = 1, no início, o primeiro byte apresenta */
        while ((first_byte & 0b10000000) != 0)
        {
            first_byte <<= 1;
            n_bytes++;
        }

        /* ifs para tratar cada caso de número de bytes e gravar no arquivo novo utf32 */
        if (n_bytes == 0)
        {

            unsigned char byte1, padding_byte = 0;

            byte1 = final_value & 0b01111111;

            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
        }

        else if (n_bytes == 2)
        {

            unsigned char byte1, byte2, padding_byte = 0;

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */

            fwrite(&byte2, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
        }

        else if (n_bytes == 3)
        {
            unsigned char byte1, byte2, byte3, padding_byte = 0;

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bits de continuacao */

            fwrite(&byte3, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte2, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
        }

        else if (n_bytes == 4)
        {
            unsigned char byte1, byte2, byte3, byte4;

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte4, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00000111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte4 = byte4 & 0b00111111;       /* & operation para remover bits de continuacao */

            fwrite(&byte4, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte3, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte2, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
        }
    }
    return 0;
}

// função auxiliar
int count_bits(unsigned char byte)
{
    unsigned int count = 0;

    while (byte)
    {
        byte >>= 1;
        count++;
    }
    return count;
}

int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned int utf32_conteudo, final_value, endianness, num_bytes = 0;
    unsigned int utf32_BOM;

    if (!arquivo_entrada)
    {
        fprintf(stderr, "erro ao abrir arquivo para leitura\n");
        return -1;
    }

    fread(&utf32_BOM, sizeof(unsigned int), 1, arquivo_entrada); /* lendo BOM do arquivo */

    if (utf32_BOM == 0x0000FEFF) /* verificando se BOM é little endian */
    {
        endianness = 1;
    }

    else if (utf32_BOM == 0xFFFE0000) /* verificando se BOM é big endian */
    {
        endianness = 0;
    }

    else /* caso de BOM inválido */
    {
        fprintf(stderr, "BOM invalido\n");
        return -1;
    }

    while (fread(&utf32_conteudo, sizeof(unsigned int), 1, arquivo_entrada) == 1)
    {
        if (endianness == 1) /* caso little endian */
        {
            unsigned char byte1, byte2, byte3, byte4;
            int count_bits_byte1, count_bits_byte2, count_bits_byte3, count_bits_byte4;

            num_bytes = 0;
            final_value = utf32_conteudo;
            printf("conteudo antes: %x\n", utf32_conteudo);

            // byte1 = (final_value & 0x000000FF);
            // byte2 = (final_value & 0x0000FF00) >> 8;
            // byte3 = (final_value & 0x00FF0000) >> 16;
            // byte4 = (final_value & 0xFF000000) >> 24;

            // count_bits_byte1 = count_bits(byte1);
            // count_bits_byte2 = count_bits(byte2);
            // count_bits_byte3 = count_bits(byte3);
            // count_bits_byte4 = count_bits(byte4);

            // if (count_bits_byte1)
            // {

            // }

            /* verificando quantidade de bytes realmente usados (antes da extensão para 32 bits) por cada caracter */
            while (utf32_conteudo != 0)
            {
                utf32_conteudo >>= 8;
                printf("conteudo: %x\n", utf32_conteudo);
                num_bytes++;
            }

            /* tratando gravação de cada caracter dependendo da quantidade de bytes que ocupa */
            if (num_bytes == 1)
            {
                printf("1byte\n");
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
                unsigned char numBytes_bits = 0b00000000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;
                int count;

                byte1_to_write = final_value & 0x000000FF;

                count = count_bits(byte1_to_write);

                /* concatenando os bytes com os respectivos bits de representacao */
                byte1_to_write = (byte1_to_write | numBytes_bits);

                /* escrevendo os bytes para o arquivo de saída */
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 2)
            {
                printf("2byte\n");

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
                unsigned char numBytes_bits = 0b11000000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;
                int count;

                byte1_to_write = final_value & 0x000000FF;
                byte2_to_write = (final_value & 0x0000FF00) >> 8;

                count = count_bits(byte2_to_write);

                if (count > 5)
                {
                    numBytes_bits = 0b11100000;
                    byte3_to_write = (final_value & 0x00FF0000) >> 16;

                    byte1_to_write = (byte1_to_write | cont_bits);
                    byte2_to_write = (byte2_to_write | cont_bits);
                    byte3_to_write = (byte3_to_write | numBytes_bits);

                    fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
                }

                else
                {
                    byte1_to_write = (byte1_to_write | cont_bits);
                    byte2_to_write = (byte2_to_write | numBytes_bits);

                    /* escrevendo os bytes para o arquivo de saída */
                    fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
                }
            }

            else if (num_bytes == 3)
            {
                printf("3byte\n");

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11100000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;
                int count;

                byte1_to_write = final_value & 0x000000FF;
                byte2_to_write = (final_value & 0x0000FF00) >> 8;
                byte3_to_write = (final_value & 0x00FF0000) >> 16;

                count = count_bits(byte3_to_write);

                if (count > 4)
                {
                    numBytes_bits = 0b11110000;
                    byte4_to_write = (final_value & 0xFF000000) >> 24;

                    byte1_to_write = (byte1_to_write | cont_bits);
                    byte2_to_write = (byte2_to_write | cont_bits);
                    byte3_to_write = (byte3_to_write | cont_bits);
                    byte4_to_write = (byte4_to_write | numBytes_bits);

                    fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
                }

                else
                {
                    byte1_to_write = (byte1_to_write | cont_bits);
                    byte2_to_write = (byte2_to_write | cont_bits);
                    byte3_to_write = (byte3_to_write | numBytes_bits);

                    /* escrevendo os bytes para o arquivo de saída */
                    fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                    fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
                }
            }
        }

        else /* caso big endian */
        {

            fread(&utf32_conteudo, sizeof(unsigned int), 1, arquivo_entrada); /* lendo valores do arquivo */
            final_value = utf32_conteudo;

            while (utf32_conteudo != 0)
            {
                utf32_conteudo <<= 8;
                num_bytes++;
            }

            /* tratando gravação de cada caracter dependendo da quantidade de bytes que ocupa */
            if (num_bytes == 1)
            {
                unsigned char byte1_to_write, byte2_to_write;
                unsigned char numBytes_bits = 0b00000000; // bits representando numero de bytes ocupados pelo caracter

                byte1_to_write = final_value & 0xFF000000;

                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 2)
            {

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
                unsigned char numBytes_bits = 0b11000000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xFF000000) >> 8;
                byte2_to_write = (final_value & 0x00FF0000);

                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 3)
            {

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11100000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xFF000000) >> 24;
                byte2_to_write = (final_value & 0x00FF0000) >> 16;
                byte3_to_write = (final_value & 0x0000FF00) >> 8;

                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 4)
            {
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11110000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xff000000) >> 24;
                byte2_to_write = (final_value & 0x00ff0000) >> 16;
                byte3_to_write = (final_value & 0x0000ff00) >> 8;
                byte4_to_write = (final_value & 0x000000ff);

                fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }
        }
    }

    return 0;
}
