#include <stdio.h>
#include <stdlib.h>
#include "converteutf.h"

int main(void)
{

    FILE *entry_fileUtf8, *output_fileUtf8;
    // FILE *entry_fileUtf32, *output_fileUtf32;

    entry_fileUtf8 = fopen("utf8_testFileIn", "rb");
    output_fileUtf8 = fopen("utf8_testFileOut", "wb");
    converteUtf8Para32(entry_fileUtf8, output_fileUtf8);
    fclose(entry_fileUtf8);
    fclose(output_fileUtf8);

    // entry_fileUtf32 = fopen("utf32_testFileIn", "rb");
    // output_fileUtf32 = fopen("utf32_testFileOut", "wb");
    // converteUtf32Para8(entry_fileUtf32, output_fileUtf32);
    // fclose(entry_fileUtf32);
    // fclose(output_fileUtf32);

    return 0;
}