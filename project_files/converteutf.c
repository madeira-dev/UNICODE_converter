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
        printf("%b\n", first_byte);

        /* loop para descobrir quantos bits = 1, no início, o primeiro byte apresenta */
        while ((first_byte & 0b10000000) != 0)
        {
            first_byte <<= 1;
            n_bytes++;
        }

        /* ifs para tratar cada caso de número de bytes e gravar no arquivo novo utf32 */
        if (n_bytes == 0)
        {
            printf("1 byte\n");

            unsigned char byte1, padding_byte = 0; // corrigir o nome dessas variaveis
            // unsigned int mask_to_concat = 0x0, concat_bytes = 0x0;

            // printf("antes: %x\n", first_byte);

            byte1 = final_value & 0b01111111;

            // printf("depois: %x\n", first_byte);

            // printf("n_bytes=0 - byte1: %x\n\n", byte1);

            // concat_bytes = (byte1 & 0x000000FF);

            // printf("AQUI: %x\n", byte1);
            // fwrite(&final_value, sizeof(unsigned int), 1, arquivo_saida);

            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
        }

        else if (n_bytes == 2)
        {
            printf("2 bytes\n"); // modificar esse caso aqui pra gravar em little endian

            unsigned char byte1, byte2, padding_byte = 0;
            // unsigned int mask_to_concat = 0x0, concat_bytes = 0x0, total_bits = 0;

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */

            // printf("n_bytes=2 - byte1: %x\n", byte1);
            // printf("n_bytes=2 - byte2: %x\n\n", byte2);

            /* ideia anterior que concatenava os bytes porem na hora de gravar ia em big endian */
            // concat_bytes = byte1;
            // concat_bytes <<= count_bits(byte2);
            // total_bits += count_bits(byte2);
            // concat_bytes |= byte2;
            // concat_bytes |= mask_to_concat;

            // printf("AQUI: %x\n", concat_bytes);

            // fwrite(&concat_bytes, sizeof(unsigned int), 1, arquivo_saida);
            fwrite(&byte2, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);
        }

        else if (n_bytes == 3)
        {
            printf("3 bytes\n"); // modificar esse caso aqui pra gravar em little endian

            unsigned char byte1, byte2, byte3, padding_byte = 0;
            // unsigned int concat_bytes = 0x0, total_bits = 0, mask_to_concat = 0x0;
            // unsigned char endianness_byte1, endianness_byte2;

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);

            byte1 = final_value & 0b00011111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bits de continuacao */

            // printf("n_bytes=3 - byte1: %x\n", byte1);
            // printf("n_bytes=3 - byte2: %x\n", byte2);
            // printf("n_bytes=3 - byte3: %x\n\n", byte3);

            /* a principio isso aqui é inutil */
            // concat_bytes = byte1;
            // concat_bytes <<= count_bits(byte2);
            // total_bits += count_bits(byte2);
            // concat_bytes |= byte2;
            // concat_bytes <<= count_bits(byte3);
            // total_bits += count_bits(byte3);
            // concat_bytes |= byte3;
            // concat_bytes |= mask_to_concat;

            fwrite(&byte3, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte2, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&byte1, sizeof(unsigned char), 1, arquivo_saida);
            fwrite(&padding_byte, sizeof(unsigned char), 1, arquivo_saida);

            /* acho que daqui pra baixo ta errado pq ta gravando errado */
            /* invertendo os bytes para gravar em little endian */
            // endianness_byte1 = (concat_bytes & 0b1111111100000000) >> 8;
            // endianness_byte2 = concat_bytes & 0b0000000011111111;

            // concat_bytes = 0x0;

            // concat_bytes |= endianness_byte2;
            // concat_bytes <<= 8;
            // concat_bytes |= endianness_byte1;

            // fwrite(&concat_bytes, sizeof(unsigned int), 1, arquivo_saida);
        }

        else if (n_bytes == 4)
        {
            printf("4 bytes\n"); // modificar esse caso aqui pra gravar em little endian

            unsigned char byte1, byte2, byte3, byte4;

            // printf("hex: %x\n", final_value);

            fread(&byte2, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte3, sizeof(unsigned char), 1, arquivo_entrada);
            fread(&byte4, sizeof(unsigned char), 1, arquivo_entrada);

            // printf("n_bytes=4 - final_value antes: %x\n", final_value);
            // printf("n_bytes=4 - byte2 antes: %x\n", byte2);
            // printf("n_bytes=4 - byte3 antes: %x\n", byte3);
            // printf("n_bytes=4 - byte4 antes: %x\n\n", byte4);

            byte1 = final_value & 0b00000111; /* definindo o primeiro byte como os bits do byte lido exceto os iniciais representando o numero de bytes total */
            byte2 = byte2 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte3 = byte3 & 0b00111111;       /* & operation para remover bits de continuacao */
            byte4 = byte4 & 0b00111111;       /* & operation para remover bits de continuacao */

            // printf("n_bytes=4 - byte1: %x\n", byte1);
            // printf("n_bytes=4 - byte2: %x\n", byte2);
            // printf("n_bytes=4 - byte3: %x\n", byte3);
            // printf("n_bytes=4 - byte4: %x\n\n", byte4);

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
        count++;
        byte >>= 1;
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
    printf("BOM: %x\n", utf32_BOM);

    if (utf32_BOM == 0x0000FEFF) /* verificando se BOM é little endian */
    {
        printf("LITTLE ENDIAN\n"); /* LEMBRAR DE DELETAR ESSE PRINT */
        endianness = 1;
    }

    else if (utf32_BOM == 0xFFFE0000) /* verificando se BOM é big endian */
    {
        // printf("utf32_BOM: %x\n", utf32_BOM);
        printf("big endian\n");
        // endianness = 0;
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
            num_bytes = 0;
            final_value = utf32_conteudo;

            printf("ENTROU NO ENDIANNESS = 1\n");
            printf("%x\n", utf32_conteudo);

            byte1 = final_value & 0x000000FF;
            byte2 = (final_value & 0x0000FF00) >> 8;
            byte3 = (final_value & 0x00FF0000) >> 16;
            byte4 = (final_value & 0xFF000000) >> 24;

            printf("byte1: %x\n", byte1);
            printf("byte2: %x\n", byte2);
            printf("byte3: %x\n", byte3);
            printf("byte4: %x\n", byte4);

            /* verificando quantidade de bytes realmente usados (antes da extensão para 32 bits) por cada caracter */
            while ((utf32_conteudo & 0x000000FF) != 0)
            {
                utf32_conteudo >>= 8;
                num_bytes++;
            }

            /* tratando gravação de cada caracter dependendo da quantidade de bytes que ocupa */
            if (num_bytes == 1)
            {
                printf("bytes=1\n");
                unsigned char byte1_to_write, byte2_to_write;
                unsigned char numBytes_bits = 0b00000000; // bits representando numero de bytes ocupados pelo caracter

                byte1_to_write = final_value & 0x000000FF;

                /* print de debug */
                // printf("byte_to_write 1: %x\n", byte1_to_write);

                /* concatenando os bytes com os respectivos bits de representacao */
                byte1_to_write = (byte1_to_write | numBytes_bits);

                /* escrevendo os bytes para o arquivo de saída */
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 2)
            {
                printf("bytes=2\n");
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
                unsigned char numBytes_bits = 0b11000000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = final_value & 0x000000FF;
                byte2_to_write = (final_value & 0x0000FF00) >> 8;

                /* concatenando os bytes com os respectivos bits de representacao */
                byte1_to_write = (byte1_to_write | cont_bits);
                byte2_to_write = (byte2_to_write | numBytes_bits);

                /* prints de debug */
                // printf("byte_to_write 1: %x\n", byte1_to_write);
                // printf("byte_to_write 2: %x\n", byte2_to_write);
                // printf("byte_to_write 3: %x\n", byte3_to_write);

                /* escrevendo os bytes para o arquivo de saída */
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 3)
            {
                printf("bytes=3\n");
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write = 0x0;
                unsigned char numBytes_bits = 0b11100000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = final_value & 0x000000FF;
                byte2_to_write = (final_value & 0x0000FF00) >> 8;
                byte3_to_write = (final_value & 0x00FF0000) >> 16;

                /* concatenando os bytes com os respectivos bits de representacao */
                byte1_to_write = (byte1_to_write | cont_bits);
                byte2_to_write = (byte2_to_write | cont_bits);
                byte3_to_write = (byte3_to_write | numBytes_bits);
                // byte4_to_write = (byte4_to_write | numBytes_bits);

                /* escrevendo os bytes para o arquivo de saída */
                // fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 4)
            {
                printf("bytes=4\n");
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11110000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                // printf("final_value utf32: %x\n", final_value);

                byte1_to_write = final_value & 0x000000FF;
                byte2_to_write = (final_value & 0x0000FF00) >> 8;
                byte3_to_write = (final_value & 0x00FF0000) >> 16;
                byte4_to_write = (final_value & 0xFF000000) >> 24;

                /* concatenando os bytes com os respectivos bits de representacao */
                byte1_to_write = (byte1_to_write | cont_bits);
                byte2_to_write = (byte2_to_write | cont_bits);
                byte3_to_write = (byte3_to_write | cont_bits);
                byte4_to_write = (byte4_to_write | numBytes_bits);

                /* prints de debug */
                // printf("byte_to_write 1: %x\n", byte1_to_write);
                // printf("byte_to_write 2: %x\n", byte2_to_write);
                // printf("byte_to_write 3: %x\n", byte3_to_write);
                // printf("byte_to_write 4: %x\n", byte4_to_write);

                /* escrevendo os bytes para o arquivo de saída */
                fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }
        }

        else /* caso big endian */
        {
            /* print de debug */
            printf("BIG ENDIAN????????????????????????\n");

            fread(&utf32_conteudo, sizeof(unsigned int), 1, arquivo_entrada); /* lendo valores do arquivo */
            final_value = utf32_conteudo;

            /* print de debug */
            printf("final_value: %x\n", final_value);

            while ((utf32_conteudo & 0xFF000000) != 0)
            {
                utf32_conteudo = utf32_conteudo << 8;
                num_bytes++;
            }

            /* tratando gravação de cada caracter dependendo da quantidade de bytes que ocupa */
            if (num_bytes == 1)
            {
                printf("bytes=1\n");
                unsigned char byte1_to_write, byte2_to_write;
                unsigned char numBytes_bits = 0b00000000; // bits representando numero de bytes ocupados pelo caracter

                byte1_to_write = final_value & 0xFF000000;

                /* print de debug */
                printf("byte_to_write 1: %x\n", byte1_to_write);

                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 2)
            {
                /* print de debug */
                printf("bytes=2\n");

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write;
                unsigned char numBytes_bits = 0b11000000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xFF000000) >> 8;
                byte2_to_write = (final_value & 0x00FF0000);

                /* print de debug */
                printf("byte_to_write 1: %x\n", byte1_to_write);
                printf("byte_to_write 2: %x\n", byte2_to_write);

                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 3)
            {
                /* print de debug */
                printf("bytes=3\n");

                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11100000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xFF000000) >> 24;
                byte2_to_write = (final_value & 0x00FF0000) >> 16;
                byte3_to_write = (final_value & 0x0000FF00) >> 8;

                /* prints de debug */
                printf("byte_to_write 1: %x\n", byte1_to_write);
                printf("bit continuacao: %b\n", cont_bits);
                printf("concat com byte1: %x\n", (byte1_to_write | cont_bits));

                printf("byte_to_write 2: %x\n", byte2_to_write);
                printf("bit continuacao: %b\n", cont_bits);
                printf("concat com byte2: %x\n", (byte2_to_write | cont_bits));

                printf("byte_to_write 3: %x\n", byte3_to_write);
                printf("bit quant bytes: %b\n", numBytes_bits);
                printf("concat com byte3: %x\n", (byte3_to_write | numBytes_bits));

                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }

            else if (num_bytes == 4)
            {
                printf("bytes=4\n");
                unsigned char byte1_to_write, byte2_to_write, byte3_to_write, byte4_to_write;
                unsigned char numBytes_bits = 0b11110000; // bits representando numero de bytes ocupados pelo caracter
                unsigned char cont_bits = 0b10000000;

                byte1_to_write = (final_value & 0xff000000) >> 24;
                byte2_to_write = (final_value & 0x00ff0000) >> 16;
                byte3_to_write = (final_value & 0x0000ff00) >> 8;
                byte4_to_write = (final_value & 0x000000ff);

                printf("byte_to_write 1: %x\n", byte1_to_write);
                printf("bit continuacao: %b\n", cont_bits);

                printf("byte_to_write 2: %x\n", byte2_to_write);
                printf("bit continuacao: %b\n", cont_bits);

                printf("byte_to_write 3: %x\n", byte3_to_write);
                printf("bit continuacao: %b\n", cont_bits);

                printf("byte_to_write 4: %x\n", byte4_to_write);
                printf("bit quant bytes: %b\n", numBytes_bits);

                fwrite(&byte4_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte3_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte2_to_write, sizeof(unsigned char), 1, arquivo_saida);
                fwrite(&byte1_to_write, sizeof(unsigned char), 1, arquivo_saida);
            }
        }
    }

    return 0;
}
