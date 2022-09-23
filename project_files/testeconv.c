#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int main(void)
{

    FILE *entry_fileUtf8, *output_fileUtf8;
    FILE *entry_fileUtf32, *output_fileUtf32;

    printf("lendo de arquivo utf8 e escrevendo para utf32\n");
    entry_fileUtf8 = fopen("utf8_testFileIn", "rb");
    output_fileUtf8 = fopen("utf8_testFileOut", "wb");
    converteUtf8Para32(entry_fileUtf8, output_fileUtf8);
    fclose(entry_fileUtf8);
    fclose(output_fileUtf8);
    printf("fim da leitura do arquivo utf8\n\n\n");

    printf("lendo de arquivo utf32 e escrevendo para utf8\n");
    entry_fileUtf32 = fopen("utf8_testFileOut", "rb");
    output_fileUtf32 = fopen("utf32_testFileOut", "wb");
    converteUtf32Para8(entry_fileUtf32, output_fileUtf32);
    fclose(entry_fileUtf32);
    fclose(output_fileUtf32);
    printf("fim da leitura do arquivo utf32\n");

    return 0;
}
